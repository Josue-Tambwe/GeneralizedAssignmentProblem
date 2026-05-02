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
 * @file GreedyLocalSearchMinCost.hpp
 * @brief  improves a solution of an instance of the Generalized Assignment Problem 
 * constructed by a Greedy approch
 * @author Josué Tambwe
 * @date 17 Mar 2026
 */

 #pragma once 

 #include "gap/GapInstance.hpp"
 #include "gap/GapSolution.hpp"
 #include "metaheuristics/greedy/GreedyElement.hpp"
 #include "hpc/cpu/Thread.hpp"
 #include "configuration/Config.hpp"
 #include "input/Parameters.hpp"
 #include <vector>
 #include <queue>

 namespace gap::greedy{

  /**
    * @brief Computation of  agents residual capacities within the current solution
    */

   std::vector<int> computeResidualCapacity(gap::GapSolution &solution,
                                          gap::GapInstance &instance);


  // -------------------------------  BALANCE MOVE (NEIGHBORHOOD) ----------------------------                                   
  
   /**
    * @brief Computation of the assignment cost of an individual agent within the current solution
    */

   std::vector<int> computeIndividualCostAgent(gap::GapSolution &solution,
                                              gap::GapInstance &instance);


   /**
    * @brief The global most and least expensive agents are identified in order to transfer (if it is possible) a task
    *        from the most expensive agent to the least expensive agent while reducing the global cost
    */

   void findMostAndLeastExpensiveAgents(int &most_expensive_agent,
                                      int &least_expensive_agent,
                                      std::vector<int> &individual_cost_agents);


  /**
    * @brief After  both  global most and least expensive agents are identified, the tasks on the most
    *        expensive agent are sorted regarding the criteria :  cost / weight
    *         - cost   :  the cost of the task when assigned to the least expensive agent
    *         - weight :  the weight of the task when assigned to the least expensive agent 
    *       This creteria allows the most expensive (relatively to their weight) tasks on the least expensive agent to be treated first
    *       therefore the residual capacity of the least expensive agent is used more efficiently to drastically reduce the global cost
    */

  void sortTaskFromMostToLeastExpensive(int most_expensive_agent,
                                        int least_expensive_agent,
                                        std::priority_queue<gap::greedy::Element> &tasks,
                                        gap::GapSolution &solution,
                                        gap::GapInstance &instance);


   /**
    * @brief When tasks of the most expensive agent had been sorted regarding the previous criteria on the least expensive agent,
    *        attempt of re-assignment of tasks are performed
    */

   int assignTaskFromMostToLeastExpensive(std::vector<int> &residual_capacity,
                                        gap::GapSolution &solution,
                                        gap::GapInstance &instance);


   /**
    * @brief After the greedy construction, this move consists in finding the global most expensive
    *        agent and re-assigning one of its task to the global least expensive agent if the global cost is reduced
    */
  
   void balanceMove(gap::GapSolution &solution,
                    gap::GapInstance &instance);

  // -------------------------------  END BALANCE MOVE (NEIGHBORHOOD) ---------------------------- 



  

  // -------------------------------  CHEAP MOVE (NEIGHBORHOOD) ---------------------------- 
   
  /**
    * @brief For the given task, the agents are sorted from the most cheaper agent to the least cheaper one,
    *        regarding the criteria : 1 / cost. 
    *        This criteria is greater when the assignment cost for the given task to an agent is low 
    *        The criteria allows cheaper agents to be treated first
    */
   void sortCheapAgent(int task,
                      int current_agent,
                      std::priority_queue<gap::greedy::Element> &agents,
                      gap::GapInstance &instance);


   /**
    * @brief Computation of the score of a given task. the score consists in the gain of cost reduce when the
    *        given task is re-assigned to another agent. Since the agent are sorted from the most chearper agents
    *        to the least cheaper agents for the given task, this function checks the best suitable (cheapest) agents first
    */
   void computeScoreTask(int task,
                        std::vector<int> &residual_capacity,
                        std::vector<int> &tasks_scores,
                        std::vector<int> &tasks_best_agent,
                        gap::GapSolution &solution,
                        gap::GapInstance &instance);
  

  /**
    * @brief Computation of the score  a group of tasks by a single CPU thread. 
    *        The thread starts computing the score of tasks from the tasks at the index "start" to the index "end"
    */                      
  void computeGroupScoreTask(int start,
                            int end,
                            std::vector<int> &residual_capacity,
                            std::vector<int> &tasks_scores,
                            std::vector<int> &tasks_best_agent,
                            gap::GapSolution &solution,
                            gap::GapInstance &instance);

  
  /**
    * @brief Computation of the score  a group of tasks in parallel (with "nb_threads" threads running concurrently) 
    *        the task with the greatest score is returned
    *        a task with the greatest score represents the one with the greatest gain in cost reduced when that task
    *        is re-assigned to a cheaper agent. That cheaper agent for this task has been memorised during the computation of the task score
    */                           
  int findBestTask(int nb_threads,
                  std::vector<int> &residual_capacity,
                  std::vector<int> &tasks_best_agent,
                  gap::GapSolution &solution,
                  gap::GapInstance &instance);


  /**
    * @brief This method computes, in a loop ,  the re-assignment of task from the current agent to the cheaper agent 
    *        while reducing the global cost, until an improvement is no longer possible
    */                
  int assignTaskToCheapAgent (int nb_threads,
                              std::vector<int> &residual_capacity,
                              gap::GapSolution &solution,
                              gap::GapInstance &instance);


  /**
    * @brief After the greedy construction and the balance move (neighborhood), this move consists in finding tasks that could be re-assigned to
    *        agents  that are cheaper for those taks than the current agents that those tasks are assigned to in order to reduce the global cost      
    */
  void cheapMove(int nb_threads,
                gap::GapSolution &solution,
                gap::GapInstance &instance);

  // -------------------------------  END CHEAP MOVE (NEIGHBORHOOD) ---------------------------- 
  



  /**
    * @brief This method performs at first the balance move neighborhood and the the cheap move neighborhood
    */
  void localSearch(gap::Params &params,
                gap::GapSolution &solution,
                gap::GapInstance &instance);

 }
