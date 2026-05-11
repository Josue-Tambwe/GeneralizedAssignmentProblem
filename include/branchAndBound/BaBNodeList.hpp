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
 * @file BaBNodeList.hpp
 * @brief Defines the data structure of the list of open nodes in the Branch and Bound algorithm
 * @class BaBNodeList
 * @author Josué Tambwe
 * @date 4 May 2026
 */

 #pragma once

 
 #include "branchAndBound/BaBNode.hpp"

 namespace gap::BaB{

    template <typename Strategy>

    class BaBNodeList{

        private:
            Strategy strategy; // BestFirstStrategy or DepthFirstStrategy

        public:

            // constructor
            BaBNodeList() = default;


            double getLowestDualBound() const {return strategy.getLowestDualBound();}

            gap::BaB::BaBNode pop(){return strategy.pop();}

            bool isEmpty() const {return strategy.isEmpty();}

            size_t getSize(){return strategy.getSize();}

            void add(gap::BaB::BaBNode node){strategy.add(node);}

            void print() const{strategy.print();}

    };


 }
 