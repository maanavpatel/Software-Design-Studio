package student.adventure;

import java.util.HashMap;
import java.util.List;

public class Adventure {
  private Layout currentLayout;
  private Room currentRoom;
  private String startingRoom;
  private String endingRoom;
  private List<Room> rooms;
  private HashMap<String, Room> nameAndRooms;

  public Adventure(Layout l) {
    currentLayout = l;
    startingRoom = l.getStartingRoom();
    endingRoom = l.getEndingRoom();
    rooms = l.getRooms();
    nameAndRooms = roomAndNameMapper(rooms);
    currentRoom = nameAndRooms.get(startingRoom);
  }

  /**
   * Makes a HashMap mapping String room's name to the Room object.
   * @param roomsList is a List of all rooms.
   * @return a HashMap that has keys as the names of the Rooms and values as the
   * corresponding room object.
   */
  private HashMap<String, Room> roomAndNameMapper(final List<Room> roomsList) {
    HashMap<String, Room> map = new HashMap<>();
    for (int i = 0; i < roomsList.size(); i++) {
      map.put(roomsList.get(i).getName(), roomsList.get(i));
    }
    return map;
  }

  public Room getCurrentRoom() {
    return currentRoom;
  }

  public String getEndingRoom() {
    return endingRoom;
  }

  /**
   * This method checks to see if it is possible to travel
   * in a given direction and does so if valid.
   *
   * @param direction
   * @return output message
   */
  public String goDirection(final String direction) {
    String output = "I can't go " + direction + "!";
    List<Direction> possibleDirections = currentRoom.getDirections();
    for (Direction d : possibleDirections) {
      if (d.getDirectionName().toLowerCase().equals(direction.toLowerCase())) {
        currentRoom = nameAndRooms.get(d.getRoom());
        output = "";
      }
    }
    return output;
  }

  public String getDescription() {
    return currentRoom.getDescription();
  }

  public List<Room> getRooms() {
    return rooms;
  }


}