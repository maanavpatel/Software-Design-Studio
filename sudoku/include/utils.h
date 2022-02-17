//
// Created by Maanav Patel on 3/21/20.
//

#ifndef SUDOKU_UTILS_H
#define SUDOKU_UTILS_H

#endif  // SUDOKU_UTILS_H

#include <sudoku/file-helper.h>
#include <sudoku/solver.h>

#include <fstream>
#include <iostream>
#include <sstream>

using std::cout;
using std::endl;
using std::ifstream;
using std::string;

namespace sudoku {
bool AreArgumentsValid(int argc, char** argv);
void Solve(string path_to_file);
}  // namespace sudoku
