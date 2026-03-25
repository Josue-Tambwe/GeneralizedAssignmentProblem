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
 * @file GreedyElement.hpp
 * @class Element
 * @brief Represents an agent or task of an instance of the Generalized Assignment Problem
 * @author Josué Tambwe
 * @date 25 Feb 2026
 */

 #pragma once

 namespace gap::greedy{
    class Element{
        private:
            int id;
            float score;
        public:
            Element(int id, float &score);
            // getters
            int getId();
            float getScore();
            
            bool operator<(const Element &other) const;

    };
 }
 
