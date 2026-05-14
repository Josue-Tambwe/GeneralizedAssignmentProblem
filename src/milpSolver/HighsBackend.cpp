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
 * @file HighsBackend.cpp
 * @author Josué Tambwe
 * @date 14 May 2026
 */

 #if HAS_HIGHS

 #include "milpSolver/HighsBackend.hpp"

 namespace gap{



    void HighsBackend::solveIntegerModel(double time_limit){
        // disable verbose mode
        optimizer.setOptionValue("output_flag", false);
        
        // setting the time budget
        optimizer.setOptionValue("time_limit", time_limit);

        // solving the model
        optimizer.run();

    }




    void HighsBackend::buildIntegerModel(gap::GapInstance &instance){

        size_t nb_agent = instance.getNbAgent();
        size_t nb_task = instance.getNbTask();
        variables.resize(nb_agent * nb_task);

        const std::vector<std::vector<int>> & cost_matrix = instance.getCost();

        // adding decision variables 
        for(size_t i = 0; i < nb_agent; i++){

            for(size_t j = 0; j < nb_task; j++){

                HighsInt col = optimizer.getNumCol();

                // cost, lb, ub, nb coef in the matrix constraints, index, value
                optimizer.addCol(static_cast<double>(cost_matrix[i][j]),
                                 0.0,
                                 1.0,
                                 0,
                                 nullptr,
                                 nullptr);

                // integrality constraint
                optimizer.changeColIntegrality(col, HighsVarType::kInteger);

                variables[(i * nb_task) + j] = col;
                                                            
            }
        }

        // assignment constraints
        for(size_t j = 0; j < nb_task; j++){

            std::vector<HighsInt> non_zero_agent_indexes(nb_agent);
            std::vector<double> coefficient(nb_agent, 1.0);

            for(size_t i = 0; i < nb_agent; i++){

                non_zero_agent_indexes[i] = variables[(i * nb_task) + j];
            }

            // lb, ub, nb items in the constraint, ptr to var indexes, ptr to coefficients
            optimizer.addRow(1.0, 
                             1.0, 
                             nb_agent, 
                             non_zero_agent_indexes.data(), 
                             coefficient.data());

        }

        const std::vector<std::vector<int>>& weight_matrix = instance.getWeight();
        const std::vector<int>& capacity_vector = instance.getCapacity();


        // capacity constraints 
        for(size_t i = 0; i < nb_agent; i++){

            std::vector<HighsInt> non_zero_task_indexes(nb_task);
            std::vector<double> coefficient(nb_task);

            for(size_t j = 0; j < nb_task; j++){

                non_zero_task_indexes[j] = variables[(i * nb_task) + j];
                coefficient[j] = static_cast<double>(weight_matrix[i][j]);
            }

            // lb, ub, nb items in the constraint, ptr to var indexes, ptr to coefficients
            optimizer.addRow(0.0, 
                             static_cast<double>(capacity_vector[i]), 
                             nb_task, 
                             non_zero_task_indexes.data(), 
                             coefficient.data());

        }


    }




    void HighsBackend::solveContinuousModel(){optimizer.run();}



    void HighsBackend::buildContinuousModel(gap::GapInstance &instance){

        size_t nb_agent = instance.getNbAgent();
        size_t nb_task = instance.getNbTask();
        variables.resize(nb_agent * nb_task);

        const std::vector<std::vector<int>> & cost_matrix = instance.getCost();

        // adding decision variables 
        for(size_t i = 0; i < nb_agent; i++){

            for(size_t j = 0; j < nb_task; j++){

                HighsInt col = optimizer.getNumCol();

                // cost, lb, ub, nb coef in the matrix constraints, index, value
                optimizer.addCol(static_cast<double>(cost_matrix[i][j]),
                                 0.0,
                                 1.0,
                                 0,
                                 nullptr,
                                 nullptr);

                variables[(i * nb_task) + j] = col;
                                                            
            }
        }

        // assignment constraints
        for(size_t j = 0; j < nb_task; j++){

            std::vector<HighsInt> non_zero_agent_indexes(nb_agent);
            std::vector<double> coefficient(nb_agent, 1.0);

            for(size_t i = 0; i < nb_agent; i++){

                non_zero_agent_indexes[i] = variables[(i * nb_task) + j];
            }

            // lb, ub, nb items in the constraint, ptr to var indexes, ptr to coefficients
            optimizer.addRow(1.0, 
                             1.0, 
                             nb_agent, 
                             non_zero_agent_indexes.data(), 
                             coefficient.data());

        }

        const std::vector<std::vector<int>>& weight_matrix = instance.getWeight();
        const std::vector<int>& capacity_vector = instance.getCapacity();


        // capacity constraints 
        for(size_t i = 0; i < nb_agent; i++){

            std::vector<HighsInt> non_zero_task_indexes(nb_task);
            std::vector<double> coefficient(nb_task);

            for(size_t j = 0; j < nb_task; j++){

                non_zero_task_indexes[j] = variables[(i * nb_task) + j];
                coefficient[j] = static_cast<double>(weight_matrix[i][j]);
            }

            // lb, ub, nb items in the constraint, ptr to var indexes, ptr to coefficients
            optimizer.addRow(0.0, 
                             static_cast<double>(capacity_vector[i]), 
                             nb_task, 
                             non_zero_task_indexes.data(), 
                             coefficient.data());

        }


    }

        



    void HighsBackend::addConstraints(gap::BaB::BaBNode &node){

        for(int index : node.getIndexesFixedToOne()){

            // var index, lb, ub
            optimizer.changeColBounds(index, 1.0, 1.0);
        }

        for(int index : node.getIndexesFixedToZero()){

            // var index, lb, ub
            optimizer.changeColBounds(index, 0.0, 0.0);
        }

    }





    void HighsBackend::resetLinearModel(gap::BaB::BaBNode &node){

        for(int index : node.getIndexesFixedToOne()){

            // var index, lb, ub
            optimizer.changeColBounds(index, 0.0, 1.0);
        }

        for(int index : node.getIndexesFixedToZero()){

            // var index, lb, ub
            optimizer.changeColBounds(index, 0.0, 1.0);
        }

    }




    void HighsBackend::setWarmStart(std::vector<double> &warm_start){

        HighsSolution initial_solution;

        // indicates that the initial solution will be feasible
        initial_solution.value_valid = true;

        initial_solution.col_value.resize(optimizer.getNumCol());

        // injecting the warm start values into the initial solution 
        for(size_t index = 0; index < variables.size(); index++){

            initial_solution.col_value[variables[index]] = warm_start[index];
        }

        // injecting the initial solution into the optimizer 
        optimizer.setSolution(initial_solution);
    }





    bool HighsBackend::isOptimal(){

        return optimizer.getModelStatus() == HighsModelStatus::kOptimal;
    }


    bool HighsBackend::isInFeasible() {

        return optimizer.getModelStatus() == HighsModelStatus::kInfeasible;
    }




    std::vector<double> HighsBackend::getSolution(){

        std::vector<double>  solution(variables.size());
        const HighsSolution& highs_sol = optimizer.getSolution();

        for(size_t index = 0; index < variables.size(); index++){

            solution[index] = highs_sol.col_value[variables[index]];
        }

        return solution;

    }



    double HighsBackend::getObjectiveValue(){

        return optimizer.getInfo().objective_function_value;
    }



 }
 #endif

