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
 * @class Params
 * @brief Stores options and flags defines by the user
 * @author Josué Tambwe
 * @date 11 Mar 2026
 */

 #pragma once
 
 #include "Algorithm.hpp"
 #include <string>

 namespace gap{

    struct Params{

        // constructor
        Params();

        // general parameters
        gap::Algorithm algorithm; 
        std::string instance_path;
        double time_limit;
        int nb_threads;
        bool verbose;

        // greedy
        bool low_cost_construction;

        // ACO
        bool use_max_iterations;
        bool use_time_limit;
        int nb_ants;
        int nb_max_iterations;
        float gamma;
        float rho;
        char influence;
        /* Possible value for the attribute "influence"
         - 'p' : pheromone -> alpha = 2 and beta = 1
         - 'b' : balance   -> alpha = 1 and beta = 1
         - 'h ': heuristic -> alpha = 1 and beta = 2
        */

        // Branch and Bound
        char milp_solver;
        /* Possible value for the attribute "milp_solver"
         - 'g' : gurobi
         - 'h' : highs
         - 'x ': hexaly 
        */

        char exploration_strategy;
        /* Possible value
         - 'b' : best first search
         - 'd' : depth first search
        */

        bool warm_start;

        double branching_value;
        double optimality_gap;


    };


    
 }