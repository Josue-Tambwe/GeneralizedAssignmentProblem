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
 * @file RunGreedy.hpp
 * @author Josué Tambwe
 * @date 18 March 2026
 */

 #pragma once

 #include "gap/GapInstance.hpp"
 #include "gap/Status.hpp"
 #include "gap/GapSolution.hpp"
 #include "configuration/Config.hpp"
 #include "utils/Logger.hpp"
 #include "utils/Timer.hpp"
 #include "metaheuristics/greedy/GreedyConstruction.hpp"
 #include "metaheuristics/greedy/GreedyLocalSearch.hpp"
 #include "output/OutputFormat.hpp"
 #include "utils/Logger.hpp"
 #include <iostream>
 #include <string>
 #include <cstdint>

 namespace gap{

    void runGreedy(gap::Params params);
 }

