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
 * @file Algorithm.hpp
 * @brief Defines all algorithm options than can be used in a command from the standard input
 * @author Josué Tambwe
 * @date 08 Mar 2026
 */

#pragma once

#include <ostream>

namespace gap {

enum  Algorithm {
    Greedy,
    AntColonyOptimizer,
    BranchAndBound,
    Milp,
    Unknown,
};

gap::Algorithm parseAlgorithm(std::string value);

inline std::ostream& operator<<(std::ostream& output_stream, Algorithm algo);

}
