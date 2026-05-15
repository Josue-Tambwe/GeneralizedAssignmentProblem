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
 * @file RunMilpSolver.hpp
 * @brief Defines functions for MIP resolution approch
 * @author Josué Tambwe
 * @date 14 May 2026
 */


 #pragma once

 #if USE_MILP

 #include "gap/GapInstance.hpp"
 #include "gap/GapSolution.hpp"
 #include "input/Parameters.hpp"
 #include "gap/Status.hpp"
 #include "utils/Logger.hpp"
 #include "utils/Timer.hpp"
 #include "output/OutputFormat.hpp"
 #include "configuration/Config.hpp"
 #include "branchAndBound/BaBUtils.hpp"
 #include "metaheuristics/greedy/GreedyConstruction.hpp"
 #include "metaheuristics/greedy/GreedyLocalSearch.hpp"
 #include <vector>

 #if HAS_GUROBI
 #include "milpSolver/GurobiBackend.hpp"
 #endif

 #if HAS_HEXALY
 #include "milpSolver/HexalyBackend.hpp"
 #endif

 #if HAS_HIGHS
 #include "milpSolver/HighsBackend.hpp"
 #endif


 namespace gap{

    const double tolerance = 1e-4;  // tolerance  on variables integrality


    /**
     * @brief generates an initial with greedy construction + local search
     */
    gap::GapSolution generateInitialSolution(gap::GapInstance &instance);




    /**
     * @brief convert a solution (GapSolution) into a 1D array in order to set an initial
     *        solution for a MILP solver (warm start)
     */
    std::vector<double> computeWarmStart(gap::GapSolution &solution);






    /**
     * @brief converts a 1D solution vector into the standard data solution for the GAP solver
     */
    void updateMilpSolution(std::vector<double> &sol, gap::GapSolution &solution);



    /**
     * @brief runs the MILP resolution without a warm start solution
     */

   template <typename Backend>

   void genericMilpWithoutWarmStart(gap::Params &params, Backend &solver){

         // initialization
         GapInstance instance(params);
         printHeaderMilp(params, instance);
         solver.buildIntegerModel(instance);
         Timer timer;
         Logger log;

         timer.start();
         solver.solveIntegerModel(params.time_limit);
         timer.stop();

         // feasibility test
         if(solver.isInFeasible()){

            log.warning("the problem is infeasible.");
            std::cout << " \n Processing time : " << timer.getElapsed() << " (s) \n\n" << std::endl;
            return;
         }

         // retrieving the model solution vector
         std::vector<double> sol = solver.getSolution();

         // integrality test
         if(gap::BaB::isInteger(sol)){

            GapSolution solution(instance);
            updateMilpSolution(sol, solution);

            if(!solution.isFeasible(instance)){
               log.warning("the solution found is infeasible.");
               std::cout << " \n Processing time : " << timer.getElapsed() << " (s) \n\n" << std::endl;
               return;
            }

            if(solver.isOptimal()){solution.setStatus(gap::Status::OPTIMAL);}
            else{solution.setStatus(gap::Status::FEASIBLE);}

            log.info("MILP solver algorithm completed. Final best known solution :");
            solution.print(instance);

            finalStatisticsMilp(0.0,
                                timer.getElapsed(),
                                solution.objectiveValue(instance),
                                solution.getStatus());
         }

         else{

            log.warning("the solver has not found an integer solution.");
            std::cout << " \n Processing time : " << timer.getElapsed() << " (s) \n\n" << std::endl;
            return; 
         }


   }






   /**
     * @brief runs the MILP resolution with a warm start solution
     */

   template <typename Backend>

   void genericMilpWithWarmStart(gap::Params &params, Backend &solver){

         // initialization
         GapInstance instance(params);
         printHeaderMilp(params, instance);
         solver.buildIntegerModel(instance);
         Timer timer;
         Logger log;

         timer.start();
         GapSolution solution = generateInitialSolution(instance);
         timer.stop();

         double preprocessing_time = timer.getElapsed();
         timer.reset();

         // case of a failed feasible primal solution
         if(!solution.isFeasible(instance)){
            log.warning("the computation of a warm start solution failed.");
         }

         else{
            std::vector<double> warm_start = computeWarmStart(solution);
            solver.setWarmStart(warm_start);
         }

         timer.start();
         solver.solveIntegerModel(params.time_limit);
         timer.stop();

         // feasibility test
         if(solver.isInFeasible()){
            log.warning("the problem is infeasible.");
            std::cout << " \n Processing time : " << timer.getElapsed() << " (s) \n\n" << std::endl;
            return;
         }

         // retrieving the model solution vector
         std::vector<double> sol = solver.getSolution();

         // integrality test
         if(gap::BaB::isInteger(sol)){

            GapSolution solution(instance);
            updateMilpSolution(sol, solution);

            if(!solution.isFeasible(instance)){
               log.warning("the solution found is infeasible.");
               std::cout << " \n Processing time : " << timer.getElapsed() << " (s) \n\n" << std::endl;
               return;
            }

            if(solver.isOptimal()){solution.setStatus(gap::Status::OPTIMAL);}
            else{solution.setStatus(gap::Status::FEASIBLE);}

            log.info("MILP solver algorithm completed. Final best known solution :");
            solution.print(instance);

            finalStatisticsMilp(preprocessing_time,
                                (timer.getElapsed() + preprocessing_time),
                                solution.objectiveValue(instance),
                                solution.getStatus());
      
         }

         else{

            log.warning("the solver has not found an integer solution.");
            std::cout << " \n Processing time : " << timer.getElapsed() << " (s) \n\n" << std::endl;
            return; 
         }


   }



    /**
     * @brief runs the MILP resolution
     */
    void runMilpSolver(gap::Params &params);





 }

 #endif

