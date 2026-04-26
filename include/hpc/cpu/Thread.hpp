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
 * @file Thread.hpp
 * @brief  Defines functions for using simultaneous multi-threading on CPU
 * @author Josué Tambwe
 * @date 16 Mar 2026
 */

 #pragma once
 
 #include <thread>
 #include <random>
 
 namespace gap{

    /** 
     * @brief computes the starting index of the chunck for a thread within
     *        a vector of work items
    */
    int start_index(int id, int work_size, int nb_threads);


    /** 
    * @brief computes the ending index of the chunck for a thread within
    *        a vector of work items
    */
    int end_index(int id, int work_size, int nb_threads);
    

    /** 
    * @brief creates a local random number generator for a thread within its scope
    *        
    */
    std::mt19937& getThreadLocalRng();
 }