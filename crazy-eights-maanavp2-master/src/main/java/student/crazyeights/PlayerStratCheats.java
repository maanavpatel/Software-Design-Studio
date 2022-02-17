package student.crazyeights;

import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;

/**
 * The overall strategy for this PlayerStrategy implementation is to cheat by playing the top card.
 */
public class PlayerStratCheats implements PlayerStrategy {
  private List<Integer> myOpponentsIDs;
  private int myId;
  private List<Card> cardsInHand;
  private Card cardToPlay;

  public PlayerStratCheats() {}

  @Override
  public void init(int playerId, List<Integer> opponentIds) {
    myId = playerId;
    cardsInHand = new LinkedList<>();
    myOpponentsIDs = new LinkedList<>();
    myOpponentsIDs = opponentIds;
  }

  @Override
  public void receiveInitialCards(List<Card> cards) {
    cardsInHand.addAll(cards);
  }

  @Override
  public boolean shouldDrawCard(Card topPileCard, Card.Suit changedSuit) {
    cardToPlay = topPileCard;
    return false;
  }

  @Override
  public void receiveCard(Card drawnCard) {
    cardsInHand.add(drawnCard);
  }

  @Override
  public Card playCard() {
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
    cardToPlay = null;
  }

  public String toString() {
    return "Player " + myId;
  }
}
