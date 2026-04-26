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
        std::cout << setw(85) << right << "  GAP-Solver - Generalized Assignment Problem Solver" << "\n";
        std::cout << setw(35) << right << " " << std::string(50, '=') << "\n\n";
    }

    void printUsage(){
        std::cout << " Usage:\n";
        std::cout << " ------\n";
        std::cout << "    gap_solver [OPTIONS]\n\n";
    }

    void printRequiredOptions(){
        std::cout << " Required options:\n";
        std::cout << " -----------------\n";
        std::cout << "    " << setw(22) << left << "--algorithm=value"
                  << "Algorithm to use (greedy, antColony, BandB)\n";
        std::cout << "    " << setw(22) << left << "--instance=path"
                  << "Path to the instance file\n\n";
    }

    void printOptionalOptions(){
        std::cout << " Optional options:\n";
        std::cout << " -----------------\n";
        std::cout << "    " << setw(22) << left << "--nb-threads=value"
                  << "Number of threads (default: NUMBER_PHYSICAL_CORES)\n";
        std::cout << "    " << setw(22) << left << "--time-limit=value"
                  << "Time limit in seconds (default: 60)\n";
        std::cout << "    " << setw(22) << left << "--verbose"
                  << "Enable verbose mode \n";
        std::cout << "    " << setw(22) << left << "--low-cost-construction"
                  << "Enable the cost-and-weight based priority rule when building initial solution for the Greedy algorithm\n\n";
    }

    void printExampleRun(){
        std::cout << " Examples:\n";
        std::cout << " ---------\n";
        std::cout << "    gap_solver --algorithm=greedy "
                  << "--instance=../benchmarks/gap_a/a05100\n";
        std::cout << "    gap_solver --algorithm=antColony "
                  << "--instance=data/inst.dat --time-limit=120 --verbose\n\n";
    }


    void printHelp(){
        printHeader();
        printUsage();
        printRequiredOptions();
        printOptionalOptions();
        printExampleRun();
        std::exit(0);
    }

    void printHeaderGreedy(gap::Params& params,
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





 }