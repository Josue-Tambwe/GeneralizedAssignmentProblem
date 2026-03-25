#------------------------------------------------------------------------------
# GAP-Solver — An educational solver for the Generalized Assignment Problem
#              using MILP and heuristic methods.
#------------------------------------------------------------------------------
# Copyright (c) 2025 Josué Tambwe
#               Nantes Université, France
#------------------------------------------------------------------------------
# This software is released under the MIT License.
# See the LICENSE file for more details.
#------------------------------------------------------------------------------


project('GAP-Solver',
        'cpp',
        version : 'v.0.1',
        default_options : [
            'cpp_std=c++20',
            'warning_level=3'
        ])

# header files
inc = include_directories('include')

# getting options 

nb_physical_cores = get_option('NUMBER_PHYSICAL_CORES')
has_sse        = get_option('HAS_SSE')
has_avx2        = get_option('HAS_AVX2')
has_fma        = get_option('HAS_FMA')
has_avx512f    = get_option('HAS_AVX512F')
has_avx512fma  = get_option('HAS_AVX512FMA')
has_armv8      = get_option('HAS_ARMV8')
has_x86      = get_option('HAS_X86')
has_asimd      = get_option('HAS_ASIMD')

# converting boolean flags to '1' or '0' explicitly
if has_sse
    sse_flag = '1'
else
    sse_flag = '0'
endif

if has_avx2
    avx2_flag = '1'
else
    avx2_flag = '0'
endif

if has_fma
    fma_flag = '1'
else
    fma_flag = '0'
endif

if has_avx512f
    avx512f_flag = '1'
else
    avx512f_flag = '0'
endif

if has_avx512fma
    avx512fma_flag = '1'
else
    avx512fma_flag = '0'
endif

if has_armv8
    armv8_flag = '1'
else
    armv8_flag = '0'
endif

if has_x86
    x86_flag = '1'
else
    x86_flag = '0'
endif

if has_asimd
    asimd_flag = '1'
else
    asimd_flag = '0'
endif

# adding options 

add_project_arguments(
    '-DNUMBER_PHYSICAL_CORES=' + nb_physical_cores,
    '-DHAS_SSE=' + sse_flag,
    '-DHAS_AVX2=' + avx2_flag,
    '-DHAS_FMA=' + fma_flag,
    '-DHAS_AVX512F=' + avx512f_flag,
    '-DHAS_AVX512FMA=' + avx512fma_flag,
    '-DHAS_ARMV8=' + armv8_flag,
    '-DHAS_X86=' + x86_flag,
    '-DHAS_ASIMD=' + asimd_flag,
    language : 'cpp'
)

# source files
subdir('src')