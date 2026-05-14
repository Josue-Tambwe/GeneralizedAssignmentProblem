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
 * @file Logger.cpp
 * @author Josué Tambwe
 * @date 23 Feb 2026
 */

#include "utils/Logger.hpp"

namespace gap{ 

/**
 * @brief Prints an informational message to the standard output.
 * @param message The message to display.
 */

void Logger::info(const std::string &message){
    std::cout << GREEN << "    [INFO]" << RESET << " : " << message <<  "\n" << std::endl;
}

void Logger::warning(const std::string &message){
    std::cout <<  YELLOW << " [WARNING]" << RESET << " : " << message << "\n" << std::endl;
}

/**
 * @brief Prints an error message and throws a runtime exception.
 * @param message The error message to display before throwing.
 */

void Logger::error(const std::string &message){
    std::cout << "\n";
    std::cerr << RED << "   [ERROR]" << RESET << " : " << message << "\n" << std::endl;
    std::exit(1);
}
}