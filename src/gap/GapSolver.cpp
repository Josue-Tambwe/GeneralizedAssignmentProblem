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
   #include "metaheuristics/greedy/RunGreedy.hpp"
   #include "metaheuristics/antColonyOptimizer/RunAntColonyOptimizer.hpp"
   #include "milpSolver/GurobiBackend.hpp"
   #include "milpSolver/MilpSolver.hpp"
   #include <iostream> // to remove

   using namespace gap; 

   int main(int argc, char** argv){

      Params params = parseOptions(argc, argv);

      GapInstance instance(params);
      //GurobiBackend gurobi;
      MilpSolver <GurobiBackend> gurobi;
      gurobi.buildContinuousModel(instance);
      gurobi.solveContinuousModel();
      std::cout << " \n Solution LP : " << gurobi.getObjectiveValue() << "\n " << std::endl;


      gurobi.clearModel();
      gurobi.buildIntegerModel(instance);
      gurobi.solveIntegerModel(60.0);
      std::cout << " \n Solution IP : " << gurobi.getObjectiveValue() << "\n " << std::endl;


      //if(params.algorithm == Algorithm::Greedy){runGreedy(params);}

      //if(params.algorithm == Algorithm::AntColonyOptimizer){ACO::RunACO(params);}



      return 0;
   }