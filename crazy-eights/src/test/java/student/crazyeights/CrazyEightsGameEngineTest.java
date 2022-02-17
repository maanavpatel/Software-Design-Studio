package student.crazyeights;
import java.util.List;
import java.util.Random;
import java.util.Stack;
import org.junit.Before;
import org.junit.Test;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotEquals;

/**
 * Tests the the CrazyEightsGameEngine class.
 * This test relies on the use of a seed for Random so that the deck of cards that is
 * created as a result is always shuffled in a consistent manner and thus easily testable.
 */
public class CrazyEightsGameEngineTest {
  private CrazyEightsGameEngine game;
  private List<Card> deckList;
  private PlayerStrategy a;
  private PlayerStrategy b;
  private PlayerStrategy c;
  private PlayerStrategy d;

  @Before
  public void setUp() throws Exception {
    a = new PlayerStratHold8s();
    b = new PlayerStratHold8s();
    c = new PlayerStratHold8s();
    d = new PlayerStratHold8s();
    game = new CrazyEightsGameEngine(a,b,c,d);
    deckList = Card.getDeck();
  }

  @Test
  public void noCheaterGame() {
    game.setDeck();
    assertNotEquals(null, game.playGame());
  }

  @Test
  public void playerCWinsGame() {
    game.setShuffleRandomizer(new Random(4));
    game.setDeck();
    Stack<Card> deck = game.getCopyOfDeck();
    for (Card card : deck) {
      System.out.println(card.getRank() + " \t" +card.getSuit());
    }
    assertEquals(c, game.playGame());
  }

  @Test
  public void playerDWinsGame() {
    game.setShuffleRandomizer(new Random(7));
    game.setDeck();
    Stack<Card> deck = game.getCopyOfDeck();
    for (Card card : deck) {
      System.out.println(card.getRank() + " \t" +card.getSuit());
    }
    assertEquals(d, game.playGame());
  }

  @Test
  public void cheatingGame() {
    d = new PlayerStratCheats();
    game = new CrazyEightsGameEngine(a,b,c,d);
    deckList = Card.getDeck();
    game.setShuffleRandomizer(new Random(4));
    game.setDeck();
    Stack<Card> deck = game.getCopyOfDeck();
    for (Card card : deck) {
      System.out.println(card.getRank() + " \t" +card.getSuit());
    }
    //output should be null if there is a cheater
    assertEquals(null , game.playGame());
  }

  @Test
  public void cheatingTournament() {
    d = new PlayerStratCheats();
    game = new CrazyEightsGameEngine(a,b,c,d);
    game.setDeck();
    Stack<Card> deck = game.getCopyOfDeck();
    for (Card card : deck) {
      System.out.println(card.getRank() + " \t" +card.getSuit());
    }
    //output should be null if there is a cheater
    assertEquals(null , game.playGame());
  }

  @Test
  public void noCheatingTournament() {
    game.setDeck();
    Stack<Card> deck = game.getCopyOfDeck();
    for (Card card : deck) {
      System.out.println(card.getRank() + " \t" +card.getSuit());
    }
    //output should be null if there is a cheater
    assertNotEquals(null , game.playGame());
  }

}