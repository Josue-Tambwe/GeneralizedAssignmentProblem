/*------------------------------------------------------------------------------
 * GAP-Solver — An educational solver for the Generalized Assignment Problem
 *              using MILP and heuristic methods.
 *------------------------------------------------------------------------------
 * Copyright (c) 2025 Josué Tambwe
 *               Nantes Université, France
 *------------------------------------------------------------------------------
 * This software is released under the MIT License.
 * See the LICENSE file for more details.
 *------------------------------------------------------------------------------
 */


/** 
 * @file AntConstruction.cpp
 * @author Josué Tambwe
 * @date 1 May 2026
 */

 #include "metaheuristics/antColonyOptimizer/AntConstruction.hpp"


 namespace gap::ACO{


    //----------------------------------- INITIALIZATION -----------------------------------

    void colonyInitialization(std::vector<std::vector<int>> &residual_capacities,
                              std::vector<std::unordered_set<int> > &ant_tasks,
                              gap::GapInstance &instance){

        // initialization of the set of unassigned tasks
        std::unordered_set<int> tasks;
        for(size_t task = 0; task < instance.getNbTask(); task++){tasks.insert(task);}
        
        // initialization of ants and their residual capacities
        for(size_t ant = 0; ant < residual_capacities.size(); ant++){

            residual_capacities[ant] = instance.getCapacity();
            ant_tasks[ant] = tasks;
        }

    }




    gap::GapSolution generateReferenceAnt(gap::Params &params, gap::GapInstance &instance){

        // greedy construction
        gap::GapSolution greedy_solution = gap::greedy::constructionRiskyTasks(instance);
        // local search 
        gap::greedy::localSearch(params, greedy_solution, instance);

        return greedy_solution;

    }




    float computeInverseReferenceValue(gap::GapSolution &solution,
                                       gap::GapInstance &instance){

        // the reference value is : 1 / obj
        std::int64_t objective_value = solution.objectiveValue(instance);

        if(objective_value == 0){return 0.001f;}

        return (1.f / objective_value);

    }


    //----------------------------------- END INITIALIZATION -----------------------------------




    //---------------------------------- ASSIGNMENT OF THE FIRST TASK -----------------------------------


    bool assignFirstTaskRandomly(std::unordered_set<int> &tasks,
                                 std::vector<int> &residual_capacity,
                                 gap::Params &params,
                                 gap::GapSolution &ant,
                                 gap::GapInstance &instance){

        // initialization of the thread random number generator
        auto& rng = getThreadLocalRng();
        
        // initialization of the uniform (discrete) distribution on tasks
        int nb_task = static_cast<int>(instance.getNbTask());
        std::uniform_int_distribution<int> dist_task(0, (nb_task - 1));

        // picking the first task randomly
        int first_task = dist_task(rng); 

        int nb_agent = static_cast<int>(instance.getNbAgent());

        const std::vector<std::vector<int>>& weight_matrix = instance.getWeight();

        // finding the max and min weights
        int max_weight = weight_matrix[0][first_task];
        int min_weight = weight_matrix[0][first_task];

        for(int agent = 1; agent < nb_agent; agent++){

            if(weight_matrix[agent][first_task] > max_weight){max_weight = weight_matrix[agent][first_task];}
            if(weight_matrix[agent][first_task] < min_weight){min_weight = weight_matrix[agent][first_task];}
        }

        // computation of the threshold  : min + gamma (max - min)
        int threshold = static_cast<int>(
                            std::ceil(min_weight + params.gamma * (max_weight - min_weight))
                        );

        // counter of agents that qualified to be assigned the first task
        int counter = 0;
        

        for(int agent = 0; agent < nb_agent; agent++){

            if(weight_matrix[agent][first_task] <= threshold && 
               residual_capacity[agent] >= weight_matrix[agent][first_task]){
                
                counter += 1;
            }
        }

        // when the problem is infeasible
        if(counter == 0){return false;}

        // picking the rank of the agent in {1, ..., counter}
        std::uniform_int_distribution<int> dist_agent(1, counter);
        int random_agent_rank = dist_agent(rng);
        
        counter = 0;

        for(int agent = 0; agent < nb_agent; agent++){

            // looking for the random agent selected priviously by its rank
            if(weight_matrix[agent][first_task] <= threshold && 
               residual_capacity[agent] >= weight_matrix[agent][first_task]){
             
                counter += 1;
            }

            if(counter == random_agent_rank){

                // assignment
                std::vector<int>& ant_solution =  ant.getSolutionVector();
                ant_solution[first_task] = agent;

                // updating of the residual capacity
                residual_capacity[agent] -= weight_matrix[agent][first_task];

                // removing the assigned task from the unassigned tasks set
                tasks.erase(first_task);

                return true;
            }
        }

        return false;

    }





    void multiFirstTaskAssignment(int start,
                                  int end,
                                  std::vector<std::unordered_set<int>> &ants_tasks,
                                  std::vector<std::vector<int>> &residual_capacities,
                                  gap::Params &params,
                                  std::vector<bool> &ants_construction_status,
                                  std::vector<gap::GapSolution> &colony,
                                  gap::GapInstance &instance){


        for(int ant = start; ant <= end; ant++){

            ants_construction_status[ant] = assignFirstTaskRandomly(ants_tasks[ant],
                                                                     residual_capacities[ant],
                                                                     params,
                                                                     colony[ant],
                                                                     instance);

        }

    }





    void firstTaskAssignment(std::vector<std::unordered_set<int>> &ants_tasks,
                            std::vector<std::vector<int>> &residual_capacities,
                            gap::Params &params,
                            std::vector<bool> &ants_construction_status,
                            std::vector<gap::GapSolution> &colony,
                            gap::GapInstance &instance){


        int work_size = static_cast<int>(colony.size());
        int nb_threads_used = std::min(params.nb_threads, work_size);
        std::vector<std::thread> workers(nb_threads_used);

        for(int id = 0; id < nb_threads_used; id++){

            int start = start_index(id, work_size, nb_threads_used);
            int end = end_index(id, work_size, nb_threads_used);

            workers[id] = std::thread(multiFirstTaskAssignment,
                                      start,
                                      end,
                                      std::ref(ants_tasks),
                                      std::ref(residual_capacities),
                                      std::ref(params),
                                      std::ref(ants_construction_status),
                                      std::ref(colony),
                                      std::ref(instance));
        }

        // waiting for all threads to finish
        for(auto &worker : workers){worker.join();}

    }





    bool checkProblemFeasibility(std::vector<bool> &ants_construction_status){

        for(bool status : ants_construction_status){

            if(!status){return status;}
        }

        return true;
    }



    //----------------------------------- END ASSIGNMENT OF THE FIRST TASK -----------------------------------





    //----------------------------------- ANT CONSTRUCTION & LOCAL SEARCH -----------------------------------


    int findTask(std::unordered_set<int> &tasks,
                int &max_weight,
                gap::GapInstance &instance){


        const std::vector<std::vector<int>>& weight_matrix = instance.getWeight();
        int heaviest_task = -1;

        for(int task : tasks){

            for(size_t agent = 0; agent < instance.getNbAgent(); agent++){

                if(max_weight < weight_matrix[agent][task]){

                    max_weight = weight_matrix[agent][task];
                    heaviest_task = task;
                }

            }

        }

        return heaviest_task;

    }





    int findAgentHeuristic(int task,
                          float inverse_max_weight,
                          gap::Params &params,
                          std::vector<int> &residual_capacity,
                          std::vector<std::vector<float>> &pheromone_matrix,
                          gap::GapInstance &instance){

        
        int best_agent = -1;
        float best_score =-1.0f;
        const std::vector<std::vector<int>>& weight_matrix = instance.getWeight();

        for(int agent = 0; agent < static_cast<int>(instance.getNbAgent()); agent++){

            // checking for the capacity constraint
            if(weight_matrix[agent][task] <= residual_capacity[agent]){

                float eta = computeEta(weight_matrix[agent][task], inverse_max_weight);

                float agent_score = heuristic_score(pheromone_matrix[agent][task],
                                                    eta,
                                                    params);

                // updating the best score and the best agent
                if(best_score < agent_score){best_agent = agent; best_score = agent_score;}

            }

        }
        
        return best_agent;
    }




    bool heuristicAssignment(int task,
                            int max_weight,
                            gap::Params &params,
                            std::vector<int> &residual_capacity,
                            std::vector<std::vector<float>> &pheromone_matrix,
                            gap::GapSolution &ant,
                            gap::GapInstance &instance){


        float inverse_max_weight = 1.0f / (max_weight + epsilon);

        int best_agent = findAgentHeuristic(task,
                                            inverse_max_weight,
                                            params,
                                            residual_capacity,
                                            pheromone_matrix,
                                            instance);

        // signal of a failed construction                                    
        if(best_agent == -1){return false;}

        // case of an available agent
        std::vector<int>& ant_solution =  ant.getSolutionVector();

        // performing the assignment
        ant_solution[task] = best_agent;

        // updating residual capacity
        const std::vector<std::vector<int>>& weight_matrix = instance.getWeight();
        residual_capacity[best_agent] -= weight_matrix[best_agent][task];

        return true;

    }




    int countAvailableAgent(int task,
                            std::vector<int> &residual_capacity,
                            gap::GapInstance &instance){


        const std::vector<std::vector<int>>& weight_matrix = instance.getWeight();
        int counter = 0;

        for(int agent = 0; agent < static_cast<int>(instance.getNbAgent()); agent++){

            if(weight_matrix[agent][task] <= residual_capacity[agent]){counter++;}

        }
        
        return counter;

    }




    float computeCumulativeStochasticScore(int task,
                                           int max_weight,
                                           std::vector<int> &residual_capacity,
                                           std::vector<int> &agent_indexes,
                                           std::vector<float> &agent_scores,
                                           std::vector<std::vector<float>> &pheromone_matrix,
                                           gap::Params &params,
                                           gap::GapInstance &instance){

        
        float cumulative_score = 0.0f;
        float inverse_max_weight = computeInverseMaxWeight(max_weight);

        const std::vector<std::vector<int>>& weight_matrix = instance.getWeight();
        int counter = 0;

        // initialization of agents indexes and their scores
        for(int agent = 0; agent < static_cast<int>(instance.getNbAgent()); agent++){

            if(weight_matrix[agent][task] <= residual_capacity[agent]){

                agent_indexes[counter] = agent;

                float eta = computeEta(weight_matrix[agent][task], 
                                       inverse_max_weight); 

                agent_scores[counter] =  heuristic_score(pheromone_matrix[agent][task],
                                                         eta,
                                                         params);
                                               
                cumulative_score += agent_scores[counter];
        
                counter++;
            }

        }

        return cumulative_score;

    }




    int findAgentStochastic(std::vector<int> &agent_indexes,
                            std::vector<float> &agent_scores,
                            float cumulative_score){
        
        float inverse_cumulative_score = 1.0f / (cumulative_score + epsilon);

        // initialization of the thread random number generator
        auto& rng = getThreadLocalRng();

        std::uniform_real_distribution<float> dist(0.0f, 1.0f);
        float random_number = dist(rng);
        float cumul_score = 0.0f;

        for(int agent = 0; agent < static_cast<int>(agent_indexes.size()); agent++){

            cumul_score += agent_scores[agent] * inverse_cumulative_score;

            if(cumul_score > random_number){return agent_indexes[agent];}

        }

        // the last available agent on the list
        return agent_indexes.back();


    }




    bool stochasticAssignment(int task,
                              int max_weight,
                              gap::Params &params,
                              std::vector<int> &residual_capacity,
                              std::vector<std::vector<float>> &pheromone_matrix,
                              gap::GapSolution &ant,
                              gap::GapInstance &instance){

        int nb_available_agents = countAvailableAgent(task,
                                                      residual_capacity,
                                                      instance);
        
        // no agent has enough capacity left => failed construction
        if(nb_available_agents == 0){return false;}

        std::vector<int> agent_indexes(nb_available_agents);
        std::vector<float> agent_scores(nb_available_agents);

        float cumulative_score = computeCumulativeStochasticScore(task,
                                                                  max_weight,
                                                                  residual_capacity,
                                                                  agent_indexes,
                                                                  agent_scores,
                                                                  pheromone_matrix,
                                                                  params,
                                                                  instance);

        int selected_agent = findAgentStochastic(agent_indexes,
                                                 agent_scores,
                                                 cumulative_score);

        if(selected_agent < 0 || 
           selected_agent >= static_cast<int>(instance.getNbAgent())){return false;}
        
        std::vector<int>& ant_solution =  ant.getSolutionVector();

        // performing the assignment
        ant_solution[task] = selected_agent;

        // updating residual capacity
        const std::vector<std::vector<int>>& weight_matrix = instance.getWeight();
        residual_capacity[selected_agent] -= weight_matrix[selected_agent][task];

        return true;


    }





    bool partialAntConstruction(std::unordered_set<int> &tasks,
                                std::vector<int> &residual_capacity,
                                double probability_threshold,
                                gap::Params &params,
                                std::vector<std::vector<float>> &pheromone_matrix,
                                gap::GapSolution &ant,
                                gap::GapInstance &instance){


        while(!tasks.empty()){

            int max_weight = -1;

            int task = findTask(tasks,
                                max_weight,
                                instance);
            
            // when no suitable tak has been found  
            
            if(task == -1){return false;}

            auto& rng = getThreadLocalRng();
            std::uniform_real_distribution<float> dist(0.0f, 1.0f);
            float random_number = dist(rng);

            // case exploitation (heuristic approch)
            if(random_number <= probability_threshold){

                bool heuristic_assignment_performed = heuristicAssignment(task,
                                                                        max_weight,
                                                                        params,
                                                                        residual_capacity,
                                                                        pheromone_matrix,
                                                                        ant,
                                                                        instance);

                // removing the task from the set of unassigned task
                if(heuristic_assignment_performed){tasks.erase(task);}

                // signal of a failed construction
                else{return false;}

            }

            // case exploration (stochastic approch)
            else{

                bool stochastic_assignment_performed = stochasticAssignment(task,
                                                                            max_weight,
                                                                            params,
                                                                            residual_capacity,
                                                                            pheromone_matrix,
                                                                            ant,
                                                                            instance);

                // removing the task from the set of unassigned task
                if(stochastic_assignment_performed){tasks.erase(task);}

                // signal of a failed construction
                else{return false;}

            }
            
        }

        // when the solution of an ant has been constructed fully
        return true;

    }





    void multiPartialAntConstruction(int start,
                                     int end,
                                     double probability_threshold,
                                     gap::Params &params,
                                     std::vector<std::unordered_set<int>> &ants_tasks,
                                     std::vector<bool> &ants_construction_status,
                                     std::vector<std::vector<int>> &residual_capacities,
                                     std::vector<std::vector<float>> &pheromone_matrix,
                                     std::vector<gap::GapSolution> &colony,
                                     gap::GapInstance &instance){

        for(int ant = start; ant <= end; ant++){

            ants_construction_status[ant] = partialAntConstruction(ants_tasks[ant],
                                                                    residual_capacities[ant],
                                                                    probability_threshold,
                                                                    params,
                                                                    pheromone_matrix,
                                                                    colony[ant],
                                                                    instance);


        }


    }



    

    bool antConstruction(double probability_threshold,
                        gap::Params &params,
                        std::vector<bool> &ants_construction_status,
                        std::vector<std::vector<float>> &pheromone_matrix,
                        std::vector<gap::GapSolution> &colony,
                        gap::GapInstance &instance){


        std::vector<std::vector<int>> residual_capacities(params.nb_ants, 
                                                          std::vector<int>(instance.getNbAgent(), 0));

        std::vector<std::unordered_set<int> > ants_tasks(params.nb_ants);
        colonyInitialization(residual_capacities, ants_tasks, instance);

        firstTaskAssignment(ants_tasks,
                            residual_capacities,
                            params,
                            ants_construction_status,
                            colony,
                            instance);

        // when the first task was not assigned for an ant in the colony => the problem is infeasible
        // because it means that there exists a task which weight exceeds all agents capacities
        if(!checkProblemFeasibility(ants_construction_status)){return false;}

        int work_size = static_cast<int>(colony.size());
        int nb_threads_used = std::min(params.nb_threads, work_size);
        std::vector<std::thread> workers(nb_threads_used);

        for(int id = 0; id < nb_threads_used; id++){

            int start = start_index(id, work_size, nb_threads_used);
            int end = end_index(id, work_size, nb_threads_used);

            workers[id] = std::thread(multiPartialAntConstruction,
                                      start,
                                      end,
                                      probability_threshold,
                                      std::ref(params),
                                      std::ref(ants_tasks),
                                      std::ref(ants_construction_status),
                                      std::ref(residual_capacities),
                                      std::ref(pheromone_matrix),
                                      std::ref(colony),
                                      std::ref(instance));
        }

        // waiting for all threads to finish
        for(auto &worker : workers){worker.join();}
        
        return true;
    }





    void antLocalSearch(gap::GapSolution &ant,
                        gap::GapInstance &instance){


        // balance move neighborhood
        gap::greedy::balanceMove(ant, 
                                 instance);

        // cheap move neighborhood with a single thread
        gap::greedy::cheapMove(1, 
                               ant, 
                               instance);

    }





    void multiAntImprovement(int start,
                            int end,
                            gap::GapSolution &reference_ant,
                            std::vector<bool> &ants_construction_status,
                            std::vector<gap::GapSolution> &colony,
                            gap::GapInstance &instance){

        for(int ant = start; ant <= end; ant++){

            // case of fully constructed ant solution
            if(ants_construction_status[ant]){

                // setting the ant solution status to Feasible
                colony[ant].setStatus(gap::Status::FEASIBLE);

                // performing the greedy Local Search (balance + cheap neighborhoods)
                antLocalSearch(colony[ant], instance);
            }

            // case of failed construction ant
            // the ant within the colony is replaced by the reference ant
            // in order to have only feasible ants in the colony
            else{colony[ant] = reference_ant;};
        }
            
    }




    void antImprovement(gap::GapSolution &reference_ant,
                        gap::Params &params,
                        std::vector<bool> &ants_construction_status,
                        std::vector<gap::GapSolution> &colony,
                        gap::GapInstance &instance){

        int work_size = static_cast<int>(colony.size());
        int nb_threads_used = std::min(params.nb_threads, work_size);
        std::vector<std::thread> workers(nb_threads_used);

        for(int id = 0; id < nb_threads_used; id++){

            int start = start_index(id, work_size, nb_threads_used);
            int end = end_index(id, work_size, nb_threads_used);

            workers[id] = std::thread(multiAntImprovement,
                                      start,
                                      end,
                                      std::ref(reference_ant),
                                      std::ref(ants_construction_status),
                                      std::ref(colony),
                                      std::ref(instance));
        }

        // waiting for all threads to finish
        for(auto &worker : workers){worker.join();}

    }


    //----------------------------------- END ANT CONSTRUCTION & LOCAL SEARCH -----------------------------------



 }