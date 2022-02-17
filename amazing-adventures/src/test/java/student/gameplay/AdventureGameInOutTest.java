package student.gameplay;

import static org.junit.Assert.assertEquals;

import com.fasterxml.jackson.databind.ObjectMapper;
import java.io.File;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;
import student.adventure.Adventure;
import student.adventure.Layout;

/**
 * Tests the AdventureGameInOutTest class.
 */
public class AdventureGameInOutTest {
  private Adventure adventure;

  /**
   * Creates a new instance of Adventure using the siebel.json layout.
   */
  @Before
  public void setUp() {
    Layout l = null;
    try {
      File f = new File("src/main/resources/siebel.json");
      l = new ObjectMapper().readValue(f, Layout.class);
    } catch (Exception e) {
      System.out.println("Bad filepath or file type");
    }
    adventure = new Adventure(l);
  }
  //TODO Figure out a good way to test these without revealing what is happening (without public)

  /* In order to run these tests you will have to uncomment the outputMessageBuilderTest method
    in the AdventureGameInOut class
   */

  /*
  @Test
  public void blank() {
    Assert.assertEquals("I don't understand ''",
        AdventureGameInOut.outputMessageBuilderTest(adventure, ""));
  }

  @Test
  public void goBlank() {
    assertEquals("I don't understand 'go'", A
        dventureGameIO.outputMessageBuilderTest(adventure, "go"));
  }
  @Test
  public void spaces() {
    assertEquals("I don't understand '   '",
        AdventureGameInOut.outputMessageBuilderTest(adventure, "   "));
  }

  @Test
  public void random() {
    assertEquals("I don't understand 'jf aDkl'",
        AdventureGameInOut.outputMessageBuilderTest(adventure, "jf aDkl"));
  }

  @Test
  public void exit() {
    assertEquals("Good bye!", AdventureGameInOut.outputMessageBuilderTest(adventure, "exit"));
    assertEquals("Good bye!", AdventureGameInOut.outputMessageBuilderTest(adventure, "quit"));

  }

  @Test
  public void goDirectionRandom() {
    assertEquals("I can't go abc DEF g!",
        AdventureGameInOut.outputMessageBuilder(adventure, "go abc DEF g"));
    assertEquals("I can't go KEIE!",
        AdventureGameInOut.outputMessageBuilder(adventure, "go KEIE"));
  }

  @Test
  public void finishSiebelGame() {
    AdventureGameInOut.outputMessageBuilderTest(adventure, "go east");
    AdventureGameInOut.outputMessageBuilderTest(adventure, "go east");
    AdventureGameInOut.outputMessageBuilderTest(adventure, "go south");
    assertEquals("Siebel1314", adventure.getCurrentRoom().getName());
  }

  @Test
  public void siebelGame() {
    AdventureGameInOut.outputMessageBuilderTest(adventure, "go EAST");
    AdventureGameInOut.outputMessageBuilderTest(adventure, "go NOrtheAsT");
    AdventureGameInOut.outputMessageBuilderTest(adventure, "go soUTh");
    assertEquals("SiebelEntry", adventure.getCurrentRoom().getName());
  }
  */

}