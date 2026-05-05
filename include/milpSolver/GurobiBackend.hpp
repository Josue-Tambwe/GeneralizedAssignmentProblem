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
 #include <vector>
 #include <memory>
 #include <unordered_set>

 namespace gap{

    class GurobiBackend{

        private:

            std::unique_ptr<GRBEnv> env;
            std::unique_ptr<GRBModel> model;
            

        public:

            // constructors
            GurobiBackend();
            


            void buildIntegerModel(gap::GapInstance &instance); 
            void buildContinuousModel(gap::GapInstance &instance);

            void solveContinuousModel(); 
            void solveIntegerModel(double time_limit); 

            void addConstraints(gap::BaB::BaBNode &node);
            void setVariableToOne(int index);
            void setVariableToZero(int index);
            void clearModel();

            bool isInFeasible();
            bool isOptimal();
            bool isSubOptimal();
            bool isUnbounded();

            std::vector<double> getSolution();
            double getObjectiveValue();


            

    };
    


 }
#endif
 
