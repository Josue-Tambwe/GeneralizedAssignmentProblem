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
 * @file BaBUtils.hpp
 * @brief This file defines some functions used in the Branch and Bound algorithm
 * @author Josué Tambwe
 * @date 28 April 2026
 */

 #pragma once


 #include "input/Parameters.hpp"
 #include <vector>
 #include <cmath>

 namespace gap::BaB{


    const double tolerance = 1e-4;  // tolerance  on variables integrality

    /**
     * @brief converts the index k in a 1D vector into the index of an agent in a 2D matrix
     */
    inline int convertTo2DAgentIndex(size_t k, size_t nb_task){
        return static_cast<int>(k / nb_task);
    } 



    /**
     * @brief converts the index k in a 1D vector into the index of an task in a 2D matrix
     */
    inline int convertTo2DTaskIndex(size_t k, size_t nb_task){
        return static_cast<int>(k % nb_task);
    }



    /**
     * @brief checks for integrality of the solution
     */
    inline bool isInteger(std::vector<double> &solution){

        for(size_t i = 0; i < solution.size(); i++){

            if(std::abs(solution[i]) > tolerance && std::abs(1.0 - solution[i]) > tolerance){
                return false;
            }
        }
        return true;

    }




    /**
     * @brief finds the index of the branching variable
     */
    inline int branchingVariableIndex(std::vector<double> solution, 
                                      gap::Params params){

        int index = -1;
        double best_score = std::numeric_limits<double>::max();

        for(int i = 0; i < static_cast<int>(solution.size()); i++){

            if(std::abs(solution[i]) > tolerance && 
               std::abs(1.0 - solution[i]) > tolerance){

                if(std::abs(solution[i] - params.branching_value) < best_score){
                    
                    index = i;
                    best_score = std::abs(solution[i] - params.branching_value);
                }

            }

        }

        return index;
    }



    /**
     * @brief check of the stopping criteria for the Best First node exploration strategy
     */
    inline bool stoppingCriteriaBestFirst(double primal_bound,
                                        double dual_bound,
                                        double current_time,
                                        gap::Params &params){

        if((primal_bound - dual_bound) <= (params.optimality_gap * primal_bound)){return true;}

        if(current_time >= params.time_limit){return true;}

        return false;

    }





    /**
     * @brief check of the stopping criteria for the Depth First node exploration strategy
     */
    inline bool stoppingCriteriaDepthFirst(double current_time,
                                           gap::Params &params){

        return (current_time >= params.time_limit);

    }


    
 }