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

# subdirectories
subdir('gap')
subdir('utils')
subdir('metaheuristics')
subdir('input')
subdir('hpc')
subdir('output')

# combining all source files
all_sources = gap_sources + utils_sources + metaheuristics_sources + input_sources + hpc_sources + output_sources

# the final binary file
executable('gap_solver', 
            all_sources,
            include_directories : inc,
            install : true,
            install_dir : 'bin')