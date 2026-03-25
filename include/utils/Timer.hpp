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
 * @file Timer.hpp
 * @brief Management of time mesurement
 * 
 * This class defines how to mesure time during the computation
 * @author Josué Tambwe
 * @date 2 Mar 2026
 */
 
 #pragma once
 
 #include <chrono>

 namespace gap{

    class Timer{
        private : 
            bool running;
            std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
            double elapsed;

        public : 
            Timer();
            void start();
            void stop();
            void reset();
            double getElapsed();
            bool isRunning();
    };
 }