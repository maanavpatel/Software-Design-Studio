package student.crazyeights;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Random;
import java.util.Stack;

/**
 * Capable of orchestrating a game or tournament between four PlayerStrategy objects.
 * The game follows rules outlined by
 * this spec: https://courses.grainger.illinois.edu/cs126/sp2020/assignments/crazy-eights/
 * This class has many different outputs to the console to update the user on
 * the progress of the game.
 */
public class CrazyEightsGameEngine {
  private Stack<Card> deck;
  private List<PlayerStrategy> playerStrategies;
  private HashMap<PlayerStrategy, Integer> playerToID;
  private HashMap<PlayerStrategy, Integer> playerToScore;
  private PlayerTurn[] playerActions;
  private PlayerHands allPlayersCards;
  private int highestScore;
  private boolean cheaterDetected;
  private int roundNumber;
  private Card.Suit declaredSuit;
  private PlayerStrategy gameWinner;
  private final int TOURNEY_MINIMUM = 200;
  private PlayerStrategy tournamentWinner;
  private boolean thereIsATie;
  private Random shuffleRandomizer;

  /**
   * This is mainly for testing. If used the deck will be shuffled the same way each time.
   * This means this should not be used if wanting to play multiple games (e.g. a tournament).
   *
   * @param random a Random object to use when shuffling deck.
   */
  void setShuffleRandomizer(final Random random) {
    shuffleRandomizer = random;
  }

  void setDeck() {
    deck = fillDeckStackFromList(Card.getDeck());
    if (shuffleRandomizer == null) {
      Collections.shuffle(deck);
    } else {
      Collections.shuffle(deck, shuffleRandomizer);
    }
  }

  /**
   * @return a Stack of Cards that is a copy of the game deck
   */
  Stack<Card> getCopyOfDeck() {
    Stack<Card> copy = new Stack<>();
    copy.addAll(deck);
    return deck;
  }

  /**
   * Constructor for the CrazyEightsGameEngine.
   * @param a first PlayerStrategy.
   * @param b second PlayerStrategy.
   * @param c third PlayerStrategy.
   * @param d fourth PlayerStrategy.
   */
  public CrazyEightsGameEngine(PlayerStrategy a, PlayerStrategy b,
                               PlayerStrategy c, PlayerStrategy d) {
    cheaterDetected = false;
    //initialize all data structures
    playerStrategies = new LinkedList<>();
    playerToID = new HashMap<>();
    playerToScore = new HashMap<>();
    fillPlayersList(a, b, c, d);
    initializePlayers(playerStrategies);
    highestScore = 0;
    gameWinner = null;
    thereIsATie = false;
  }

  private void newGame() {
    allPlayersCards = new PlayerHands(playerStrategies);
    playerActions = new PlayerTurn[playerStrategies.size()];
    setDeck();
    roundNumber = 0;
    gameWinner = null;
  }

  public PlayerStrategy playTournament() {
    PlayerStrategy winner = null;
    while (tournamentWinner == null) {
      winner = playGame();
      if (cheaterDetected) {
        return null;
      }
      resetPlayers();
      setDeck();
    }
    return winner;
  }

  public PlayerStrategy playGame() {
    newGame();
    System.out.println(getScoreString());
    printHorizontalLine();
    System.out.println("NEW GAME OF CRAZY 8's");
    printHorizontalLine();
    //hand out cards
    dealCards();
    // make two piles, discard and regular
    Stack<Card> drawPile = deck;
    Stack<Card> discardPile = new Stack<>();
    //flip the top card over, place on discard pile
    discardPile.push(drawPile.pop());
    boolean shouldKeepPlaying = true;
    while (shouldKeepPlaying) { //play rounds until cards run out from deck or a player hand
      shouldKeepPlaying = playRound(drawPile, discardPile);
      if (cheaterDetected) { //stop the game if there is a cheater
        return null;
      }
      roundNumber++;
    }
    calculateScores(); //calculate score at end of each game
    System.out.println(getScoreString());
    System.out.println();
    return getHighestScorer(); //return the player with the highest score
  }

  private void printHorizontalLine() {
    for (int i = 0; i < 40; i++) {
      System.out.print("==");
    }
    System.out.println();
  }

  private void fillPlayersList(final PlayerStrategy p1, final PlayerStrategy p2,
                               final PlayerStrategy p3, final PlayerStrategy p4) {
    playerStrategies.add(p1);
    playerStrategies.add(p2);
    playerStrategies.add(p3);
    playerStrategies.add(p4);
    return;
  }

  /**
   * Calls the init method for all the PlayerStrategy instances for this game.
   *
   * @param playerStrategyList
   */
  private void initializePlayers(final List<PlayerStrategy> playerStrategyList) {
    int playerId = 0;
    //go through each player
    for (PlayerStrategy playerStrat : playerStrategyList) {
      playerToID.put(playerStrat, playerId);
      //make a list of ints that does not include the number of the player's id
      List<Integer> opponentIds = new ArrayList<>();
      for (int i = 0; i < playerStrategyList.size(); i++) {
        if (i != playerId) {
          opponentIds.add(i);
        }
      }
      //initializes player with IDs
      playerStrat.init(playerId, opponentIds);
      //make a new list of actions for each player
      playerId++;
    }
  }

  /**
   * @param deckList will make a Stack of Card objects using a List containing Card objects.
   * @return a Stack of Cards representing a deck of cards.
   */
  private Stack<Card> fillDeckStackFromList(final List<Card> deckList) {
    Stack<Card> deckStack = new Stack<>();
    deckStack.addAll(deckList);
    return deckStack;
  }

  /**
   * Deals cards to each player 5 at a time and also calculates and sets the players score based off
   * the initial hand.
   */
  private void dealCards() {
    for (PlayerStrategy playerStrat : playerStrategies) {
      PlayerTurn turn = new PlayerTurn();
      List<Card> initialHand = new LinkedList<>();
      //get their current score: will be 0 if first game
      //give out five cards per player
      for (int i = 0; i < 5; i++) {
        //removes the top card of the deck and gives it to the player.
        initialHand.add(deck.pop());
      }
      allPlayersCards.initializePlayerHand(playerStrat, initialHand);
      playerStrat.receiveInitialCards(initialHand);
    }
  }

  /**
   * Given a PlayerStrategy this method will make a list of PlayerTurn objects that contain
   * the most recent actions of all other players.
   *
   * @param playerStrategy the PlayerStrategy for whom opponent Actions want to be retrieved.
   * @return a LinkedList of PlayerTurns that contain the most recent actions of all opponents.
   */
  public List<PlayerTurn> getOpponentActions(final PlayerStrategy playerStrategy) {
    List<PlayerTurn> opponentActions = new LinkedList<>();
    for (PlayerTurn turn : playerActions) {
      if (turn == null) {
        opponentActions.add(turn);
      } else if (turn.playerId != playerToID.get(playerStrategy)) {
        opponentActions.add(turn);
      }
    }
    return opponentActions;
  }

  /**
   * Calculates each PlayerStrategy's score. Updates scoreToPlayer which maps each score
   * to a PlayerStrategy. Also updates the value of the highestScore.
   */
  private void calculateScores() {
    int high = 0; //find the highest score
    System.out.println("CALCULATING SCORES...");
    //calculating score for round
    for (PlayerStrategy player : playerStrategies) {
      int gameScoreForPlayer = 0;
      //look through all players
      for (PlayerStrategy otherPlayer : playerStrategies) {
        //when there is a tie player gets sum of opponent cards
        if (thereIsATie) {
          if (!otherPlayer.equals(player)) {
            gameScoreForPlayer += allPlayersCards.getHandValue(otherPlayer);
          }
        } else if (gameWinner != null) { //there is a winner
          if (playerToID.get(gameWinner) == playerToID.get(player)) { //if 'player' is the winner
            if (playerToID.get(player) != playerToID.get(otherPlayer)) {
              //'player' is not 'other player'
              //summation of opponent scores
              gameScoreForPlayer += allPlayersCards.getHandValue(otherPlayer);
            }
          }
        }
      }// done with summation
      int totalScore = gameScoreForPlayer;
      if (playerToScore.size() == playerStrategies.size()) {
        int currentScoreForPlayer = playerToScore.get(player);
        totalScore = totalScore + currentScoreForPlayer;
        playerToScore.put(player, totalScore);
      } else if (playerToScore.size() < playerStrategies.size()) {
        playerToScore.put(player, gameScoreForPlayer);
      }
      high = Math.max(high, totalScore);
    }

    highestScore = Math.max(high, highestScore);
    System.out.println("Highest is: " + highestScore);
  }

  /**
   * Looks through the HashMap containing all players and scores to find the PlayerStrategy that
   * has the highest score so far.
   *
   * @return the PlayerStrategy that has the highest score
   */
  private PlayerStrategy getHighestScorer() {
    List<PlayerStrategy> potentialWinners = new LinkedList<>();
    PlayerStrategy highestScorer;
    for (PlayerStrategy playerStrategy : playerStrategies) {
      if (playerToScore.get(playerStrategy) == highestScore) {
        potentialWinners.add(playerStrategy);
      }
    }
    if (potentialWinners.size() > 1) {
      System.out.println("There is a tie between "
          + potentialWinners);
      System.out.println(getScoreString());
    }
    highestScorer = potentialWinners.get(0);
    if (playerToScore.get(highestScorer) >= TOURNEY_MINIMUM) {
      tournamentWinner = highestScorer;
    }
    return potentialWinners.get(0);
  }

  /**
   * Used to print the scores of all players in a neatly formatted manner.
   *
   * @return a formatted String that can be used to print scores for all players
   */
  public String getScoreString() {
    StringBuilder scores = new StringBuilder();
    scores.append(ConsoleColors.PURPLE + "\n");
    for (PlayerStrategy playerStrategy : playerStrategies) {
      scores.append(playerStrategy + " score: " + playerToScore.get(playerStrategy) + "\n");
    }
    scores.append(ConsoleColors.RESET + "\n");
    return scores.toString();
  }

  /**
   * Will play a round of Crazy 8's where each PlayerStrategy will take one turn.
   *
   * @param drawPile    the Stack of Cards representing the draw pile.
   * @param discardPile the Stack of Cards representing the draw pile.
   * @return a boolean representing if another round can be played
   */
  private boolean playRound(Stack<Card> drawPile, Stack<Card> discardPile) {
    if (roundNumber % 2 == 0) {
      System.out.println(ConsoleColors.CYAN);
    } else {
      System.out.println(ConsoleColors.YELLOW);
    }

    for (PlayerStrategy player : playerStrategies) {
      PlayerTurn turnInfo = new PlayerTurn();
      //turn information
      turnInfo.playerId = playerToID.get(player);
      //look at top card from discard
      Card topCard = discardPile.peek();

      //Print out info
      System.out.println("\nTop card: " + topCard.getRank() + "\tof\t" + topCard.getSuit());
      System.out.println("Player " + playerToID.get(player) + "'s hand:"
          + allPlayersCards.getHandAsString(player));

      //tell player strategy about oppnent actions
      player.processOpponentActions(getOpponentActions(player));

      //player needs to draw a card
      if (player.shouldDrawCard(topCard, declaredSuit)) {
        turnInfo.drewACard = drawCard(player, drawPile);
        if (!turnInfo.drewACard) {
          return false; //if player was not able to draw card then no cards left so end the round
        }
      } else { //player needs to play a card
        Card toPlay = player.playCard();
        //check for cheating
        if (isCheating(player, toPlay, drawPile, discardPile) || !isValidCard(toPlay, topCard)) {
          cheaterDetected = true;
          System.out.println("CHEATER HAS BEEN DETECTED!");
          System.out.println("Player " + playerToID.get(player)
              + " is cheating! They tried to play " + toPlay.getRank() + "\t" + toPlay.getSuit());
          return false;
        }
        declaredSuit = playCard(player, toPlay, discardPile);
        turnInfo.declaredSuit = declaredSuit; //will change values only when someone plays a card
        turnInfo.playedCard = discardPile.peek();
      }

      if (allPlayersCards.getHand(player).size() == 0) {
        //if a player runs out of cards, we cannot play another round;
        System.out.println(player + " ran out of cards.");
        gameWinner = player;
        System.out.println(allPlayersCards.getHandAsString(player));
        return false;
      }
      //update the player's most recent move
      playerActions[playerToID.get(player)] = turnInfo;
    }
    return true;
  }

  /**
   * Checks if a played Card follows the rules.
   *
   * @param playerCard the Card the player tried to play
   * @param topCard    the Card at the top of the discard pile
   * @return a boolean that shows if the card can be played without breaking rules.
   */
  private boolean isValidCard(final Card playerCard, final Card topCard) {
    if (playerCard.getRank().equals(Card.Rank.EIGHT)) {
      return true;
    } else if (topCard.getRank() == playerCard.getRank()
        || topCard.getSuit() == playerCard.getSuit() || playerCard.getSuit().equals(declaredSuit)) {
      return true;
    }
    return false;
  }


  /**
   * Tries to give a card from the top of the draw pile to the PlayerStrategy who needs it.
   *
   * @param playerStrategy the PlayerStrategy that wants to draw a Card.
   * @param drawPile       the Stack of Cards representing the draw pile.
   * @return a boolean representing if the PlayerStrategy was successfully given a card.
   */
  private boolean drawCard(final PlayerStrategy playerStrategy, Stack<Card> drawPile) {
    if (drawPile.empty()) { //no cards left in drawPile
      System.out.println("Draw pile ran out of Cards.");
      thereIsATie = true;
      return false;
    } else {
      //add top card from drawpile to the player's hand
      allPlayersCards.addCard(playerStrategy, drawPile.peek());
      //give the top from draw pile to the player
      playerStrategy.receiveCard(drawPile.pop());
      System.out.println("Player " + playerToID.get(playerStrategy) + " drew a card.");
      return true;
    }
  }

  /**
   * Places the card that PlayerStrategy wants to play on top of the discard pile.
   *
   * @param playerStrategy the PlayerStrategy wanting to play a card.
   * @param toPlay         the Card that the PlayerStrategy wants to play.
   * @param discardPile    the discard pile that the card being played will be placed onto.
   * @return a Card.Suit representing the declared suit if an 8 is played (will be null otherwise).
   */
  private Card.Suit playCard(final PlayerStrategy playerStrategy, final Card toPlay,
                             final Stack<Card> discardPile) {
    allPlayersCards.removeCard(playerStrategy, toPlay);
    discardPile.push(toPlay);
    System.out.println("Player " + playerToID.get(playerStrategy) + " played the " +
        toPlay.getRank() + " of " + toPlay.getSuit());
    //if player played an 8 ask for suit
    if (discardPile.peek().getRank().equals(Card.Rank.EIGHT)) {
      Card.Suit declaredSuit = playerStrategy.declareSuit();
      System.out.println("Player " + playerToID.get(playerStrategy) + " declares " +
          declaredSuit + " as suit.");
      return declaredSuit;
    }
    return null;
  }

  /**
   * This method checks to make sure that the Card that was played is not in anyone else's hand
   * and that it is not in the draw or discard pile.
   *
   * @param suspect     the PlayerStrategy that needs to be checked for cheating.
   * @param toPlay      the Card the PlayerStrategy tried to play.
   * @param drawPile    the Stack of Cards representing the draw pile.
   * @param discardPile the Stack of Cards representing the discard pile.
   * @return a boolean representing if the the player is cheating (Will be false if innocent).
   */
  private boolean isCheating(final PlayerStrategy suspect, final Card toPlay,
                             final Stack<Card> drawPile, final Stack<Card> discardPile) {
    //make sure the player had the card in their hand and just now put it in the discard pile
    if (!allPlayersCards.getHand(suspect).contains(toPlay) || drawPile.contains(toPlay)) {
      System.out.println("CHEATER: Played a card that is in the draw pile");
      return true;
    }
    //check all other player hands to make sure they don't have the same card
    for (PlayerStrategy playerStrategy : playerStrategies) {
      if (!playerStrategy.equals(suspect)) {
        List<Card> playerHand = allPlayersCards.getHand(playerStrategy);
        if (playerHand.contains(toPlay)) {
          System.out.println("CHEATER: Played a card in someone else's hand");
          return true;
        }
      }
    }
    return false;
  }

  /**
   * Calls the reset() function of all PlayerStrategies before each new game is played.
   */
  private void resetPlayers() {
    for (PlayerStrategy player : playerStrategies) {
      player.reset();
    }
  }

}
