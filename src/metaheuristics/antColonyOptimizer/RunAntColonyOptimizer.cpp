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
 * @file AntColonyOptimizer.cpp
 * @author Josué Tambwe
 * @date 24 Mar 2026
 */

 #include "metaheuristics/antColonyOptimizer/RunAntColonyOptimizer.hpp"
 
 namespace gap::ACO{



    gap::GapSolution& findBestAnt(std::int64_t &best_value,
                                  std::int64_t &worst_value,
                                  std::int64_t &cumulative_score,
                                  std::vector<gap::GapSolution> &colony,
                                  gap::GapInstance &instance){


        best_value = colony[0].objectiveValue(instance);
        worst_value = colony[0].objectiveValue(instance);
        cumulative_score = colony[0].objectiveValue(instance);
        int best_index = 0;

        for(int ant = 1; ant < static_cast<int>(colony.size()); ant++){

            std::int64_t obj_value = colony[ant]. objectiveValue(instance);
            cumulative_score += obj_value;

            if(obj_value < best_value){best_index = ant; best_value = obj_value;}
            if(obj_value > worst_value){worst_value = obj_value;}

        }

        return colony[best_index];

    }





    void RunACO(gap::Params &params){

        gap::GapInstance instance(params);
        printHeader();
        printHeaderACO(params, instance);
        printHeaderLineACO();
        gap::Timer timer = Timer();
        timer.start();

        gap::Logger log;

        // initialization of the reference ant
        gap::GapSolution reference_ant = generateReferenceAnt(instance);
        std::int64_t reference_value = reference_ant.objectiveValue(instance);


        // initialization of the best solution (ant)
        gap::GapSolution global_best_ant = reference_ant;
        std::int64_t global_best_value = reference_value;
        float inverse_reference_value = computeInverseReferenceValue(global_best_value);


        // initialization of the pheromone matrix
        AlignedMatrix pheromone_matrix(static_cast<int>(instance.getNbAgent()),
                                       static_cast<int>(instance.getNbTask()));

        pheromone_matrix.initialize(computeInitialPheromone(inverse_reference_value, params));


        double preprocessing_time = timer.getElapsed();
        double inverse_max_time = 1.0 / (params.time_limit + 1e-5);
        double inverse_max_iteration = 1.0 / (static_cast<double>(params.nb_max_iterations) + 1e-5);
        float max_pheromone = computeMaximumPheromone(params);

        int iteration = 0;

        do{
            iteration++;
            double probability_threshold = computeProbabilityThreshold(iteration,
                                                                       inverse_max_iteration,
                                                                       timer.getElapsed(),
                                                                       inverse_max_time,
                                                                       params);

            // colony initialization
            std::vector<gap::GapSolution> colony(params.nb_ants, gap::GapSolution(instance));
            std::vector<bool> ants_construction_status(params.nb_ants, true);

            // colony construction
            bool is_feasible = antConstruction(probability_threshold,
                                               params,
                                               ants_construction_status,
                                               pheromone_matrix,
                                               colony,
                                               instance);

            if(!is_feasible){log.warning("the problem is infeasible !"); break;}


            // colony improvement by local search and reparation of infeasible ants
            antImprovement(reference_ant,
                           params,
                           ants_construction_status,
                           colony,
                           instance);


            // pheromones evaporation
            scalarPheromoneMatrixEvaporation(params, pheromone_matrix);


            // finding the best ant within the colony
            std::int64_t local_best_value = 0;
            std::int64_t local_worst_value = 0;
            std::int64_t cumulative_score = 0;

            gap::GapSolution& local_best_ant = findBestAnt(local_best_value,
                                                           local_worst_value,
                                                           cumulative_score,
                                                           colony,
                                                           instance);

            
            if(local_best_value <= reference_value){

                // pheromones deposit (only the best ant => elitism strategy)
                pheromoneDeposit(inverse_reference_value,
                                max_pheromone,
                                local_best_ant,
                                instance,
                                pheromone_matrix);

                
            }


            printACOIteration(iteration,
                              timer.getElapsed(),
                              local_worst_value,
                              cumulative_score,
                              local_best_value,
                              global_best_value,
                              (local_best_value < global_best_value),
                              params);

            
            // updating the best solution
            if(local_best_value < global_best_value){

                global_best_ant = local_best_ant;
                global_best_value = local_best_value;

                if(params.verbose){
                    std::cout << "\n" << std::endl;
                    log.info(" The best solution has been improved !");
                    global_best_ant.print(instance); 
                    printHeaderLineACO();
                }

            }
            

        }
        while(!stoppingCriteria(iteration, timer.getElapsed(), params));

        std::cout << "\n" << std::endl;
        log.info("ACO algorithm completed. Final best known solution :");
        global_best_ant.print(instance);

        finalStatisticsACO(preprocessing_time,
                           iteration,
                           global_best_value,
                           global_best_ant.getStatus(),
                           timer,
                           params);

        
    }



 }

