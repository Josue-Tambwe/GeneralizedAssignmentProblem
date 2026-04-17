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

# adding options 

add_project_arguments(
    '-DNUMBER_PHYSICAL_CORES=' + nb_physical_cores,
    language : 'cpp'
)

# source files
subdir('src')