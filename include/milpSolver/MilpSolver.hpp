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
 * @file GurobiBackend.hpp
 * @brief Defines a generic class for MILP solvers backend
 * @class MilpSolver
 * @author Josué Tambwe
 * @date 5 May 2026
 */


 #pragma once

 #include "gap/GapInstance.hpp"
 #include "branchAndBound/BaBNode.hpp"
 #include <vector>

 namespace gap{


    class MilpSolver{

        public:

            // destructor
            virtual ~MilpSolver() = default;

            virtual void buildContinuousModel(gap::GapInstance &instance) = 0;
            virtual void buildIntegerModel(gap::GapInstance &instance) = 0;
            virtual void solveContinuousModel() = 0;
            virtual void solveIntegerModel(double time_limit) = 0;


            virtual void addConstraints(gap::BaB::BaBNode &node) = 0;
            virtual void resetLinearModel() = 0;


            virtual bool isInFeasible() = 0;
            virtual bool isOptimal() = 0;
            virtual bool isSubOptimal() = 0;
            virtual bool isUnbounded() = 0;


            virtual std::vector<double> getSolution() = 0;
            virtual double getObjectiveValue() = 0;


    };


 }


