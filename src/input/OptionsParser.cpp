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

 #include "input/OptionsParser.hpp"
 
 namespace gap{

    void checkRequiredOptions(int argc, char** argv, gap::Params &params){

        bool has_algorithm = false;
        bool has_instance = false;
        bool has_nb_ants = false;
        bool use_milp_solver = false;

        for(int i = 1; i < argc; i++){

            std::string arg = argv[i];

            if (arg.find("--instance=") == 0) {has_instance = true;}
            if (arg.find("--algorithm=") == 0) {has_algorithm = true;}
            if (arg.find("--nb-ants=") == 0) {has_nb_ants = true;}
            if (arg.find("--solver=") == 0) {use_milp_solver = true;}
        }

        if(!has_algorithm){
            gap::Logger log;
            log.error(" Missing required option : --algorithm=value");
        }

        if(!has_instance){
            gap::Logger log;
            log.error(" Missing required option : --instance=value");
        }

        if(params.algorithm == gap::Algorithm::AntColonyOptimizer 
           && !has_nb_ants){

            gap::Logger log;
            log.error(" Missing required option : --nb-ants=value");
        }

        if((params.algorithm == gap::Algorithm::BranchAndBound ||
            params.algorithm == gap::Algorithm::Milp) &&
            !use_milp_solver){

            gap::Logger log;
            log.error(" Missing required option : --solver=value");

        }

    }






    void unsupportedOptionsGreedy(int argc, char** argv){
        
        gap::Logger log; 

        for(int i = 1; i < argc; i++){

            std::string arg = argv[i];

            if (arg.find("--time-limit=") == 0) {log.error(" --time-limit option is not supported for the greedy algorithm! ");}
            if (arg.find("--nb-ants=") == 0) {log.error(" --nb-ants option is not supported for the greedy algorithm! ");}
            if (arg.find("--warm-start") == 0) {log.error(" --warm-start flag is not supported for the greedy algorithm! ");}
            if (arg.find("--solver=") == 0) {log.error(" --solver option is not supported for the greedy algorithm! ");}
            if (arg.find("--gamma=") == 0) {log.error(" --gamma option is not supported for the greedy algorithm! ");}
            if (arg.find("--gap=") == 0) {log.error(" --gap option is not supported for the greedy algorithm! ");}
            if (arg.find("--branching-rule=") == 0) {log.error(" --branching-rule option is not supported for the greedy algorithm! ");}
            if (arg.find("--influence=") == 0) {log.error(" --influence option is not supported for the greedy algorithm! ");}
            if (arg.find("--iterations=") == 0) {log.error(" --iterations option is not supported for the greedy algorithm! ");}
            if (arg.find("--exploration=") == 0) {log.error(" --exploration option is not supported for the greedy algorithm! ");}
            if (arg.find("--rho=") == 0) {log.error(" --rho option is not supported for the greedy algorithm! ");}
            
            
        }


    }





    void unsupportedOptionsACO(int argc, char** argv){
        
        gap::Logger log; 

        for(int i = 1; i < argc; i++){

            std::string arg = argv[i];

            if (arg.find("--warm-start") == 0) {log.error(" --warm-start flag is not supported for the aco algorithm! ");}
            if (arg.find("--solver=") == 0) {log.error(" --solver option is not supported for the aco algorithm! ");}
            if (arg.find("--low-cost-construction") == 0) {log.error(" --low-cost-construction flag is not supported for the aco algorithm! ");}
            if (arg.find("--gap=") == 0) {log.error(" --gap option is not supported for the aco algorithm! ");}
            if (arg.find("--branching-rule=") == 0) {log.error(" --branching-rule option is not supported for the aco algorithm! ");}
            if (arg.find("--exploration=") == 0) {log.error(" --exploration option is not supported for the aco algorithm! ");}
            
        }


    }






    void unsupportedOptionsBaB(int argc, char** argv){
        
        gap::Logger log; 

        for(int i = 1; i < argc; i++){

            std::string arg = argv[i];

            if (arg.find("--nb-ants=") == 0) {log.error(" --nb-ants option is not supported for the bab algorithm! ");}
            if (arg.find("--nb-threads=") == 0) {log.error(" --nb-threads option is not supported for the bab algorithm! ");}
            if (arg.find("--warm-start") == 0) {log.error(" --warm-start flag is not supported for the bab algorithm! ");}
            if (arg.find("--low-cost-construction") == 0) {log.error(" --low-cost-construction flag is not supported for the bab algorithm! ");}
            if (arg.find("--gamma=") == 0) {log.error(" --gamma option is not supported for the bab algorithm! ");}
            if (arg.find("--influence=") == 0) {log.error(" --influence option is not supported for the bab algorithm! ");}
            if (arg.find("--iterations=") == 0) {log.error(" --iterations option is not supported for the bab algorithm! ");}
            if (arg.find("--rho=") == 0) {log.error(" --rho option is not supported for the bab algorithm! ");}
            
            
        }


    }





    void unsupportedOptionsMilp(int argc, char** argv){
        
        gap::Logger log; 

        for(int i = 1; i < argc; i++){

            std::string arg = argv[i];

            if (arg.find("--nb-ants=") == 0) {log.error(" --nb-ants option is not supported for the milp algorithm! ");}
            if (arg.find("--nb-threads=") == 0) {log.error(" --nb-threads option is not supported for the milp algorithm! ");}
            if (arg.find("--low-cost-construction") == 0) {log.error(" --low-cost-construction flag is not supported for the milp algorithm! ");}
            if (arg.find("--gamma=") == 0) {log.error(" --gamma option is not supported for the milp algorithm! ");}
            if (arg.find("--influence=") == 0) {log.error(" --influence option is not supported for the milp algorithm! ");}
            if (arg.find("--iterations=") == 0) {log.error(" --iterations option is not supported for the milp algorithm! ");}
            if (arg.find("--gap=") == 0) {log.error(" --gap option is not supported for the milp algorithm! ");}
            if (arg.find("--branching-rule=") == 0) {log.error(" --branching-rule option is not supported for the milp algorithm! ");}
            if (arg.find("--exploration=") == 0) {log.error(" --exploration option is not supported for the milp algorithm! ");}
            if (arg.find("--rho=") == 0) {log.error(" --rho option is not supported for the milp algorithm! ");}            
            
        }


    }





    gap::Params parseOptions(int argc, char** argv){

        gap::Params params;

        for(int i = 1; i < argc; i++){

            std::string arg = argv[i];

            // case of Help
            if(arg == "--help"){
                printHelp();
                break;
            }

            // Checking if the option contains '=' 
            std::size_t position = arg.find('=');

            bool hasValue = (position != std::string::npos);

            // case of a flag
            if(!hasValue){

                if(arg == "--verbose"){params.verbose = true; continue;}

                if(arg == "--warm-start"){params.warm_start = true; continue;}

                else if(arg == "--low-cost-construction"){params.low_cost_construction = true; continue;}

                else{gap::Logger log; log.error(" Unknown flag: " + arg);}
            }

            // case of an option with argument
            else{
                std::string name = arg.substr(0, position);
                std::string value = arg.substr(position + 1);


                if(name == "--algorithm"){
                    params.algorithm = parseAlgorithm(value);
                    if((params.algorithm == gap::Algorithm::BranchAndBound ||
                        params.algorithm == gap::Algorithm::Milp) &&
                        !(USE_BRANCH_AND_BOUND)){
                        
                        gap::Logger log; 
                        log.error(" The solver has not been built with any MILP solver "); 
                        break;

                    }

                    if(params.algorithm == gap::Algorithm::Unknown){
                        gap::Logger log; 
                        log.error(" Unknown algorithm: " + arg); 
                        break;
                    } 
                    continue;
                }


                if(name == "--instance"){params.instance_path = value; continue;}

                if(name == "--nb-threads"){
                    params.nb_threads = std::stoi(value);
                    if(params.nb_threads < 1){
                        gap::Logger log; 
                        log.error(" nb-threads must be >= 1");
                    }
                    continue;
                }


                if(name == "--time-limit"){
                    params.time_limit = std::stod(value);
                    if(params.time_limit < 0.0){
                        gap::Logger log; 
                        log.error(" time-limit must be > 0");
                    }
                    params.use_time_limit = true;
                    continue;
                }


                if(name == "--iterations"){
                    params.nb_max_iterations = std::stoi(value);
                    if(params.nb_max_iterations < 1){
                        gap::Logger log; 
                        log.error(" iterations must be >= 1");
                    }
                    params.use_max_iterations = true;
                    continue;
                }


                if(name == "--nb-ants"){
                    params.nb_ants = std::stoi(value);
                    if(params.nb_ants < 0){
                        gap::Logger log; 
                        log.error(" nb-ants must be >= 1");
                    }
                    continue;
                }


                if(name == "--rho"){
                    params.rho = std::stof(value);
                    if(params.rho < 0.0f || params.rho > 1.0f){
                        gap::Logger log; 
                        log.error(" rho must be in the interval [0,1]");
                    }
                    continue;
                }


                if(name == "--gamma"){
                    params.gamma = std::stof(value);
                    if(params.gamma < 0.0f || params.gamma > 1.0f){
                        gap::Logger log; 
                        log.error(" gamma must be in the interval [0,1]");
                    }
                    continue;
                }


                if(name == "--influence"){

                    if(value == "balance"){params.influence = 'b'; continue;}
                    if(value == "heuristic"){params.influence = 'h'; continue;}
                    if(value == "pheromone"){params.influence = 'p'; continue;}

                    gap::Logger log; 
                    log.error(" Unknown influence: " + value); 
                    break;
                    
                }


                if(name == "--solver"){

                    if(value == "gurobi"){
                        if(!HAS_GUROBI){gap::Logger log; log.error(" The solver has not been built with Gurobi");}
                        params.milp_solver = 'g'; 
                        continue;
                    }


                    if(value == "hexaly"){
                        if(!HAS_HEXALY){gap::Logger log; log.error(" The solver has not been built with Hexaly");}
                        params.milp_solver = 'x'; 
                        continue;
                    }


                    if(value == "highs"){
                        if(!HAS_HIGHS){gap::Logger log; log.error(" The solver has not been built with Highs");}
                        params.milp_solver = 'h'; 
                        continue;
                    }

                    gap::Logger log; 
                    log.error(" Unsupported milp solver : " + value); 
                    break;
                    
                }


                if(name == "--exploration"){

                    if(value == "bfs"){params.exploration_strategy = 'b'; continue;}
                    if(value == "dfs"){params.exploration_strategy = 'd'; continue;}

                    gap::Logger log; 
                    log.error(" Unknown nodes exploration strategy : " + value); 
                    break;
                    
                }


                if(name == "--branching-rule"){

                    if(value == "one"){params.branching_value = 1.0; continue;}
                    if(value == "zero"){params.branching_value = 0.0; continue;}
                    if(value == "fractional"){params.branching_value = 0.5; continue;}

                    gap::Logger log; 
                    log.error(" Unknown branching rule : " + value); 
                    break;
                    
                }

                if(name == "--gap"){
                    params.optimality_gap = std::stod(value);
                    if(params.optimality_gap < 0.0 || params.optimality_gap > 1.0){
                        gap::Logger log; 
                        log.error(" gap must be in the interval [0,1]");
                    }
                    continue;
                }



                // case of invalid option
                gap::Logger log;
                log.error("Unknown option: " + name);
                break;
            }

            
        }


        if(params.algorithm == gap::Algorithm::AntColonyOptimizer){unsupportedOptionsACO(argc, argv);}

        if(params.algorithm == gap::Algorithm::BranchAndBound){unsupportedOptionsBaB(argc, argv);}

        if(params.algorithm == gap::Algorithm::Greedy){unsupportedOptionsGreedy(argc, argv);}

        if(params.algorithm == gap::Algorithm::Milp){unsupportedOptionsMilp(argc, argv);}

        

        if(params.algorithm == gap::Algorithm::AntColonyOptimizer &&
           !params.use_time_limit && !params.use_max_iterations){

                params.use_time_limit = true;

        }

        if(params.algorithm == gap::Algorithm::BranchAndBound &&
           params.milp_solver == 'x'){

            gap::Logger log; 
            log.error(" Hexaly must not be used for linear relaxation in the Branch And Bound algorithm! "); 

        }

        
        checkRequiredOptions(argc, argv, params);
        return params;

    }


 }
