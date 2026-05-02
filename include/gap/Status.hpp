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
 * @file Status.hpp
 * @brief Defines status of instances and solutions of the Generalized Assignment Problem
 * @author Josué Tambwe
 * @date 25 Feb 2026
 */

 #pragma once 

 #include "output/OutputConfig.hpp"
 #include <ostream>

 namespace gap{

    
    enum Status{
        FEASIBLE,
        INFEASIBLE,
        OPTIMAL,
        UNKNOWN,
    };

    std::ostream& operator<<(std::ostream &output_stream, const Status &status);
     
 }

 