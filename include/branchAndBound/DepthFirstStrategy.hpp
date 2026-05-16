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
 * @file DepthFirstStrategy.hpp
 * @brief Defines the data structure of the depth-first node selection strategy in the Branch and Bound algorithm
 * @class DepthFirst
 * @author Josué Tambwe
 * @date 4 May 2026
 */


 #pragma once

 #include "branchAndBound/BaBNode.hpp"
 #include <stack>
 #include <iostream>


 namespace gap::BaB{

    class DepthFirst{

        private:
            std::stack<gap::BaB::BaBNode> node_list; // list of open nodes

        public:

            // constructor
            DepthFirst() = default;

            double getLowestDualBound() const;

            gap::BaB::BaBNode pop();

            bool isEmpty() const;

            size_t getSize() const;
            
            void add(gap::BaB::BaBNode node);


            void print() const;
    };

 }