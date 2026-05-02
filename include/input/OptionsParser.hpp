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
 * @file ParseOptions.hpp
 * @brief Parses the options and flags defines by the user
 * @author Josué Tambwe
 * @date 11 Mar 2026
 */

 #pragma once

 #include "Parameters.hpp"
 #include "Algorithm.hpp"
 #include "utils/Logger.hpp"
 #include "configuration/Config.hpp"
 #include "output/OutputConfig.hpp"
 #include "output/OutputFormat.hpp"
 #include <iostream>
 #include <string>

 namespace gap{

   /**
    * @brief checks that all required options has been given by the user
    */
   void checkRequiredOptions(int argc, char** argv, gap::Params &params);

   

   /**
    * @brief performs the parsing of all options given by the user
    */
   gap::Params parseOptions(int argc, char** argv);

 }