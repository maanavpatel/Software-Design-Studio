package student.crazyeights;

import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;

/**
 * The overall strategy for this PlayerStrategy implementation is to hold all 8's until the end.
 */
public class PlayerStratHold8s implements PlayerStrategy {
  private List<Integer> myOpponentsIDs;
  private int myId;
  private List<Card> cardsInHand;
  private Card cardToPlay;
  private int eightCount;

  public PlayerStratHold8s() {
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
    System.out.println("declared suit: " + changedSuit );
    System.out.println("eight count: " + eightCount );

    for (Card c : cardsInHand) {
      //there there are only eights in the player's hand
      if (eightCount == cardsInHand.size()) {
        cardToPlay = c;
        eightCount--;
        return false;
      } else { //when there is something other than an eight
        if (changedSuit == null) {
          //ideal case: check if card is not eight and the suit or rank is the same as top card
          if (!c.getRank().equals(Card.Rank.EIGHT)) {
            if (c.getSuit().equals(topPileCard.getSuit())
                || c.getRank().equals(topPileCard.getRank())) {
              cardToPlay = c;
              return false;
            }
          }
        } else {
          //suit was declared so check for a non-8 card that can be played
          if (c.getSuit().equals(changedSuit) && !c.getRank().equals(Card.Rank.EIGHT)) {
            cardToPlay = c;
            return false;
          }
        }
        //if cannot play anything else and eights are left play an eight
        if (eightCount != 0 && c.getRank().equals(Card.Rank.EIGHT)) {
          eightCount--;
          cardToPlay = c;
          return false;
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
