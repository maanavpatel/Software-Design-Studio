// Copyright (c) 2020 [Your Name]. All rights reserved.

#ifndef SUDOKU_SOLVER_H_
#define SUDOKU_SOLVER_H_

#include <sudoku/sudoku-puzzle.h>

namespace sudoku {
const char kUnassigned = '_';
namespace {
bool FindUnassignedLocation(sudoku::SudokuPuzzle& puzzle, size_t& x, size_t& y);
bool isSafe(sudoku::SudokuPuzzle& puzzle, size_t y, size_t x, char val);
bool UsedInRow(sudoku::SudokuPuzzle& puzzle, size_t y, char val);
bool UsedInCol(sudoku::SudokuPuzzle& puzzle, size_t y, char val);

}  // namespace
bool Solve(SudokuPuzzle& puzzle, int count);
}  // namespace sudoku

#endif  // SUDOKU_SOLVER_H_
