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
 * @file RunAntColonyOptimizer.hpp
 * @brief implements the Ant Colony Optimizer with greedy Local Search (balance move + cheap move)
 * @author Josué Tambwe
 * @date 24 Mar 2026
 */
 
 #pragma once

 #include "hpc/cpu/Thread.hpp"
 #include "gap/GapInstance.hpp"
 #include "gap/GapSolution.hpp"
 #include "input/Parameters.hpp"
 #include "gap/Status.hpp"
 #include "utils/Logger.hpp"
 #include "utils/Timer.hpp"
 #include "configuration/Config.hpp"
 #include "output/OutputFormat.hpp"
 #include "metaheuristics/antColonyOptimizer/AcoUtils.hpp"
 #include "metaheuristics/antColonyOptimizer/AntConstruction.hpp"
 #include "metaheuristics/antColonyOptimizer/PheromonesUpdate.hpp"
 #include <vector>
 #include <unordered_set>
 #include <cmath>
 #include <cstdint>
 
 namespace gap::ACO{


   /**
    * @brief return the best ant (elite) within the colony
    */
    gap::GapSolution& findBestAnt(std::int64_t &best_value,
                                  std::int64_t &worst_value,
                                  std::int64_t &cumulative_score,
                                  std::vector<gap::GapSolution> &colony,
                                  gap::GapInstance &instance);




    /**
    * @brief runs the Ant Colony Optimizer for the GAP solver
    */
    void runACO(gap::Params &params);
                                    

 }