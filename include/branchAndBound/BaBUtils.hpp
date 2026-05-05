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


    const double tolerance = 1e-5;  // tolerance  on variables integrality

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
    inline bool isInteger(std::vector<double> solution){

        for(size_t i = 0; i < solution.size(); i++){

            if(solution[i] > tolerance && (1.0 - solution[i]) > tolerance){
                return false;
            }
        }
        return true;

    }




    /**
     * @brief finds the index of the branching variable
     */
    inline size_t branchingVariableIndex(std::vector<double> solution, 
                                         gap::Params params){

        size_t index = 0;
        double best_score = std::abs(solution[0] - params.branching_value);

        for(size_t i = 0; i < solution.size(); i++){

            if(std::abs(solution[i] - params.branching_value) < best_score){

                index = i;
                best_score = std::abs(solution[i] - params.branching_value);
            }

        }
        return index;
    }


    
 }