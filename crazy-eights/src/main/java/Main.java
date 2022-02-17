
import student.crazyeights.ConsoleColors;
import student.crazyeights.CrazyEightsGameEngine;
import student.crazyeights.PlayerStratCheats;
import student.crazyeights.PlayerStratHold8s;
import student.crazyeights.PlayerStrategy;
import student.crazyeights.PlayerStrategyRandom;


public class Main {
  public static void main(String[] args) {
    //Make 4 instances of PlayerStrategy (each one is a player)
    PlayerStrategy a = new PlayerStratHold8s();
    PlayerStrategy b = new PlayerStratHold8s();
    PlayerStrategy c = new PlayerStratHold8s();
    PlayerStrategy d = new PlayerStratHold8s();
    CrazyEightsGameEngine game = new CrazyEightsGameEngine(a,b,c,d);
    PlayerStrategy winner = game.playTournament();
    if (winner == null) {
      System.out.println(ConsoleColors.RED);
      System.out.println("Nobody wins when someone cheats ");
    } else {
      System.out.println("Winner is: " + winner);
    }
  }
}