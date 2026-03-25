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
 * @file Parameters.hpp
 * @brief Stores options and flags defines by the user
 * @author Josué Tambwe
 * @date 11 Mar 2026
 */

 #pragma once
 
 #include "Algorithm.hpp"
 #include <string>

 namespace gap{

    struct Params{
        gap::Algorithm algorithm;
        std::string instance_path;
        int nb_threads;
        int time_limit;
        bool verbose;
        bool low_cost_construction;
    };


    
 }