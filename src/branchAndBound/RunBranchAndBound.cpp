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
 * @file RunBranchAndBound.cpp
 * @author Josué Tambwe
 * @date 24 Mar 2026
 */


 #if USE_BRANCH_AND_BOUND


 #include "branchAndBound/RunBranchAndBound.hpp"

 namespace gap::BaB{



    gap::GapSolution initializePrimalSolution(gap::GapInstance &instance){

        // construction
        gap::GapSolution primal_solution = gap::greedy::constructionRiskyTasks(instance);
        // local search
        gap::greedy::balanceMove(primal_solution, instance);
        gap::greedy::cheapMove(NUMBER_PHYSICAL_CORES, primal_solution, instance);

        return primal_solution;

    }




    double setInitialPrimalBound(gap::GapSolution &primal_solution,
                                gap::GapInstance &instance){

        if(primal_solution.getStatus() != gap::Status::FEASIBLE
           && primal_solution.getStatus() != gap::Status::OPTIMAL){

            return std::numeric_limits<double>::max();
        }

        return static_cast<double>(primal_solution.objectiveValue(instance));
                    

    }





    std::unique_ptr<MilpSolver> setMilpSolver(gap::Params &params){

        //if(params.milp_solver == 'g'){return std::make_unique<GurobiBackend>();}
        //if(params.milp_solver == 'h'){return std::make_unique<HighsBackend>();}
        //return return std::make_unique<HexalyBackend>();
        return std::make_unique<GurobiBackend>();

    }





    double setInitialDualBound(gap::Params &params, gap::GapInstance &instance){

        std::unique_ptr<MilpSolver> solver = setMilpSolver(params);
        solver->buildContinuousModel(instance);
        solver->solveContinuousModel();
        return solver->getObjectiveValue();

    }




    void updateSolution(std::vector<double> &sol, gap::GapSolution &solution){

        std::vector<int>& solution_vector =  solution.getSolutionVector();

        for(size_t k = 0; k < sol.size(); k++){

            if(std::abs(1.0 - sol[k]) < tolerance){

                int agent = convertTo2DAgentIndex(k, solution_vector.size());
                int task = convertTo2DTaskIndex(k, solution_vector.size());

                solution_vector[task] = agent;

            }
        }

    }




    std::unique_ptr<MilpSolver> buildLinearModel(gap::Params &params,
                                                 gap::GapInstance &instance){


        std::unique_ptr<MilpSolver> solver = setMilpSolver(params);
        solver->buildContinuousModel(instance);
        return solver;

    }




    void branchAndBoundBestFirst(gap::Params &params){

        // initialization
        gap::GapInstance instance(params);

        gap::Timer timer = Timer();
        //gap::Logger log;
        timer.start();

        // primal solution (greedy construction + local search)
        gap::GapSolution primal_solution = initializePrimalSolution(instance);

        double primal_bound = setInitialPrimalBound(primal_solution, instance);

        double preprocessing_time = timer.getElapsed();

        std::cout << " preprocessing time : " << preprocessing_time << " (s) \n ";


        // initialization of the MILP solver
        std::unique_ptr<MilpSolver> solver = buildLinearModel(params, instance);
        solver->solveContinuousModel();

        // infeasibility test
        if(!solver->isOptimal()){
            std::cout << " \n The Problem is infeasible ! \n ";
            return;

        }

        // initialization of the dual bound
        double dual_bound = solver->getObjectiveValue();

        // initialization of the list of open nodes
        BaBNodeList<gap::BaB::BestFirst> open_nodes;

        // initialization of the root node
        open_nodes.add(BaBNode(dual_bound));

        std::cout << "\n primal bound : " << primal_bound << " \n ";
        std::cout << "\n dual bound   : " << dual_bound << " \n ";

        printHeaderLineBaB();

        size_t processed_nodes = 0;

        while(!open_nodes.isEmpty() &&
              !stoppingCriteriaBestFirst(primal_bound, dual_bound, timer.getElapsed(), params)){

            //std::cout << " \n iteration : " << iteration << " \n";

            BaBNode current_node = open_nodes.pop();



            processed_nodes += 1;

            //std::cout << " pop the node : " ;
            //current_node.print() ;
            //std::cout << " \n";

            solver->addConstraints(current_node);

            solver->solveContinuousModel();

            if(solver->isInFeasible()){

               // std::cout << " problème infaisable \n ";
               solver->resetLinearModel();
                continue;
            }

            std::vector<double> relaxed_solution = solver->getSolution();

            // dominance test
            if(solver->getObjectiveValue() > primal_bound){
                //std::cout << " noeud sondé par dominance  z = " << solver->getObjectiveValue() << " \n";
                solver->resetLinearModel();
                continue;
            }

            // integrality test
            if(isInteger(relaxed_solution)){

                /*std::cout << "noeud sondé par optimalité avec z = " 
                          << solver->getObjectiveValue() << " \n";*/
                
                if(solver->getObjectiveValue() < primal_bound){

                    //std::cout << " meilleure solution améliorée \n";
                    primal_bound = solver->getObjectiveValue();
                    updateSolution(relaxed_solution, primal_solution);
                    solver->resetLinearModel();
                    continue;
                    // rajouter le test de l'arrêt de l'algorithme

                }
            }

            // branching

            int index = branchingVariableIndex(relaxed_solution, params);

            /*std::cout << " \n branching index " << index 
                      << " value " << relaxed_solution[index]
                      << " \n ";*/

            // x_ij = 0
            BaBNode left_branch_node(solver->getObjectiveValue(), current_node);

            // x_ij = 1
            BaBNode right_branch_node(solver->getObjectiveValue(), current_node);

            left_branch_node.fixToZero(index);
            right_branch_node.fixToOne(index);

            open_nodes.add(left_branch_node);
            open_nodes.add(right_branch_node);

            // undoing variables fixations
            solver->resetLinearModel();

            // upadting the global dual bound
            if(!open_nodes.isEmpty()){
               dual_bound = open_nodes.getLowestDualBound();
            }
            else{
               dual_bound = primal_bound;
            }

            if(processed_nodes % 500 == 0 || processed_nodes < 10){

                printBaBIteration(timer.getElapsed(),
                                  processed_nodes,
                                  open_nodes.getSize(),
                                  dual_bound,
                                  primal_bound);
            }
            


            //std::cout << "\n \n ";

        }

        primal_solution.print(instance);

    }






    void branchAndBoundDepthFirst(gap::Params &params){

        // initialization
        gap::GapInstance instance(params);

        gap::Timer timer = Timer();
        //gap::Logger log;
        timer.start();

        // primal solution (greedy construction + local search)
        gap::GapSolution primal_solution = initializePrimalSolution(instance);

        double primal_bound = setInitialPrimalBound(primal_solution, instance);

        double preprocessing_time = timer.getElapsed();

        std::cout << " preprocessing time : " << preprocessing_time << " (s) \n ";


        // initialization of the MILP solver
        std::unique_ptr<MilpSolver> solver = buildLinearModel(params, instance);
        solver->solveContinuousModel();

        // infeasibility test
        if(!solver->isOptimal()){
            std::cout << " \n The Problem is infeasible ! \n ";
            return;

        }

        // initialization of the dual bound
        double dual_bound = solver->getObjectiveValue();

        // initialization of the list of open nodes
        BaBNodeList<gap::BaB::DepthFirst> open_nodes;

        // initialization of the root node
        open_nodes.add(BaBNode(dual_bound));

        std::cout << "\n primal bound : " << primal_bound << " \n ";
        std::cout << "\n dual bound   : " << dual_bound << " \n ";

        size_t processed_nodes = 0;

        printHeaderLineBaB();


        while(!open_nodes.isEmpty() && 
              !stoppingCriteriaDepthFirst(timer.getElapsed(), params)){


                //std::cout << " \n iteration : " << iteration << " \n";

                BaBNode current_node = open_nodes.pop();

                processed_nodes += 1;

                /*std::cout << " pop the node : " ;
                current_node.print() ;
                std::cout << " \n";*/

                solver->addConstraints(current_node);

                solver->solveContinuousModel();

                if(solver->isInFeasible()){

                    //std::cout << " problème infaisable \n ";
                    solver->resetLinearModel();
                    continue;
                }

                std::vector<double> relaxed_solution = solver->getSolution();

                // dominance test
                if(solver->getObjectiveValue() > primal_bound){

                    //std::cout << " noeud sondé par dominance  z = " << solver->getObjectiveValue() << " \n";
                    solver->resetLinearModel();
                    continue;
                }

                // integrality test
                if(isInteger(relaxed_solution)){

                    /*std::cout << "noeud sondé par optimalité avec z = " 
                            << solver->getObjectiveValue() << " \n";*/
                    
                    if(solver->getObjectiveValue() < primal_bound){

                        //std::cout << " meilleure solution améliorée \n";
                        primal_bound = solver->getObjectiveValue();
                        updateSolution(relaxed_solution, primal_solution);
                        solver->resetLinearModel();
                        continue;
                        // rajouter le test de l'arrêt de l'algorithme

                    }
                }

                // branching

                int index = branchingVariableIndex(relaxed_solution, params);

                /*if(index == -1){
                    std::cout << " \n Pas de variable fractionaire \n ";

                    // undoing variables fixations
                    solver->resetLinearModel();
                    continue;
                }*/

                /*std::cout << " \n branching index " << index 
                        << " value " << relaxed_solution[index]
                        << " \n ";*/

                // x_ij = 0
                BaBNode left_branch_node(solver->getObjectiveValue(), current_node);

                // x_ij = 1
                BaBNode right_branch_node(solver->getObjectiveValue(), current_node);

                left_branch_node.fixToZero(index);
                right_branch_node.fixToOne(index);

                open_nodes.add(left_branch_node);
                open_nodes.add(right_branch_node);

                // to remove
                //open_nodes.print();

                // undoing variables fixations
                solver->resetLinearModel();

                // upadting the global dual bound
                if(!open_nodes.isEmpty()){
                dual_bound = open_nodes.getLowestDualBound();
                }
                else{
                dual_bound = primal_bound;
                }

                if(processed_nodes % 500 == 0 || processed_nodes < 10){
                
                printBaBIteration(timer.getElapsed(),
                                  processed_nodes,
                                  open_nodes.getSize(),
                                  open_nodes.getLowestDualBound(),
                                  primal_bound);
                }


                //std::cout << "\n \n ";

            }

            primal_solution.print(instance);

    

    }





    void test(gap::Params &params){

        if(params.exploration_strategy == 'b'){branchAndBoundBestFirst(params);}

        else{branchAndBoundDepthFirst(params);}



    }




 }

 #endif