//
// Created by Maanav Patel on 3/19/20.
//

#ifndef SUDOKU_FILE_HELPER_H
#define SUDOKU_FILE_HELPER_H

#include <fstream>
#include <iostream>

using std::cout;
using std::endl;
using std::getline;
using std::ifstream;
using std::string;

namespace sudoku {
class FileHelper {
 private:
  const char* kfileTag = "#spf1.0";
  string file_path;
  const int size = 9;
  int line_count = 1;

 public:
  void SetFilePath(string& file_path_to_spf);
  bool IsVersionCompatible();
  ifstream GetIstream();
  bool IsPuzzleValid(const string& puzzle);
};

}  // namespace sudoku

#endif  // SUDOKU_FILE_HELPER_H
