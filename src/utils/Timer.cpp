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
 * @file Timer.cpp
 * @author Josué Tambwe
 * @date 2 Mar 2026
 */

#include "utils/Timer.hpp"

namespace gap{

    Timer::Timer(): running(false), elapsed(0.0){}

    void Timer::start(){
        if (!running) { 
            running = true; 
            start_time = std::chrono::high_resolution_clock::now(); 
        }
    }

    void Timer::stop(){
        if (running) {
            elapsed += std::chrono::duration<double>( std::chrono::high_resolution_clock::now() - start_time ).count(); 
            running = false; 
        }
    }

    void Timer::reset(){
        running = false; 
        elapsed = 0.0;
    }

    double Timer::getElapsed(){
        if (running) { 
            return elapsed + std::chrono::duration<double>( std::chrono::high_resolution_clock::now() - start_time ).count(); 
        }
        else{return elapsed;}   
    }

    bool Timer::isRunning(){
        return running;
    }
 }