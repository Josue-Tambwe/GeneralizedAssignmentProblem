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
 * @file GreedyConstruction.hpp
 * @brief  builds a solution of an instance of the Generalized Assignment Problem by a Greedy approch
 * @author Josué Tambwe
 * @date 25 Feb 2026
 */
 #pragma once

 #include "gap/Status.hpp"
 #include "gap/GapInstance.hpp"
 #include "gap/GapSolution.hpp"
 #include "hpc/cpu/Thread.hpp"
 #include "configuration/Config.hpp"
 #include "input/Parameters.hpp"
 #include <algorithm>
 #include <vector>
 #include <unordered_set>
 #include <unordered_map>
 #include <iostream>
 #include <limits>

 namespace gap::greedy{

   /**
     * @brief stores the indexes of available tasks in a 1D vector
     */

   std::vector<int> tasksAvailableVector(std::unordered_set<int> &tasks);

    
  //--------------------------------------- COST & WEIGHT CONSTRUCTION --------------------------------------------

    void findPartialMinMaxCostConsumptionAgent(int agent,
                                      std::vector<int> &tasks_available,
                                      std::vector<int> &max_cost_vector,
                                      std::vector<float> &inverse_range_cost_vector,
                                      std::vector<int> &max_weight_vector,
                                      std::vector<float> &inverse_range_weight_vector,
                                      gap::GapInstance &instance);

    /**
     * @brief finds the minimum and maximum values of the cost of assignment and the consumption ressources (weight)
     * in order to normalize (min-max scaling) data when considering the computation of utility on each task for an given agent 
     */

    void findGlobalMinMaxCostConsumptionAgent(std::vector<int> &tasks_available,
                                            std::vector<int> &max_cost_vector,
                                            std::vector<float> &inverse_range_cost_vector,
                                            std::vector<int> &max_weight_vector,
                                            std::vector<float> &inverse_range_weight_vector,
                                            gap::GapInstance &instance);

    /**
     * @brief computes the score (utility) of a task on a unique given agent (hence the name partial)
     */

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
                                  gap::GapInstance &instance);

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
                              gap::GapInstance &instance);

    void findBestTAskandBestAgent(int &best_agent,
                                int &best_task,
                                int nb_threads,
                                std::vector<int> &tasks_available,
                                std::vector<int> &residual_capacity,
                                gap::GapInstance &instance);
    
    /**
     * @brief performs, based on the scores, the assignment of the best task to the best agent
     * @return true if an assignment has been performed and false otherwise
     */
                                                         
   bool assignTaskToAgent(int nb_threads,
                        std::unordered_set<int> &tasks,
                        std::vector<int> &residual_capacity,
                        gap::GapSolution &solution,
                        gap::GapInstance &instance);


   gap::GapSolution constructionLowCost(gap::Params params, gap::GapInstance &instance);

   
  //--------------------------------------- END COST & WEIGHT CONSTRUCTION --------------------------------------------





   //--------------------------------------- RISKY TASKS CONSTRUCTION --------------------------------------------


    /**
     * @brief computes the inverse : 1 / residual capacity, for all agent.
     */
   std::vector<float> computeInverseResidualCapacity(std::vector<int> &residual_capacity);




   /**
     * @brief computes the heuristic score  of a task wich is the maximimum value : weight / residual capacity
     *        for all agent
     */

   float computeMaxPressureTask(int task,
                                std::vector<float> &inverse_residual_capacity,
                                gap::GapInstance &instance);



    /**
     * @brief finds the task that puts the maximum pressure on agent with respect to their residual capacities
     */
   int findMostRiskyTask(std::vector<int> &tasks_available,
                        std::vector<float> &inverse_residual_capacity,
                        gap::GapInstance &instance);



    /**
     * @brief finds the agent that the given task puts the least pressure on
     */
   int findBestAgent(int task,
                    std::vector<int> &residual_capacity,
                    gap::GapInstance &instance);



    /**
     * @brief performs the assignment of the task found to its best agent found
     */
   bool assignRiskyTaskToAgent(std::unordered_set<int> &tasks,
                               std::vector<int> &residual_capacity,
                               gap::GapSolution &solution,
                               gap::GapInstance &instance);



    /**
     * @brief constructs the solution based on the risky-task criteria
     */
   gap::GapSolution constructionRiskyTasks(gap::GapInstance &instance);

   //--------------------------------------- END RISKY TASKS CONSTRUCTION --------------------------------------------


   /**
     * @brief constructs the solution  (risky-task criteria or the cost-weight criteria)
     */
   gap::GapSolution construction(gap::Params params, gap::GapInstance &instance);



 }