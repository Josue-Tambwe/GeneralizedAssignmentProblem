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
 * @file GapInstance.cpp
 * @author Josué Tambwe
 * @date 25 Feb 2026
 */

 #include "gap/GapInstance.hpp"

namespace gap{


GapInstance::GapInstance(gap::Params params){
    // opening the file
    std::ifstream file(params.instance_path);
    
    if (!file.is_open()) {

        Logger log;
        log.error("Error in opening the file");}
        
    else{

        this-> file_name = params.instance_path;
        file >> nb_agent;
        file >> nb_task;

        // Initializing vectors
        this->cost = std::vector<std::vector<int>>(nb_agent, std::vector<int>(nb_task));
        this->weight = std::vector<std::vector<int>>(nb_agent, std::vector<int>(nb_task));
        this->capacity = std::vector<int>(nb_agent);

        // statistics on data

        int max_cost_task = 0;
        int min_cost_task = std::numeric_limits<int>::max();

        int max_weight_task = 0;
        int min_weight_task = std::numeric_limits<int>::max();

        int max_capacity_agent = 0;
        int min_capacity_agent = std::numeric_limits<int>::max();

        // loading the cost matrix 
        for (size_t i = 0; i < nb_agent; i++) {

            for (size_t j = 0; j < nb_task; j++) {

                file >> cost[i][j];
                if(cost[i][j] >= max_cost_task){max_cost_task = cost[i][j];}
                if(cost[i][j] <= min_cost_task){min_cost_task = cost[i][j];}
            }
        }

        // loading the weight matrix
        for (size_t i = 0; i < nb_agent; i++) {
            for (size_t j = 0; j < nb_task; j++) {

                file >> weight[i][j];
                if(weight[i][j] >= max_weight_task){max_weight_task = weight[i][j];}
                if(weight[i][j] <= min_weight_task){min_weight_task = weight[i][j];}
            }
        }

        // loading the agent capacity vector
        for(size_t i = 0; i < nb_agent; i++){

            file >> capacity[i];
            if(capacity[i] >= max_capacity_agent){max_capacity_agent = capacity[i];}
            if(capacity[i] <= min_capacity_agent){min_capacity_agent = capacity[i];}
        }

        // initialization of data statistics
        this->statistics  = {static_cast<int>(nb_agent),
                             static_cast<int>(nb_task),
                             max_cost_task,
                             min_cost_task,
                             max_weight_task,
                             min_weight_task,
                             max_capacity_agent,
                             min_capacity_agent};
    }
}

void GapInstance::print()const{

    if(cost.size() == 0 || weight.size() == 0 || capacity.size() == 0){

        Logger log;
        log.error("Incomplete data!");
        std::cout << "\n";
    }
    else{

        std::cout << std::string(100, '=') << std::endl;
        std::cout << " file name          : " << this-> file_name << std::endl;
        std::cout << " number of agents   : " << this-> nb_agent << std::endl;
        std::cout << " number of tasks    : " << this-> nb_task  << std::endl;

        std::cout << std::string(100, '-') << std::endl;
        std::cout << "\n";

        std::cout << " Cost matrix : \n" << std::endl;

        for (size_t i = 0; i < nb_agent; i++) {

            for (size_t j = 0; j < nb_task; j++) {
                std::cout << cost[i][j] << " ";
            }

            std::cout << "\n";
            std::cout << std::endl;
        }

        std::cout << std::string(100, '-') << std::endl;
        std::cout << "\n";

        std::cout << " Weight matrix : \n" << std::endl;

        for (size_t i = 0; i < nb_agent; i++) {

            for (size_t j = 0; j < nb_task; j++) {

                std::cout << weight[i][j] << " ";
            }

            std::cout << "\n";
            std::cout << std::endl;
        }

        std::cout << std::string(100, '-') << std::endl;
        std::cout << "\n";

        std::cout << " Capacity vector : \n" << std::endl;

        for(int cap : capacity){
            std::cout << cap << " ";
        }
        
        std::cout << "\n \n";
        std::cout << std::string(100, '=') << std::endl;
    }
    
}

size_t GapInstance::getNbAgent(){return nb_agent;}
size_t GapInstance::getNbTask(){return nb_task;}
std::string GapInstance::getFileName(){return file_name;}

const std::vector<std::vector<int>>& GapInstance::getCost(){return cost;}
const std::vector<std::vector<int>>& GapInstance::getWeight(){return weight;}
const std::vector<int>& GapInstance::getCapacity(){return capacity;}
const InstanceStatistics& GapInstance::getStatistics(){return statistics;}

}