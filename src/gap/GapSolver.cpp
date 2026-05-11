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
   #include "milpSolver/GurobiBackend.hpp"
   #include "milpSolver/MilpSolver.hpp"
   #include "branchAndBound/RunBranchAndBound.hpp"


   #include <iostream> // to remove

   #include "branchAndBound/BaBNodeList.hpp" // to remove
   #include "branchAndBound/DepthFirstStrategy.hpp" // to remove
   #include "branchAndBound/BestFirstStrategy.hpp" // to remove
   #include "branchAndBound/BaBNode.hpp" // to remove


   using namespace gap; 

   int main(int argc, char** argv){

      Params params = parseOptions(argc, argv);

      GapInstance instance(params);

      //std::unique_ptr<MilpSolver> solver = std::make_unique<GurobiBackend>();
      //solver->buildIntegerModel(instance);
      //solver->solveIntegerModel(20.0);
      //std::cout << " \n Solution IP 1 : " << solver->getObjectiveValue() << "\n " << std::endl;

   

      gap::BaB::BaBNode n1(3.0);
      for(int i = 0; i < 9; i++){
         if(i % 2 == 0){n1.fixToOne(i);}
         else{n1.fixToZero(i);}
      }

      gap::BaB::BaBNode n2(12.0);
      for(int i = 10; i < 19; i++){
         if(i % 2 == 0){n2.fixToOne(i);}
         else{n2.fixToZero(i);}
      }

      gap::BaB::BaBNode n3(10.0);
      for(int i = 20; i < 29; i++){
         if(i % 2 == 0){n3.fixToOne(i);}
         else{n3.fixToZero(i);}
      }

      gap::BaB::BaBNode n4(16.0);
      for(int i = 30; i < 39; i++){
         if(i % 2 == 0){n4.fixToOne(i);}
         else{n4.fixToZero(i);}
      }

      gap::BaB::BaBNodeList<gap::BaB::BestFirst> list;
      list.add(n1);
      list.add(n2);
      list.add(n3);
      list.add(n4);

      //list.print();

      //std::cout << " lowest dual bound : " << list.getLowestDualBound() << " \n \n";
      
      //std::cout << " size : " << list.getSize();



      gap::BaB::test(params);









      //if(params.algorithm == Algorithm::Greedy){runGreedy(params);}

      //if(params.algorithm == Algorithm::AntColonyOptimizer){ACO::RunACO(params);}

      
      



      return 0;
   }