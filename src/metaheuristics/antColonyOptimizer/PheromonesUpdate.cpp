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
 * @file PheromonesUpdate.cpp
 * @author Josué Tambwe
 * @date 1 May 2026
 */

 #include "metaheuristics/antColonyOptimizer/PheromonesUpdate.hpp"


 namespace gap::ACO{




    void partialEvaporation(int start,
                            int end,
                            float rho,
                            std::vector<std::vector<float>> &pheromone_matrix){

        for(int agent = 0; agent < static_cast<int>(pheromone_matrix.size()); agent++){

            for(int task = start; task <= end; task++){

                pheromone_matrix[agent][task] = std::max(min_pheromone, 
                                                        (1.0f - rho) * pheromone_matrix[agent][task]);

            }

        }

    }

    





    void pheromoneMatrixEvaporation(gap::Params &params,
                                    std::vector<std::vector<float>> &pheromone_matrix){


        int work_size = static_cast<int>(pheromone_matrix[0].size());
        int nb_threads_used = std::min(params.nb_threads, work_size);
        std::vector<std::thread> workers(nb_threads_used);

        // performing the pheromones evaporation 
        for(int id = 0; id < nb_threads_used; id++){

            int start = start_index(id, work_size, nb_threads_used);
            int end = end_index(id, work_size, nb_threads_used);

            workers[id] = std::thread(partialEvaporation,
                                      start,
                                      end,
                                      params.rho,
                                      std::ref(pheromone_matrix));

        }

        // waiting for all threads to finish
        for(auto &worker : workers){worker.join();}


    }





    void pheromoneDeposit(float inverse_reference_value,
                          float max_pheromone,
                          gap::GapSolution &solution,
                          gap::GapInstance &instance,
                          std::vector<std::vector<float>> &pheromone_matrix){


        float delta = computeDelta(solution.objectiveValue(instance),
                                   inverse_reference_value);

        std::vector<int>& solution_vector =  solution.getSolutionVector();

        for(int task = 0; task < static_cast<int>(solution_vector.size()); task++){

            int agent = solution_vector[task];
            pheromone_matrix[agent][task] = std::min(max_pheromone,
                                                     pheromone_matrix[agent][task] + delta);

        }


    }






 }