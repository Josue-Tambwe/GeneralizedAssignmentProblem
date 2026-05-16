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
 * @date 23 Feb 2026
 */
 
 #include "gap/GapSolution.hpp"

 namespace gap{
    GapSolution::GapSolution(gap::GapInstance &instance){

        this-> nb_agent = instance.getNbAgent();
        this-> status = gap::Status::UNKNOWN;
        this-> solution = std::vector<int>(instance.getNbTask(), -1);
    }


    

    bool GapSolution::assignmentChecker(){

        for(int &element : solution){

            if(element == -1){return false;} // when a task is not assigned to an agent
        }

        return true; // when all tasks are assigned
    }




    bool GapSolution::capacityChecker(gap::GapInstance &instance){
        
        const std::vector<int>& capacity_vector = instance.getCapacity();
        const std::vector<std::vector<int>>& weight_matrix = instance.getWeight();
        std::vector<int> capacity_used(instance.getNbAgent(), 0);
        int agent;

        // computation of the capacity used by each agent
        for(size_t task = 0; task < solution.size(); task++){

            agent = solution[task];
            capacity_used[agent] += weight_matrix[agent][task];
        }

        // checking that an agent is not overloaded
        for(size_t i = 0; i < nb_agent; i++){

            if(capacity_used[i] > capacity_vector[i]){
               return false; 
            }
        }

        return true;
    }




    bool GapSolution::isFeasible(gap::GapInstance &instance){

        bool checker = assignmentChecker();

        if(!checker){return false;}
            
        else{return capacityChecker(instance);}
    }




    std::int64_t GapSolution::objectiveValue(gap::GapInstance &instance){

        std::int64_t obj = 0;
        const std::vector<std::vector<int>> & cost_matrix = instance.getCost();

        for(size_t j = 0; j < solution.size(); j++){

            int agent = solution[j];
            obj += cost_matrix[agent][j];
        }

        return obj;
    }




    void GapSolution::computeIndividualWeight(std::vector<int> &weight_agent,
                                                   std::vector<int> &individual_cost,
                                                   std::vector<std::unordered_set<int>> &tasks,
                                                   gap::GapInstance &instance,
                                                   std::int64_t &obj) const{

        const std::vector<std::vector<int>>& weight_matrix = instance.getWeight();
        const std::vector<std::vector<int>> & cost_matrix = instance.getCost();

        for(size_t j = 0; j < solution.size(); j++){

            int agent = solution[j];
            weight_agent[agent] += weight_matrix[agent][j];
            individual_cost[agent] += cost_matrix[agent][j];
            tasks[agent].insert(j);
            obj += cost_matrix[agent][j];
        }

    }




    void GapSolution::print(gap::GapInstance &instance) const{
        
        if(this-> status != gap::Status::FEASIBLE &&
            this-> status != gap::Status::OPTIMAL){
            gap::Logger log;
            switch(this->status){
                case gap::Status::INFEASIBLE : 
                    log.warning("the solution status is INFEASIBLE ");
                    break;

                default :
                    log.warning("the solution is has not been constructed yet! ");
                    break;
            }
        }
        else{
            std::vector<int> weight_agent(nb_agent, 0);
            std::vector<std::unordered_set<int>> tasks(nb_agent);
            std::vector<int> individual_cost(nb_agent);
            std::int64_t obj = 0;

            GapSolution::computeIndividualWeight(weight_agent, individual_cost, tasks, instance, obj);
            const std::vector<int>& capacity_vector = instance.getCapacity();
            
            std::cout << "\n";
            std::cout << std::string(100, '*') << std::endl;
            std::cout << setw(50) << right << "Solution" << "\n";
            std::cout << std::string(100, '-') << std::endl;
            
            for(size_t i = 0; i < nb_agent; i++){

                std::cout << " agent " << (i+1) << " = [";
                for(int task : tasks[i]){std::cout << (task + 1) << " ";}
                std::cout << "] \n" << std::endl;

                std::cout << " capacity used            : " << weight_agent[i] << std::endl;
                std::cout << " maximum capacity         : " << capacity_vector[i] << std::endl;
                std::cout << " capacity left            : " << (capacity_vector[i] - weight_agent[i]) << std::endl;
                std::cout << "\n";
                std::cout << " number of tasks assigned : " << tasks[i].size() << std::endl;
                std::cout << " individual cost          : " << individual_cost[i] << std::endl;
                std::cout << std::string(100, '-') << std::endl;

            }
            std::cout << " total cost               : " << obj << std::endl;
            std::cout << std::string(100, '*') << std::endl;
            std::cout << "\n";
        }
    }
    


    // getters

    size_t GapSolution::getNbAgent(){return nb_agent;}
    size_t GapSolution::getNbTask(){return solution.size();}
    gap::Status GapSolution::getStatus(){return status;}
    std::vector<int>& GapSolution::getSolutionVector(){return solution;}

    // setter

    void GapSolution::setStatus(gap::Status stat){this-> status = stat;}
 }