# Block Sudoku

This project explores an algorithm to maximize my score in a game of Block Sudoku.

## What is Block Sudoku?

Block Sudoku is a game arranged like a traditional Sudoku board, and each "round", you place 3 tetris-like blocks on the board. They can be anywhere on the board as long as they don't collide with an existing piece on the board. Unlike Tetris, though, you cannot rotate the blocks. You gain points by clearing the blocks off the board. You can clear blocks either filling up a row, column, or one of the 3x3 squares. The game ends when you cannot place all three of the blocks you were given that round.

## Implementing Block Sudoku in C++ with OpenMP

My original implementations of Block Sudoku and the solving tool were written in python.

So the bad news is that python is slow. It only touches about 1% of my GPU and 8% of my CPU (or 100% of one core) when running. We'd also hit a wall with the GIL if we try to multi-thread it.

Here I can choose to either rework the code to run in different processes, or I could use this as an excuse to rewrite the game (yet again) in C++.

I went with the latter, leveraging Eigen for my matrix operations and already the performance was night and day. Even compiling with `-O0` (no compiler optimization) and debug symbols, the difference was 10-fold.

Further optimizations with OpenMP and tuning led to a blazing fast simulation using 100% of all 12 cores of my Ryzen 9 processor.

Suddenly, I'm able to test with 5 positions (720 states) and 10 positions (6000 states) and have it complete each iteration in the time it takes Python to evaluate 3 positions (162 states).

## Building from source

### Prerequisites

All library dependencies (Catch2, Eigen3) are managed by [vcpkg](https://github.com/microsoft/vcpkg) and will be automatically downloaded and built during the CMake configuration phase.

In order to achieve better results, you should build with a compiler that supports OpenMP.

**Other Requirements:**
- **CMake** 3.21 or higher (required for CMakePresets.json support)
- **vcpkg** - Microsoft's C++ package manager ([installation guide](https://github.com/microsoft/vcpkg#get-started))