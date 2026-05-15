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
 * @date 23 Feb 2026
 */
   
   #include "input/OptionsParser.hpp"
   #include "input/Algorithm.hpp"
   #include "configuration/Config.hpp"
   #include "metaheuristics/greedy/RunGreedy.hpp"
   #include "metaheuristics/antColonyOptimizer/RunAntColonyOptimizer.hpp"

   #if HAS_GUROBI
   #include "milpSolver/GurobiBackend.hpp"
   #endif

   #if HAS_HEXALY
   #include "milpSolver/HexalyBackend.hpp"
   #endif

   #if HAS_HIGHS
   #include "milpSolver/HighsBackend.hpp"
   #endif
   
   #if USE_BRANCH_AND_BOUND
   #include "milpSolver/LPSolver.hpp"
   #include "branchAndBound/RunBranchAndBound.hpp"
   #endif

   #if USE_MILP
   #include "milpSolver/RunMilpSolver.hpp"
   #endif


   using namespace gap; 

   int main(int argc, char** argv){

      Params params = parseOptions(argc, argv);

      if(params.algorithm == Algorithm::Greedy){runGreedy(params);}

      else if(params.algorithm == Algorithm::AntColonyOptimizer){ACO::runACO(params);}

      else if(params.algorithm == Algorithm::BranchAndBound){

         #if USE_BRANCH_AND_BOUND
         BaB::runBaB(params);
         #endif
      }

      else if(params.algorithm == Algorithm::Milp){
         #if USE_MILP
         //runGurobi(params);
         runMilpSolver(params);
         #endif
      }


      return 0;
   }