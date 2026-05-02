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
 * @author Josué Tambwe
 * @date 18 Mar 2026
 */
 
 #include "metaheuristics/greedy/RunGreedy.hpp"
 
 namespace gap{

   void runGreedy(Params params){

      GapInstance instance(params);
      printHeader();
      printHeaderGreedy(params, instance);

      gap::Timer timer = Timer();
      gap::Logger log;

      // construction
      timer.start();
      GapSolution solution = greedy::construction(params, instance);
      timer.stop();

      double construction_time = timer.getElapsed();
      gap::Status construction_status = solution.getStatus();

      if(construction_status != gap::Status::FEASIBLE && construction_status != gap::Status::OPTIMAL){

        log.warning("the greedy construction heuristic failed.");
        std::cout << " Processing time : " << construction_time << " (s) \n" << std::endl;
        return;

      }else{

        std::int64_t construction_value = solution.objectiveValue(instance);
        log.info("the greedy construction heuristic succeed !");
        timer.reset();
        if(params.verbose){solution.print(instance);}

        // local search
        timer.start();
        greedy::localSearch(params, solution, instance);
        gap::Status local_search_status = solution.getStatus();
        timer.stop();
        double local_search_time = timer.getElapsed();
        timer.reset();

        if(local_search_status != gap::Status::FEASIBLE && local_search_status != gap::Status::OPTIMAL){


          log.warning("the local search improvement failed.");
          std::cout << " Processing time : " << local_search_time << " (s) \n" << std::endl;
          return;

        }else{

          log.info("the local search has been performed successfuly !");
          std::int64_t local_search_value = solution.objectiveValue(instance);
          std::cout << "\n" << std::endl;
        log.info("Greedy algorithm completed. Final best known solution :");
          solution.print(instance);
          
          finalStatisticsGreedy(construction_time,
                           construction_value,
                           construction_status,
                           local_search_time,
                           local_search_value,
                           local_search_status);
        }
        
      }
      

   }

   
 }
