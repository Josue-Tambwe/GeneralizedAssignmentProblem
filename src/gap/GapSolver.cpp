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
   #include "metaheuristics/greedy/RunGreedy.hpp"

   using namespace gap; 

   int main(int argc, char** argv){

      Params params = parseOptions(argc, argv);

      runGreedy(params);

      return 0;
   }