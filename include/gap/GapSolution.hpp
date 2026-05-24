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
 * @class GapSolution
 * @file GapSolution.hpp
 * @brief Stores a solution relating to an instance of the Generalized Assignment Problem
 * @author Josué Tambwe
 * @date 25 Feb 2026
 */
 #pragma once
 
 #include "gap/Status.hpp"
 #include "utils/Logger.hpp"
 #include "gap/GapInstance.hpp"
 #include "output/OutputFormat.hpp"
 #include "output/OutputConfig.hpp"
 #include <vector>
 #include <unordered_set>
 #include <iostream>
 #include <cstdint>


 namespace gap{

    class GapSolution{
        private:
            size_t nb_agent; ///< number of agent of the related instance of the G.A.P
            gap::Status status; ///< status of the solution
            std::vector<int> solution; ///< 1D vector of encoding the solution of the assignment

            bool assignmentChecker();  ///< checks the tasks assigment constraints
            bool capacityChecker(gap::GapInstance &instance); ///< checks the agents capacity constraints
            void computeIndividualWeight(std::vector<int> &weight_agent,
                                              std::vector<int> &individual_cost,
                                              std::vector<std::unordered_set<int>> &tasks,
                                              gap::GapInstance &instance,
                                              std::int64_t &obj) const;

        public:
            
            // default constructor
            GapSolution() = default;
            // constructor
            GapSolution(gap::GapInstance &instance);
            /**
            * @brief checks weither the solution is feasible or not with respect to the instance data associated with
            */
            bool isFeasible(gap::GapInstance &instance);
            /**
            * @brief computes the value of the objective function with respect to the instance data associated with
            */
            std::int64_t objectiveValue(gap::GapInstance &instance);
            /**
            * @brief prints the corresponding assignment of tasks to agents
            */
            void print(gap::GapInstance &instance) const;

            // Getters
            size_t getNbAgent();
            size_t getNbTask();
            gap::Status getStatus();
            std::vector<int>& getSolutionVector();

            // setter
            void setStatus(gap::Status status);


    };
 }