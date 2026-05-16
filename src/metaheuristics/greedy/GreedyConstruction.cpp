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
 * @file GreedyConstructionMinCost.cpp
 * @author Josué Tambwe
 * @date 17 Mar 2026
 */

 #include "metaheuristics/greedy/GreedyConstruction.hpp"

 namespace gap::greedy{


    std::vector<int> tasksAvailableVector(std::unordered_set<int> &tasks){

        std::vector<int> tasks_available(tasks.size());
        int j = 0;
        for(int task : tasks){tasks_available[j] = task; j++;}
        return tasks_available;
    }


    //--------------------------------------- COST & WEIGHT CONSTRUCTION --------------------------------------------

    void findPartialMinMaxCostWeightAgent(int agent,
                                      std::vector<int> &tasks_available,
                                      std::vector<int> &max_cost_vector,
                                      std::vector<float> &inverse_range_cost_vector,
                                      std::vector<int> &max_weight_vector,
                                      std::vector<float> &inverse_range_weight_vector,
                                      gap::GapInstance &instance){
        
        const std::vector<std::vector<int>>& weight_matrix = instance.getWeight();
        const std::vector<std::vector<int>> & cost_matrix = instance.getCost();
        
        int min_cost = std::numeric_limits<int>::max();
        int max_cost = 0;
        int min_weight = std::numeric_limits<int>::max();
        int max_weight = 0;

        for(size_t j = 0; j < tasks_available.size(); j++){

            int task = tasks_available[j];

            if(cost_matrix[agent][task] <= min_cost){min_cost = cost_matrix[agent][task];}
            if(cost_matrix[agent][task] >= max_cost){max_cost = cost_matrix[agent][task];}
            if(weight_matrix[agent][task] <= min_weight){min_weight = weight_matrix[agent][task];}
            if(weight_matrix[agent][task] >= max_weight){max_weight = weight_matrix[agent][task];}

        }

        max_cost_vector[agent] = max_cost;
        inverse_range_cost_vector[agent] = 1.0f / (max_cost - min_cost + epsilon);
        max_weight_vector[agent] = max_weight;
        inverse_range_weight_vector[agent] = 1.0f / (max_weight - min_weight + epsilon);


    }




    void findGlobalMinMaxCostWeightAgent(std::vector<int> &tasks_available,
                                            std::vector<int> &max_cost_vector,
                                            std::vector<float> &inverse_range_cost_vector,
                                            std::vector<int> &max_weight_vector,
                                            std::vector<float> &inverse_range_weight_vector,
                                            gap::GapInstance &instance){

        for(size_t i = 0; i < instance.getNbAgent(); i++){

            findPartialMinMaxCostWeightAgent(i, 
                                            tasks_available, 
                                            max_cost_vector, 
                                            inverse_range_cost_vector, 
                                            max_weight_vector, 
                                            inverse_range_weight_vector, 
                                            instance);
        }
    }




    float computePartialScoreTask(int agent,
                                int task,
                                std::vector<float> &alpha_vector,
                                int max_cost,
                                int task_cost,
                                float inverse_range_cost,
                                int max_weight,
                                int task_weight,
                                float inverse_range_weight,
                                std::vector<int> &residual_capacity,
                                gap::GapInstance &instance){
        
        const std::vector<std::vector<int>>& weight_matrix = instance.getWeight();
        
        if(residual_capacity[agent] < weight_matrix[agent][task]){return -1.0f;}

        else{
           float task_score = alpha_vector[agent] * (static_cast<float>(max_cost - task_cost) * inverse_range_cost) 
                              + (1.0f - alpha_vector[agent]) * (static_cast<float>(max_weight - task_weight) * inverse_range_weight);
           return task_score;
        }
    }




    void computeGroupScoreTask(int start,
                                int end,
                                std::vector<int> &tasks_available,
                                std::vector<float> &alpha_vector,
                                std::vector<int> &max_cost_vector,
                                const std::vector<std::vector<int>> & cost_matrix,
                                std::vector<float> &inverse_range_cost_vector,
                                std::vector<int> &max_weight_vector,
                                const std::vector<std::vector<int>>& weight_matrix,
                                std::vector<float> inverse_range_weight_vector,
                                std::vector<int> &residual_capacity,
                                std::unordered_map<int, float> &tasks_scores,
                                std::unordered_map<int, int> &tasks_best_agent,
                                gap::GapInstance &instance){

        for(int j = start; j <= end; j++){

            int task = tasks_available[j];

            for(size_t agent = 0; agent < instance.getNbAgent(); agent++){

                float score = computePartialScoreTask(agent,
                                                        task,
                                                        alpha_vector,
                                                        max_cost_vector[agent],
                                                        cost_matrix[agent][task],
                                                        inverse_range_cost_vector[agent],
                                                        max_weight_vector[agent],
                                                        weight_matrix[agent][task],
                                                        inverse_range_weight_vector[agent],
                                                        residual_capacity,
                                                        instance);

                if(score >= 0.0f && score > tasks_scores[task]){

                    tasks_scores[task] = score;
                    tasks_best_agent[task] = agent;
                }                                           
            }

        }

    }




    void findBestTAskandBestAgent(int &best_agent,
                                int &best_task,
                                int nb_threads,
                                std::vector<int> &tasks_available,
                                std::vector<int> &residual_capacity,
                                gap::GapInstance &instance){

        std::vector<float> alpha_vector(instance.getNbAgent());
        const std::vector<int>& capacity_vector = instance.getCapacity();

        for(size_t i = 0; i < instance.getNbAgent(); i++){

            alpha_vector[i] = static_cast<float>(residual_capacity[i]) / (capacity_vector[i] + epsilon);
        }
                
        std::vector<int> max_cost_vector(instance.getNbAgent(), 0);
        std::vector<float> inverse_range_cost_vector(instance.getNbAgent(), 0.0f);
        std::vector<int> max_weight_vector(instance.getNbAgent(), 0);
        std::vector<float> inverse_range_weight_vector(instance.getNbAgent(), 0.0f);

        findGlobalMinMaxCostWeightAgent(tasks_available, 
                                            max_cost_vector, 
                                            inverse_range_cost_vector, 
                                            max_weight_vector, 
                                            inverse_range_weight_vector, 
                                            instance);

        const std::vector<std::vector<int>>& weight_matrix = instance.getWeight();
        const std::vector<std::vector<int>> & cost_matrix = instance.getCost();
        
        // initialization
        std::unordered_map<int, float> tasks_scores;
        std::unordered_map<int, int> tasks_best_agent;
        for(int task : tasks_available){tasks_scores[task] = -1.0f;}
        for(int task : tasks_available){tasks_best_agent[task] = -1;}
        
        // computation of tasks scores
        int work_size = static_cast<int>(tasks_available.size());
        nb_threads = std::min(nb_threads, work_size);
        std::vector<std::thread> workers(nb_threads);

        for(int id = 0; id < nb_threads; id++){

            int start = start_index(id, work_size, nb_threads);
            int end = end_index(id, work_size, nb_threads);

            workers[id] = std::thread(computeGroupScoreTask,
                                     start,
                                     end,
                                     std::ref(tasks_available),
                                     std::ref(alpha_vector),
                                     std::ref(max_cost_vector),
                                     std::ref(cost_matrix),
                                     std::ref(inverse_range_cost_vector),
                                     std::ref(max_weight_vector),
                                     std::ref(weight_matrix),
                                     std::ref(inverse_range_weight_vector),
                                     std::ref(residual_capacity),
                                     std::ref(tasks_scores),
                                     std::ref(tasks_best_agent),
                                     std::ref(instance));


        }

        // waiting for all threads the finish
        for(auto &worker : workers){worker.join();}

        float best_task_score = -1.0f;

        for (const auto& [task_id, score] : tasks_scores) {

            if (score > best_task_score) {
                best_task_score = score;
                best_task = task_id;
            }
        }

        if(best_task_score >= 0.0f){best_agent = tasks_best_agent[best_task];}

        else{ best_task = -1; best_agent = -1;}

    }




    bool assignTaskToAgent(int nb_threads,
                        std::unordered_set<int> &tasks,
                        std::vector<int> &residual_capacity,
                        gap::GapSolution &solution,
                        gap::GapInstance &instance){

        std::vector<int> tasks_available = tasksAvailableVector(tasks);
        int best_agent = -1;
        int best_task = -1;

        findBestTAskandBestAgent(best_agent,
                                best_task,
                                nb_threads,
                                tasks_available,
                                residual_capacity,
                                instance);

        if(best_agent != -1 && best_task != -1){

            // security on the capacity constraint
            const std::vector<std::vector<int>>& weight_matrix = instance.getWeight();
            if(residual_capacity[best_agent] < weight_matrix[best_agent][best_task]){return false;}

            // when the best pair (agent, job) has been found
            std::vector<int>& solutionVector = solution.getSolutionVector();
            solutionVector[best_task] = best_agent;

            // update of the agent residual capacity
            residual_capacity[best_agent] -= weight_matrix[best_agent][best_task];

            // erasing the task assigned
            tasks.erase(best_task);

            return true;
        }

        // when no assignment has been performed
        return false;
    }




    gap::GapSolution constructionLowCost(gap::Params params, gap::GapInstance &instance){

        // initialization
        gap::GapSolution solution = gap::GapSolution(instance);
        std::vector<int> residual_capacity(instance.getCapacity());
        std::unordered_set<int> tasks;

        for(size_t task = 0; task < instance.getNbTask(); task++){tasks.insert(task);}

        while(!tasks.empty()){

            bool assignment_performed = assignTaskToAgent(params.nb_threads,
                                                         tasks, 
                                                         residual_capacity, 
                                                         solution, 
                                                         instance);

            if(!assignment_performed){

                solution.setStatus(gap::Status::INFEASIBLE);
                return solution;
            }
        }
        // when the construction is completed!
        if(solution.isFeasible(instance)){solution.setStatus(gap::Status::FEASIBLE);}

        else{solution.setStatus(gap::Status::INFEASIBLE);}
        
        return solution;

    }

    //--------------------------------------- END COST & WEIGHT CONSTRUCTION --------------------------------------------






    //--------------------------------------- RISKY TASKS CONSTRUCTION --------------------------------------------


    std::vector<float> computeInverseResidualCapacity(std::vector<int> &residual_capacity){

        std::vector<float> inverse_residual_capacity(residual_capacity.size());

        for(size_t agent = 0; agent < residual_capacity.size(); agent++){

            inverse_residual_capacity[agent] = 1.0f / (residual_capacity[agent] + epsilon);
        }

        return inverse_residual_capacity;

    }




    float computeMaxPressureTask(int task,
                                std::vector<float> &inverse_residual_capacity,
                                gap::GapInstance &instance){

        const std::vector<std::vector<int>>& weight_matrix = instance.getWeight();
        float max_pressure = 0.0f;

        for(int agent = 0; agent < static_cast<int>(instance.getNbAgent()); agent++){

            float pressure = weight_matrix[agent][task] * inverse_residual_capacity[agent] ;
            if(pressure > max_pressure){max_pressure = pressure;}
        }
        return max_pressure;
    }




    int findMostRiskyTask(std::vector<int> &tasks_available,
                        std::vector<float> &inverse_residual_capacity,
                        gap::GapInstance &instance){

        float max_pressure = 0.0f;

        int most_risky_task = -1;

        for(int task : tasks_available){

            float task_pressure = computeMaxPressureTask(task, 
                                                         inverse_residual_capacity, 
                                                         instance);

            if(max_pressure < task_pressure){max_pressure = task_pressure; most_risky_task = task;}

        }

        return most_risky_task;
    }



    int findBestAgent(int task,
                      std::vector<int> &residual_capacity,
                      gap::GapInstance &instance){

        const std::vector<std::vector<int>>& weight_matrix = instance.getWeight();

        float best_score = 0.0f;
        int best_agent = -1;

        for(int agent = 0; agent < static_cast<int>(instance.getNbAgent()); agent++){

            if(weight_matrix[agent][task] <= residual_capacity[agent]){

                float agent_score = static_cast<float>(residual_capacity[agent]) 
                                    / (weight_matrix[agent][task] + epsilon);

                if(agent_score >= best_score){best_agent = agent; best_score = agent_score;}
            }
            
        }
        return best_agent;
        
    }




    bool assignRiskyTaskToAgent(std::unordered_set<int> &tasks,
                               std::vector<int> &residual_capacity,
                               gap::GapSolution &solution,
                               gap::GapInstance &instance){

        std::vector<int> tasks_available = tasksAvailableVector(tasks); 
        std::vector<float> inverse_residual_capacity = computeInverseResidualCapacity(residual_capacity);
        
        int most_risky_task = findMostRiskyTask(tasks_available,
                                                inverse_residual_capacity,
                                                instance);

        int best_agent = findBestAgent(most_risky_task,
                                       residual_capacity,
                                       instance);

        // when no agent has enough capacity left
        if(best_agent == -1){return false;}
        
        // when an assignment might be performed
        else{
        // ensuring (again) the capacity constraint
        const std::vector<std::vector<int>>& weight_matrix = instance.getWeight();
        if(weight_matrix[best_agent][most_risky_task] > residual_capacity[best_agent]){return false;}

        // performing the assignment
        std::vector<int>& solutionVector = solution.getSolutionVector();
        solutionVector[most_risky_task] = best_agent;

        // update of the residual capacity
        residual_capacity[best_agent] -= weight_matrix[best_agent][most_risky_task];
        tasks.erase(most_risky_task);

        
        return true;

        }

    }



    gap::GapSolution constructionRiskyTasks(gap::GapInstance &instance){

        // initialization
        gap::GapSolution solution = gap::GapSolution(instance);
        std::vector<int> residual_capacity(instance.getCapacity());
        std::unordered_set<int> tasks;

        for(size_t task = 0; task < instance.getNbTask(); task++){tasks.insert(task);}

        while(!tasks.empty()){

            bool assignment_performed = assignRiskyTaskToAgent(tasks,
                                                               residual_capacity,
                                                               solution,
                                                               instance);
            // when a task is not assigned to an agent
            if(!assignment_performed){

                solution.setStatus(gap::Status::INFEASIBLE);
                return solution;
            }
        }
        
        // when the construction is completed!
        if(solution.isFeasible(instance)){solution.setStatus(gap::Status::FEASIBLE);}

        else{solution.setStatus(gap::Status::INFEASIBLE);}
        
        return solution;

    }

     //------------------------------ END RISKY TASKS CONSTRUCTION ---------------------------------




    gap::GapSolution construction(gap::Params params, gap::GapInstance &instance){

        if(params.low_cost_construction){
            return constructionLowCost(params, instance);
        }
        else{
            return constructionRiskyTasks(instance);
        }

    }


 }