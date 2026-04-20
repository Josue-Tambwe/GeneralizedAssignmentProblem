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
 * @file Config.hpp
 * @brief defines substancial elements for the configuration of the G.A.P solver
 * @author Josué Tambwe
 * @date 08 Mar 2026
 */
 
 #pragma once
 
 #ifndef NUMBER_PHYSICAL_CORES
    #define NUMBER_PHYSICAL_CORES 1 // default value (1 physical core)
 #endif
 
const float epsilon = 1e-5; // to avoid division by zero

#ifndef HAS_SSE
    #define HAS_SSE false
#endif

#ifndef HAS_AVX2
    #define HAS_AVX2 false
#endif

#ifndef HAS_FMA
    #define HAS_FMA false
#endif

#ifndef HAS_AVX512F
    #define HAS_AVX512F false
#endif

#ifndef HAS_AVX512FMA
    #define HAS_AVX512FMA false
#endif

#ifndef HAS_ARMV8
    #define HAS_ARMV8 false
#endif

#ifndef HAS_X86
    #define HAS_X86 false
#endif

#ifndef HAS_ASIMD
    #define HAS_ASIMD false
#endif