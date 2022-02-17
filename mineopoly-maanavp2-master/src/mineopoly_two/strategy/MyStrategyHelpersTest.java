package mineopoly_two.strategy;

import static org.junit.Assert.*;


import java.awt.Point;
import java.util.ArrayList;
import java.util.List;
import mineopoly_two.action.TurnAction;
import mineopoly_two.tiles.TileType;
import org.junit.Before;
import org.junit.Test;

/**
 * These tests will test some of the helper functions that are used by MyStrategy.
 */
public class MyStrategyHelpersTest {
  private MyStrategy myStrategy;
  private List<Point> locations;
  private Point a ;
  private Point b;
  private Point c ;
  private Point d;
  private Point e ;

  @Before
  public void setup(){
    myStrategy = new MyStrategy();
    locations = new ArrayList<>();
    a = new Point(10,10);
    b = new Point(-3,5);
    c = new Point(17,4);
    d = new Point(1,20);
    e = new Point(30,30);
    locations.add(a);
    locations.add(b);
    locations.add(c);
    locations.add(d);
    locations.add(e);
  }

  @Test
  public void findNearestSameLocation(){
    //same location as location to find
    assertEquals(e, myStrategy.findNearestPointFromList(locations, e));
    assertEquals(a, myStrategy.findNearestPointFromList(locations, a));
  }

  @Test
  public void findNearestSimple(){
    assertEquals(d, myStrategy.findNearestPointFromList(locations, new Point(2, 14)));
    assertEquals(a, myStrategy.findNearestPointFromList(locations, new Point(20, 20)));
    assertEquals(c, myStrategy.findNearestPointFromList(locations, new Point(14, 3)));
    //very far but still find closest
    assertEquals(b, myStrategy.findNearestPointFromList(locations, new Point(-100, -33)));
    //equidistant from a and e, a was added first
    assertEquals(a, myStrategy.findNearestPointFromList(locations, new Point(20, 20)));
    //null checks
    assertEquals(null, myStrategy.findNearestPointFromList(null , new Point(20, 20)));
    assertEquals(null, myStrategy.findNearestPointFromList(locations , null));
    assertEquals(null, myStrategy.findNearestPointFromList(null , null));
  }

  @Test
  public void findNearestFarPoint() {
    //very far but still find closest
    assertEquals(b, myStrategy.findNearestPointFromList(locations, new Point(-100, -33)));
  }

  @Test
  public void findNearestEquidistant(){
    //equidistant from a and e, a was added first
    assertEquals(a, myStrategy.findNearestPointFromList(locations, new Point(20, 20)));
  }

  @Test
  public void findNearestNull(){
    //null checks
    assertEquals(null, myStrategy.findNearestPointFromList(null , new Point(20, 20)));
    assertEquals(null, myStrategy.findNearestPointFromList(locations , null));
    assertEquals(null, myStrategy.findNearestPointFromList(null , null));
  }

  @Test
  public void moveUp(){
    Point destination = new Point(20 , 20);
    TurnAction up = TurnAction.MOVE_UP;
    //since moveTowards prioritizes horizontal movement x values have to be the same
    assertEquals(up, myStrategy.moveTowards(destination, new Point ( 20, 0)));
    assertEquals(up, myStrategy.moveTowards(destination, new Point ( 20, -20)));
    assertEquals(up, myStrategy.moveTowards(destination, new Point ( 20, 19)));
    assertEquals(up, myStrategy.moveTowards(destination, new Point ( 20, -3)));
  }

  @Test
  public void moveDown(){
    Point destination = new Point(0 , 0);
    TurnAction down = TurnAction.MOVE_DOWN;
    assertEquals(down, myStrategy.moveTowards(destination, new Point ( 0, 20)));
    assertEquals(down, myStrategy.moveTowards(destination, new Point ( 0, 32)));
    assertEquals(down, myStrategy.moveTowards(destination, new Point ( 0, 12)));
    assertEquals(down, myStrategy.moveTowards(destination, new Point ( 0, 1)));
  }

  @Test
  public void moveTowardsNull(){
    Point destination = null;
    TurnAction down = TurnAction.MOVE_DOWN;
    assertEquals(null, myStrategy.moveTowards(null, new Point ( 0, 20)));
    assertEquals(null, myStrategy.moveTowards(destination,null));
    assertEquals(null, myStrategy.moveTowards(destination, null));
  }

  @Test
  public void moveLeft(){
    Point destination = new Point(-10 , 10);
    TurnAction left = TurnAction.MOVE_LEFT;
    //very far right and further up
    assertEquals(left, myStrategy.moveTowards(destination, new Point ( 200, 20)));
    //same y values
    assertEquals(left, myStrategy.moveTowards(destination, new Point ( 12, 10)));
    //other simple
    assertEquals(left, myStrategy.moveTowards(destination, new Point ( -2, 5)));
    assertEquals(left, myStrategy.moveTowards(destination, new Point ( 20, -3)));
  }

  @Test
  public void moveRight(){
    Point destination = new Point(32 , 32);
    TurnAction right = TurnAction.MOVE_RIGHT;
    //very far left
    assertEquals(right, myStrategy.moveTowards(destination, new Point ( -123, 20)));
    //same y values
    assertEquals(right, myStrategy.moveTowards(destination, new Point ( 31, 32)));
    //other simple
    assertEquals(right, myStrategy.moveTowards(destination, new Point ( -2, 12)));
    assertEquals(right, myStrategy.moveTowards(destination, new Point ( 20, -3)));
  }

  @Test
  public void shouldMineTrue(){
    assertTrue(myStrategy.shouldMine(TileType.RESOURCE_DIAMOND));
    assertTrue(myStrategy.shouldMine(TileType.RESOURCE_EMERALD));
    assertTrue(myStrategy.shouldMine(TileType.RESOURCE_RUBY));
  }

  @Test
  public void shouldMineFalse(){
    assertFalse(myStrategy.shouldMine(TileType.EMPTY));
    assertFalse(myStrategy.shouldMine(TileType.RECHARGE));
    assertFalse(myStrategy.shouldMine(TileType.RED_MARKET));
    assertFalse(myStrategy.shouldMine(TileType.BLUE_MARKET));
  }

  @Test
  public void shouldMineNull(){
    assertFalse(myStrategy.shouldMine(null));
  }





}