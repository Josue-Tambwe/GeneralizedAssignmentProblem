# Introduction :

The Generalized Assignment Problem (GAP) is an **NP-hard** combinatorial optimization problem that consists in assigning tasks to agents with limited capacities. 

# Mathematical Formulation

![](docs/img/math_formulation.png)



# Resolution methods

This solver implements several complementary approaches to tackle the Generalized Assignment Problem (GAP), ranging from simple constructive heuristics to advanced metaheuristics and exact methods. The goal is to provide both educational clarity and high‑performance implementations.

## 1. Greedy Construction Heuristic

Two approches : 

- **cost‑and-weight based** (low cost construction) : builds a feasible solution by iteratively assigning tasks to agents according to a combined **cost‑and-weight** priority rule.
It generally produces **high‑quality solutions** in terms of objective value.
However, this technique may fail to construct a feasible solution on some instances, for example, the benchmark instance `benchmarks/gap_e/e20100`.

- **risky-task based** (default construction method) : always produces a feasible solution in a blink of an eye.It **prioritizes tasks that are difficult to assign**, based on their weight relative to agent capacities.This method is **robust and fast**, but the resulting solution is typically of **lower quality** compared to the **cost-and-weight based heuristic**.


## 2. Local Search with Two Neighborhood Moves

A local improvement procedure exploring two types of moves:

- **Balance** move: redistributes tasks between agents to reduce overload or improve cost.

- **Cheap** move: reassigns a task to a cheaper agent when feasible.

These neighborhoods yield significant improvements over the greedy constructions.
They are particularly **effective** when applied to the **risky‑task‑based** initialization : the local search **dramatically boosts the quality of these initially weaker solutions**, often bringing them on par with, or **even surpassing**, the solutions obtained from the cost‑and‑weight construction.


On the more challenging instances of **categories D and E** (benchmarks), the improvement is even more pronounced: the risky‑task‑based construction, once refined by local search, produces solutions that clearly outperform those derived from the cost‑and‑weight heuristic.

## 3. Ant Colony System (ACS) with Local Search — Dorigo et al.

A metaheuristic inspired by the behavior of ants.
Artificial ants construct solutions using pheromone trails and heuristic information, enabling a balance between exploration and exploitation.
ACS is particularly effective for combinatorial problems like the GAP.

## 4. Branch and Bound

An exact method that systematically explores the search tree while pruning suboptimal regions using bounds.
This approach guarantees optimality but may become expensive for large instances due to the NP-hard nature of the problem.

## 5. High‑Performance Computing (HPC) Enhancements

To accelerate computation, the solver integrates several HPC techniques:

- **CPU multi‑threading** : parallel evaluation of neighborhoods, construction heuristics, and pheromone updates. Multi‑threading provides a substantial speed‑up, especially on large instances where independent evaluations can be processed concurrently.

- **SIMD vectorization** : attempted on several kernels, including pheromone evaporation. However, vectorizing the evaporation step did not yield meaningful speed‑ups, as this **operation is memory‑bound**, which means its performance is limited by memory bandwidth rather than arithmetic throughput. 

# Dependencies :

- meson
- doxygen

# Installation : 

**Note** : The installation script works only on Linux and macOS operating systems.

## 1. Clone the repository

```bash
git clone https://github.com/Josue-Tambwe/GeneralizedAssignmentProblem.git
```

## 2. Move into the project directory

```bash
cd GeneralizedAssignmentProblem

```

## 3. Make the installation script executable


 ```bash
 chmod +x install.sh 
```
## 4. Run the installation script

```bash
./install.sh
```
___
# Usage / CLI examples

The executable is located in the `bin/` directory after installation.

## 1. Move to the `bin/` directory

```bash
cd bin
```

## 2. Display the help message

```bash
./gap_solver --help
```

## 3. Run the Greedy heuristic (construction + local search)

```bash
../gap_solver --algorithm=greedy --instance=../benchmarks/gap_a/a05100 --nb_threads=4 --low_cost_construction
```

The `--nb_threads` option is optional.
If omitted, the solver automatically uses the **number of physical CPU cores**, which generally provides the best performance. You may specify any number of threads ≥ 1 depending on your hardware and preferences.

The `--low_cost_construction` option is also optional.  
When enabled, the solver uses the **cost‑and‑weight priority rule**, which typically produces **higher‑quality** initial solutions.  
However, this strategy may fail to construct a feasible solution on a few difficult benchmark instances (notably three instances from categories and E).  
For this reason, the default construction strategy is the **risky‑task‑based priority rule**, which always produces a feasible solution whenever one exists.

![](docs/img/run_greedy_full.png)






