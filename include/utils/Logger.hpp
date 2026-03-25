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
 * @file Logger.hpp
 * @brief Management of logging messages 
 * @class Logger
 * This class defines the methods  used to print formatted
 * log messages to the standard output and standard error streams.
 * @author Josué Tambwe
 * @date 23 Feb 2026
 */


#pragma once

#include "output/OutputConfig.hpp"
#include <iostream>
#include <string>

namespace gap{ 

class Logger{
    public : 
        Logger() = default;
        void info(const std::string &message);
        void warning(const std::string &message);
        void error(const std::string &message);
};
}