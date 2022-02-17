package student.tictactoe;

import org.junit.Test;
import static org.junit.Assert.*;


public class TicTacToeTest {
    /* Invalid inputs */
    @Test
    public void tooLongInvalid() throws Exception {
        assertEquals(Evaluation.InvalidInput, TicTacToe.evaluateBoard("fjakcakqoe mc,xlfopq3qi jkdsl;"));
    }
    @Test
    public void tooLongXOInvalid()  {
        assertEquals(Evaluation.InvalidInput, TicTacToe.evaluateBoard(".XXX.OOO...OO"));
    }
    @Test
    public void tooShortInvalid()  {
        assertEquals(Evaluation.InvalidInput, TicTacToe.evaluateBoard("XO"));
    }
    @Test
    public void emptyStringInvalid()  {
        assertEquals(Evaluation.InvalidInput, TicTacToe.evaluateBoard(""));
    }
    @Test
    public void nullInvalid()  {
        assertEquals(Evaluation.InvalidInput, TicTacToe.evaluateBoard(null));
    }

    /* helper methods */
    @Test
    public void isValidTrue()  {
        assertTrue(TicTacToe.isStringValid("x..o....."));
    }
    @Test
    public void isValidFalse()  {
        assertFalse(TicTacToe.isStringValid("x.sdfjk.o.XXXXjkl.."));
    }
    @Test
    public void xCantWin()  {
        char[][] testBoard = { {'o','x','.'}, {'o','x','.'}, {'.','o','.'}};
        assertFalse(TicTacToe.didPlayerWin(testBoard, 'x'));
    }

    @Test
    public void oCanWin()  {
        char[][] testBoard = { {'o','x','x'}, {'o','o','.'}, {'x','x','o'}};
        assertEquals(true, TicTacToe.didPlayerWin(testBoard, 'o'));
    }

    @Test
    public void countX()  {
        char[][] testBoard =
                { {'o','x','.'}, {'o','x','.'}, {'.','x','.'}};
        assertEquals(3, TicTacToe.countTurns(testBoard, 'x'));
    }

    @Test
    public void simpleCreateBoard()  {
        String testBoard = "x..o...x.";
        char[][] resultArray = TicTacToe.createBoard(testBoard);
        String resultStr = "";
        for (int i = 0; i < resultArray.length; i++){
            resultStr += new String(resultArray[i]);
        }

        assertEquals(true, testBoard.equals(resultStr));
    }

    @Test
    public void messyCreateBoard()  {
        boolean works = false;
        String board = "x7-8eo=+x";
        String formattedBoard = "x....o..x";

        char[][] resultArray = TicTacToe.createBoard(board);
        String resultStr = "";

        for (int i = 0; i < resultArray.length; i++){
            resultStr += new String(resultArray[i]);
        }
        works = formattedBoard.equals(resultStr);
        assertTrue(works);
    }


    /* Unreachable state */

    @Test
    public void allXUnreachable()  {
        assertEquals(Evaluation.UnreachableState, TicTacToe.evaluateBoard("xxXxXxXxx"));
    }
    @Test
    public void tooManyXUnreachable()  {
        assertEquals(Evaluation.UnreachableState, TicTacToe.evaluateBoard("OoxXxoX-X"));
    }
    @Test
    public void tooManyOUnreachable()  {
        assertEquals(Evaluation.UnreachableState, TicTacToe.evaluateBoard("-x..Oo..-"));
    }
    @Test
    public void sameNumXOUnreachable()  {
        assertEquals(Evaluation.UnreachableState, TicTacToe.evaluateBoard("xxx.o.oo."));
    }
    /* The game should have stopped when either X or O won*/
    @Test
    public void bothCantWinUnreachable()  {
        assertEquals(Evaluation.UnreachableState, TicTacToe.evaluateBoard("oxXoxXooX"));
    }

    /* No winner */
    @Test
    public void simpleNoWinnerBoard()  {
        assertEquals(Evaluation.NoWinner, TicTacToe.evaluateBoard("O...X.X.."));
    }
    @Test
    public void simpleEmptyNoWinner()  {
        assertEquals(Evaluation.NoWinner, TicTacToe.evaluateBoard("........."));
    }
    @Test
    public void otherEmptyNoWinner()  {
        assertEquals(Evaluation.NoWinner, TicTacToe.evaluateBoard("jfal 92l "));
    }
    @Test
    public void fullBoardTieNoWinner()  {
        assertEquals(Evaluation.NoWinner, TicTacToe.evaluateBoard(
                "xoxooxxxo"));
    }
    /*Horizontal Wins*/
    @Test
    public void topRowOWin()  {
        assertEquals(Evaluation.Owins, TicTacToe.evaluateBoard("oOo.xX.8x"));
    }
    @Test
    public void bottomRowXWin()  {
        assertEquals(Evaluation.Xwins, TicTacToe.evaluateBoard("o2o[]]xxx"));
    }
    @Test
    public void middleRowOWin()  {
        assertEquals(Evaluation.Owins, TicTacToe.evaluateBoard("Zxxooox\tF"));
    }

    /*Vertical Wins*/
    @Test
    public void rightColOWin() {
        assertEquals(Evaluation.Owins, TicTacToe.evaluateBoard("2.OxXo-xO"));
    }
    @Test
    public void midColXWin() {
        assertEquals(Evaluation.Xwins, TicTacToe.evaluateBoard("oX.ox0.x="));
    }

    /* Diagonal Wins */
    @Test
    public void topLeftXWin() {
        assertEquals(Evaluation.Xwins, TicTacToe.evaluateBoard("x4roxO7-X"));
    }

    @Test
    public void topRightOWin() {
        assertEquals(Evaluation.Owins, TicTacToe.evaluateBoard("x.oxO.ox."));
    }

//    @Test
//    public void sevenBysevenXwin() {
//        assertEquals(Evaluation.Xwins, TicTacToe.evaluateBoard("x..o...x..o...xo.....xo.....x......xfo...ex.fowgy"));
//    }
//    @Test
//    public void fiveByfiveOwin() {
//        assertEquals(Evaluation.Owins, TicTacToe.evaluateBoard(
//                "o...x.o..x..oxs...ox...xo"));
//    }



}