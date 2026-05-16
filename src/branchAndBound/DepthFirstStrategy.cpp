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
 * @file DepthFirstStrategy.cpp
 * @author Josué Tambwe
 * @date 4 May 2026
 */

 #include "branchAndBound/DepthFirstStrategy.hpp"


 namespace gap::BaB{

    double DepthFirst::getLowestDualBound() const {

        double dual_bound = node_list.top().getDualBound();
        std::stack<gap::BaB::BaBNode> copy = node_list;

        while(!copy.empty()){

            BaBNode current_node = copy.top();
            
            if(current_node.getDualBound() < dual_bound){

                dual_bound = current_node.getDualBound();
            }
            copy.pop();

        }
        return dual_bound;
    }


    gap::BaB::BaBNode DepthFirst::pop(){

        gap::BaB::BaBNode element = node_list.top();
        node_list.pop();
        return element;
    }


    bool DepthFirst::isEmpty() const {return node_list.empty();}


    size_t DepthFirst::getSize() const{return node_list.size();}
    

    void DepthFirst::add(gap::BaB::BaBNode node){node_list.push(node);}


    void DepthFirst::print() const{

        int counter = 0;
        std::stack<gap::BaB::BaBNode> copy = node_list;

        while(!copy.empty()){

            counter += 1;
            std::cout << " node id : " << counter << " --- ";
            BaBNode node = copy.top();
            node.print();
            copy.pop();
        }
    }
 }