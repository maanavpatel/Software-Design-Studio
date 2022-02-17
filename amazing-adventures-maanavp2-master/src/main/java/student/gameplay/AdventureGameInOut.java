package student.gameplay;

import com.fasterxml.jackson.databind.ObjectMapper;
import java.io.File;
import java.util.Scanner;
import student.adventure.Adventure;
import student.adventure.Layout;

/**
 * Handles all the Input and Output done when playing Amazing Adventures.
 */
public class AdventureGameInOut {
  private static File defaultFile = new File("src/main/resources/siebel.json");
  private static Scanner scanner = new Scanner(System.in);
  private static final String EXIT_MESSAGE = "Good bye!";
  private static final String FILE_PICKER_MESSAGE = "If you would like to play the "
      + "default version type 'd' or press ENTER. Otherwise, enter the path to the game file.";

  /**
   * Starts the 'game' by starting a loop of input requests and output messages. All output
   * will be seen in the console (System.out)
   * @param adv an Adventure object for the Adventure game wanting to be played.
   */
  protected static void goOnAdventure(final Adventure adv) {
    boolean playGame = true;
    boolean firstRound = true;

    // This loop stops when the user wants to quit or they reach the final room.
    while (playGame) {
      //describe current room and directions
      System.out.println(adv.getDescription());
      //print this statement when game starts
      if (firstRound) {
        System.out.println("This is where your journey begins!");
        firstRound = false;
      }
      System.out.println("From here you can go: " + getPossibleDirectionNames(adv));

      //take input from user and print output message
      System.out.print("> ");
      String input = scanner.nextLine();
      String output = outputMessageBuilder(adv, input);
      System.out.println(output);

      //check if game has ended: final room reached
      playGame = !adv.getCurrentRoom().getName().equals(adv.getEndingRoom());
      if (!playGame) {
        System.out.println("Congrats you made it to the ending room: "
            + adv.getCurrentRoom().getName() + EXIT_MESSAGE);
      }
      //To exit or quit the game
      if (output.equals(EXIT_MESSAGE)) {
        playGame = false;
      }
    }
  }

  /* Only use when need to test input output functionality
  public static String outputMessageBuilderTest(final Adventure adv, final String testInput) {
    return outputMessageBuilder(adv, testInput);
  }
 */

  /**
   * Will read user input and call necessary function to play game.
   * @param input a String that represents the user's input.
   * @return a String that is the output message.
   */
  private static String outputMessageBuilder(final Adventure adv, final String input) {
    //splits the input strings at a space to make a String array of words
    String[] inputWords = input.split(" ");
    if (inputWords.length != 0) {
      //if there is more than one word and the first word is go, call the goInputHandler()
      if (inputWords.length > 1 && inputWords[0].toLowerCase().equals("go")) {
        return goInputHandler(adv, input);
      }
      //if there is one word matching the two exit key words, out put will be
      if (inputWords.length == 1 && inputWords[0].toLowerCase().equals("exit")
          || inputWords[0].toLowerCase().equals("quit")) {
        return EXIT_MESSAGE;
      }
    }
    return "I don't understand '" + input + "'";
  }

  /**
   * Makes a nice list of all directions as a String to use in output.
   * @return a comma separated list of directions that can be visited from currentRoom as a String.
   */
  private static String getPossibleDirectionNames(final Adventure adv) {
    String directionNames = "";
    //make sure there's more than one direction
    if (adv.getCurrentRoom().getDirections().size() != 1) {
      //put commas in between each direction
      for (int i = 0; i < adv.getCurrentRoom().getDirections().size(); i++) {
        String direction = adv.getCurrentRoom().getDirections().get(i).getDirectionName();
        // put an 'or' before the last direction
        if (i == adv.getCurrentRoom().getDirections().size() - 1) {
          directionNames += "or " + direction;
        } else {
          directionNames += direction + ", ";
        }
      }
    } else {
      //there is only one direction so just return that name
      directionNames = adv.getCurrentRoom().getDirections().get(0).getDirectionName();
    }
    return directionNames;
  }

  /**
   * Handles input strings that start with 'go '.
   * @param input a String that represents the user's input.
   * @return
   */
  private static String goInputHandler(final Adventure adv, final String input) {
    String[] words = input.split(" ");
    String output = "";
    //everything after the space after 'go' is sent to goDirection()
    String direction = input.split("go ")[1];
    return adv.goDirection(direction);
  }

  /**
   * Gives the user the choice to pick a game file or play the default game.
   * Will reprompt if given a bad file path or a non compatible JSON.
   * @return a Layout object that maps to the json given by the user.
   */
  protected static Layout pickFile() {
    String input;
    while (true) {
      System.out.println(FILE_PICKER_MESSAGE);
      input = scanner.nextLine();
      if (input.trim().equals("d") || input.equals("")) {
        //start adventure game with default.
        Layout l = null;
        try {
          l = new ObjectMapper().readValue(defaultFile, Layout.class);
          if (l != null) {
            return l;
          }
        } catch (Exception e) {
          System.out.println("Sorry, can't find default game.");
        }
      } else {
        File file = new File(input);
        if (file.canRead()) {
          Layout l = null;
          try {
            l = new ObjectMapper().readValue(file, Layout.class);
            return l;
          } catch (Exception e) {
            System.out.println("Sorry, path to file is invalid or "
                + "file is not the correct type. ");
          }
        } else {
          System.out.println("Cannot find file at: " + input);
        }
      }
    }
  }
}
