// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <sudoku/solver.h>
#include <utils.h>

int main(int argc, char** argv) {
  if (sudoku::AreArgumentsValid(argc, argv)) {
    sudoku::Solve(argv[argc - 1]);
    return 0;
  }
  return 1;
}

/*
 * >Solve:
 *  takes in arguments
 *  if file path is valid then solve the file's puzzle
 * >Solver:
 *  actually solves a given sudoku puzzle (will take in a sudoku object or
 *  something)
 * >SudokuPuzzle
 *  represents a sudoku puzzle
 * >SPFHelper
 *  can check if the given file is the correct format make sure
 *  there are no illegal characters,
 *  length of each line = size x size don't have to check that the puzzles are
 *  solvable or that start out in a sane format.
 */