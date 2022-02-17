package student.crazyeights;

import java.util.LinkedList;
import java.util.List;

public class PlayerStrategyRandom implements PlayerStrategy{
  private List<Integer> myOpponentsIDs;
  private int myId;
  private List<Card> cardsInHand;
  private Card cardToPlay;
  private int eightCount;

  public PlayerStrategyRandom() {
  }

  @Override
  public void init(final int playerId, final List<Integer> opponentIds) {
    myOpponentsIDs = new LinkedList<>();
    cardsInHand = new LinkedList<>();
    myId = playerId;
    myOpponentsIDs = opponentIds;
  }

  @Override
  public void receiveInitialCards(final List<Card> cards) {
    cardsInHand.addAll(cards);
    eightCount = countEights();
  }

  public int getEightCount() {
    return eightCount;
  }

  /**
   * Called by receiveInitialCards to count the number of eights in the players hand.
   *
   * @return an int for the count of eights in the player's hand.
   */
  private int countEights() {
    int count = 0;
    for (Card c : cardsInHand) {
      if (c.getRank().equals(Card.Rank.EIGHT)) {
        count++;
      }
    }
    return count;
  }

  @Override
  public boolean shouldDrawCard(Card topPileCard, Card.Suit changedSuit) {
    //look through cards in hand
    int random = (int) (Math.random() * 2);
    if (random == 1) { // pick up a card
      return true;
    } else {
      for (Card c : cardsInHand) {
        if (changedSuit == null) {
          if (c.getSuit().equals(topPileCard.getSuit())) { //matches top card
            cardToPlay = c;
            return false;
          }
          if (c.getRank().equals(topPileCard.getRank())) {
            cardToPlay = c;
            return false;
          }
        } else {
          if (c.getSuit().equals(changedSuit)) {
            cardToPlay = c;
            return false;
          }
        }
      }
    }
    return true;
  }

  @Override
  public void receiveCard(Card drawnCard) {
    cardsInHand.add(drawnCard);
    if (drawnCard.getRank() == Card.Rank.EIGHT) {
      eightCount++;
    }
  }

  @Override
  public Card playCard() {
    cardsInHand.remove(cardToPlay);
    return cardToPlay;
  }

  @Override
  public Card.Suit declareSuit() {
    return cardToPlay.getSuit();
  }

  @Override
  public void processOpponentActions(List<PlayerTurn> opponentActions) {
  }

  @Override
  public void reset() {
    myOpponentsIDs = null;
    cardsInHand.clear();
    eightCount = 0;
    cardToPlay = null;
  }

  public String toString() {
    return "Player " + myId;
  }
}
