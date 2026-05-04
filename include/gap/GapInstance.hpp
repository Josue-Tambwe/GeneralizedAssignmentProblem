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
 * @class GapInstance
 * @file GapInstance.hpp
 * @brief Stores and loads instance data for the Generalized Assignment Problem
 * @author Josué Tambwe
 * @date 23 Feb 2026
 */



#pragma once

#include "input/Parameters.hpp"
#include "utils/Logger.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>


namespace gap{ 

struct InstanceStatistics{
    int nb_agent;
    int nb_task;

    int max_cost_task;
    int min_cost_task;

    int max_weight_task;
    int min_weight_task;

    int max_capacity_agent;
    int min_capacity_agent;

};

class GapInstance{
    private: 
        std::string file_name; ///< Name of the instance
        size_t nb_agent; ///<  Number of agents
        size_t nb_task; ///< Number of tasks

        std::vector<std::vector<int>> cost; ///< Cost matrix
        std::vector<std::vector<int>> weight; ///< Weight matrix
        std::vector<int> capacity; /// Capacity of each agent

        InstanceStatistics statistics;
        

    public:

        /**
         * @brief constructor : builds instance from a file 
         */
        GapInstance(gap::Params params);
        
        /**
         * @brief prints the instance data 
         */

        void print() const;

        // Getters

        size_t getNbAgent();
        size_t getNbTask();
        std::string getFileName();

        const std::vector<std::vector<int>>& getCost();
        const std::vector<std::vector<int>>& getWeight();
        const std::vector<int>& getCapacity();
        const InstanceStatistics& getStatistics();

};

}