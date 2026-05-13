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
 #include "milpSolver/MilpSolver.hpp"
 #include <vector>


 namespace gap{

    class HexalyBackend : public MilpSolver{

        private : 
            hexaly::HexalyOptimizer optimizer;
            hexaly::HxModel model;
            std::vector<hexaly::HxExpression> variables;

        public :
            // constructor
            HexalyBackend();

            // destructor
            ~HexalyBackend() = default;

            void buildIntegerModel(gap::GapInstance &instance) override; 
            void buildContinuousModel(gap::GapInstance &instance) override;


            void solveContinuousModel() override; 
            void solveIntegerModel(double time_limit) override; 


            void addConstraints(gap::BaB::BaBNode &node) override;
            void resetLinearModel() override;


            bool isInFeasible() override;
            bool isOptimal() override;
            bool isSubOptimal() override;
            bool isUnbounded() override;

            std::vector<double> getSolution() override;
            double getObjectiveValue() override;




    };


 }

 #endif