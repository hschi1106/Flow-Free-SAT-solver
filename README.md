# Flow-Free-SAT-solver

This repository contains a C++ implementation of a SAT-based solver for the puzzle game **Flow Free** as a course project.

The idea is to encode a Flow Free instance as a Boolean satisfiability (SAT) problem in CNF form, then use a SAT solver to find a valid assignment corresponding to a complete, non-overlapping set of flows on the grid.

---

## Problem Overview

In a Flow Free puzzle:

- The board is a 2D grid.
- Each color appears exactly twice on the grid.
- The goal is to connect each pair of same-colored terminals with a path:
  - Paths must be vertex-disjoint (no overlapping cells).
  - All paths must lie within the grid.
  - Optionally, the puzzle can require the grid to be fully filled.

This project encodes these constraints as SAT:

- Boolean variables represent color assignments to each cell and/or edges.
- CNF clauses enforce:
  - Each cell contains at most one color.
  - Color continuity between neighboring cells along a path.
  - Terminals of the same color are connected.
  - Optional “no empty cell” constraint if required by the instance.

The input format is documented in `input format.txt`.

---

## Project Structure

- `src/`
  - Core C++ implementation of:
    - Data structures for the grid and variables.
    - CNF construction for Flow Free constraints.
    - SAT solving routine (DPLL-style or similar).
- `makefile`
  - Build script for compiling the solver.
- `input format.txt`
  - Description of the expected puzzle input format.

---

## Build

A typical build flow (see `makefile` for the exact target name):

```bash
git clone https://github.com/hschi1106/Flow-Free-SAT-solver.git
cd Flow-Free-SAT-solver

make
