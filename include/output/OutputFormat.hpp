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
 #include "utils/Timer.hpp"
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

   void printHeaderGreedy(gap::Params &params,
                           gap::GapInstance &instance);


   void finalStatisticsGreedy(double construction_time,
                        std::int64_t construction_value,
                        gap::Status &construction_status,
                        double local_time,
                        std::int64_t local_search_value,
                        gap::Status &local_search_status);


   void printHeaderACO(gap::Params &params,
                        gap::GapInstance &instance);



   void printHeaderLineACO();


   void printACOIteration(int iteration,
                           double time,
                           std::int64_t worst,
                           std::int64_t cumulative_score,
                           std::int64_t local_best,
                           std::int64_t global_best,
                           bool improvement,
                           gap::Params &params);


   void finalStatisticsACO(double preprocessing_time,
                            int iteration,
                            std::int64_t obj_value,
                            gap::Status status,
                            gap::Timer &timer,
                            gap::Params &params);




    void printHeaderBaB(gap::Params& params,
                        gap::GapInstance &instance);
                        


  void printHeaderLineBaB();



  void printBaBIteration(double time,
                         size_t processed_nodes,
                         size_t open_nodes,
                         double dual_bound,
                         double primal_bound);



  void finalStatisticsBaB(double preprocessing_time,
                                double preprocessing_obj_value,
                                double dual_bound,
                                double primal_bound,
                                double total_time,
                                gap::Status status,
                                size_t processed_nodes,
                                size_t open_nodes,
                                size_t nodes_fathomed_by_optimality,
                                size_t nodes_fathomed_by_dominance,
                                size_t nodes_fathomed_by_infeasibility,
                                gap::Params &params);



  void printHeaderMilp(gap::Params &params,
                       gap::GapInstance &instance);


  
  void finalStatisticsMilp(double preprocessing_time,
                           double total_time,
                           std::int64_t obj_value,
                           gap::Status status);

      
 }