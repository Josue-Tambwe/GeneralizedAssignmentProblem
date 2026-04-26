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
                                 float gamma,
                                 std::vector<int> &residual_capacity,
                                 gap::GapSolution &solution,
                                 gap::GapInstance &instance){

        // initialization of the thread random number generator
        auto& rng = getThreadLocalRng();
        
        // initialization of the uniform (discrete) distribution on tasks
        int nb_task = static_cast<int>(instance.getNbTask());
        std::uniform_int_distribution<int> dist_task(0, (nb_task - 1));

        // picking the first task randomly
        int first_task = dist_task(rng); 

        // initialization of the uniform (discrete) distribution on agents
        int nb_agent = static_cast<int>(instance.getNbAgent());

        const std::vector<std::vector<int>>& weight_matrix = instance.getWeight();

        // finding the max and min weights
        int max_weight = weight_matrix[0][first_task];
        int min_weight = weight_matrix[0][first_task];

        for(int agent = 1; agent < nb_agent; agent++){
            if(weight_matrix[agent][first_task] > max_weight){max_weight = weight_matrix[agent][first_task];}
            if(weight_matrix[agent][first_task] < min_weight){min_weight = weight_matrix[agent][first_task];}
        }

        // computation of the threshold (min + gamma (max - min))
        int threshold = static_cast<int>(
                            std::ceil(min_weight + gamma * (max_weight - min_weight))
                        );

        // counter of agents that qualified to be assigned the first task
        int counter = 0;
        

        for(int agent = 0; agent < nb_agent; agent++){
            if(weight_matrix[agent][first_task] <= threshold && 
               residual_capacity[agent] >= weight_matrix[agent][first_task]){
                
                counter += 1;
            }
        }

        // picking the rank of the best agent in {1, ..., counter}
        std::uniform_int_distribution<int> dist_agent(1, counter);
        int random_agent_rank = dist_agent(rng);

        // performing the assignment
        std::vector<int>& solution_vector =  solution.getSolutionVector();
        counter = 0;

        for(int agent = 0; agent < nb_agent; agent++){

            if(weight_matrix[agent][first_task] <= threshold && 
               residual_capacity[agent] >= weight_matrix[agent][first_task]){
             
                counter += 1;
            }

            if(counter == random_agent_rank){
                // assignment
                solution_vector[first_task] = agent;
                // updating of the residual capacity
                residual_capacity[agent] -= weight_matrix[agent][first_task];
                // removing the assigned task from the unassigned tasks set
                tasks.erase(first_task);
                return;
            }
        }

        

    }
 }