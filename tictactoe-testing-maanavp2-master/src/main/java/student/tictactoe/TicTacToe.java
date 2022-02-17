package student.tictactoe;

/**
 * The TicTacToe class has the ability to evaluate a board of any size and return the state of the game.
 * There are six possible outcomes represented as enums all of which come from the Evaluation class.
 */
public class TicTacToe {
    public static final int BOARD_SIZE = 3;

    /**
     * Evaluates a tic tac toe board with dimensions BOARD_SIZE * BOARD_SIZE.
     *
     * @param boardState String representing the state of the tic-tac-toe board in row major order.
     * @return an enum representing the evaluation of the given board.
     */
    public static Evaluation evaluateBoard(String boardState) {
        if (!isStringValid(boardState)) {
            return Evaluation.InvalidInput;
        }

        boardState = boardState.toLowerCase();
        char[][] board = createBoard(boardState);

        int xCount = countTurns(board, 'x');
        int oCount = countTurns(board, 'o');
        //make sure either player has not taken too many turns
        if (xCount - oCount > 1 || xCount - oCount < 0) {
            return Evaluation.UnreachableState;
        }

        boolean xWins;
        boolean oWins;
        xWins = didPlayerWin(board, 'x');
        oWins = didPlayerWin(board, 'o');

        if (!xWins && !oWins) {
            return Evaluation.NoWinner;
        } else if (xWins && oWins || xWins && (oCount >= xCount)) {
            return Evaluation.UnreachableState;
        } else if (xWins) {
            return Evaluation.Xwins;
        } else if (oWins) {
            return Evaluation.Owins;
        }

        return Evaluation.NoWinner;
    }


    /**
     * Checks the given board to see if the player has enough in a line to win.
     *
     * @param board 2d character array representing the game board
     * @param c character representing the player x or o
     * @return boolean representing if the player has 3 in a row
     */
    static boolean didPlayerWin(char[][] board, char c){
        boolean checkedHoriz = false;
        //checks horizontal wins then vertical (increase col# first time around, then row#)
        for (int i = 0; i < 2; i++) {
            if (i == 1) {
                checkedHoriz = true;
            }

            for (int direction1 = 0; direction1 < BOARD_SIZE; direction1++) {
                char first = board[direction1][0];

                if(checkedHoriz) {
                    first = board[0][direction1];
                }

                if (first == c) {
                    int playerCount = 0;

                    for (int direction2 = 0; direction2 < BOARD_SIZE; direction2++) {
                        int row = direction1;
                        int col = direction2;
                        if (checkedHoriz) {
                            row = direction2;
                            col = direction1;
                        }
                        if (first != board[row][col]) {
                            break;
                        } else {
                            playerCount++;
                        }
                    }

                    if (playerCount == board.length) {
                        return true;
                    }
                }
            }
        }
        //check diagonals
        int topLeftDiagCount = 0;
        int topRightDiagCount = 0;
        char topLeftSquare = board[0][0];
        char topRight = board[0][board.length - 1];

        for (int pos = 0; pos < BOARD_SIZE; pos++) {

            if (topLeftSquare == c && board[pos][pos] == c) {
                topLeftDiagCount++;
            }
            if (topRight == c && board[pos][board.length - 1 - pos] == c) {
                topRightDiagCount++;
            }
            if (topRightDiagCount == board.length || topLeftDiagCount == board.length) {
                return true;
            }
        }
        return false;
    }

    /**
     * Checks if the input String is valid and can be used to evaluate a board.
     *
     * @param input is a String representing the state of the tic-tac-toe board.
     * @return a boolean representing if the input is valid.
     */
    static boolean isStringValid(String input) {
        if (input != null) {
            if (input.length() == BOARD_SIZE * BOARD_SIZE) {
                return true;
            }
        }
        return false;
    }

    /**
     * Given a string of a valid board, it will return a 2D char array where all characters
     * not 'x' or 'o' will be converted to '.'.
     *
     * @param boardState is a String representing the state of a valid tic-tac-toe board.
     * @return a two-dimensional char array representing the game board, with the first char given in
     *     the string at position [0][0], third at [0][2], last at [BOARD_SIZE][BOARD_SIZE];
     */
    static char[][] createBoard(String boardState) {
        char[][] board = new char[BOARD_SIZE][BOARD_SIZE];
        int boardIndex = 0;
        for (int row = 0; row < board.length; row++) {
            for (int col = 0; col < board[row].length; col++) {
                char c = boardState.charAt(boardIndex);
                if (c != 'x' && c != 'o') {
                    c = '.';
                }
                board[row][col] = c;
                boardIndex++;
            }
        }
        return board;
    }

    /**
     * Counts how many turns a given player has taken.
     *
     * @param board 2d character array representing the game board
     * @param player char representing the player whose turns need to be counted.
     * @return an int representing the number of turns taken.
     */
    static int countTurns(char[][] board, char player) {
        int turns = 0;
        for (int col = 0; col < board.length; col++) {
            for (int row = 0; row < board[col].length; row++ ) {
                if (board[col][row] == player) {
                    turns++;
                }
            }
        }
        return turns;
    }
}
