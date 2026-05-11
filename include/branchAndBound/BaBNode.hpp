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
 * @file BaBNode.hpp
 * @brief Defines the structure of a Node in the Branch and Bound algorithm
 * @class BaBNode
 * @author Josué Tambwe
 * @date 4 May 2026
 */

 #pragma once

 #include <unordered_set>
 #include <iostream> // to remove



 namespace gap::BaB{

    class BaBNode{

        private: 

            double dual_bound; // The value of the linear relaxation
            std::unordered_set<int> fixed_to_one; // set of variable indexes fixed to  one
            std::unordered_set<int> fixed_to_zero; // set of variable indexes fixed to  zero

        public:

            // constructors

            BaBNode(double value);
            BaBNode(double value, BaBNode &other);


            // getters

            double getDualBound() const;

            std::unordered_set<int> getIndexesFixedToOne() const;

            std::unordered_set<int> getIndexesFixedToZero() const;


            // setters

            void fixToOne(int index);
            void fixToZero(int index);

            // operator overloading
            bool operator<(const BaBNode &other) const;


            void print() const;


    };



 }