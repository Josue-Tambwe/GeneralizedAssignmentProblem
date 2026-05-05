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
 * @file RunBranchAndBound.cpp
 * @author Josué Tambwe
 * @date 24 Mar 2026
 */



 #include "branchAndBound/RunBranchAndBound.hpp"

 namespace gap::BaB{


    void setSolutionVector(std::vector<double> sol, gap::GapSolution solution){

        std::vector<int>& solution_vector =  solution.getSolutionVector();

        for(size_t k = 0; k < solution_vector.size(); k++){

            if(sol[k] > 0.5){

                int agent = convertTo2DAgentIndex(k, solution_vector.size());
                int task = convertTo2DTaskIndex(k, solution_vector.size());

                solution_vector[task] = agent;

            }
        }

    }




 }