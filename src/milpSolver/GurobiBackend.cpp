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
 * @file GurobiBackend.cpp
 * @author Josué Tambwe
 * @date 4 May 2026
 */

 #if HAS_GUROBI

 #include "milpSolver/GurobiBackend.hpp"

 namespace gap{


    // constructors

    GurobiBackend::GurobiBackend(){

        env = std::make_unique<GRBEnv>(true); 
        env->set(GRB_IntParam_OutputFlag, 0); // disable verbose mode
        env->start();
        model = std::make_unique<GRBModel>(*env);
    }




    
    void GurobiBackend::solveIntegerModel(double time_limit){

        model->set(GRB_DoubleParam_TimeLimit, time_limit);
        model->optimize();

    }


    void GurobiBackend::buildIntegerModel(gap::GapInstance &instance){
        // decision variables

        std::vector<std::vector<GRBVar>> x(instance.getNbAgent(),
                                           std::vector<GRBVar>(instance.getNbTask()));


        for(size_t i = 0; i < instance.getNbAgent(); i++){

            for(size_t j = 0; j < instance.getNbTask(); j++){

                // lb, ub, obj coef
                x[i][j] = model->addVar(0.0,
                                       1.0,
                                       0.0,
                                       GRB_BINARY,
                                       "x" + std::to_string(i) + std::to_string(j));
            }

        }

        const std::vector<std::vector<int>> & cost_matrix = instance.getCost();

        // ojective function
        GRBLinExpr z = 0;
        for(size_t i = 0; i < instance.getNbAgent(); i++){

            for(size_t j = 0; j < instance.getNbTask(); j++){

                z += cost_matrix[i][j] * x[i][j];
            }

        }
        model->setObjective(z, GRB_MINIMIZE);


        // assignment contraints
        for(size_t j = 0; j < instance.getNbTask(); j++){

            GRBLinExpr constraint = 0;

            for(size_t i = 0; i < instance.getNbAgent(); i++){

                constraint += x[i][j];
            }

            model->addConstr(constraint == 1);
        }

        const std::vector<std::vector<int>>& weight_matrix = instance.getWeight();
        const std::vector<int>& capacity_vector = instance.getCapacity();

        // capacity constraints
        for(size_t i = 0; i < instance.getNbAgent(); i++){

            GRBLinExpr constraint = 0;

            for(size_t j = 0; j < instance.getNbTask(); j++){

                constraint += weight_matrix[i][j] * x[i][j];
            }

            model->addConstr(constraint <= capacity_vector[i]);

        }
    }




    void GurobiBackend::solveContinuousModel(){model->optimize();}



    void GurobiBackend::buildContinuousModel(gap::GapInstance &instance){

        // decision variables

        std::vector<std::vector<GRBVar>> x(instance.getNbAgent(),
                                           std::vector<GRBVar>(instance.getNbTask()));


        for(size_t i = 0; i < instance.getNbAgent(); i++){

            for(size_t j = 0; j < instance.getNbTask(); j++){

                // lb, ub, obj coef
                x[i][j] = model->addVar(0.0,
                                       1.0,
                                       0.0,
                                       GRB_CONTINUOUS,
                                       "x" + std::to_string(i) + std::to_string(j));
            }

        }

        const std::vector<std::vector<int>> & cost_matrix = instance.getCost();

        // ojective function
        GRBLinExpr z = 0;
        for(size_t i = 0; i < instance.getNbAgent(); i++){

            for(size_t j = 0; j < instance.getNbTask(); j++){

                z += cost_matrix[i][j] * x[i][j];
            }

        }
        model->setObjective(z, GRB_MINIMIZE);


        // assignment contraints
        for(size_t j = 0; j < instance.getNbTask(); j++){

            GRBLinExpr constraint = 0;

            for(size_t i = 0; i < instance.getNbAgent(); i++){

                constraint += x[i][j];
            }

            model->addConstr(constraint == 1);
        }

        const std::vector<std::vector<int>>& weight_matrix = instance.getWeight();
        const std::vector<int>& capacity_vector = instance.getCapacity();

        // capacity constraints
        for(size_t i = 0; i < instance.getNbAgent(); i++){

            GRBLinExpr constraint = 0;

            for(size_t j = 0; j < instance.getNbTask(); j++){

                constraint += weight_matrix[i][j] * x[i][j];
            }

            model->addConstr(constraint <= capacity_vector[i]);

        }

    }



    void GurobiBackend::clearModel(){model->reset();}

    void GurobiBackend::addConstraints(gap::BaB::BaBNode &node){

        std::unordered_set<int> indexes_fixed_to_one = node.getIndexesFixedToOne();

        for(int index : indexes_fixed_to_one){

            model->getVars()[index].set(GRB_DoubleAttr_LB, 1.0);
            model->getVars()[index].set(GRB_DoubleAttr_UB, 1.0);
        }

        std::unordered_set<int> indexes_fixed_to_zero = node.getIndexesFixedToZero();

        for(int index : indexes_fixed_to_zero){

            model->getVars()[index].set(GRB_DoubleAttr_LB, 0.0);
            model->getVars()[index].set(GRB_DoubleAttr_UB, 0.0);
        }

    }

    void GurobiBackend::setVariableToOne(int index){

        model->getVars()[index].set(GRB_DoubleAttr_LB, 1.0);
        model->getVars()[index].set(GRB_DoubleAttr_UB, 1.0);
    }

    void GurobiBackend::setVariableToZero(int index){

        model->getVars()[index].set(GRB_DoubleAttr_LB, 0.0);
        model->getVars()[index].set(GRB_DoubleAttr_UB, 0.0);
    }



    bool GurobiBackend::isInFeasible(){return model->get(GRB_IntAttr_Status) == GRB_INFEASIBLE;}
    bool GurobiBackend::isOptimal(){return model->get(GRB_IntAttr_Status) == GRB_OPTIMAL;}
    bool GurobiBackend::isSubOptimal(){return model->get(GRB_IntAttr_Status) == GRB_SUBOPTIMAL;}
    bool GurobiBackend::isUnbounded(){return model->get(GRB_IntAttr_Status) == GRB_UNBOUNDED;}

    std::vector<double> GurobiBackend::getSolution(){

        std::vector<double> solution(model->get(GRB_IntAttr_NumVars));

        for(size_t i = 0; i < solution.size(); i++){

            solution[i] = model->getVars()[i].get(GRB_DoubleAttr_X);
        }

        return solution;
    }

    
    double GurobiBackend::getObjectiveValue(){return model->get(GRB_DoubleAttr_ObjVal);}



 }

 #endif


