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
 * @file AntConstruction.hpp
 * @brief implements the construction of ant within the colony
 * @author Josué Tambwe
 * @date 1 May 2026
 */

 #pragma once

 #include "hpc/cpu/Thread.hpp"
 #include "gap/GapInstance.hpp"
 #include "gap/GapSolution.hpp"
 #include "input/Parameters.hpp"
 #include "gap/Status.hpp"
 #include "utils/Logger.hpp"
 #include "configuration/Config.hpp"
 #include "metaheuristics/antColonyOptimizer/AlignedMatrix.hpp"
 #include "metaheuristics/antColonyOptimizer/AcoUtils.hpp"
 #include "metaheuristics/greedy/GreedyConstruction.hpp"
 #include "metaheuristics/greedy/GreedyLocalSearch.hpp"
 #include <vector>
 #include <unordered_set>
 #include <cmath>
 #include <cstdint>

namespace gap::ACO{


    //----------------------------------- INITIALIZATION -----------------------------------


    /**
     *@brief initialization of ants in the colony
     */
      void colonyInitialization(std::vector<std::vector<int>> &residual_capacities,
                                std::vector<std::unordered_set<int> > &ant_tasks,
                                gap::GapInstance &instance);




    /**
     * @brief computes the reference ant solution with  a greedy construction (risky-tasks)
     *        with a local search in the balance move neighborhood
     */
      gap::GapSolution generateReferenceAnt(gap::GapInstance &instance);




    /**
     * @brief computes the inverse of the reference value 
     *        which is the objective value of a greedy solution 
     *        with a local search in the balance move neighborhood
     */                        
      float computeInverseReferenceValue(gap::GapSolution &solution,
                                        gap::GapInstance &instance);

    //----------------------------------- END INITIALIZATION -----------------------------------





    //----------------------------------- ASSIGNMENT OF THE FIRST TASK -----------------------------------


          /**
           *  @brief assigns the first task randomly for diversification
           */
          bool assignFirstTaskRandomly(std::unordered_set<int> &tasks,
                                    std::vector<int> &residual_capacity,
                                    gap::Params &params,
                                    gap::GapSolution &ant,
                                    gap::GapInstance &instance);




          /**
           *  @brief performs multiple first task assignment randomly from index "start" to index "end" within the colony
           */
          void multiFirstTaskAssignment(int start,
                                        int end,
                                        std::vector<std::unordered_set<int>> &ants_tasks,
                                        std::vector<std::vector<int>> &residual_capacities,
                                        gap::Params &params,
                                        std::vector<bool> &ants_construction_status,
                                        std::vector<gap::GapSolution> &colony,
                                        gap::GapInstance &instance);




          /**
           *  @brief performs first task assignment randomly with multi-threading
           */
          void firstTaskAssignment(std::vector<std::unordered_set<int>> &ants_tasks,
                                  std::vector<std::vector<int>> &residual_capacities,
                                  gap::Params &params,
                                  std::vector<bool> &ants_construction_status,
                                  std::vector<gap::GapSolution> &colony,
                                  gap::GapInstance &instance);





          /**
           *  @brief checks that the first task has  been assigned randomly for all ants
           *         otherwise the problem is infeasible
           */
          bool checkProblemFeasibility(std::vector<bool> &ants_construction_status);




    //----------------------------------- END ASSIGNMENT OF THE FIRST TASK -----------------------------------






    //----------------------------------- ANT CONSTRUCTION & LOCAL SEARCH -----------------------------------


       /**
        * @brief finds the agent with the highest weight on available agent
        */
        int findTask(std::unordered_set<int> &tasks,
                    int &max_weight,
                    gap::GapInstance &instance);




    

        /**
        * @brief finds the agent that maximizes the criteria : (tau_ij)^alpha * (eta_ij)^beta
        */
          int findAgentHeuristic(int task,
                                float inverse_max_weight,
                                gap::Params &params,
                                std::vector<int> &residual_capacity,
                                AlignedMatrix &pheromone_matrix,
                                gap::GapInstance &instance);



        /**
         *  @brief performs the assignment based on the heuristic criteria : (tau_ij)^alpha * (eta_ij)^beta
         */
          bool heuristicAssignment(int task,
                                  int max_weight,
                                  gap::Params &params,
                                  std::vector<int> &residual_capacity,
                                  AlignedMatrix &pheromone_matrix,
                                  gap::GapSolution &ant,
                                  gap::GapInstance &instance);



          /**
           *  @brief countes the number of agents with enough residual capacity for the given task
           */
          int countAvailableAgent(int task,
                                  std::vector<int> &residual_capacity,
                                  gap::GapInstance &instance);



          /**
           *  @brief computes the cumulative score of agents while initializing agent indexes and agent scores
           *         agent indexes : indexes of agent with enough capacity left for the given task
           *         agent score   : numerator score of an agent : (tau)^alpha * (eta)^beta
           */
          float computeCumulativeStochasticScore(int task,
                                                int max_weight,
                                                std::vector<int> &residual_capacity,
                                                std::vector<int> &agent_indexes,
                                                std::vector<float> &agent_scores,
                                                AlignedMatrix &pheromone_matrix,
                                                gap::Params &params,
                                                gap::GapInstance &instance);


                                  
          /**
           *  @brief finds the agent with the probabilistic approch
           */
          int findAgentStochastic(std::vector<int> &agent_indexes,
                                  std::vector<float> &agent_scores,
                                  float cumulative_score);




         /**
          *  @brief performs the assignment based on the stochastic approch : probability = (tau_ij)^alpha * (eta_ij)^beta / cumulative sum
          */
          bool stochasticAssignment(int task,
                                    int max_weight,
                                    gap::Params &params,
                                    std::vector<int> &residual_capacity,
                                    AlignedMatrix &pheromone_matrix,
                                    gap::GapSolution &ant,
                                    gap::GapInstance &instance);




          /**
           *  @brief constructs the ant solution (apart from the first task which is assigned randomly)
           */
          bool partialAntConstruction(std::unordered_set<int> &tasks,
                                      std::vector<int> &residual_capacity,
                                      double probability_threshold,
                                      gap::Params &params,
                                      AlignedMatrix &pheromone_matrix,
                                      gap::GapSolution &ant,
                                      gap::GapInstance &instance);





          /**
           *  @brief constructs ant solutions from index "start" to index "end" within the colony
           */
          void multiPartialAntConstruction(int start,
                                     int end,
                                     double probability_threshold,
                                     gap::Params &params,
                                     std::vector<std::unordered_set<int>> &ants_tasks,
                                     std::vector<bool> &ants_construction_status,
                                     std::vector<std::vector<int>> &residual_capacities,
                                     AlignedMatrix &pheromone_matrix,
                                     std::vector<gap::GapSolution> &colony,
                                     gap::GapInstance &instance);




          /**
           *  @brief constructs ant solutions  within the colony
           */
          bool antConstruction(double probability_threshold,
                              gap::Params &params,
                              std::vector<bool> &ants_construction_status,
                              AlignedMatrix &pheromone_matrix,
                              std::vector<gap::GapSolution> &colony,
                              gap::GapInstance &instance);



          /**
          * @brief performs the greedy local search on the ant solution
          */
          void antLocalSearch(gap::GapSolution &ant,
                              gap::GapInstance &instance);




          /**
           * @brief performs the greedy local search if the ant solution has been fully constructed
           *        repair the infeasible solution by replacing the infeasible ant by a reference ant
           *        which was constructed with a greedy heuristic approch
           */
          void multiAntImprovement(int start,
                                  int end,
                                  gap::GapSolution &reference_ant,
                                  std::vector<bool> &ants_construction_status,
                                  std::vector<gap::GapSolution> &colony,
                                  gap::GapInstance &instance);




          /**
          * @brief performs the ant improvement describe above on the entire colony
          */
          void antImprovement(gap::GapSolution &reference_ant,
                              gap::Params &params,
                              std::vector<bool> &ants_construction_status,
                              std::vector<gap::GapSolution> &colony,
                              gap::GapInstance &instance);


      //----------------------------------- END ANT CONSTRUCTION & LOCAL SEARCH -----------------------------------






}