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
        if(value == "antColony"){return gap::Algorithm::AntColonyOptimizer;}
        if(value == "BandB"){return gap::Algorithm::BranchAndBound;}
        else{return gap::Algorithm::Unknown;}
    }

    std::ostream& operator<<(std::ostream& output_stream, Algorithm algo) {

        switch (algo) {
            case Algorithm::Greedy:  output_stream << "Greedy"; break;
            case Algorithm::AntColonyOptimizer:  output_stream << "Ant Colony Optimizer"; break;
            case Algorithm::BranchAndBound:   output_stream << "Branch and Bound"; break;
            default : output_stream << "Branch and Bound"; break;
        }
        return output_stream;
    }
 }