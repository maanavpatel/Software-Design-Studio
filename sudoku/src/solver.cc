// Copyright 2020 [Your Name]. All rights reserved.

#include <sudoku/solver.h>

namespace sudoku {
// code below derived from:
// https://www.geeksforgeeks.org/sudoku-backtracking-7/
namespace {
bool FindUnassignedLocation(SudokuPuzzle &puzzle, size_t &x, size_t &y) {
  // look through all ys and xs
  for (y = 0; y < puzzle.GetSize(); y++) {
    for (x = 0; x < puzzle.GetSize(); x++) {
      // x is x, y is y
      if (puzzle.GetValueAt(x, y) == kUnassigned) {  // found empty space
        // the y& and x& will be set to the current index
        return true;
      }
    }
  }
  return false;
}

bool UsedInRow(SudokuPuzzle &puzzle, size_t y, char val) {
  for (size_t x = 0; x < puzzle.GetSize(); x++)
    if (puzzle.GetValueAt(x, y) == val) {
      return true;
    }
  return false;
}

bool UsedInCol(SudokuPuzzle &puzzle, size_t x, char val) {
  for (size_t y = 0; y < puzzle.GetSize(); y++) {
    if (puzzle.GetValueAt(x, y) == val) {
      return true;
    }
  }
  return false;
}

bool UsedInBox(SudokuPuzzle &puzzle, size_t boxStartRow, size_t boxStartCol,
               char val) {
  // the size of sudoku board will be a perfect square
  size_t end_of_box = sqrt(puzzle.GetSize());
  // look through ys and xs
  for (size_t x = 0; x < end_of_box; x++) {
    for (size_t y = 0; y < end_of_box; y++) {
      // check if the the box contains the value
      if (puzzle.GetValueAt(x + boxStartCol, y + boxStartRow) == val) {
        return true;
      }
    }
  }
  return false;
}
bool isSafe(SudokuPuzzle &puzzle, size_t x, size_t y, char val) {
  // the size of sudoku board will be a perfect square
  size_t box_size = sqrt(puzzle.GetSize());

  /* Check if 'num' is not already placed in
  current y, current xumn and current size by size box */
  return !UsedInRow(puzzle, y, val) && !UsedInCol(puzzle, x, val) &&
         !UsedInBox(puzzle, y - y % box_size, x - x % box_size, val) &&
         puzzle.GetValueAt(x, y) == kUnassigned;
}
}  // namespace

bool Solve(SudokuPuzzle &puzzle, int count) {
  std::cout << count << std::endl;
  size_t y;
  size_t x;
  // If there is no unassigned locations, we are done
  if (!FindUnassignedLocation(puzzle, y, x)) {
    std::cout << "SUCCESS solved:\n" << puzzle << std::endl;
    return true;  // success!
  }

  size_t size = puzzle.GetSize();
  // consider digits 1 to size
  for (char num = '1'; num <= '0' + size; num++) {
    // if looks promising
    if (isSafe(puzzle, x, y, num)) {
      // make tentative assignment
      puzzle.SetValueAt(x, y, num);
      // return, if success, yay!
      if (Solve(puzzle, count + 1)) {
        return true;
      } else {
        // failure, unmake & try again
        std::cout << "num: " << num << std::endl;
        puzzle.SetValueAt(x, y, kUnassigned);
      }
    }
  }
  return false;  // this triggers backtracking
}

}  // namespace sudoku
