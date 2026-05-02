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
 * @file OutputFormat.cpp
 * @author Josué Tambwe
 * @date 17 Mar 2026
 */

 #include "output/OutputFormat.hpp"

 namespace gap{

    void printHeader(){

        std::cout << "\n";
        std::cout << setw(35) << right << " " << std::string(50, '=') << "\n";
        std::cout << setw(85) << right << "  GAP-Solver : Generalized Assignment Problem Solver" << "\n";
        std::cout << setw(35) << right << " " << std::string(50, '=') << "\n\n";
    }



    void printUsage(){

        std::cout << " Usage:\n";
        std::cout << " ------\n\n";
        std::cout << "    gap_solver [OPTIONS]\n\n\n";
    }



    void printRequiredOptions(){

        std::cout << " Required options:\n";
        std::cout << " -----------------\n\n";

        std::cout << "    " << setw(22) << left << "--algorithm=value"
                  << "Algorithm to use (greedy, aco, bab)\n \n";

        std::cout << "    " << setw(22) << left << "--instance=path"
                  << "Path to the instance file\n\n";

        std::cout << "    " << setw(22) << left << "--nb-ants=value"
                  << "Number of ants within a colony for the ACO algorithm \n\n \n";
    }



    void printOptionalOptions(){

        std::cout << " Optional options:\n";
        std::cout << " -----------------\n \n";

        std::cout << "  " << setw(27) << left << "--nb-threads=value"
                  << "Number of threads (default: NUMBER_PHYSICAL_CORES)\n \n";

        std::cout << "  " << setw(27) << left << "--verbose"
                  << "Enable verbose mode \n \n";


        std::cout << "  " << setw(27) << left << "--low-cost-construction" 
                  << "Enable the cost-and-weight based priority rule when building initial solution for the Greedy algorithm\n\n";

        std::cout << "  " << setw(27) << left << "--time-limit=value"
                  << "Time limit in seconds (default: 10)\n \n";

        std::cout << "  " << setw(27) << left << "--iterations=value"
                  << "Number of maximum iterations for the ACO algorithm (default: 1)\n \n";


        std::cout << "  " << setw(27) << left << "--influence=value"
                  << "Major influence in an ant solution construction  for the ACO algorithm  (values : balance, pheromone, heuristic) \n \n";

        std::cout << "  " << setw(27) << left << "--rho=value"
                  << "Rate in [0,1] of pheromones evaporation for the ACO algorithm (default: 0.1)\n \n";

        std::cout << "  " << setw(27) << left << "--gamma=value"
                  << "Rate in [0,1] of randomization  for the assignment of the first task  for the ACO algorithm (default: 0.5)\n \n \n";

        
    }




    void printExampleRun(){

        std::cout << " Examples:\n";
        std::cout << " ---------\n\n";

        std::cout << "    gap_solver --algorithm=greedy "
                  << "--instance=../benchmarks/gap_a/a05100 --verbose\n\n";

        std::cout << "    gap_solver --algorithm=antColony "
                  << "--instance=../benchmarks/gap_a/a05100 --time-limit=30  --nb-ants=100  --influence=pheromone --rho=0.15 \n\n \n";
    }




    void printHelp(){

        printHeader();
        printUsage();
        printRequiredOptions();
        printOptionalOptions();
        printExampleRun();
        std::exit(0);
    }



    void printHeaderGreedy(gap::Params &params,
                           gap::GapInstance &instance){

        const gap::InstanceStatistics& stats = instance.getStatistics();

        const int w_inst_label = 24;
        const int w_inst_sep   = 2;
        const int w_inst_value = 14;

        const int w_algo       = 30;
        const int w_set_label  = 20;
        const int w_set_sep    = 2;
        const int w_set_value  = 14;
        const int w_flags      = 26;

        // Headers
        std::cout << YELLOW;
        std::cout << std::left << std::setw(w_inst_label + w_inst_sep + w_inst_value) << " Instance statistics";
        std::cout << std::left << std::setw(w_algo)    << " Algorithm";
        std::cout << std::left << std::setw(w_set_label + w_set_sep + w_set_value) << " Setting";
        std::cout << std::left << std::setw(w_flags)   << "  Flags";
        std::cout << RESET << "\n";

        std::cout << std::left << std::setw(w_inst_label + w_inst_sep + w_inst_value) << " -------------------"
                << std::left << std::setw(w_algo)    << " ---------"
                << std::left << std::setw(w_set_label + w_set_sep + w_set_value) << " -------"
                << std::left << std::setw(w_flags)   << "  -----"
                << "\n";

        std::cout << std::left  << std::setw(w_inst_label) << " number of agents"
                << std::right << std::setw(w_inst_sep)   << " : "
                << std::left  << std::setw(w_inst_value) << stats.nb_agent;

        std::cout << MAGENTA;
        std::cout << std::left  << std::setw(w_algo)       << " Greedy";
        std::cout << RESET;

        std::cout << std::left  << std::setw(w_set_label)  << "nb threads used"
                << std::right << std::setw(w_set_sep)    << " : "
                << std::left  << std::setw(w_set_value)  << params.nb_threads;

        std::cout << std::left << std::setw(w_flags - 16) << "verbose";
        std::cout << std::right << std::setw(14) << " : ";

        if(params.verbose)
        {
            std::cout << GREEN << "Enabled" << RESET;
        }

        else
        {
            std::cout << RED << "Disabled" << RESET;
        }

        std::cout << "\n";

        std::cout << std::left  << std::setw(w_inst_label) << " number of tasks"
                << std::right << std::setw(w_inst_sep)   << " : "
                << std::left  << std::setw(w_inst_value) << stats.nb_task
                << std::left  << std::setw(w_algo)       << ""
                << std::left  << std::setw(w_set_label)  << "nb physical cores"
                << std::right << std::setw(w_set_sep)    << " : "
                << std::left  << std::setw(w_set_value)  << NUMBER_PHYSICAL_CORES;
        std::cout << std::left << std::setw(w_flags - 16) << "low cost construction";
        std::cout << std::right << std::setw(3) << " : ";

        if(params.low_cost_construction)
        {
        std::cout << GREEN << "Enabled" << RESET;
        }

        else
        {
        std::cout << RED << "Disabled" << RESET;
        }

        std::cout << std::left  << std::setw(w_flags) << "";

        std::cout << "\n";

        std::cout << std::left  << std::setw(w_inst_label) << " task cost range"
                << std::right << std::setw(w_inst_sep)   << " : "
                << std::left  << std::setw(w_inst_value)
                << (std::to_string(stats.min_cost_task) + " - " + std::to_string(stats.max_cost_task))
                << "\n";

        std::cout << std::left  << std::setw(w_inst_label) << " task weight range"
                << std::right << std::setw(w_inst_sep)   << " : "
                << std::left  << std::setw(w_inst_value)
                << (std::to_string(stats.min_weight_task) + " - " + std::to_string(stats.max_weight_task))
                << "\n";

        std::cout << std::left  << std::setw(w_inst_label) << " agent capacity range"
                << std::right << std::setw(w_inst_sep)   << " : "
                << std::left  << std::setw(w_inst_value)
                << (std::to_string(stats.min_capacity_agent) + " - " + std::to_string(stats.max_capacity_agent))
                << "\n\n";
    }



    
    void finalStatisticsGreedy(double construction_time,
                            std::int64_t construction_value,
                            gap::Status &construction_status,
                            double local_time,
                            std::int64_t local_search_value,
                            gap::Status &local_search_status){


        const int w_step = 16;
        const int w_time = 12;
        const int w_obj  = 20;
        const int gap    = 8; 
        
        std::cout << "\n";

        // headers
        std::cout << YELLOW;
        
        std::cout << std::left  << std::setw(w_step) << " Steps";
        std::cout << std::right << std::setw(w_time) << "Time (s)";
        std::cout << std::string(gap, ' ');
        std::cout << std::right << std::setw(w_obj)  << "Objective value";
        std::cout << std::string(gap, ' ');
        std::cout << std::left  << "Status";
        std::cout << RESET << "\n";

        std::cout << std::left  << std::setw(w_step) << " -----"
                << std::right << std::setw(w_time) << "--------"
                << std::string(gap, ' ')
                << std::right << std::setw(w_obj)  << "---------------"
                << std::string(gap, ' ')
                << std::left  << "-------\n";

        // Construction
        std::cout << std::left  << std::setw(w_step) << " Construction"
                << std::right << std::setw(w_time) << std::fixed << std::setprecision(4) << construction_time
                << std::string(gap, ' ');

        std::cout << BRIGHT_YELLOW;
        std::cout << std::right << std::setw(w_obj) << construction_value;
        std::cout << RESET;

        std::cout << std::string(gap, ' ')
                << std::left  << construction_status << "\n";

        // Local search
        std::cout << std::left  << std::setw(w_step) << " Local search"
                << std::right << std::setw(w_time) << std::fixed << std::setprecision(4) << local_time
                << std::string(gap, ' ');

        std::cout << BRIGHT_CYAN;
        std::cout << std::right << std::setw(w_obj) << local_search_value;
        std::cout << RESET;

        std::cout << std::string(gap, ' ')
                << std::left  << local_search_status << "\n";

        std::cout << "\n";

        // gap
        std::int64_t abs_gap = construction_value - local_search_value;
        double rel_gap = 100.0 * (double(abs_gap) / double(construction_value));

        std::cout << YELLOW << " gap" << RESET << "\n";
        std::cout << " ---\n";
        std::cout << " absolute improvement gap     : " <<  CYAN << abs_gap << RESET << "\n";
        std::cout << " relative improvement gap (%) : " << std::fixed << std::setprecision(4) <<  MAGENTA << rel_gap << "\n\n" << RESET;
    }




     void printHeaderACO(gap::Params& params,
                        gap::GapInstance &instance){

        const gap::InstanceStatistics& stats = instance.getStatistics();

        const int w_inst_label = 26;
        const int w_inst_sep   = 2;
        const int w_inst_value = 14;

        const int w_algo       = 25;
        const int w_set_label  = 20;
        const int w_set_sep    = 2;
        const int w_set_value  = 18;
        const int w_flags      = 26;

        // Headers
        std::cout << YELLOW;
        std::cout << std::left << std::setw(w_inst_label + w_inst_sep + w_inst_value + 5) << " Instance statistics";
        std::cout << std::left << std::setw(w_algo - 5)    << " Algorithm";
        std::cout << std::left << std::setw(w_set_label + w_set_sep + w_set_value) << " Setting";
        std::cout << std::left << std::setw(w_flags)   << "  Flags";
        std::cout << RESET << "\n";

        std::cout << std::left << std::setw(w_inst_label + w_inst_sep + w_inst_value + 5) << " -------------------"
                << std::left << std::setw(w_algo - 5)    << " ---------"
                << std::left << std::setw(w_set_label + w_set_sep + w_set_value) << " -------"
                << std::left << std::setw(w_flags)   << "  -----"
                << "\n";

        // line 1
        std::cout << std::left  << std::setw(w_inst_label) << " number of agents"
                << std::right << std::setw(w_inst_sep)   << " : "
                << std::left  << std::setw(w_inst_value) << stats.nb_agent;

        std::cout << MAGENTA;
        std::cout << std::left  << std::setw(w_algo)       << "Ant Colony Optimizer";
        std::cout << RESET;

        std::cout << std::left  << std::setw(w_set_label)  << "nb threads used"
                << std::right << std::setw(w_set_sep)    << " : "
                << std::left  << std::setw(w_set_value)  << params.nb_threads;

        std::cout << std::left << std::setw(w_flags - 19) << "verbose";
        std::cout << std::right << std::setw(3) << " : ";

        if(params.verbose)
        {
            std::cout << GREEN << "Enabled" << RESET;
        }

        else
        {
            std::cout << RED << "Disabled" << RESET;
        }

        std::cout << "\n";


        // line 2
        std::cout << std::left  << std::setw(w_inst_label) << " number of tasks"
                  << std::right << std::setw(w_inst_sep)   << " : "
                  << std::left  << std::setw(w_inst_value) << stats.nb_task
                  << std::left  << std::setw(w_algo)       << ""
                  << std::left  << std::setw(w_set_label)  << "nb physical cores"
                  << std::right << std::setw(w_set_sep)    << " : "
                  << std::left  << std::setw(w_set_value)  << NUMBER_PHYSICAL_CORES;


        // line 3 
        std::cout << std::left  << std::setw(w_inst_label) << ""
                << std::right << std::setw(w_inst_sep)   << ""
                << std::left  << std::setw(w_inst_value + 4) << ""
                << std::left << std::setw(w_set_label) << "nb ants"
                << std::right << std::setw(w_set_sep)    << " : "
                << std::left << std::setw(w_set_value) << params.nb_ants;

        std::cout << "\n";


        // line 4
        std::cout << std::left  << std::setw(w_inst_label) << " task cost range"
                << std::right << std::setw(w_inst_sep)   << " : "
                << std::left  << std::setw(w_inst_value)
                << (std::to_string(stats.min_cost_task) + " - " + std::to_string(stats.max_cost_task))
                << std::left  << std::setw(w_algo) << ""
                << std::left << std::setw(w_set_label) << "rho"
                << std::right << std::setw(w_set_sep) << " : "
                << std::left << std::setw(w_set_value) << params.rho
                << "\n";
        
        // line 5
        std::cout << std::left  << std::setw(w_inst_label) << " task weight range"
                << std::right << std::setw(w_inst_sep)   << " : "
                << std::left  << std::setw(w_inst_value)
                << (std::to_string(stats.min_weight_task) + " - " + std::to_string(stats.max_weight_task))
                << std::left  << std::setw(w_algo) << ""
                << std::left << std::setw(w_set_label) << "gamma"
                << std::right << std::setw(w_set_sep) << " : "
                << std::left << std::setw(w_set_value) << params.gamma
                << "\n";

        // line 6
        std::cout << std::left  << std::setw(w_inst_label) << " agent capacity range"
                << std::right << std::setw(w_inst_sep)   << " : "
                << std::left  << std::setw(w_inst_value)
                << (std::to_string(stats.min_capacity_agent) + " - " + std::to_string(stats.max_capacity_agent))
                << std::left  << std::setw(w_algo) << ""
                << std::left << std::setw(w_set_label) << "influence"
                << std::right << std::setw(w_set_sep) << " : ";

                if(params.influence == 'b'){std::cout << std::left << "balance";}

                if(params.influence == 'p'){std::cout << std::left << "pheromone";}

                if(params.influence == 'h'){std::cout << std::left << "heuristic";}
                
                std::cout << "\n";


                // line 7
                if(params.use_time_limit){
                        std::cout << std::left  << std::setw(w_flags) << "";
                        std::cout << std::left  << std::setw(w_inst_label) << ""
                                  << std::right << std::setw(w_inst_sep)   << ""
                                  << std::left  << std::setw(w_inst_value) << ""
                                  << std::left << std::setw(w_set_label) << "time limit (sec)"
                                  << std::right << std::setw(w_set_sep)    << " : "
                                  << std::left << std::setw(w_set_value) << params.time_limit;

                        std::cout << "\n";
                }

                // line 8
                if(params.use_max_iterations){
                        std::cout << std::left  << std::setw(w_flags) << "";
                        std::cout << std::left  << std::setw(w_inst_label) << ""
                                  << std::right << std::setw(w_inst_sep)   << ""
                                  << std::left  << std::setw(w_inst_value) << ""
                                  << std::left << std::setw(w_set_label) << "max iterations"
                                  << std::right << std::setw(w_set_sep)    << " : "
                                  << std::left << std::setw(w_set_value) << params.nb_max_iterations;

                        std::cout << "\n";
                }
                std::cout << "\n \n";
                

    }




    void printHeaderLineACO(){

        const int init_sep = 2;

        const int w_iter   = 10;
        const int iter_sep = 8;

        const int w_time   = 12;
        const int time_sep = 10;

        const int w_worst  = 14;
        const int worst_sep = 10;

        const int w_avg    = 14;
        const int av_sep = 18;

        const int w_local  = 16;
        const int local_sep = 6;

        const int w_global = 16;

        std::cout << "\n";

        // line 1
        std::cout << YELLOW;
        std::cout << std::right << std::setw(init_sep)   << ""
                  << std::left  << std::setw(w_iter) << "Iterations" 
                  << std::right << std::setw(iter_sep)   << ""

                  << std::left  << std::setw(w_time) << "Time (s)"
                  << std::right << std::setw(time_sep)  << ""

                  << std::left  << std::setw(w_worst) << "Worst ant"
                  << std::right << std::setw(worst_sep)  << ""

                  << std::left  << std::setw(w_avg) << "Average value"
                  << std::right << std::setw(av_sep)   << ""

                  << std::left  << std::setw(w_local) << "Best ant"
                  << std::right << std::setw(local_sep)   << ""

                  << std::left  << std::setw(w_global) << "Best known solution"
                  << RESET
                  << "\n";

        // line 2
        std::cout << std::right << std::setw(init_sep)   << ""
                  << std::left  << std::setw(w_iter)  << std::string(10, '-')
                  << std::right << std::setw(iter_sep)   << ""

                  << std::left  << std::setw(w_time)   << std::string(8, '-')
                  << std::right << std::setw(time_sep)   << ""

                  << std::left  << std::setw(w_worst)  << std::string(9, '-')
                  << std::right << std::setw(worst_sep)   << ""

                  << std::left  << std::setw(w_avg)    << std::string(13, '-')
                  << std::right << std::setw(av_sep)   << ""

                  << std::left  << std::setw(w_local)  << std::string(8, '-')
                  << std::right << std::setw(local_sep)   << ""

                  << std::left  << std::setw(w_global) << std::string(19, '-')
                  << "\n\n";


    }




    void printACOIteration(int iteration,
                        double time,
                        std::int64_t worst,
                        std::int64_t cumulative_score,
                        std::int64_t local_best,
                        std::int64_t global_best,
                        bool improvement,
                        gap::Params &params){
                                
                                
        const int init_sep = 2;
        
        const int w_iter   = 6;
        const int iter_sep = 8;

        const int w_time   = 12;
        const int time_sep = 8;
                        
        const int w_worst  = 15;
        const int worst_sep = 7;

        const int w_avg    = 21;
        const int av_sep   = 10;

        const int w_local  = 17;
        const int local_sep = 12;

        const int w_global = 21;

        double average = static_cast<double>(cumulative_score) / params.nb_ants;

        std::cout << std::right << std::setw(init_sep)   << ""
                  << std::right  << std::setw(w_iter)     << iteration
                  << std::right << std::setw(iter_sep)   << ""

                  << std::right << std::setw(w_time)      << std::fixed << std::setprecision(4) << time
                  << std::right << std::setw(time_sep)    << ""

                  << std::right << std::setw(w_worst)     << worst
                  << std::right << std::setw(worst_sep)   << ""

                  << std::right << std::setw(w_avg)       << std::fixed << std::setprecision(2) << average
                  << std::right << std::setw(av_sep)      << "";

        if(improvement){
            std::cout << GREEN 
                      << std::right << std::setw(w_local) << local_best 
                      << RESET;
        }
        else{
            std::cout << std::right << std::setw(w_local) << local_best;
        }

        std::cout << std::right << std::setw(local_sep) << "";


        if(improvement){
            std::cout << BRIGHT_YELLOW
                      << std::right << std::setw(w_global) << global_best
                      << RESET;
        }
        else{
            std::cout << std::right << std::setw(w_global) << global_best;
        }

        std::cout << "\n \n";
    }



    void finalStatisticsACO(double preprocessing_time,
                            int iteration,
                            std::int64_t obj_value,
                            gap::Status status,
                            gap::Timer &timer,
                            gap::Params &params){

        std::cout << "\n";
        const int init_sep = 2;
        const int w_item   = 27;


        double average_time = (timer.getElapsed() - preprocessing_time) / iteration;

        std::cout << std::right << std::setw(init_sep)   << ""
                  << std::right  << YELLOW << "Summary" << RESET << "\n"
                  << std::string(init_sep, ' ')
                  << std::string(7, '-')
                  << "\n \n";

        std::cout << std::string(init_sep, ' ')
                  << std::right << std::setw(init_sep) 
                  << std::left << std::setw(w_item)  << "Preprocessing time"
                  << std::right  << " :  " 
                  << std::left << preprocessing_time << " seconds"
                  << "\n"

                  << std::string(init_sep, ' ')
                  << std::left << std::setw(w_item)   << "Average time per iteration"
                  << std::right  << " :  " 
                  << std::left << average_time  << " seconds"
                  << "\n"

                  << std::string(init_sep, ' ')
                  << std::left << std::setw(w_item)   << "Total elapsed time"
                  << std::right  << " :  " 
                  << std::left << timer.getElapsed() << " seconds"
                  << "\n"

                  << std::string(init_sep, ' ')
                  << std::left << std::setw(w_item)   << "Number of iterations"
                  << std::right  << " :  " 
                  << std::left << iteration
                  << "\n\n"

                  << std::string(init_sep, ' ')
                  << std::left << std::setw(w_item)   << "Number of ants"
                  << std::right  << " :  " 
                  << std::left << params.nb_ants
                  << "\n"

                  << std::string(init_sep, ' ')
                  << std::left << std::setw(w_item)   << "Rho"
                  << std::right  << " :  " 
                  << std::left << params.rho
                  << "\n"

                  << std::string(init_sep, ' ')
                  << std::left << std::setw(w_item)   << "Gamma"
                  << std::right  << " :  " 
                  << std::left << params.gamma
                  << "\n"

                  << std::string(init_sep, ' ')
                  << std::left << std::setw(w_item)   << "Influence"
                  << std::right  << " :  " ;

                  if(params.influence == 'b'){
                        std::cout << BRIGHT_CYAN;
                        std::cout  << "balance" << RESET;}

                  if(params.influence == 'h'){
                        std::cout << BRIGHT_CYAN;
                        std::cout << "heuristic" << RESET;}

                  if(params.influence == 'p'){
                        std::cout << BRIGHT_CYAN;
                        std::cout  << "pheromone" << RESET;}

                  std::cout << "\n\n";

                  std::cout << std::string(init_sep, ' ')
                  << std::left << std::setw(w_item)   << "Solution status"
                  << std::right  << " :  " 
                  << std::left << status
                  << "\n";
        
                  std::cout << std::string(init_sep, ' ')
                  << std::left << std::setw(w_item)   << "Objective value"
                  << std::right  << " :  " ;
                  std::cout << BRIGHT_YELLOW;
                  std::cout << std::left  << obj_value
                  << RESET
                  << "\n\n";
                  

     }



 }