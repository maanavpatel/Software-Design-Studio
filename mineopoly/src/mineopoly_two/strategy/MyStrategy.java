package mineopoly_two.strategy;

import java.awt.Point;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Random;
import mineopoly_two.action.TurnAction;
import mineopoly_two.game.Economy;
import mineopoly_two.item.InventoryItem;
import mineopoly_two.tiles.TileType;

/**
 * This is a implementation of MinePlayerStrategy that plays the Mineopoly 2.0 game.
 * This strategy follows simple logic to play the game. It will try to mine the nearest
 * resource, pick up the nearest item and only recharge when it has a low charge.
 */
public class MyStrategy implements MinePlayerStrategy {
  private final String NAME = "MineSellChargeRepeat";
  private final double PERCENT_FOR_RECHARGE = .02;
  private int boardSize;
  private int maxInventorySize;
  private int maxCharge;
  private PlayerBoardView startingBoard;
  private Point myLocation;
  private boolean isRedPlayer;
  private int count;
  private List<Point> marketLocations;
  private List<Point> rechargeLocations;
  private List<InventoryItem> inventory;
  private boolean needToCharge;
  private List<Point> resourceLocations;

  @Override
  public void initialize(final int boardSize, final int maxInventorySize, final int maxCharge,
                         final int winningScore, final PlayerBoardView startingBoard,
                         final Point startTileLocation, final boolean isRedPlayer,
                         final Random random) {
    this.boardSize = boardSize;
    this.maxInventorySize = maxInventorySize;
    this.maxCharge = maxCharge;
    this.startingBoard = startingBoard;
    this.myLocation = startTileLocation;
    this.isRedPlayer = isRedPlayer;
    this.needToCharge = false;
    count = 0;
    initializeListAndMaps();
  }

  /**
   * Initializes all Lists or Maps used by this class.
   */
  private void initializeListAndMaps() {
    //this method is placed before public methods to easily see and understand initialization
    inventory = new LinkedList<>();
    marketLocations = new ArrayList<>();
    rechargeLocations = new ArrayList<>();
    resourceLocations = new LinkedList<>();
    fillListOfTilePositions(TileType.RESOURCE_DIAMOND, resourceLocations);
    fillListOfTilePositions(TileType.RESOURCE_RUBY, resourceLocations);
    fillListOfTilePositions(TileType.RESOURCE_EMERALD, resourceLocations);
    if (isRedPlayer) {
      fillListOfTilePositions(TileType.RED_MARKET, marketLocations);
    } else {
      fillListOfTilePositions(TileType.BLUE_MARKET, marketLocations);
    }
    fillListOfTilePositions(TileType.RECHARGE, rechargeLocations);
  }

  @Override
  public void onReceiveItem(final InventoryItem itemReceived) {
    inventory.add(itemReceived);
    resourceLocations.remove(myLocation);
  }

  @Override
  public void onSoldInventory(final int totalSellPrice) {
    inventory.clear();
  }

  @Override
  public String getName() {
    return NAME;
  }

  @Override
  public void endRound(final int pointsScored, final int opponentPointsScored) {
  }

  @Override
  public TurnAction getTurnAction(final PlayerBoardView boardView, final Economy economy,
                                  final int currentCharge, final boolean isRedTurn) {
    myLocation = boardView.getYourLocation();
    //If charge is low then need to charge
    if (currentCharge == maxCharge) { //fully charged
      needToCharge = false;
    } else if (currentCharge < (int) (PERCENT_FOR_RECHARGE * maxCharge)) {
      needToCharge = true;
    }
    if (needToCharge) {
      return recharge();
    }

    //check if items need to be sold (will only sell if inventory is full)
    TurnAction action = sellItems(myLocation);
    if (action == null) { // didn't need to sell so check if player can pick something up
      action = pickUpItem(myLocation, boardView);
    }

    //action will be PICKUP if not null
    if (action != null) {
      return action;
    }

    //no move made yet so check if current location should be mined
    if (shouldMine(boardView.getTileTypeAtLocation(myLocation))) {
      return TurnAction.MINE;
    }

    //if no other action taken, go to nearest resource tile
    if (action == null) {
      action = moveTowards(findNearestPointFromList(resourceLocations, myLocation), myLocation);
    }
    return action;
  }

  /**
   * This method will find the nearest point in the given list depending on your location.
   * If two points are the same distance apart the point that was added first will be returned.
   *
   * @param locations  the list of Points that contains all locations that want to be considered.
   * @param myLocation a Point to represent this MineStrategy's current location on the game board.
   * @return a Point in the list that is the least distance from the player's location.
   * Will return the first closest if two are equidistant.
   */
  Point findNearestPointFromList(final List<Point> locations, final Point myLocation) {
    //This method was made package private for testing purposes
    if (locations == null || myLocation == null) {
      return null;
    }
    Point closest = null;
    for (Point p : locations) {
      if (closest == null) {
        closest = p;
      }
      double dist = myLocation.distance(p);
      if (dist < myLocation.distance(closest)) {
        closest = p;
      }
    }
    return closest;
  }

  /**
   * This method is called any time the player wants to move in a direction. Can be called multiple
   * times to go to a destination. It will move in the x-direction first then the y-direction.
   *
   * @param destination a Point that represent's the location that the player wants to go to.
   * @param myLocation  a Point that represent's this MineStrategy's current
   *                    location on the game board.
   * @return a TurnAction that moves the player closer to the destination, or null if the
   * player is already at the destination.
   */
  TurnAction moveTowards(final Point destination, final Point myLocation) {
    //This method was made package private for testing purposes
    if (destination == null || myLocation == null) {
      return null;
    }
    // move x direction first
    if (myLocation.x > destination.x) {
      return TurnAction.MOVE_LEFT;
    } else if (myLocation.x < destination.x) {
      return TurnAction.MOVE_RIGHT;
    }
    // move y direction second
    if (myLocation.y > destination.y) {
      return TurnAction.MOVE_DOWN;
    } else if (myLocation.y < destination.y) {
      return TurnAction.MOVE_UP;
    }
    return null;
  }

  /**
   * Called to check if the player's current location is a mine-able resource tile.
   *
   * @param currentTileType the TileType at the current location.
   * @return a boolean that is true if the player should mine the tile.
   */
  boolean shouldMine(final TileType currentTileType) {
    //This method was made package private for testing purposes
    if (currentTileType == null) {
      return false;
    }
    return currentTileType.equals(TileType.RESOURCE_DIAMOND)
        || currentTileType.equals(TileType.RESOURCE_EMERALD)
        || currentTileType.equals(TileType.RESOURCE_RUBY);
  }

  /**
   * This method is called to fill a List of Points with all locations of a certain TileType.
   *
   * @param tileType the TileType that is wanting to be added.
   * @param tileLocationsList a list of Points that wants to be filled.
   */
  private void fillListOfTilePositions(final TileType tileType, final List<Point> tileLocationsList) {
    for (int i = 0; i < boardSize; i++) {
      for (int j = 0; j < boardSize; j++) {
        TileType type = startingBoard.getTileTypeAtLocation(i, j);
        if (type.equals(tileType)) {
          tileLocationsList.add(new Point(i, j));
        }
      }
    }
  }

  /**
   * Called when the Strategy would like to go and recharge. It will only return a TurnAction if
   * the player needs to charge and is not already at a recharge location.
   *
   * @return a TurnAction that moves the player in the direction of the nearest recharge tile.
   */
  private TurnAction recharge() {
    //find the distance to nearest recharge tile and nearest market
    double distToRecharge =
        myLocation.distance(findNearestPointFromList(rechargeLocations, myLocation));
    double distToMarket = myLocation.distance(findNearestPointFromList(marketLocations, myLocation));
    //inventory is full and the market is closer than recharge then go sell items first
    if (inventory.size() == maxInventorySize && distToMarket < distToRecharge) {
      return sellItems(myLocation);
    } else if (!rechargeLocations.contains(myLocation)) {
      //Note: nearestChargingTile could be an instance variable somehow,
      // but could not think of how to efficiently implement this

      Point nearestChargingTile = findNearestPointFromList(rechargeLocations, myLocation);
      return moveTowards(nearestChargingTile, myLocation);
    }

    //player is at the recharge tile and inventory check is complete so no move necessary
    return null;
  }

  /**
   * This method is called to attempt to sell a full inventory. It will return a TurnAction that
   * moves the player in the direction of the nearest market.
   *
   * @param myLocation a Point to represent this MineStrategy's current location on the game board.
   * @return a TurnAction to move in the direction of the nearest market.
   */
  private TurnAction sellItems(final Point myLocation) {
    //If inventory is full start to move towards a market
    if (inventory.size() == maxInventorySize && !marketLocations.contains(myLocation)) {
      Point nearestMarket = findNearestPointFromList(marketLocations, myLocation);
      return moveTowards(nearestMarket, myLocation);
    }
    //already at a market or inventory is not full
    return null;
  }

  /**
   * Called to pickUp an item at the current Location is at. It will only add it to the inventory
   * if it is not full.
   *
   * @param currLoc a Point that represent's this MineStrategy's current location on the game board.
   * @param boardView the PlayerBoardView that represents the current state of the board.
   * @return
   */
  private TurnAction pickUpItem(final Point currLoc, final PlayerBoardView boardView) {
    //If inventory is not full
    // and there is something at the tile this strategy's current location then pick it up
    if (inventory.size() < maxInventorySize && boardView.getItemsOnGround().get(currLoc) != null) {
      return TurnAction.PICK_UP;
    }
    return null;
  }

}
