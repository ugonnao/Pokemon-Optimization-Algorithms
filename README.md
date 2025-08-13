# Optimization Algorithms: TSP and MST Solver

This project implements classic optimization algorithms such as **Minimum Spanning Tree (MST)**, **Fast Traveling Salesperson Problem (FASTTSP)**, and **Optimal TSP (OPTTSP)** using C++. The program simulates and evaluates different strategies to solve routing and optimization problems efficiently.

## Features

- **MST Mode**: Computes a Minimum Spanning Tree of a graph using Prim’s algorithm.
- **FASTTSP Mode**: Generates a quick, near-optimal TSP route using Arbitrary Insertion.
- **OPTTSP Mode**: Computes the exact optimal route for TSP using permutation generation and pruning based on MST and distance heuristics.

## Technologies Used

- Language: C++ (Standard Library)
- Algorithms: Permutations, MST (Prim’s), Greedy Heuristics, Backtracking
- Input: Command-line arguments for different modes

## How to Run

```
./poke --mode=MST < input.txt
./poke --mode=FASTTSP < input.txt
./poke --mode=OPTTSP < input.txt
```

## File Structure

- `poke.cpp`: Main entry point and mode dispatcher
- `MST.h`: MST computation logic
- `FASTTSP.h`: Fast heuristic solution for TSP
- `OPTTSP.h`: Exact solution using backtracking and MST pruning
- `genPerms.cpp`: Utility for generating permutations (used by OPTTSP)

## Sample Input Format

```
N
x1 y1
x2 y2
...
xN yN
```

Where `N` is the number of nodes and `(xi, yi)` are 2D coordinates.

## Output Format

Outputs either the MST total weight or the TSP route and its total distance.

## Author

Ugonna O. — University of Michigan Computer Science Student

---
