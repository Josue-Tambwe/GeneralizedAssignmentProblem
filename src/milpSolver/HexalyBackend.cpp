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
        model(optimizer.getModel())
    {
            // disable verbose mode
            optimizer.getParam().setVerbosity(0);
    }





    void HexalyBackend::solveIntegerModel(double time_limit){

        /*if( optimizer.getState() != hexaly::HxState::Ready){
            model.close();
        }*/

        // setting the time limit
        optimizer.getParam().setTimeLimit(time_limit);

        // solving the model
        optimizer.solve();
    }

    



    void HexalyBackend::buildIntegerModel(gap::GapInstance &instance){

        // initialization of decision variables vector
        variables.resize(instance.getNbAgent() * instance.getNbTask());

        for(size_t i = 0; i < variables.size(); i++){

            // adding binary variables  to the model
            variables[i] = model.boolVar();
        }

        // objective function
        hexaly::HxExpression obj = model.sum();

        const std::vector<std::vector<int>> & cost_matrix = instance.getCost();

        for(size_t i = 0; i < instance.getNbAgent(); i++){

            for(size_t j = 0; j < instance.getNbTask(); j++){

                hexaly::HxExpression expr = cost_matrix[i][j] * variables[(i * instance.getNbTask() + j)];
                obj.addOperand(expr);
            }

        }

        // adding the objective expression to the model
        model.minimize(obj);


        // assignment constraints 
        for(size_t j = 0; j < instance.getNbTask(); j++){

            hexaly::HxExpression assignment_constraint = model.sum();

            for(size_t i = 0; i < instance.getNbAgent(); i++){

                hexaly::HxExpression constraint_expr = variables[(i * instance.getNbTask() + j)];
                assignment_constraint.addOperand(constraint_expr);

            }
            // adding the constraint expression to the model
            model.constraint(assignment_constraint == 1);
        }


        const std::vector<std::vector<int>>& weight_matrix = instance.getWeight();
        const std::vector<int>& capacity_vector = instance.getCapacity();

        // capacity constraints
        for(size_t i = 0; i < instance.getNbAgent(); i++){

            hexaly::HxExpression capacity_constraint = model.sum();

            for(size_t j = 0; j < instance.getNbTask(); j++){

                hexaly::HxExpression constraint_expr = weight_matrix[i][j] * variables[(i * instance.getNbTask() + j)];
                capacity_constraint.addOperand(constraint_expr);
            }
            // adding the constraint expression to the model
            model.constraint(capacity_constraint <= capacity_vector[i]);

        }

        model.close();


    }




    void HexalyBackend::setWarmStart(std::vector<double> &warm_start){

        for(size_t index = 0; index < warm_start.size(); index++){

            hexaly::hxint value;
            
            if(warm_start[index] > 0.5){value = 1;}
            else{value = 0;}

            variables[index].setValue(value);

        }

    }




    bool HexalyBackend::isInFeasible(){

        return optimizer.getSolution().getStatus() == hexaly::SS_Infeasible;
    }

    


    bool HexalyBackend::isOptimal(){

        return optimizer.getSolution().getStatus() == hexaly::SS_Optimal;
    }





    std::vector<double> HexalyBackend::getSolution(){

        std::vector<double> solution(variables.size());

        for(size_t index = 0; index < variables.size(); index++){

            solution[index] = variables[index].getValue();
        }

        return solution;
    }




    double HexalyBackend::getObjectiveValue(){

        // 0 is the index of the objective (first objective function in multi-objective optimization)
        return model.getObjective(0).getValue();
    }


 }

 #endif

