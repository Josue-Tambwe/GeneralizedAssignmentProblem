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
 * @file GreedyLocalSearchMinCost.cpp
 * @author Josué Tambwe
 * @date 17 Mar 2026
 */

 #include "metaheuristics/greedy/GreedyLocalSearch.hpp"

 namespace gap::greedy{


   std::vector<int> computeResidualCapacity(gap::GapSolution &solution,
                              gap::GapInstance &instance){
      
      const std::vector<std::vector<int>>& weight_matrix = instance.getWeight();
      const std::vector<int>& capacity_vector = instance.getCapacity();
      std::vector<int>& solution_vector =  solution.getSolutionVector();
      std::vector<int> residual_capacity(capacity_vector);

      for(size_t task = 0; task < instance.getNbTask(); task++){
         
         int agent = solution_vector[task];
         residual_capacity[agent] -= weight_matrix[agent][task];
      }

      return residual_capacity;


   }

   

   // -------------------------------  BALANCE MOVE (NEIGHBORHOOD) ----------------------------

   std::vector<int> computeIndividualCostAgent(gap::GapSolution &solution,
                                              gap::GapInstance &instance){

      std::vector<int> individual_cost_agents(instance.getNbAgent(), 0);
      std::vector<int>& solution_vector =  solution.getSolutionVector();
      const std::vector<std::vector<int>> & cost_matrix = instance.getCost();

      for(size_t task = 0; task < instance.getNbTask(); task++){

         int agent = solution_vector[task];
         individual_cost_agents[agent] += cost_matrix[agent][task];
      }

      return individual_cost_agents;
   }



   
   void findMostAndLeastExpensiveAgents(int &most_expensive_agent,
                                        int &least_expensive_agent,
                                        std::vector<int> &individual_cost_agents){

      int max_cost = individual_cost_agents[0];
      int min_cost = individual_cost_agents[0];

      for(size_t agent = 1; agent < individual_cost_agents.size(); agent++){

         if(individual_cost_agents[agent] >= max_cost){max_cost = individual_cost_agents[agent]; most_expensive_agent = agent;}
         if(individual_cost_agents[agent] <= min_cost){min_cost = individual_cost_agents[agent]; least_expensive_agent = agent;}
      }

   }



   void sortTaskFromMostToLeastExpensive(int most_expensive_agent,
                                        int least_expensive_agent,
                                        std::priority_queue<gap::greedy::Element> &tasks,
                                        gap::GapSolution &solution,
                                        gap::GapInstance &instance){

      const std::vector<std::vector<int>> & cost_matrix = instance.getCost();
      std::vector<int>& solution_vector =  solution.getSolutionVector();
      const std::vector<std::vector<int>>& weight_matrix = instance.getWeight();

      for(int task = 0; task < static_cast<int>(instance.getNbTask()); task++){

         if(solution_vector[task] == most_expensive_agent){

            float score_task = static_cast<float>(cost_matrix[least_expensive_agent][task]) /
                               (weight_matrix[least_expensive_agent][task] + epsilon);

            tasks.push(gap::greedy::Element(task, score_task));

         }

      }

   }


   int assignTaskFromMostToLeastExpensive(std::vector<int> &residual_capacity,
                                          gap::GapSolution &solution,
                                          gap::GapInstance &instance){

      std::vector<int> individual_cost_agents = computeIndividualCostAgent(solution, instance);
      int most_expensive_agent = 0;
      int least_expensive_agent = 0;
      
      findMostAndLeastExpensiveAgents(most_expensive_agent,
                                    least_expensive_agent,
                                    individual_cost_agents);

      // when all agents cost the same
      if(most_expensive_agent == least_expensive_agent){return -1;}

      // sorting tasks in order to transfer from the most expensive agent to the least expensive one
      std::priority_queue<gap::greedy::Element> tasks;

      sortTaskFromMostToLeastExpensive(most_expensive_agent,
                                       least_expensive_agent,
                                       tasks,
                                       solution,
                                       instance);

      const std::vector<std::vector<int>> & cost_matrix = instance.getCost();
      std::vector<int>& solution_vector =  solution.getSolutionVector();
      const std::vector<std::vector<int>>& weight_matrix = instance.getWeight();

      while(!tasks.empty()){

         gap::greedy::Element current = tasks.top();
         int task = current.getId();
         tasks.pop();

         // case of a promissing transfer
         if(cost_matrix[most_expensive_agent][task] > cost_matrix[least_expensive_agent][task]){

            // checking for the capacity constraint
            if(weight_matrix[least_expensive_agent][task] <= residual_capacity[least_expensive_agent]){

               // performing the transfer
               solution_vector[task] = least_expensive_agent;

               // updating residual capacities
               residual_capacity[least_expensive_agent] -= weight_matrix[least_expensive_agent][task];
               residual_capacity[most_expensive_agent] += weight_matrix[most_expensive_agent][task];

               return 1; // signal that a transfer has been performed
            }
         }

      }
      // when no transfer has been performed
      return -1;

   }



   void balanceMove(gap::GapSolution &solution,
                    gap::GapInstance &instance){

      std::vector<int> residual_capacity = computeResidualCapacity(solution, instance);
      int re_assignment_performed;

      do{
         re_assignment_performed = assignTaskFromMostToLeastExpensive(residual_capacity,
                                                                     solution,
                                                                     instance);

      }while(re_assignment_performed == 1);

   }

// -------------------------------  END BALANCE MOVE (NEIGHBORHOOD) ---------------------------- 





// -------------------------------  CHEAP MOVE (NEIGHBORHOOD) ----------------------------------

   void sortCheapAgent(int task,
                      int current_agent,
                      std::priority_queue<gap::greedy::Element> &agents,
                      gap::GapInstance &instance){
       
      const std::vector<std::vector<int>> & cost_matrix = instance.getCost();

      for(int agent = 0; agent < static_cast<int>(instance.getNbAgent()); agent++){

         if(agent != current_agent){

            float score_agent = 1.0f / (cost_matrix[agent][task] + epsilon);
            agents.push(gap::greedy::Element(agent, score_agent));

         }

      }

   }


   void computeScoreTask(int task,
                        std::vector<int> &residual_capacity,
                        std::vector<int> &tasks_scores,
                        std::vector<int> &tasks_best_agent,
                        gap::GapSolution &solution,
                        gap::GapInstance &instance){

      std::priority_queue<gap::greedy::Element> agents;
      std::vector<int>& solution_vector =  solution.getSolutionVector();
      int current_agent = solution_vector[task];

      sortCheapAgent(task,
                     current_agent,
                     agents,
                     instance);
      
      const std::vector<std::vector<int>>& weight_matrix = instance.getWeight();
      const std::vector<std::vector<int>> & cost_matrix = instance.getCost();

      while(!agents.empty()){

         gap::greedy::Element current = agents.top();
         int agent = current.getId();
         agents.pop();

         // case of a promissing agent
         if(cost_matrix[current_agent][task] > cost_matrix[agent][task]){

            // checking for the capacity constraint
            if(residual_capacity[agent] > weight_matrix[agent][task]){

               tasks_scores[task] = cost_matrix[current_agent][task] - cost_matrix[agent][task];
               tasks_best_agent[task] = agent;
               return;
            }
         }
      }
      // when constraints are violated (no agent found)
      tasks_best_agent[task] = -1;

   }


   void computeGroupScoreTask(int start,
                              int end,
                              std::vector<int> &residual_capacity,
                              std::vector<int> &tasks_scores,
                              std::vector<int> &tasks_best_agent,
                              gap::GapSolution &solution,
                              gap::GapInstance &instance){

      for(int i = start; i <= end; i++){

         computeScoreTask(i,
                        residual_capacity,
                        tasks_scores,
                        tasks_best_agent,
                        solution,
                        instance);
      }

   }


   int findBestTask(int nb_threads,
                  std::vector<int> &residual_capacity,
                  std::vector<int> &tasks_best_agent,
                  gap::GapSolution &solution,
                  gap::GapInstance &instance){

      int work_size = static_cast<int>(instance.getNbTask());
      std::vector<int> tasks_scores(work_size ,0);
      nb_threads = std::min(nb_threads, work_size);
      std::vector<std::thread> workers(nb_threads);

      for(int id = 0; id < nb_threads; id++){

         int start = start_index(id, work_size, nb_threads);
         int end = end_index(id, work_size, nb_threads);

         workers[id] = std::thread(computeGroupScoreTask,
                                    start,
                                    end,
                                    std::ref(residual_capacity),
                                    std::ref(tasks_scores),
                                    std::ref(tasks_best_agent),
                                    std::ref(solution),
                                    std::ref(instance));
      }

      // waiting for all threads to finish
      for(int id = 0; id < nb_threads; id++){
         workers[id].join();
      }

      int best_task = -1;
      int best_score = 0;

      for(int task = 0; task < work_size; task++){

         if(tasks_scores[task] > best_score){
            best_task = task;
            best_score = tasks_scores[task];
         }
      }

      return best_task;

   }


   int assignTaskToCheapAgent (int nb_threads,
                              std::vector<int> &residual_capacity,
                              gap::GapSolution &solution,
                              gap::GapInstance &instance){
      
      std::vector<int> tasks_best_agent(instance.getNbTask(), -1);
      int best_task;

      do{
         best_task = findBestTask(nb_threads,
                                    residual_capacity,
                                    tasks_best_agent,
                                    solution,
                                    instance);
         if(best_task != -1){
            
            std::vector<int>& solution_vector =  solution.getSolutionVector();
            const std::vector<std::vector<int>>& weight_matrix = instance.getWeight();

            // re-assginment of the task
            int old_agent = solution_vector[best_task];
            int cheapest_agent = tasks_best_agent[best_task];
            solution_vector[best_task] = cheapest_agent;

            // update of residual capacities
            residual_capacity[old_agent] += weight_matrix[old_agent][best_task];
            residual_capacity[cheapest_agent] -= weight_matrix[cheapest_agent][best_task];

            return 1; // signal of a performed re-assignment

         }
         
      } while(best_task != -1);

      // when no re-assignment has been performed
      return -1;

   }


   void cheapMove(int nb_threads,
                gap::GapSolution &solution,
                gap::GapInstance &instance){
      
      std::vector<int> residual_capacity = computeResidualCapacity(solution, instance);
      int re_assignment_performed;

      do{
         re_assignment_performed = assignTaskToCheapAgent(nb_threads,
                                                         residual_capacity,
                                                         solution,
                                                         instance);

      }while(re_assignment_performed == 1);

   }


// -------------------------------  END CHEAP MOVE (NEIGHBORHOOD) ---------------------------- 






   void localSearch(gap::Params &params,
                gap::GapSolution &solution,
                gap::GapInstance &instance){

      balanceMove(solution, instance);
      cheapMove(params.nb_threads, solution, instance);

      // feasibility certification
      if(solution.isFeasible(instance)){solution.setStatus(gap::Status::FEASIBLE);}
      else{solution.setStatus(gap::Status::INFEASIBLE);}
   }
   

 }

