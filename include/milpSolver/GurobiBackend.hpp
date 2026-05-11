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
 * @brief Defines an API for the Gurobi backend
 * @class GurobiBackend
 * @author Josué Tambwe
 * @date 4 May 2026
 */


 #pragma once

 #if HAS_GUROBI

 #include "gurobi_c++.h"
 #include "gap/GapInstance.hpp"
 #include "branchAndBound/BaBNode.hpp"
 #include "milpSolver/MilpSolver.hpp"
 #include <vector>
 #include <memory>
 #include <unordered_set>

 namespace gap{

    class GurobiBackend : public MilpSolver{

        private:

            std::unique_ptr<GRBEnv> env;
            std::unique_ptr<GRBModel> model;
            std::vector<GRBVar> variables;
            

        public:

            // constructors
            GurobiBackend();

            // destruction
             ~GurobiBackend() = default;
            


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
 
