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

 #include "metaheuristics/antColonyOptimizer/AntColonyOptimizer.hpp"
 
 namespace gap::ACO{

    void assignFirstTaskRandomly(std::unordered_set<int> &tasks,
                                std::vector<int> &residual_capacity,
                                gap::GapSolution &solution,
                                gap::GapInstance &instance){

        int nb_task = static_cast<int>(instance.getNbTask());
        int nb_agent = static_cast<int>(instance.getNbAgent());
        const std::vector<std::vector<int>>& weight_matrix = instance.getWeight();
        std::vector<int>& solution_vector =  solution.getSolutionVector();

        auto& rng = getThreadLocalRng();
        std::uniform_int_distribution<int> dist_task(0, (nb_task - 1));
        std::uniform_int_distribution<int> dist_agent(0, (nb_agent - 1));
        bool assignment_performed = false;
        int first_task;
        int agent;

        while(!assignment_performed){

            first_task = dist_task(rng);
            agent = dist_agent(rng);
            // ensuring the capacity constraint
            if(weight_matrix[agent][first_task] <= residual_capacity[agent]){
                // performing the assignment
                solution_vector[first_task] = agent;
                // updating the agent residual capacity
                residual_capacity[agent] -= weight_matrix[agent][first_task];
                // removing the task assigned from the set of tasks available
                tasks.erase(first_task);
                return;
            }
        }
        

    }

 }