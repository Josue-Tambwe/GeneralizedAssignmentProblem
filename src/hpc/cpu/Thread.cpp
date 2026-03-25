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

 #include "hpc/cpu/Thread.hpp"
 

 namespace gap{

    int start_index(int id, int work_size, int nb_threads){
        int base = work_size / nb_threads;
        int rest = work_size % nb_threads;
        int start;

        if (id < rest) {start = id * (base + 1);} 
        else {start = rest * (base + 1) + (id - rest) * base;}
        return start;
    }

    int end_index(int id, int work_size, int nb_threads){
        int base = work_size / nb_threads;
        int rest = work_size % nb_threads;
        int block_size;

        if (id < rest) {block_size = base + 1;}
        else {block_size = base;}

        int end = start_index(id, work_size, nb_threads) + block_size - 1;
        if (end >= work_size) {end = work_size - 1;}
        return end; 
    }

    // create a local random number generator for a thread within its scope
    std::mt19937& getThreadLocalRng() {
        thread_local std::mt19937 gen(
            std::hash<std::thread::id>{}(std::this_thread::get_id())
        );
    return gen;
}


 }