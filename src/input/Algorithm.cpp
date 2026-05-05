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

 #include "input/Algorithm.hpp"
 
 namespace gap{

    gap::Algorithm parseAlgorithm(std::string value){

        if(value == "greedy"){return gap::Algorithm::Greedy;}
        if(value == "aco"){return gap::Algorithm::AntColonyOptimizer;}
        if(value == "bab"){return gap::Algorithm::BranchAndBound;}
        if(value == "milp"){return gap::Algorithm::Milp;}
        else{return gap::Algorithm::Unknown;}
    }

    std::ostream& operator<<(std::ostream& output_stream, Algorithm algo) {

        switch (algo) {
            case Algorithm::BranchAndBound:  output_stream << "Branch and Bound"; break;
            case Algorithm::AntColonyOptimizer:  output_stream << "Ant Colony Optimizer"; break;
            case Algorithm::Milp:   output_stream << "Milp Solver"; break;
            default : output_stream << "Greedy"; break;
        }
        return output_stream;
    }
 }