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
 * @file Parameters.cpp
 * @author Josué Tambwe
 * @date 11 Mar 2026
 */

 #include "input/Parameters.hpp"


 namespace gap{

    Params::Params(){

        // default values
        algorithm = gap::Algorithm::Greedy;
        instance_path = "";
        nb_threads = NUMBER_PHYSICAL_CORES;
        time_limit = 10.0;
        verbose = false;

        // greedy
        low_cost_construction = false;

        // ACO 
        use_max_iterations = false; 
        use_time_limit = false; 
        
        nb_ants = 1; 
        nb_max_iterations = 1; 
        influence = 'b'; 
        gamma = 0.5f; 
        rho = 0.1f;

        // Branch and Bound
        milp_solver='g';
        exploration_strategy='b';
        warm_start = false;
        branching_value = 0.0;
        optimality_gap = 0.0;

    }

 }