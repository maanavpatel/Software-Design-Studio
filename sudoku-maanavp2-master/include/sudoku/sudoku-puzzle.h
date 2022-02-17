//
// Created by Maanav Patel on 3/22/20.
//

#ifndef SUDOKU_SUDOKU_PUZZLE_H
#define SUDOKU_SUDOKU_PUZZLE_H

#endif  // SUDOKU_SUDOKU_PUZZLE_H

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace sudoku {
class SudokuPuzzle {
 private:
  size_t size = 0;
  // 2d vector to hold all values
  std::vector<std::vector<char>> board;
  // size of the board (ex. size = 9 for a board with 81 values)
  bool IsCharValid(char c);

 public:
  friend std::istream& operator>>(std::istream& is, SudokuPuzzle& s);
  friend std::ostream& operator<<(std::ostream& os, SudokuPuzzle& sp);
  char GetValueAt(int x, int y);
  bool SetValueAt(int x, int y, char c);
  int GetSize();
};
namespace {
// this is used to keep track of the initial values so that they cannot be
// overwritten when setting values
SudokuPuzzle initial_version;
}  // namespace
}  // namespace sudoku
