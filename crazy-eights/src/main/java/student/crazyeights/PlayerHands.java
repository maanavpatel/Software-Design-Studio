package student.crazyeights;

import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;

/**
 * This class will track the hands of all PlayerStrategy implementations in the
 * CrazyEightsGameEngine class.
 */
public class PlayerHands {
  private List<PlayerStrategy> allPlayers;
  private HashMap<PlayerStrategy, List<Card>> playerHands;


  public PlayerHands(final List<PlayerStrategy> players) {
    allPlayers = new LinkedList<>();
    playerHands = new HashMap<>();
    allPlayers.addAll(players);
  }

  /**
   * Give each player their first cards.
   * @param player
   * @param cardsInHand
   */
  public void initializePlayerHand(final PlayerStrategy player, final List<Card> cardsInHand) {
    playerHands.put(player, cardsInHand);
  }

  /**
   * add a card to the hand for the PlayerStrategy.
   * @param player
   * @param c
   */
  public void addCard(final PlayerStrategy player, final Card c) {
    List<Card> handWithAdded = new LinkedList<>();
    handWithAdded.addAll(playerHands.get(player)); //copy current hand
    handWithAdded.add(c); //add the card
    playerHands.replace(player, handWithAdded); //replace current hand with updated
  }

  /**
   * remove a card to the hand for the PlayerStrategy.
   * @param player
   * @param c
   */
  public void removeCard(final PlayerStrategy player, final Card c) {
    List<Card> handWithRemoved = new LinkedList<>();
    handWithRemoved.addAll(playerHands.get(player));
    handWithRemoved.remove(c);
    playerHands.replace(player, handWithRemoved);
  }

  /**
   * Get all the cards for the PlayerStrategy
   * @param player
   * @return
   */
  public List<Card> getHand(PlayerStrategy player){
    return playerHands.get(player);
  }

  /**
   *Get the Hand as a nicely formatted string.
   * @param player
   * @return
   */
  public String getHandAsString(PlayerStrategy player) {
    List<Card> currentHand = playerHands.get(player);
    StringBuilder s = new StringBuilder();
    for (Card c : currentHand) {
      s.append("\n\t");
      s.append(c.getRank());
      s.append(" \t");
      s.append(c.getSuit());
    }
    return s.toString();
  }

  /**
   * Get the summation of the point values of all the Cards in the PlayerStrategy's hand.
   * @param player
   * @return
   */
  public int getHandValue(final PlayerStrategy player) {
    List<Card> currentHand = playerHands.get(player);
    int handValue = 0;
    if (currentHand != null) {
      for (Card c : currentHand) {
        handValue += c.getPointValue();
      }
    }
    return handValue;
  }



}
