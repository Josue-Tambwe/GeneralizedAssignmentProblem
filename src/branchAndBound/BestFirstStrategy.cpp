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
 * @file BestFirstStrategy.cpp
 * @author Josué Tambwe
 * @date 4 May 2026
 */

 #include "branchAndBound/BestFirstStrategy.hpp"


 namespace gap::BaB{

    double BestFirst::getLowestDualBound() const {

        if(!node_list.empty()){
            return node_list.top().getDualBound();
        }

        return std::numeric_limits<double>::max();
    }


    gap::BaB::BaBNode BestFirst::pop(){

        gap::BaB::BaBNode element = node_list.top();
        node_list.pop();
        return element;
    }


    bool BestFirst::isEmpty() const{return node_list.empty();}

    void BestFirst::add(gap::BaB::BaBNode node){node_list.push(node);}

 }
