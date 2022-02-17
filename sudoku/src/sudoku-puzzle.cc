//
// Created by Maanav Patel on 3/22/20.
//

#include "sudoku/sudoku-puzzle.h"

namespace sudoku {
bool SudokuPuzzle::IsCharValid(char c) { return (c >= '1' && c <= '0' + size); }

std::istream& operator>>(std::istream& is, SudokuPuzzle& sp) {
  std::string puzzle_str;
  std::getline(is, puzzle_str);
  sp.size = (int)sqrt(puzzle_str.length());
  size_t str_index = 0;
  for (size_t i = 0; i < sp.size; ++i) {  // columns
    std::vector<char> row;
    for (size_t j = 0; j < sp.size; ++j) {  // rows
      row.push_back(puzzle_str[str_index]);
      ++str_index;
    }
    sp.board.push_back(row);
  }
  initial_version = sp;
  return is;
}

int SudokuPuzzle::GetSize() { return size; }
char SudokuPuzzle::GetValueAt(int x, int y) {
  if (x < 0 || y < 0 || x >= size || y >= size) {
    std::cout << "index out of bounds: " << x << ',' << y << std::endl;
    return ' ';
  }
  return board[x][y];
}

bool SudokuPuzzle::SetValueAt(int x, int y, char c) {
  // out of bounds check
  if (x < 0 || y < 0 || y >= size || x >= size) {
    return false;
  } else {
    if (initial_version.GetValueAt(x, y) != '_') {
      return false;
    } else if (IsCharValid(c)) {
      board[x][y] = c;
      return true;
    }
    return false;
  }
}

std::ostream& operator<<(std::ostream& os, SudokuPuzzle& sp) {
  for (int i = 0; i < sp.size; ++i) {
    if (i % (int)sqrt(sp.size) == 0) {
      for (int k = 0; k < sp.size; ++k) {
        os << "_____";
      }
      os << std::endl;
    }
    for (int j = 0; j < sp.size; ++j) {
      os << sp.GetValueAt(i, j) << '\t';
      if ((j + 1) % (int)sqrt(sp.size) == 0 && j + 1 != sp.size) {
        os << "|\t";
      }
    }
    os << std::endl;
  }

  for (int k = 0; k < sp.size; ++k) {
    os << "_____";
  }
  os << "\n" << std::endl;

  return os;
}

}  // namespace sudoku

// be able to retrieve any value at any position
// be able to get all values within a square (9 squares for a size 9)
// row and col should be easy but fig out how to easily split into squares
// may have to use mod or something
