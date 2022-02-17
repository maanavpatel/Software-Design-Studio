package student.adventure;

import static org.junit.Assert.assertEquals;


import com.fasterxml.jackson.databind.ObjectMapper;
import java.io.File;
import java.util.List;
import org.junit.Before;
import org.junit.Test;


public class AdventureTest {
  private Adventure a;

  @Before
  public void setUp() {
    Layout l = null;
    try {
      File f = new File("src/main/resources/siebel.json");
      l = new ObjectMapper().readValue(f, Layout.class);
    } catch (Exception e) {
      System.out.println("Bad filepath or file type");
    }
    a = new Adventure(l);
  }

  @Test
  public void correctNumberOfRooms() {
    List<Room> rooms = a.getRooms();
    assertEquals(8, rooms.size());
  }

  @Test
  public void correctData() {
    //Matthew street, directions available: East
    assertEquals("East", a.getRooms().get(0).getDirections().get(0).getDirectionName());
    //ACMOffice, directions available: South: Room: SiebelEntry
    assertEquals("SiebelEntry", a.getRooms().get(2).getDirections().get(0).getRoom());
    //SiebelNorthHallway, directions available: NorthEast
    assertEquals("NorthEast", a.getRooms().get(3).getDirections().get(1).getDirectionName());
  }

  @Test
  public void goEastFromMatthew() {
    String result = a.goDirection("eAst");
    assertEquals("", result);
  }

  @Test
  public void goBlastFromMatthew() {
    String result = a.goDirection("BlAst");
    assertEquals("I can't go BlAst!", result);
  }
//
//  @Test
//  public void possibleDirectionsMatthew() {
//    String result = a.getPossibleDirectionNames();
//    assertEquals("East", result);
//  }
//
//  @Test
//  public void possibleDirectionsSiebelEastHallway() {
//    //go to siebel entry
//    a.goDirection("east");
//    //go to siebel East entry
//    a.goDirection("eaST");
//    String result = a.getPossibleDirectionNames();
//    assertEquals("West, South, or Down", result);
//  }
}