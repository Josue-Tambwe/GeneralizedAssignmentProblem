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



    void updateMilpSolution(std::vector<double> &sol, gap::GapSolution &solution){

        std::vector<int>& solution_vector =  solution.getSolutionVector();

        for(size_t k = 0; k < sol.size(); k++){

            if(std::abs(1.0 - sol[k]) < tolerance){

                int agent = gap::BaB::convertTo2DAgentIndex(k, solution_vector.size());
                int task = gap::BaB::convertTo2DTaskIndex(k, solution_vector.size());

                solution_vector[task] = agent;

            }
        }

    }





    void runMilpSolver(gap::Params &params){

        printHeader();

        if(params.milp_solver == 'g'){
            GurobiBackend gurobi;
            if(params.warm_start){genericMilpWithWarmStart(params, gurobi);}
            else{genericMilpWithoutWarmStart(params, gurobi);}
            
        }

        else if(params.milp_solver == 'h'){
            HighsBackend highs;
            if(params.warm_start){genericMilpWithWarmStart(params, highs);}
            else{genericMilpWithoutWarmStart(params, highs);}
        
        }

        else{
            HexalyBackend hexaly;
            if(params.warm_start){genericMilpWithWarmStart(params, hexaly);}
            else{genericMilpWithoutWarmStart(params, hexaly);}
        }

    }



 }

 #endif
