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
 * @file HexalyBackend.cpp
 * @author Josué Tambwe
 * @date 12 May 2026
 */

 #if HAS_HEXALY

 #include "milpSolver/HexalyBackend.hpp"

 namespace gap{

    // constructor
    HexalyBackend::HexalyBackend():
        optimizer(),
        model(optimizer.getModel()){}


    void HexalyBackend::solveIntegerModel(double time_limit){

        optimizer.getParam().setTimeLimit(time_limit);
        optimizer.solve();
    }


    void GurobiBackend::buildIntegerModel(gap::GapInstance &instance){

        // initialization of decision variables vector
        variables.resize(instance.getNbAgent() * instance.getNbTask());

        for(size_t i = 0; i < variables.size(); i++){

            // adding variables  to the model
            variables[i] = model.boolVar();
        }

        // objective function
        HxExpression obj = model.sum();

        const std::vector<std::vector<int>> & cost_matrix = instance.getCost();

        for(size_t i = 0; i < instance.getNbAgent(); i++){

            for(size_t j = 0; j < instance.getNbTask(); j++){

                HxExpression expr = cost_matrix[i][j] * variables[(i * instance.getNbTask() + j)];
                obj.addOperand(expr);
            }

        }

        // adding the objective expression to the model
        model.minimize(obj);


        // assignment constraints 
        for(size_t j = 0; j < instance.getNbTask(); j++){

            HxExpression assignment_constraint = model.sum();

            for(size_t i = 0; i < instance.getNbAgent(); i++){

                HxExpression constraint_expr = variables[(i * instance.getNbTask() + j)];
                assignment_constraint.addOperand(constraint_expr);

            }
            // adding the constraint expression to the model
            model.constraint(assignment_constraint == 1);
        }


        const std::vector<std::vector<int>>& weight_matrix = instance.getWeight();
        const std::vector<int>& capacity_vector = instance.getCapacity();

        // capacity constraints
        for(size_t i = 0; i < instance.getNbAgent(); i++){

            HxExpression capacity_constraint = model.sum();

            for(size_t j = 0; j < instance.getNbTask(); j++){

                HxExpression constraint_expr = weight_matrix[i][j] * variables[(i * instance.getNbTask() + j)];
                capacity_constraint.addOperand(constraint_expr);
            }
            // adding the constraint expression to the model
            model.constraint(assignment_constraint <= capacity_vector[i]);

        }

        model.close();


    }












    double GurobiBackend::getObjectiveValue(){
        return model.getObjective().getValue();
    }

 }

 #endif
