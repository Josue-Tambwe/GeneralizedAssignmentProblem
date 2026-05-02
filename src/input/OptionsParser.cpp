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

        for(int i = 1; i < argc; i++){

            std::string arg = argv[i];

            if (arg.find("--instance=") == 0) {has_algorithm = true;}
            if (arg.find("--algorithm=") == 0) {has_instance = true;}
            if (arg.find("--nb-ants=") == 0) {has_nb_ants = true;}
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

    }




    gap::Params parseOptions(int argc, char** argv){

        //checkRequiredOptions(argc, argv);

        gap::Params params;
        // default values
        params.algorithm = gap::Algorithm::Greedy;
        params.instance_path = "";
        params.nb_threads = NUMBER_PHYSICAL_CORES;
        params.time_limit = 10.0;
        params.verbose = false;

        // greedy
        params.low_cost_construction = false;

        // ACO
        params.simd = false; 
        params.use_max_iterations = false; 
        params.use_time_limit = false; 
        
        params.nb_ants = 1; 
        params.nb_max_iterations = 1; 
        params.influence = 'b'; 
        params.gamma = 0.5f; 
        params.rho = 0.1f;

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

                else if(arg == "--low-cost-construction"){params.low_cost_construction = true; continue;}

                if(arg == "--simd"){params.simd = true; continue;}

                else{gap::Logger log; log.error(" Unknown option: " + arg);}
            }

            // case of an option with argument
            else{
                std::string name = arg.substr(0, position);
                std::string value = arg.substr(position + 1);


                if(name == "--algorithm"){
                    params.algorithm = parseAlgorithm(value);
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


                // case of invalid option
                gap::Logger log;
                log.error("Unknown option: " + name);
                break;
            }

            
        }



        if(params.algorithm == gap::Algorithm::AntColonyOptimizer &&
           !params.use_time_limit && !params.use_max_iterations){

                params.use_time_limit = true;

        }
        
        checkRequiredOptions(argc, argv, params);
        return params;
    }


 }