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
 * @file OutputFormat.hpp
 * @brief Defines output format and manipulation in the standard output strean
 * @author Josué Tambwe
 * @date 17 March 2026
 */

 #pragma once

 #include <iostream>
 #include <iomanip>
 #include <cstdlib>
 #include <cstdint>

 using std::setw;
 using std::left;
 using std::right;

 namespace gap{
 

    static constexpr const char* GREEN  = "\033[32m";
    static constexpr const char* BLUE = "\033[34m";
    static constexpr const char* YELLOW = "\033[33m";
    static constexpr const char* BRIGHT_YELLOW  = "\033[93m";
    static constexpr const char* RED    = "\033[31m";
    static constexpr const char* MAGENTA = "\033[35m";
    static constexpr const char* CYAN    = "\033[36m";
    static constexpr const char* BRIGHT_CYAN    = "\033[96m";
    static constexpr const char* RESET  = "\033[0m";


 }