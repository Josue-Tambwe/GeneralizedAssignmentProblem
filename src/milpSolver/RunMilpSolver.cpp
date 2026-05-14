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
 * @file RunMilpSolver.cpp
 * @author Josué Tambwe
 * @date 14 May 2026
 */

 #if USE_MILP

 #include "milpSolver/RunMilpSolver.hpp"


 namespace gap{


    gap::GapSolution generateInitialSolution(gap::GapInstance &instance){

        // construction
        gap::GapSolution initial_solution = gap::greedy::constructionRiskyTasks(instance);

        // local search
        gap::greedy::balanceMove(initial_solution, instance);
        gap::greedy::cheapMove(NUMBER_PHYSICAL_CORES, initial_solution, instance);

        return initial_solution;

    }


    std::vector<double> computeWarmStart(gap::GapSolution &solution){

        std::vector<double> warm_start(solution.getNbAgent() * solution.getNbTask(), 0.0);
        std::vector<int>& solution_vector =  solution.getSolutionVector();

        int nb_task = static_cast<int>(solution.getNbTask());

        for(int task = 0; task < nb_task; task++){

            int agent = solution_vector[task];
            warm_start[(agent * nb_task) + task] = 1.0;
        }

        return warm_start;
    }


    void runGurobi(gap::Params &params){

        GapInstance instance(params);
        HighsBackend gurobi;
        gurobi.buildIntegerModel(instance);
        Timer timer;

        // without warm start
        if(!params.warm_start){

            timer.start();
            gurobi.solveIntegerModel(params.time_limit);
            timer.stop();

            std::cout << "\n z = " << gurobi.getObjectiveValue() 
                      << " time : " << timer.getElapsed() << " (s) \n \n";

            
        }
        else{

            timer.start();
            GapSolution solution = generateInitialSolution(instance);
            timer.stop();

            double preprocessing_time = timer.getElapsed();
            timer.reset();

            std::vector<double> warm_start = computeWarmStart(solution);
            gurobi.setWarmStart(warm_start);

            timer.start();
            gurobi.solveIntegerModel(params.time_limit);
            timer.stop();

            std::cout << "\n  preprocessing time " << preprocessing_time  << " (s) \n \n";
            std::cout << " z = " << gurobi.getObjectiveValue() 
                      << " time : " << timer.getElapsed() << " (s) \n \n";

        }
    }


 }

 #endif
