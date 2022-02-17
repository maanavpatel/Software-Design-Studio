// Copyright (c) 2020 [Your Name]. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <string>

#include <catch2/catch.hpp>
#include <tictactoe/tictactoe.h>


using tictactoe::EvaluateBoard;
using tictactoe::TicTacToeState;

//No winner test cases
TEST_CASE("Simple no winner", "[no-winner]") {
  REQUIRE(EvaluateBoard("O...X.X..") == TicTacToeState::NoWinner);
}

TEST_CASE("Simple Empty No Winner", "[no-winner]") {
  REQUIRE(EvaluateBoard(".........") == TicTacToeState::NoWinner);
}

TEST_CASE("Other Empty No Winner", "[no-winner]") {
  REQUIRE(EvaluateBoard("JfAl 92l ") == TicTacToeState::NoWinner);
}

TEST_CASE("Full Board Tie No Winner", "[no-winner]") {
  REQUIRE(EvaluateBoard("xoxooxxxo") == TicTacToeState::NoWinner);
}

//invalid inputs
TEST_CASE("Input too long Random", "[invalid-input]") {
  REQUIRE(EvaluateBoard("here is a string that would be too long") ==
          TicTacToeState::InvalidInput);
}

TEST_CASE("too Short Invalid", "[invalid-input]") {
  REQUIRE(EvaluateBoard("xo.") == TicTacToeState::InvalidInput);
}

TEST_CASE("Input too long", "[invalid-input]") {
  REQUIRE(EvaluateBoard(".XXX.OOO...OO") == TicTacToeState::InvalidInput);
}

TEST_CASE("Empty board", "[invalid-input]") {
  REQUIRE(EvaluateBoard("") == TicTacToeState::InvalidInput);
}

// unreachable states
TEST_CASE("All Xs", "[unreachable-state]") {
  REQUIRE(EvaluateBoard("xxXxXxXxx") == TicTacToeState::UnreachableState);
}

TEST_CASE("too Many X Unreachable", "[unreachable-state]") {
  REQUIRE(EvaluateBoard("OoxXxoX-X") == TicTacToeState::UnreachableState);
}

TEST_CASE("O Win but too Many X so Unreachable", "[o-wins]") {
  REQUIRE(EvaluateBoard("X.XX.XOOO") == TicTacToeState::UnreachableState);
}

TEST_CASE("too Many O Unreachable", "[unreachable-state]") {
  REQUIRE(EvaluateBoard("-x..Oo..-") == TicTacToeState::UnreachableState);
}

TEST_CASE("same Num XO Unreachable", "[unreachable-state]") {
  REQUIRE(EvaluateBoard("xxx.o.oo.") == TicTacToeState::UnreachableState);
}

TEST_CASE("both Cant Win Unreachable", "[unreachable-state]") {
  REQUIRE(EvaluateBoard("oxXoxXooX") == TicTacToeState::UnreachableState);
}

//O wins
TEST_CASE("right column o win", "[o-wins]") {
  REQUIRE(EvaluateBoard("2.OxXo-xO") == TicTacToeState::Owins);
}

TEST_CASE("middle row O", "[o-wins]") {
  REQUIRE(EvaluateBoard("Zxxooox\tF") == TicTacToeState::Owins);
}

TEST_CASE("top Row O Win", "[o-wins]") {
  REQUIRE(EvaluateBoard("x.oxO.ox.") == TicTacToeState::Owins);
}

TEST_CASE("bottom O Win, same X count", "[o-wins]") {
  REQUIRE(EvaluateBoard("..XX.XOOO") == TicTacToeState::Owins);
}

// X Wins
TEST_CASE("bottom Row X Win", "[x-wins]") {
  REQUIRE(EvaluateBoard("o2o[]]xxx") == TicTacToeState::Xwins);
}

TEST_CASE("mid Col X Win", "[x-wins]") {
  REQUIRE(EvaluateBoard("oX.ox0.x=") == TicTacToeState::Xwins);
}

TEST_CASE("top Left X Win", "[x-wins]") {
  REQUIRE(EvaluateBoard("x4roxO7-X") == TicTacToeState::Xwins);
}

/*
 * The following tests will only pass if the kBoard_size value is
 * changed for each one.
 */
/*
TEST_CASE("seven by seven x win", "[x-wins][bigger-board]") {
  REQUIRE(EvaluateBoard("x..o...x..o...xo.....xo.....x......xfo...ex.fowgy")
  == TicTacToeState::Xwins);
}

TEST_CASE("five by five o win", "[x-wins][bigger board]") {
  REQUIRE(EvaluateBoard("o...x.o..x..oxs...ox...xo")
          == TicTacToeState::Owins);
}
*/