package student.crazyeights;

import static org.junit.Assert.assertEquals;
import java.util.Collections;
import java.util.LinkedList;
import java.util.List;
import java.util.Random;
import org.junit.Before;
import org.junit.Ignore;
import org.junit.Test;

/**
 * Tests the PlayerStratHold8s.java file. This test relies on the use of a seed for Random
 * so that the deck of cards that is created as a result is always shuffled in a consistent manner.
 */
public class PlayerStratHold8sTest {
private List<Card> deck;
private PlayerStratHold8s p;

  @Ignore
  private void giveCards(int randomSeed) {
    int randSeed = randomSeed;
    Collections.shuffle(deck, new Random(randomSeed));
    List<Card> toGive = new LinkedList<>();
    for (int i = 0; i < 5; i++) {
      System.out.println(deck.get(0).getRank() + " of " + deck.get(0).getSuit());
      toGive.add(deck.remove(0));
    }
    p.receiveInitialCards(toGive);
  }
  @Before
  public void setUp() throws Exception {
    //make a new player
    p = new PlayerStratHold8s();
    //add opponent Id's to list and initialize player
    List<Integer> opponentIds = new LinkedList<>();
    opponentIds.add(1);
    opponentIds.add(2);
    opponentIds.add(3);
    p.init(0, opponentIds);
    //get a new deck of cards
    deck = Card.getDeck();
  }

  @Test
  public void testCountEights() {
     /* the hand that results from the random seed is known and therefore I can guarantee there will
     always be 1 eight in the hand.*/
    giveCards(8);
    assertEquals(1, p.getEightCount());
  }

  @Test
  public void testCountEightsNone() {
    /* the hand that results from the random seed is known and therefore I can guarantee there will
     always be 0 eights in the hand.*/
    giveCards(0);
    assertEquals(0, p.getEightCount());
  }

  @Test
  public void shouldDrawCardFalse(){
    giveCards(3);
    Card c = deck.remove(0); //TWO OF HEARTS
    System.out.println("top card: " + c.getRank() + " of " + c.getSuit());
    boolean result = p.shouldDrawCard(c, null);
    assertEquals(false, result);
  }

  @Test
  public void shouldDrawCardTrue(){
    giveCards(2);
    Card c = deck.remove(0); //FIVE OF DIAMONDS
    System.out.println("top card: " + c.getRank() + " of " + c.getSuit());
    boolean result = p.shouldDrawCard(c, null);
    assertEquals(true, result);
  }

  @Test
  public void declaredSuitDrawFalse(){
    giveCards(2);
    Card c = deck.remove(0); //FIVE OF DIAMONDS
    System.out.println("top card: " + c.getRank() + " of " + c.getSuit());
    boolean result = p.shouldDrawCard(c, Card.Suit.HEARTS);
    assertEquals(false, result);
  }

  @Test
  public void declaredSuitDrawTrue(){
    giveCards(3);
    Card c = deck.remove(0); //Two of Hearts
    System.out.println("top card: " + c.getRank() + " of " + c.getSuit());
    boolean result = p.shouldDrawCard(c, Card.Suit.SPADES);
    assertEquals(true, result);
  }

  @Test
  public void drawOnLastTrue(){
    Collections.shuffle(deck, new Random(8));
    List<Card> oneCard = new LinkedList<>();
    oneCard.add(deck.remove(0));
    System.out.println(oneCard.get(0).getRank() + "\t" + oneCard.get(0).getSuit());
    Card c = deck.remove(0); //KING of HEARTS
    System.out.println("top card: " + c.getRank() + " of " + c.getSuit());
    boolean result = p.shouldDrawCard(c, null);
    System.out.println("should draw: " + result);
    assertEquals(true, result);
  }

  @Test
  public void drawOnLastChangedSuitTrue() {
    Collections.shuffle(deck, new Random(8));
    List<Card> oneCard = new LinkedList<>();
    oneCard.add(deck.remove(0)); //QUEEN of SPADES
    System.out.println(oneCard.get(0).getRank() + "\t" + oneCard.get(0).getSuit());
    Card c = deck.remove(0); //KING of HEARTS
    System.out.println("top card: " + c.getRank() + " of " + c.getSuit());
    boolean result = p.shouldDrawCard(c, Card.Suit.DIAMONDS);
    System.out.println("should draw: " + result);
    assertEquals(true, result);
  }

  @Test
  public void drawOnLastChangedSuitFalse() {
    Collections.shuffle(deck, new Random(8));
    List<Card> oneCard = new LinkedList<>();
    oneCard.add(deck.remove(0)); //QUEEN of SPADES
    System.out.println(oneCard.get(0).getRank() + "\t" + oneCard.get(0).getSuit());
    Card c = deck.remove(0); //KING of HEARTS
    System.out.println("top card: " + c.getRank() + " of " + c.getSuit());
    boolean result = p.shouldDrawCard(c, Card.Suit.DIAMONDS);
    System.out.println("should draw: " + result);
    assertEquals(true, result);
  }

}