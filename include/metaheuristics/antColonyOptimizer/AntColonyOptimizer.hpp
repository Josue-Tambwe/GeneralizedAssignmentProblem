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
 * @file AntColonyOptimizer.hpp
 * @brief implements the Ant Colony Optimizer with greedy Local Search
 * @author Josué Tambwe
 * @date 24 Mar 2026
 */
 #pragma once

 #include "hpc/cpu/Thread.hpp"
 #include "gap/GapInstance.hpp"
 #include "gap/GapSolution.hpp"
 #include <vector>
 #include <unordered_set>
 
 namespace gap::ACO{

    void assignFirstTaskRandomly(std::unordered_set<int> &tasks,
                                std::vector<int> &residual_capacity,
                                gap::GapSolution &solution,
                                gap::GapInstance &instance);

 }