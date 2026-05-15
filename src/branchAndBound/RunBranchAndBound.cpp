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





    std::unique_ptr<LPSolver> setLPSolver(gap::Params &params){

        #if HAS_HIGHS
        if(params.milp_solver == 'h'){return std::make_unique<HighsBackend>();}
        #endif
        
        #if HAS_GUROBI
            return std::make_unique<GurobiBackend>();
        #endif

        throw std::runtime_error("No LP solver enabled");

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




    std::unique_ptr<LPSolver> buildLinearModel(gap::Params &params,
                                               gap::GapInstance &instance){


        std::unique_ptr<LPSolver> solver = setLPSolver(params);
        solver->buildContinuousModel(instance);
        return solver;

    }
    




    void branchAndBoundBestFirst(gap::Params &params){

        // initialization
        gap::GapInstance instance(params);
        printHeaderBaB(params, instance);

        gap::Timer timer = Timer();
        gap::Logger log;
        timer.start();

        // primal solution (greedy construction + local search)
        gap::GapSolution primal_solution = initializePrimalSolution(instance);

        double primal_bound = setInitialPrimalBound(primal_solution, instance);
        double preprocessing_time = timer.getElapsed();
        double preprocessing_obj_value = primal_bound;

        // initialization of the LP solver
        std::unique_ptr<LPSolver> solver = buildLinearModel(params, instance);
        solver->solveContinuousModel();

        // infeasibility test
        if(!solver->isOptimal()){
            log.warning("the problem is infeasible.");
            std::cout << " \n Processing time : " << timer.getElapsed() << " (s) \n\n" << std::endl;
            return;
        }

        // initialization of the dual bound
        double dual_bound = solver->getObjectiveValue();

        // initialization of the list of open nodes
        BaBNodeList<gap::BaB::BestFirst> open_nodes;

        // initialization of the root node
        open_nodes.add(BaBNode(dual_bound));

        printHeaderLineBaB();

        size_t processed_nodes = 0;
        size_t nodes_fathomed_by_infeasibility = 0;
        size_t nodes_fathomed_by_dominance = 0;
        size_t nodes_fathomed_by_optimality = 0;

        while(!open_nodes.isEmpty() &&
              !stoppingCriteriaBestFirst(primal_bound, dual_bound, timer.getElapsed(), params)){

            BaBNode current_node = open_nodes.pop();

            processed_nodes += 1;

            solver->addConstraints(current_node);
            solver->solveContinuousModel();

            if(solver->isInFeasible()){

                nodes_fathomed_by_infeasibility += 1;
                // undoing variables fixation
                solver->resetLinearModel(current_node);
                continue;
            }

            std::vector<double> relaxed_solution = solver->getSolution();

            // dominance test
            if(solver->getObjectiveValue() > primal_bound){

                nodes_fathomed_by_dominance += 1;
                // undoing variables fixation
                solver->resetLinearModel(current_node); 
                continue;
            }

            // integrality test
            if(isInteger(relaxed_solution)){

                nodes_fathomed_by_optimality += 1;
                
                if(solver->getObjectiveValue() < primal_bound){

                    primal_bound = solver->getObjectiveValue();
                    updateSolution(relaxed_solution, primal_solution);
                }

                // undoing variables fixation
                solver->resetLinearModel(current_node);

                continue;
            }

            // branching

            int index = branchingVariableIndex(relaxed_solution, params);

            // x_ij = 0
            BaBNode left_branch_node(solver->getObjectiveValue(), current_node);

            // x_ij = 1
            BaBNode right_branch_node(solver->getObjectiveValue(), current_node);

            left_branch_node.fixToZero(index);
            right_branch_node.fixToOne(index);

            open_nodes.add(left_branch_node);
            open_nodes.add(right_branch_node);

            // upadting the global dual bound
            if(!open_nodes.isEmpty()){
               dual_bound = open_nodes.getLowestDualBound();
            }
            else{dual_bound = primal_bound;}

            if(processed_nodes % 1000 == 0 || processed_nodes < 10){

                printBaBIteration(timer.getElapsed(),
                                  processed_nodes,
                                  open_nodes.getSize(),
                                  dual_bound,
                                  primal_bound);
            }

            // undoing variables fixation
            solver->resetLinearModel(current_node);
            
        }
        std::cout << "\n";
        log.info("Branch and Bound algorithm completed. Final best known solution :");

        // update of solution status
        if((std::abs(dual_bound - primal_bound) / primal_bound) <= tolerance 
            || open_nodes.isEmpty()){
                primal_solution.setStatus(gap::Status::OPTIMAL);
        }

        primal_solution.print(instance);

        finalStatisticsBaB(preprocessing_time,
                           preprocessing_obj_value,
                           dual_bound,
                           primal_bound,
                           timer.getElapsed(),
                           primal_solution.getStatus(),
                           processed_nodes,
                           open_nodes.getSize(),
                           nodes_fathomed_by_optimality,
                           nodes_fathomed_by_dominance,
                           nodes_fathomed_by_infeasibility,
                           params);




    }






    void branchAndBoundDepthFirst(gap::Params &params){

        // initialization
        gap::GapInstance instance(params);
        printHeaderBaB(params, instance);

        gap::Timer timer = Timer();
        gap::Logger log;
        timer.start();

        // primal solution (greedy construction + local search)
        gap::GapSolution primal_solution = initializePrimalSolution(instance);

        double primal_bound = setInitialPrimalBound(primal_solution, instance);
        double preprocessing_time = timer.getElapsed();
        double preprocessing_obj_value = primal_bound;

        // initialization of the MILP solver
        std::unique_ptr<LPSolver> solver = buildLinearModel(params, instance);
        solver->solveContinuousModel();

        // infeasibility test
        if(!solver->isOptimal()){
            log.warning("the problem is infeasible.");
            std::cout << " \n Processing time : " << timer.getElapsed() << " (s) \n\n" << std::endl;
            return;

        }

        // initialization of the dual bound
        double dual_bound = solver->getObjectiveValue();

        // initialization of the list of open nodes
        BaBNodeList<gap::BaB::DepthFirst> open_nodes;

        // initialization of the root node
        open_nodes.add(BaBNode(dual_bound));

        size_t processed_nodes = 0;
        size_t nodes_fathomed_by_infeasibility = 0;
        size_t nodes_fathomed_by_dominance = 0;
        size_t nodes_fathomed_by_optimality = 0;

        printHeaderLineBaB();


        while(!open_nodes.isEmpty() && 
              !stoppingCriteriaDepthFirst(timer.getElapsed(), params)){

                BaBNode current_node = open_nodes.pop();

                processed_nodes += 1;

                solver->addConstraints(current_node);
                solver->solveContinuousModel();

                if(solver->isInFeasible()){
                    
                    nodes_fathomed_by_infeasibility += 1;
                    // undoing variables fixation
                    solver->resetLinearModel(current_node); 
                    continue;
                }

                std::vector<double> relaxed_solution = solver->getSolution();

                // dominance test
                if(solver->getObjectiveValue() > primal_bound){

                    nodes_fathomed_by_dominance += 1;
                    // undoing variables fixation
                    solver->resetLinearModel(current_node); 
                    continue;
                }

                // integrality test
                if(isInteger(relaxed_solution)){

                    nodes_fathomed_by_optimality += 1;
                    
                    if(solver->getObjectiveValue() < primal_bound){

                        primal_bound = solver->getObjectiveValue();
                        updateSolution(relaxed_solution, primal_solution);
                        if(params.verbose){primal_solution.print(instance);} 
                    }

                    // undoing variables fixation
                    solver->resetLinearModel(current_node);

                    continue;
                }

                // branching

                int index = branchingVariableIndex(relaxed_solution, params);

                // x_ij = 0
                BaBNode left_branch_node(solver->getObjectiveValue(), current_node);

                // x_ij = 1
                BaBNode right_branch_node(solver->getObjectiveValue(), current_node);

                left_branch_node.fixToZero(index);
                right_branch_node.fixToOne(index);

                open_nodes.add(left_branch_node);
                open_nodes.add(right_branch_node);


                // upadting the global dual bound
                if(!open_nodes.isEmpty()){
                dual_bound = open_nodes.getLowestDualBound();
                }

                else{dual_bound = primal_bound;}

                 // runtime processing information
                if(processed_nodes % 1000 == 0 || processed_nodes < 10){
                printBaBIteration(timer.getElapsed(),
                                  processed_nodes,
                                  open_nodes.getSize(),
                                  open_nodes.getLowestDualBound(),
                                  primal_bound);
                }

                // undoing variables fixation
                solver->resetLinearModel(current_node);


            }
            std::cout << "\n";
            log.info("Branch and Bound algorithm completed. Final best known solution :");

            // update of solution status
            if((std::abs(dual_bound - primal_bound) / primal_bound) <= tolerance 
                || open_nodes.isEmpty()){
                    primal_solution.setStatus(gap::Status::OPTIMAL);
            }
            primal_solution.print(instance);

            finalStatisticsBaB(preprocessing_time,
                           preprocessing_obj_value,
                           dual_bound,
                           primal_bound,
                           timer.getElapsed(),
                           primal_solution.getStatus(),
                           processed_nodes,
                           open_nodes.getSize(),
                           nodes_fathomed_by_optimality,
                           nodes_fathomed_by_dominance,
                           nodes_fathomed_by_infeasibility,
                           params);


    }





    void runBaB(gap::Params &params){
        
        printHeader();

        if(params.exploration_strategy == 'b'){
            branchAndBoundBestFirst(params);
        }
        else{branchAndBoundDepthFirst(params);}

    }




 }

 #endif