package student;

import com.fasterxml.jackson.databind.ObjectMapper;
import java.io.File;
import java.io.IOException;
import java.util.Scanner;
import student.adventure.Adventure;
import student.adventure.Layout;
import student.gameplay.AdventureGameInOut;


public class Main extends AdventureGameInOut {
  private static File defaultFile = new File("src/main/resources/siebel.json");
  private static File file;
  private static Scanner scanner = new Scanner(System.in);

  /** Main method that starts the game.
   * @param args
   */
  public static void main(String[] args) {
    //default file is siebel.json
    file = defaultFile;
    //user input for file
    Layout gameLayout = AdventureGameInOut.pickFile();
    //If the player gives a bad JSON then they will be redirected to the default game.
    try {
      Adventure adventure = new Adventure(gameLayout);
      AdventureGameInOut.goOnAdventure(adventure);
    } catch (Exception e) {
      System.out.println("Sorry that game won't work. Let's just explore Siebel!\n");
      playDefault();
    }
  }

  /**
   * In case the given file is not a compatible JSON this will be used.
   */
  private static void playDefault() {
    try {
      Layout defaultGameLayout = new ObjectMapper().readValue(defaultFile, Layout.class);
      Adventure defaultAdventure = new Adventure(defaultGameLayout);
      AdventureGameInOut.goOnAdventure(defaultAdventure);
    } catch (Exception e) {
      System.out.println("Something went wrong!");
    }
  }
}