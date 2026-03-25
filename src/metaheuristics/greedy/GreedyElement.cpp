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
 * @file GreedyElement.cpp
 * @author Josué Tambwe
 * @date 25 Feb 2026
 */

 #include "metaheuristics/greedy/GreedyElement.hpp"

 namespace gap::greedy{

    Element::Element(int id, float &score){
        this-> id = id;
        this -> score = score;
    }

    int Element::getId(){return id;}
    float Element::getScore(){return score;}
            
    bool Element::operator<(const Element &other) const{return score < other.score;}
 }
 
