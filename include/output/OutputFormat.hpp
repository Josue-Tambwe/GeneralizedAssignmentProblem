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

 #include "gap/Status.hpp"
 #include "output/OutputConfig.hpp"
 #include "configuration/Config.hpp"
 #include "input/Parameters.hpp"
 #include "gap/GapInstance.hpp"
 #include <iostream>
 #include <iomanip>
 #include <cstdlib>
 #include <cstdint>



 namespace gap{


    void printHeader();

    void printUsage();

    void printRequiredOptions();

    void printOptionalOptions();

    void printExampleRun();

    void printHelp();

    void printHeaderGreedy(gap::Params& params,
                           gap::GapInstance &instance);


    void finalStatisticsGreedy(double construction_time,
                        std::int64_t construction_value,
                        gap::Status &construction_status,
                        double local_time,
                        std::int64_t local_search_value,
                        gap::Status &local_search_status);


    void printHeaderACO(gap::Params& params,
                        gap::GapInstance &instance);


   void printACOLine(double time,
                     int iteration,
                     std::int64_t best_ant,
                     std::int64_t global_best,
                     const std::string& info);

      
 }