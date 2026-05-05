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

    template <typename Backend>

    class MilpSolver{

        private:

            Backend backend;

        public:

            // constructor
            MilpSolver() = default;



            void buildContinuousModel(gap::GapInstance &instance){

                backend.buildContinuousModel(instance);
            }


            void buildIntegerModel(gap::GapInstance &instance){

                backend.buildIntegerModel(instance);
            } 


            void solveContinuousModel(){backend.solveContinuousModel();}


            void solveIntegerModel(double time_limit){

                backend.solveIntegerModel(time_limit);
            } 


            void addConstraints(gap::BaB::BaBNode &node){

                backend.addConstraints(node);
            }


            void setVariableToOne(int index){backend.setVariableToOne(index);}


            void setVariableToZero(int index){backend.setVariableToZero(index);}


            void clearModel(){backend.clearModel();}


            bool isInFeasible(){return backend.isInFeasible();}


            bool isOptimal(){return backend.isOptimal();}


            bool isSubOptimal(){return backend.isSubOptimal();}


            bool isUnbounded(){return backend.isUnbounded();}


            std::vector<double> getSolution(){return backend.getSolution();}


            double getObjectiveValue(){return backend.getObjectiveValue();}

    };

 }

