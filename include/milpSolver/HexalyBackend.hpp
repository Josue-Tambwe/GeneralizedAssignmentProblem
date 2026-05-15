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
 * @file HexalyBackend.hpp
 * @brief Defines an API for the Hexaly backend
 * @class HexalyBackend
 * @author Josué Tambwe
 * @date 12 May 2026
 */


 #pragma once

 #if HAS_HEXALY

 #include "optimizer/hexalyoptimizer.h"
 #include "gap/GapInstance.hpp"
 #include "branchAndBound/BaBNode.hpp"
 #include <vector>


 namespace gap{

    class HexalyBackend{

        private : 
            hexaly::HexalyOptimizer optimizer;
            hexaly::HxModel model;
            std::vector<hexaly::HxExpression> variables;

        public :
            // constructor
            HexalyBackend();

            // destructor
            ~HexalyBackend() = default;

            void buildIntegerModel(gap::GapInstance &instance); 
            void solveIntegerModel(double time_limit);
            void setWarmStart(std::vector<double> &warm_start); 


            bool isInFeasible();
            bool isOptimal();


            std::vector<double> getSolution();
            double getObjectiveValue();


    };


 }

 #endif