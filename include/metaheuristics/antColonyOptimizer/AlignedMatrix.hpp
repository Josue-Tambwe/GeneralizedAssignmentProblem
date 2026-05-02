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
 * @file AlignedMatrix.hpp
 * @class AlignedMatrix
 * @brief This class defines 2D matrix for the pheromone matrix, aligned on 64 bytes for SIMD vectorization
 * @author Josué Tambwe
 * @date 27 April 2026
 */
 #pragma once

 #include <iostream>
 #include <cstdlib>


 namespace gap::ACO{

    class AlignedMatrix{

        private :
            size_t nb_agent, nb_task;
            float** matrix;


        public :

            // constructor
            AlignedMatrix(size_t m, size_t n);

            // destructor
            ~AlignedMatrix();

            // operator overloading
            float* operator[](int index);
            const float* operator[](int index) const;

            // initialization of the initial pheromone deposit
            void initialize(float tau);

            // printing the pheromone matrix
            void print() const;

            // getters
            size_t getNbAgent() const;
            size_t getNbTask() const;

    };

 }