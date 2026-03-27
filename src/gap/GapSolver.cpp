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

      //if(HAS_X86){std::cout << " J'ai x86" << std::endl;}
      //if(HAS_SSE){std::cout << " J'ai SSE" << std::endl;}
      //if(HAS_FMA){std::cout << " J'ai FMA" << std::endl;}
      //if(HAS_AVX512F){std::cout << " J'ai AVX512" << std::endl;}
      //if(HAS_AVX512FMA){std::cout << " J'ai AVX512FMA" << std::endl;}
      //if(HAS_ARMV8){std::cout << " J'ai ARMV8" << std::endl;}
      
      return 0;
   }