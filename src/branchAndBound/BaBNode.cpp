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
 * @file BaBNode.cpp
 * @author Josué Tambwe
 * @date 4 May 2026
 */

 #include "branchAndBound/BaBNode.hpp"


 namespace gap::BaB{

    // constructors

    BaBNode::BaBNode(double value): dual_bound(value){}

    BaBNode::BaBNode(double value, BaBNode &other):dual_bound(value)
        {
         this->fixed_to_one = other.getIndexesFixedToOne();
         this->fixed_to_zero = other.getIndexesFixedToZero();
        }


    // getters

    double BaBNode::getDualBound() const {return dual_bound;}

    std::unordered_set<int> BaBNode::getIndexesFixedToOne() const{return fixed_to_one;}

    std::unordered_set<int> BaBNode::getIndexesFixedToZero() const {return fixed_to_zero;}


    // setters

    void BaBNode::fixToOne(int index){fixed_to_one.insert(index);}

    void BaBNode::fixToZero(int index){fixed_to_zero.insert(index);}

    // operator overloading
    bool BaBNode::operator<(const BaBNode &other) const {return dual_bound > other.dual_bound;}


    void BaBNode::print() const{

        std::cout << " dual bound : " << dual_bound << "  ---  ones : [ ";
        for(int index : fixed_to_one){std::cout << index << " ";}
        std::cout << "] --- zeros : [ ";
        for(int index : fixed_to_zero){std::cout << index << " ";}
        std::cout << "] \n" << std::endl;
    }



 }