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
 * @file HighsBackend.hpp
 * @brief Defines an API for the Highs backend
 * @class HighsBackend
 * @author Josué Tambwe
 * @date 14 May 2026
 */


 #pragma once

 #if HAS_HIGHS

 #include "Highs.h"
 #include "gap/GapInstance.hpp"
 #include "branchAndBound/BaBNode.hpp"
 #include "milpSolver/MilpSolver.hpp"
 #include <vector>
 #include <memory>


 namespace gap{

    class HighsBackend{

        private : 

            Highs optimizer;
            //HighsModel model;
            std::vector<HighsInt> variables;


        public : 

            // constructor
            HighsBackend(){optimizer.setOptionValue("log_to_console", false);};

            // destructor 
            ~HighsBackend() = default;


            void solveIntegerModel(double time_limit); 
            void buildIntegerModel(gap::GapInstance &instance);
            
            bool isInFeasible();
            bool isOptimal();

            std::vector<double> getSolution();
            double getObjectiveValue();



    };


 }

 #endif