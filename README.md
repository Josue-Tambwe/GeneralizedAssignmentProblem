# Introduction :

The Generalized Assignment Problem (GAP) is an **NP-hard** combinatorial optimization problem that consists in assigning tasks to agents with limited capacities. 

Formally, let $n \ge 1$ be the number of tasks and $m \ge 1$ the number of agents. The objective is to minimize the total assignment cost :


$$
\min \sum_{i=1}^{m} \sum_{j=1}^{n} c_{ij} \cdot x_{ij}
$$ ()


Subject to : 

$$
\sum_{i=1}^{m} x_{ij} = 1 \quad \forall j \in \{1,\dots,n\} \tag{1}
$$

$$
\sum_{j=1}^{n} a_{ij} \cdot x_{ij} \le b_i \quad \forall i \in \{1,\dots,m\} \tag{2}
$$

With:

- $a_{ij}$ : the **weight** of task $j$ when assigned to agent $i$
- $b_i$ : the **capacity** of agent $i$

The constraint $(1)$ requires every task to be assigned exactly once and the constraint $(2)$ ensures that the maximum capacity of each agent is not exceeded.

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

- **SIMD vectorization** : attempted on several kernels, including pheromone evaporation. However, vectorizing the evaporation step did not yield meaningful speed‑ups, as this `operation is memory‑bound`, which means its performance is limited by memory bandwidth rather than arithmetic throughput. 

# Dependencies :

- meson
- doxygen

# Installation : 

**Note** : The installation script works only on Linux and macOS operating systems.

## 1. Clone the repository

```bash
git clone https://github.com/<Josue-Tambwe>/GeneralizedAssignmentProblem.git
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

# Examples of output