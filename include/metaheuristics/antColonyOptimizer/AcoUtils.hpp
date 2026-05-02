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
 * @file AcoUtils.hpp
 * @brief This file defines some functions used during the construction of ant solution in the Ant Colony Optimizer algorithm
 * @author Josué Tambwe
 * @date 28 April 2026
 */

 #pragma once

 #include "input/Parameters.hpp"
 #include <algorithm>
 #include <cstdint>


 namespace gap::ACO{


    /**
     *@brief the lower bound of phoromones
     */
    const float min_pheromone = 1e-3;
    


    /**
     * @brief computes the linear decreasing function for the probability threshold q_0 at the time t
     *        q_0 determines wether the ant chooses exploitation (heuristic choice) or collective experience (pheromone-based choice)
     *        q_0 (t) = q_start + rate * (q_end - q_start)
     */

    const double q_start = 0.1;
    const double q_end = 0.9;

    inline double computeProbabilityThreshold(int current_iteration,
                                       double inverse_max_iteration,
                                       double current_time,
                                       double inverse_max_time,
                                       gap::Params &params){

        if(params.use_time_limit){
            return (q_end - q_start) * (current_time * inverse_max_time) + q_start;
        }
        else{
            return (q_end - q_start) * (current_iteration * inverse_max_iteration) + q_start;
        }
    }





    /**
     *@brief computes the inverse of the objective value of the reference ant.
     *       this value is used to compute the value of "delta" : the amount of pheromone to
     *       drop when considering pheromone deposit
     */
    inline float computeInverseReferenceValue(std::int64_t reference_value){

        return (1.0f / (static_cast<float>(reference_value) + epsilon));
    }




    /**
     * @brief check of the stopping criteria
     */
    inline bool stoppingCriteria(int current_iteration,
                                double current_time,
                                gap::Params &params){

        if(params.use_time_limit && !params.use_max_iterations){return current_time >= params.time_limit;}
        if(!params.use_time_limit && params.use_max_iterations){return current_iteration >= params.nb_max_iterations;}
        else{
            return (current_iteration >= params.nb_max_iterations) || (current_time >= params.time_limit);
        }
        
    }




    /**
     * @brief computes the initial amount of pheromone deposit : 1 / (f_ref * rho)
     *         f_ref : is the reference value (objective value of the reference ant)
     *         rho   : is the parameter that determines the evaporation rate
     */
    inline float computeInitialPheromone(float inverse_reference_value,
                                         gap::Params &params){
        
        return (inverse_reference_value / (params.rho + epsilon));

    }


    /**
     * @brief computes the heuristic score etha = 1 - (weight / max_weight)
     *        weight     : is the task when assign to the considered agent
     *        max_weight : the maximum weight of unassigned tasks
     *        the score is greater for agents on who the task weights less 
     */  
    inline float computeEta(int weight, float inverse_max_weight){return 1.0f - (weight * inverse_max_weight);}
    
    


    /**
     * @brief computes the inverse of the denominator "max weight" which is used in the 
     *        computation of the eta heuristic score
     */
    inline float computeInverseMaxWeight(int max_weight){return 1 / (max_weight + epsilon);}



    /**
     * @brief computes the heuristic score of a variable x_ij : (tau_ij)^alpha * (eta_ij)^beta
     *        when the decision is to choose the variable x_ij that maximize the heuristic score
     */
    inline float heuristic_score(float tau,
                                float eta,
                                gap::Params &params){

        // 'b' : balance -> alpha = beta = 1              
        if(params.influence == 'b'){return tau * eta;}

        // 'h' : heuristic -> alpha = 1 and beta = 2
        if(params.influence == 'h'){return tau * eta * eta;}

        // 'p' : pheromone -> alpha = 2 and beta = 1
        return tau * tau * eta;

    }




    /**
     * @brief computes the uppper bound of pheromones
     */
    inline float computeMaximumPheromone(gap::Params &params){

        if(params.rho != 0.0f){
            return (1 / params.rho);
        }
        else{
            return 100.0f; // 1 / 10^-2
        }
    }



    
    /**
     * @brief computes the pheromone deposition on the solution of the best ant
     */
    inline float computeDelta(std::int64_t best_ant_value, 
                              float inverse_reference_value){

        return std::max(0.0f, 1.0f - (static_cast<float>(best_ant_value) * 
                                      inverse_reference_value));
    }





 }