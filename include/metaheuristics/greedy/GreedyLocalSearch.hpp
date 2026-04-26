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
 * @file GreedyLocalSearchMinCost.hpp
 * @brief  improves a solution of an instance of the Generalized Assignment Problem 
 * constructed by a Greedy approch
 * @author Josué Tambwe
 * @date 17 Mar 2026
 */

 #pragma once 

 #include "gap/GapInstance.hpp"
 #include "gap/GapSolution.hpp"
 #include "metaheuristics/greedy/GreedyElement.hpp"
 #include "hpc/cpu/Thread.hpp"
 #include "configuration/Config.hpp"
 #include "input/Parameters.hpp"
 #include <vector>
 #include <queue>

 namespace gap::greedy{

  /**
    * @brief Computation of  agents residual capacities within the current solution
    */

   std::vector<int> computeResidualCapacity(gap::GapSolution &solution,
                                          gap::GapInstance &instance);


  // -------------------------------  BALANCE MOVE (NEIGHBORHOOD) ----------------------------                                   
  
   /**
    * @brief Computation of the assignment cost of an individual agent within the current solution
    */

   std::vector<int> computeIndividualCostAgent(gap::GapSolution &solution,
                                              gap::GapInstance &instance);


   /**
    * @brief The global most and least expensive agents are identified in order to transfer (if it is possible) a task
    *        from the most expensive agent to the least expensive agent while reducing the global cost
    */

   void findMostAndLeastExpensiveAgents(int &most_expensive_agent,
                                      int &least_expensive_agent,
                                      std::vector<int> &individual_cost_agents);


  /**
    * @brief After  both  global most and least expensive agents are identified, the tasks on the most
    *        expensive agent are sorted regarding the criteria :  cost / weight
    *         - cost   :  the cost of the task when assigned to the least expensive agent
    *         - weight :  the weight of the task when assigned to the least expensive agent 
    *       This creteria allows the most expensive (relatively to their weight) tasks on the least expensive agent to be treated first
    *       therefore the residual capacity of the least expensive agent is used more efficiently to drastically reduce the global cost
    */

  void sortTaskFromMostToLeastExpensive(int most_expensive_agent,
                                        int least_expensive_agent,
                                        std::priority_queue<gap::greedy::Element> &tasks,
                                        gap::GapSolution &solution,
                                        gap::GapInstance &instance);


   /**
    * @brief When tasks of the most expensive agent had been sorted regarding the previous criteria on the least expensive agent,
    *        attempt of re-assignment of tasks are performed
    */

   int assignTaskFromMostToLeastExpensive(std::vector<int> &residual_capacity,
                                        gap::GapSolution &solution,
                                        gap::GapInstance &instance);


   /**
    * @brief After the greedy construction, this movement consists in finding the global most expensive
    *        agent and re-assigning one of its task to the global least expensive agent if the global cost is reduced
    */
  
   void balanceMove(gap::GapSolution &solution,
                      gap::GapInstance &instance);

  // -------------------------------  END BALANCE MOVE (NEIGHBORHOOD) ---------------------------- 



  // -------------------------------  CHEAP MOVE (NEIGHBORHOOD) ---------------------------- 
   void sortCheapAgent(int task,
                      int current_agent,
                      std::priority_queue<gap::greedy::Element> &agents,
                      gap::GapInstance &instance);

   void computeScoreTask(int task,
                        std::vector<int> &residual_capacity,
                        std::vector<int> &tasks_scores,
                        std::vector<int> &tasks_best_agent,
                        gap::GapSolution &solution,
                        gap::GapInstance &instance);

  void computeGroupScoreTask(int start,
                            int end,
                            std::vector<int> &residual_capacity,
                            std::vector<int> &tasks_scores,
                            std::vector<int> &tasks_best_agent,
                            gap::GapSolution &solution,
                            gap::GapInstance &instance);

  
  int findBestTask(int nb_threads,
                  std::vector<int> &residual_capacity,
                  std::vector<int> &tasks_best_agent,
                  gap::GapSolution &solution,
                  gap::GapInstance &instance);

  int assignTaskToCheapAgent (int nb_threads,
                              std::vector<int> &residual_capacity,
                              gap::GapSolution &solution,
                              gap::GapInstance &instance);

  void cheapMove(int nb_threads,
                gap::GapSolution &solution,
                gap::GapInstance &instance);

  // -------------------------------  END CHEAP MOVE (NEIGHBORHOOD) ---------------------------- 
  
  void localSearch(gap::Params &params,
                gap::GapSolution &solution,
                gap::GapInstance &instance);

 }
