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


    // constructor

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

        // initialization of decision variables vector
        variables.resize(instance.getNbAgent() * instance.getNbTask());

        // decision variables
        int counter = 0;
        for(size_t i = 0; i < instance.getNbAgent(); i++){

            for(size_t j = 0; j < instance.getNbTask(); j++){

                                    // lb, ub, obj coef
                variables[counter] = model->addVar(0.0,
                                                   1.0,
                                                   0.0,
                                                   GRB_BINARY,
                                                   "x" + std::to_string(i) + std::to_string(j));

                counter +=1;
            }

        }

        const std::vector<std::vector<int>> & cost_matrix = instance.getCost();

        // ojective function
        GRBLinExpr z = 0;
        for(size_t i = 0; i < instance.getNbAgent(); i++){

            for(size_t j = 0; j < instance.getNbTask(); j++){

                z += cost_matrix[i][j] * variables[(i * instance.getNbTask() + j)];
            }

        }
        model->setObjective(z, GRB_MINIMIZE);


        // assignment contraints
        for(size_t j = 0; j < instance.getNbTask(); j++){

            GRBLinExpr constraint = 0;

            for(size_t i = 0; i < instance.getNbAgent(); i++){

                constraint += variables[(i * instance.getNbTask() + j)];
            }

            model->addConstr(constraint == 1);
        }

        const std::vector<std::vector<int>>& weight_matrix = instance.getWeight();
        const std::vector<int>& capacity_vector = instance.getCapacity();

        // capacity constraints
        for(size_t i = 0; i < instance.getNbAgent(); i++){

            GRBLinExpr constraint = 0;

            for(size_t j = 0; j < instance.getNbTask(); j++){

                constraint += weight_matrix[i][j] * variables[(i * instance.getNbTask() + j)];
            }

            model->addConstr(constraint <= capacity_vector[i]);

        }

        model->update();

    }





    void GurobiBackend::solveContinuousModel(){model->optimize();}



    void GurobiBackend::buildContinuousModel(gap::GapInstance &instance){

        // initialization of variables vector
        variables.resize(instance.getNbAgent() * instance.getNbTask());

        // decision variables
        int counter = 0;
        for(size_t i = 0; i < instance.getNbAgent(); i++){

            for(size_t j = 0; j < instance.getNbTask(); j++){

                                    // lb, ub, obj coef
                variables[counter] = model->addVar(0.0,
                                                   1.0,
                                                   0.0,
                                                   GRB_CONTINUOUS,
                                                   "x" + std::to_string(i) + std::to_string(j));

                counter +=1;
            }

        }

        const std::vector<std::vector<int>> & cost_matrix = instance.getCost();

        // ojective function
        GRBLinExpr z = 0;
        for(size_t i = 0; i < instance.getNbAgent(); i++){

            for(size_t j = 0; j < instance.getNbTask(); j++){

                z += cost_matrix[i][j] * variables[(i * instance.getNbTask() + j)];
            }

        }
        model->setObjective(z, GRB_MINIMIZE);


        // assignment contraints
        for(size_t j = 0; j < instance.getNbTask(); j++){

            GRBLinExpr constraint = 0;

            for(size_t i = 0; i < instance.getNbAgent(); i++){

                constraint += variables[(i * instance.getNbTask() + j)];
            }

            model->addConstr(constraint == 1);
        }

        const std::vector<std::vector<int>>& weight_matrix = instance.getWeight();
        const std::vector<int>& capacity_vector = instance.getCapacity();

        // capacity constraints
        for(size_t i = 0; i < instance.getNbAgent(); i++){

            GRBLinExpr constraint = 0;

            for(size_t j = 0; j < instance.getNbTask(); j++){

                constraint += weight_matrix[i][j] * variables[(i * instance.getNbTask() + j)];
            }

            model->addConstr(constraint <= capacity_vector[i]);

        }

        model->update();

    }





    void GurobiBackend::addConstraints(gap::BaB::BaBNode &node){

        for(int index : node.getIndexesFixedToOne()){

            variables[index].set(GRB_DoubleAttr_LB, 1.0);
            variables[index].set(GRB_DoubleAttr_UB, 1.0);
        }

        for(int index : node.getIndexesFixedToZero()){

            variables[index].set(GRB_DoubleAttr_LB, 0.0);
            variables[index].set(GRB_DoubleAttr_UB, 0.0);
        }

        model->update();

    }





    void GurobiBackend::resetLinearModel(gap::BaB::BaBNode &node){

        for(int index : node.getIndexesFixedToOne()){

            variables[index].set(GRB_DoubleAttr_LB, 0.0);
            variables[index].set(GRB_DoubleAttr_UB, 1.0);
        }

        for(int index : node.getIndexesFixedToZero()){

            variables[index].set(GRB_DoubleAttr_LB, 0.0);
            variables[index].set(GRB_DoubleAttr_UB, 1.0);
        }

        model->update();

        model->reset();
    }




    bool GurobiBackend::isInFeasible(){return model->get(GRB_IntAttr_Status) == GRB_INFEASIBLE;}
    bool GurobiBackend::isOptimal(){return model->get(GRB_IntAttr_Status) == GRB_OPTIMAL;}
    bool GurobiBackend::isSubOptimal(){return model->get(GRB_IntAttr_Status) == GRB_SUBOPTIMAL;}
    bool GurobiBackend::isUnbounded(){return model->get(GRB_IntAttr_Status) == GRB_UNBOUNDED;}



    std::vector<double> GurobiBackend::getSolution(){

        std::vector<double> solution(variables.size());

        for(size_t i = 0; i < solution.size(); i++){

            solution[i] = variables[i].get(GRB_DoubleAttr_X);
        }

        return solution;
    }


    
    double GurobiBackend::getObjectiveValue(){return model->get(GRB_DoubleAttr_ObjVal);}


 }

 #endif


