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
 * @file AlignedMatrix.cpp
 * @author Josué Tambwe
 * @date 27 April 2026
 */


 #include "metaheuristics/antColonyOptimizer/AlignedMatrix.hpp"

 namespace gap::ACO{

    // constructor

    AlignedMatrix::AlignedMatrix(size_t m, size_t n)
        : nb_agent(m), nb_task(n) {

            // lines allocation
            matrix = new float*[m];

            // column allocation
            for(size_t line = 0; line < m; line++){

                // aligned memory allocation
                posix_memalign(reinterpret_cast<void**>(&matrix[line]),
                                64,
                                n * sizeof(float));
            }
    }


    // destructor

    AlignedMatrix::~AlignedMatrix(){
        for(size_t line = 0; line < nb_agent; line++){free(matrix[line]);}
        delete[] matrix;
        std::cout << " mémoire libérée avec succès! " << std::endl;
    }

    // operator overloading

    float* AlignedMatrix::operator[](int index){return matrix[index];}

    const float* AlignedMatrix::operator[](int index) const {return matrix[index];}



    // initialization of the initial pheromone deposit

    void AlignedMatrix::initialize(float tau){
        for(size_t i = 0; i < nb_agent; i++){
            for(size_t j = 0; j < nb_task; j++){
                matrix[i][j] = tau;
            }
        }
    }


    void AlignedMatrix::print() const{
        std::cout << "\n  Pheromone Matrix: \n \n";
        for(size_t i = 0; i < nb_agent; i++){
            for(size_t j = 0; j < nb_task; j++){
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "\n" << std::endl;
    }

    // getters

    size_t AlignedMatrix::getNbAgent() const {return nb_agent;}
    size_t AlignedMatrix::getNbTask() const {return nb_task;}

 }


