// Copyright 2020 [Your Name]. All rights reserved.

#include <tictactoe/tictactoe.h>

#include <iostream>
#include <set>

namespace tictactoe {

using std::string;

/*
 * The size of the board that the game will be played on.
 * (Usually tic tac toe is played on a 3 by 3 so kBoardSize = 3)
 */
const int kBoardSize = 3;

/**
 * Checks if the given input string representing the board is of the
 * valid format.
 *
 * @param input represents the tic tac toe board that needs to be evaluated.
 * @return a boolean representing if the input is valid.
 */
bool IsInputValid(const string& input) {
  return input.length() == kBoardSize * kBoardSize;
}

/**
 * Creates a string that is the lower case equivalent of the the input.
 * @param input the string that is wanting to be converted.
 * @return a
 */
string MakeStringLowerCase(string input) {
  for (char& c : input) {
    // uses the std::string's tolower for each char in the string
    c = (char)tolower((int)c);
  }
  return input;
}

/**
 * Modifies an array representing a game board by filling values in as
 * either 'x', 'o', or '.' (for empty spaces).
 *
 * @param board_to_fill an array representing a game board that needs
 * to be filled.
 * @param board_str the string that will be used to fill the board. This must be
 * a lowercase string.
 */
void FillBoardArray(char board_to_fill[kBoardSize][kBoardSize],
                    const string& board_str) {
  int board_index = 0;
  for (int i = 0; i < kBoardSize; ++i) {
    for (int j = 0; j < kBoardSize; ++j) {
      /*space_value refers to the value of a certain square or space on the
       game board.*/
      char space_value = board_str[board_index];
      if (space_value != 'x' && space_value != 'o') {
        // any other character is an empty space
        space_value = '.';
      }
      std::cout << space_value << "\t";

      board_to_fill[i][j] = space_value;
      ++board_index;
    }
    std::cout << "\n";
  }
}

/**
 * Counts how many turns were taken by a given player by counting how many
 * spaces match the given player's char.
 *
 * @param board_array an array of size kBoardSize representing the game board.
 * @param player the player for which turns want to be counted.
 * @return how many turns the given player has taken.
 */
int CountTurns(const char board_array[kBoardSize][kBoardSize],
               const char& player) {
  int turns = 0;
  for (int i = 0; i < kBoardSize; ++i) {
    for (int j = 0; j < kBoardSize; ++j) {
      // i is the column number, j is the row number
      if (board_array[i][j] == player) {
        ++turns;
      }
    }
  }
  return turns;
}

/**
 * Checks 'rows' and 'columns' of the game board to find if the player is in a
 * winning position, by figuring out if they occupy all spaces in row or column.
 *
 * @param board_array an array of size kBoardSize representing the game board.
 * @param player the player to perform the win check on.
 * @return true if the player occupies kBoardSize spaces in a row or column.
 */
bool VertOrHorizWinCheck(const char board_array[kBoardSize][kBoardSize],
                         const char& player) {
  bool checked_horiz = false;
  // checks horizontal wins then vertical
  for (int i = 0; i < 2; ++i) {
    if (i == 1) {
      checked_horiz = true;
    }
    // j represents col# when checking horizontal win,
    // then row# afterwards to check vertical wins
    for (int j = 0; j < kBoardSize; ++j) {
      char first = board_array[j][0];
      if (checked_horiz) {
        first = board_array[0][j];
      }
      if (first == player) {
        int player_count = 0;
        // k represents row# when checking horizontal win,
        // then col# afterwards to check vertical wins
        for (int k = 0; k < kBoardSize; ++k) {
          int row = j;
          int col = k;
          if (checked_horiz) {
            row = k;
            col = j;
          }
          if (first != board_array[row][col]) {
            break;
          } else {
            ++player_count;
          }
        }
        if (player_count == kBoardSize) {
          return true;
        }
      }
    }
  }
  return false;
}

/**
 * Checks 'diagonals' of the game board to find if the player is in a
 * winning position.
 *
 * @param board an array of size kBoardSize representing the game board.
 * @param player the player to perform the win check on.
 * @return true if the player occupies kBoardSize spaces in a diagonal.
 */
bool DiagWinCheck(const char board[kBoardSize][kBoardSize],
                  const char& player) {
  int top_left_diag_count = 0;
  int top_right_diag_count = 0;
  char top_left_space = board[0][0];
  char top_right_space = board[0][kBoardSize - 1];

  for (int i = 0; i < kBoardSize; ++i) {
    // i is similar to a position or coordinate on the board
    if (top_left_space == player && board[i][i] == player) {
      ++top_left_diag_count;
    }
    if (top_right_space == player && board[i][kBoardSize - 1 - i] == player) {
      ++top_right_diag_count;
    }
    if (top_right_diag_count == kBoardSize ||
        top_left_diag_count == kBoardSize) {
      return true;
    }
  }
  return false;
}

/**
 * Checks if the given player can win in horizontal, vertical,
 * or diagonal directions.
 *
 * @param boardArr an array of size kBoardSize representing the game board.
 * @param player the player to perform the win check on.
 * @return whether the player is a possible winner.
 */
bool PlayerIsPossibleWinner(const char boardArr[kBoardSize][kBoardSize],
                            const char& player) {
  return VertOrHorizWinCheck(boardArr, player) ||
         DiagWinCheck(boardArr, player);
}

TicTacToeState EvaluateBoard(const string& board) {
  if (!IsInputValid(board)) {
    return TicTacToeState::InvalidInput;
  }
  // change to lower case and make an array
  char board_array[kBoardSize][kBoardSize];
  FillBoardArray(board_array, MakeStringLowerCase(board));
  int x_count = CountTurns(board_array, 'x');
  int o_count = CountTurns(board_array, 'o');
  // make sure either player has not taken too many turns
  if (x_count - o_count > 1 || x_count - o_count < 0) {
    return TicTacToeState::UnreachableState;
  }
  // find out if each player has possibly won
  bool x_wins;
  bool o_wins;
  x_wins = PlayerIsPossibleWinner(board_array, 'x');
  o_wins = PlayerIsPossibleWinner(board_array, 'o');

  if (!x_wins && !o_wins) {
    return TicTacToeState::NoWinner;
  } else if ((x_wins && o_wins) || (x_wins && (o_count >= x_count)) ||
             (o_wins && (x_count > o_count))) {
    // if both are possible winners OR there are not less 'o' than 'x' when xWin
    return TicTacToeState ::UnreachableState;
  } else if (x_wins) {
    return TicTacToeState ::Xwins;
  } else {  // o_wins will be true
    return TicTacToeState::Owins;
  }
}
}  // namespace tictactoe
