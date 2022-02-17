// Copyright (c) 2020 [Your Name]. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <sudoku/solver.h>
//#include <sudoku/sudoku-puzzle.h>

#include <catch2/catch.hpp>
namespace sudoku {
// TODO(you): Remove this unnecessary test case.
TEST_CASE("Load data into a SudokuPuzzle", "[sudoku-puzzle]") {
  SECTION("Getter") {
    // valid puzzle format string
    std::string puzzle =
        "85___24__72______9__4_________1_7__23_5___9___4___________8__7__17____"
        "__"
        "____36_4_";
    // create an inputstream from the string
    std::istringstream line_stream(puzzle);
    SudokuPuzzle sudoku_puzzle;
    // load the input into the puzzle
    line_stream >> sudoku_puzzle;
    REQUIRE(sudoku_puzzle.GetValueAt(0, 1) == '5');
    REQUIRE(sudoku_puzzle.GetValueAt(1, 8) == '9');
    REQUIRE(sudoku_puzzle.GetValueAt(5, 1) == '4');
    REQUIRE(sudoku_puzzle.GetValueAt(8, 5) == '6');
  }

  SECTION("Setter") {
    // valid puzzle format string
    std::string puzzle =
        "85___24__72______9__4_________1_7__23_5___9___4___________8__7__17____"
        "______36_4_";
    // create an inputstream from the string
    std::istringstream line_stream(puzzle);
    SudokuPuzzle sudoku_puzzle;
    // load the input into the puzzle
    line_stream >> sudoku_puzzle;
    std::cout << "BEFORE:\n" << sudoku_puzzle << std::endl;

    //    SECTION("Setting invalid chars") {
    REQUIRE(sudoku_puzzle.GetValueAt(0, 4) == '_');
    REQUIRE(!sudoku_puzzle.SetValueAt(0, 4, 'k'));
    REQUIRE(sudoku_puzzle.GetValueAt(4, 5) == '_');
    REQUIRE(!sudoku_puzzle.SetValueAt(4, 5, '0'));
    //    }

    //    SECTION("Setting open spaces") {
    // set an empty space
    REQUIRE(sudoku_puzzle.GetValueAt(0, 2) == '_');
    REQUIRE(sudoku_puzzle.SetValueAt(0, 2, '3'));
    std::cout << "Set '3' at 0,2" << std::endl;

    REQUIRE(sudoku_puzzle.GetValueAt(4, 4) == '_');
    REQUIRE(sudoku_puzzle.SetValueAt(4, 4, '8'));
    std::cout << "Set '8' at 4,4" << std::endl;

    //    }

    //    SECTION("Rewriting values") {
    // make sure you cannot rewrite values that have already been set
    REQUIRE(!sudoku_puzzle.SetValueAt(0, 1, '3'));
    REQUIRE(!sudoku_puzzle.SetValueAt(1, 8, '3'));
    REQUIRE(!sudoku_puzzle.SetValueAt(5, 1, '3'));
    // set an already set/modified space again (should be allowed)
    REQUIRE(sudoku_puzzle.SetValueAt(0, 2, '4'));
    std::cout << "Set '4' at 0,2" << std::endl;

    //    }

    std::cout << "AFTER:\n" << sudoku_puzzle << std::endl;
  }
}
}  // namespace sudoku