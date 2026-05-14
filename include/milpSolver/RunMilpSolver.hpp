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
 * @file RunMilpSolver.hpp
 * @brief Defines functions for MIP resolution approch
 * @author Josué Tambwe
 * @date 14 May 2026
 */


 #pragma once

 #if USE_MILP

 #include "gap/GapInstance.hpp"
 #include "gap/GapSolution.hpp"
 #include "input/Parameters.hpp"
 #include "gap/Status.hpp"
 #include "utils/Logger.hpp"
 #include "utils/Timer.hpp"
 #include "output/OutputFormat.hpp"
 #include "configuration/Config.hpp"
 #include "metaheuristics/greedy/GreedyConstruction.hpp"
 #include "metaheuristics/greedy/GreedyLocalSearch.hpp"
 #include <vector>

 #if HAS_GUROBI
 #include "milpSolver/GurobiBackend.hpp"
 #endif

 #if HAS_HEXALY
 #include "milpSolver/HexalyBackend.hpp"
 #endif

 #if HAS_HIGHS
 #include "milpSolver/HighsBackend.hpp"
 #endif


 namespace gap{


    /**
     * @brief generates an initial with greedy construction + local search
     */
    gap::GapSolution generateInitialSolution(gap::GapInstance &instance);




    /**
     * @brief convert a solution (GapSolution) into a 1D array in order to set an initial
     *        solution for a MILP solver (warm start)
     */
    std::vector<double> computeWarmStart(gap::GapSolution &solution);



    /**
     * @brief runs the MILP resolution with the solver Gurobi
     */
    void runGurobi(gap::Params &params);


 }

 #endif