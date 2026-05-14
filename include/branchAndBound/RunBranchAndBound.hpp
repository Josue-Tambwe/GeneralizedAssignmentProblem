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
 * @file RunBranchAndBound.hpp
 * @brief implements the Branch and Bound (B&B) algorithm
 * @author Josué Tambwe
 * @date 5 May 2026
 */

 #pragma once

 #if USE_BRANCH_AND_BOUND

 #include "gap/GapInstance.hpp"
 #include "gap/GapSolution.hpp"
 #include "input/Parameters.hpp"
 #include "gap/Status.hpp"
 #include "utils/Logger.hpp"
 #include "utils/Timer.hpp"
 #include "output/OutputFormat.hpp"
 #include "configuration/Config.hpp"
 #include "metaheuristics/greedy/GreedyConstruction.hpp"
 #include "metaheuristics/greedy/GreedyLocalSearch.hpp"
 #include "branchAndBound/BaBUtils.hpp"
 #include "branchAndBound/BestFirstStrategy.hpp"
  #include "branchAndBound/DepthFirstStrategy.hpp"
 #include "branchAndBound/BaBNodeList.hpp"

 #if HAS_GUROBI
 #include "milpSolver/GurobiBackend.hpp"
 #endif
 
 #if HAS_HIGHS
 #include "milpSolver/HighsBackend.hpp"
 #endif

 #include "milpSolver/LPSolver.hpp"
 #include <vector>
 #include <limits>




 namespace gap::BaB{



   /**
     * @brief initializes the primal solution for the Branch And Bound algorithm
     */
   gap::GapSolution initializePrimalSolution(gap::GapInstance &instance);





   /**
     * @brief initializes the primal bound
     */
   double setInitialPrimalBound(gap::GapSolution &primal_solution,
                                gap::GapInstance &instance);



    /**
     * @brief set the LP solver to use (Gurobi or Highs)
     */
    std::unique_ptr<LPSolver> setLPSolver(gap::Params &params);






    /**
     * @brief converts a 1D solution vector into the standard data solution for the GAP solver
     */
    void updateSolution(std::vector<double> &sol, gap::GapSolution &solution);





    /**
     * @brief builds the model for linear relaxation
     */
    std::unique_ptr<LPSolver> buildLinearModel(gap::Params &params,
                                                 gap::GapInstance &instance);





    /**
     * @brief runs the B&B algorithm with the best first node exploration strategy
     */
    void branchAndBoundBestFirst(gap::Params &params);





     /**
     * @brief runs the B&B algorithm with the depth first node exploration strategy
     */

    void branchAndBoundDepthFirst(gap::Params &params);



    /**
     * @brief defines the generic Branch And Bound Algorithm
     */
    void runBaB(gap::Params &params);


 }

 #endif

