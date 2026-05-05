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
 * @file RunBranchAndBound.hpp
 * @brief implements the Branch and Bound (B&B) algorithm
 * @author Josué Tambwe
 * @date 5 May 2026
 */

 #pragma once


 #include "gap/GapInstance.hpp"
 #include "gap/GapSolution.hpp"
 #include "branchAndBound/BaBUtils.hpp"
 #include <vector>




 namespace gap::BaB{


    /**
     * @brief converts a 1D solution vector into the standard data solution in the GAP solver
     */
    void setSolutionVector(std::vector<double> sol, gap::GapSolution solution);


 }


