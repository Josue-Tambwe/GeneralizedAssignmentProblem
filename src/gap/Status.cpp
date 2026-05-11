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
 * @file GapInstance.cpp
 * @author Josué Tambwe
 * @date 25 Feb 2026
 */
 #include "gap/Status.hpp"

 namespace gap{
    
    std::ostream& operator<<(std::ostream &output_stream, const gap::Status &status){
        switch(status){
            case FEASIBLE : 
                output_stream << GREEN << "Feasible" << RESET;
                return output_stream;
            case OPTIMAL : 
                output_stream << BRIGHT_CYAN << "Optimal" << RESET ;
                return output_stream;
            case INFEASIBLE : 
                output_stream << RED << "Infeasible" << RESET ;
                return output_stream;
            default : 
                output_stream << RED << "Unkwon" << RESET;
                return output_stream;
        }
    }
     
 }

 