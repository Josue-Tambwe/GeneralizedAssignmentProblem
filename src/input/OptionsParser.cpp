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

    void checkRequiredOptions(int argc, char** argv){
        bool hasAlgorithm = false;
        bool hasInstance = false;

        for(int i = 1; i < argc; i++){
            std::string arg = argv[i];
            if (arg.find("--instance=") == 0) {hasInstance = true;}
            if (arg.find("--algorithm=") == 0) {hasAlgorithm = true;}
        }
        if(!hasAlgorithm){
            gap::Logger log;
            log.error(" Missing required option : --algorithm=value");
        }
        if(!hasInstance){
            gap::Logger log;
            log.error(" Missing required option : --instance=value");
        }

    }

    gap::Params parseOptions(int argc, char** argv){

        //checkRequiredOptions(argc, argv);

        gap::Params params;
        // default values
        params.algorithm = gap::Algorithm::Greedy;
        params.instance_path = "";
        params.nb_threads = NUMBER_PHYSICAL_CORES;
        params.time_limit = 60;
        params.verbose = false;
        params.low_cost_construction = false;

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
                else if(arg == "--low_cost_construction"){params.low_cost_construction = true; continue;}
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

                if(name == "--nb_threads"){
                    params.nb_threads = std::stoi(value);
                    if(params.nb_threads < 1){
                        gap::Logger log; 
                        log.error(" nb_threads must be >= 1");
                    }
                    continue;
                }

                if(name == "--time_limit"){
                    params.time_limit = std::stoi(value);
                    if(params.time_limit < 1){
                        gap::Logger log; 
                        log.error(" time_limit must be >= 1");
                    }
                    continue;
                }

                // no valid option
                gap::Logger log;
                log.error("Unknown option: " + name);
                break;
            }

            
        }
        checkRequiredOptions(argc, argv);
        return params;
    }


 }