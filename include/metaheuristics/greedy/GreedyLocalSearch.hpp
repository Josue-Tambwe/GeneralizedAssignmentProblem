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


   std::vector<int> computeResidualCapacity(gap::GapSolution &solution,
                                          gap::GapInstance &instance);

   std::vector<int> computeIndividualCostAgent(gap::GapSolution &solution,
                                              gap::GapInstance &instance);

   void findMostAndLeastExpensiveAgents(int &most_expensive_agent,
                                      int &least_expensive_agent,
                                      std::vector<int> &individual_cost_agents);

  void sortTaskFromMostToLeastExpensive(int most_expensive_agent,
                                        int least_expensive_agent,
                                        std::priority_queue<gap::greedy::Element> &tasks,
                                        gap::GapSolution &solution,
                                        gap::GapInstance &instance);

   int assignTaskFromMostToLeastExpensive(std::vector<int> &residual_capacity,
                                        gap::GapSolution &solution,
                                        gap::GapInstance &instance);

  

   void balanceMove(gap::GapSolution &solution,
                      gap::GapInstance &instance);

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

  
  void localSearch(gap::Params &params,
                gap::GapSolution &solution,
                gap::GapInstance &instance);

 }
