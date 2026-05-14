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
 * @file Config.hpp
 * @brief defines substancial elements for the configuration of the G.A.P solver
 * @author Josué Tambwe
 * @date 08 Mar 2026
 */
 
 #pragma once
 
 #ifndef NUMBER_PHYSICAL_CORES
    #define NUMBER_PHYSICAL_CORES 1 // default value (1 physical core)
 #endif

 #ifndef HAS_GUROBI
    #define HAS_GUROBI false
 #endif

 #ifndef HAS_HIGHS
    #define HAS_HIGHS false
 #endif

 #ifndef HAS_HEXALY
   #define HAS_HEXALY false
 #endif

 #ifndef USE_BRANCH_AND_BOUND
   #define USE_BRANCH_AND_BOUND false
 #endif

 #ifndef USE_MILP
   #define USE_MILP false
 #endif
 
const float epsilon = 1e-5; // to avoid division by zero
