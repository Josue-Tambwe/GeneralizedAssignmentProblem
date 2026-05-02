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
 * @file PheromonesUpdate.hpp
 * @brief Takes care of pheromones management : evaporation and deposit
 * @author Josué Tambwe
 * @date 1 May 2026
 */

 #pragma once

 #include "hpc/cpu/Thread.hpp"
 #include "gap/GapInstance.hpp"
 #include "gap/GapSolution.hpp"
 #include "input/Parameters.hpp"
 #include "configuration/Config.hpp"
 #include "metaheuristics/antColonyOptimizer/AlignedMatrix.hpp"
 #include "metaheuristics/antColonyOptimizer/AcoUtils.hpp"
 #include <vector>
 #include <unordered_set>
 #include <cmath>



 namespace gap::ACO{


    //----------------------------------- WITHOUT SIMD VECTORIZATION -----------------------------------

    /**
     *@brief performs a partial evaporation on the pheromone matrix  (for a single thread)
     */
    void partialScalarEvaporation(int start,
                                  int end,
                                  float rho,
                                  AlignedMatrix &pheromone_matrix);




    /**
     *@brief performs the evaporation on the pheromone matrix without using SIMD vectorization
     */
    void scalarPheromoneMatrixEvaporation(gap::Params &params,
                                          AlignedMatrix &pheromone_matrix);




    /**
     *@brief performs the pheromone deposit on the solution of the best ant
     */
    void pheromoneDeposit(float inverse_reference_value,
                          float max_pheromone,
                          gap::GapSolution &solution,
                          gap::GapInstance &instance,
                          AlignedMatrix &pheromone_matrix);


    //----------------------------------- END WITHOUT SIMD VECTORIZATION -----------------------------------


 }