// Copyright (c) 2020 [Your Name]. All rights reserved.

#ifndef CPPTICTACTOE_TICTACTOE_H_
#define CPPTICTACTOE_TICTACTOE_H_

#include <string>

namespace tictactoe {

// Represents the states of a tictactoe game.
enum class TicTacToeState {
  UnreachableState,
  Xwins,
  Owins,
  NoWinner,
  InvalidInput,
};

// Returns the corresponding state of the board.
/**
 * Evaluates a tic tac toe board.
 *
 * @param board a string representing the state of the tic-tac-toe board
 * in row major order.
 * @return the state/evaluation of the board.
 */
TicTacToeState EvaluateBoard(const std::string& board);

}  // namespace tictactoe

#endif  // CPPTICTACTOE_TICTACTOE_H_
