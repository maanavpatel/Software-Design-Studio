//
// Created by Maanav Patel on 3/21/20.
//
#include <utils.h>

namespace sudoku {
namespace {}
bool AreArgumentsValid(int argc, char** argv) {
  if (argc <= 1) {
    cout << "no file path entered" << endl;
    return false;
  }
  cout << "You have entered " << (argc - 1) << " arguments:" << endl;
  // check if file is valid
  ifstream file(argv[argc - 1]);
  if (file.fail()) {
    std::cout << "Something is wrong with the file path you entered." << endl;
    return false;
  }
  return true;
}

void Solve(string path_to_file) {
  FileHelper file_helper;
  file_helper.SetFilePath(path_to_file);
  auto file_stream = file_helper.GetIstream();
  size_t line_count = 0;
  string line;
  while (std::getline(file_stream, line)) {
    if (line_count == 0) {
      if (!file_helper.IsVersionCompatible()) {
        break;
      }
    } else {
      if (file_helper.IsPuzzleValid(line)) {
        cout << "==========\n"
             << "Puzzle #" << line_count << "\n==========" << endl;
        string puzzle = line;
        std::istringstream line_stream(puzzle);
        SudokuPuzzle sudoku_puzzle;
        line_stream >> sudoku_puzzle;
        cout << sudoku_puzzle;
        bool x = Solve(sudoku_puzzle, 0);
        cout << x << sudoku_puzzle;
      } else {
        cout << "invalid puzzle found on line: " << line_count + 1 << endl;
        break;
      }
    }
    ++line_count;
  }
}
}  // namespace sudoku
