
package student.adventure;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

import com.fasterxml.jackson.annotation.JsonAnyGetter;
import com.fasterxml.jackson.annotation.JsonAnySetter;
import com.fasterxml.jackson.annotation.JsonIgnore;
import com.fasterxml.jackson.annotation.JsonInclude;
import com.fasterxml.jackson.annotation.JsonProperty;
import com.fasterxml.jackson.annotation.JsonPropertyOrder;

@JsonInclude(JsonInclude.Include.NON_NULL)
@JsonPropertyOrder({
    "startingRoom",
    "endingRoom",
    "rooms"
})
public class Layout {

    @JsonProperty("startingRoom")
    private String startingRoom;
    @JsonProperty("endingRoom")
    private String endingRoom;
    @JsonProperty("rooms")
    private List<Room> rooms = null;
    @JsonIgnore
    private Map<String, Object> additionalProperties = new HashMap<String, Object>();

    /**
     * No args constructor for use in serialization
     * 
     */
    public Layout() {
    }

    /**
     * 
     * @param startingRoom
     * @param rooms
     * @param endingRoom
     */
    public Layout(String startingRoom, String endingRoom, List<Room> rooms) {
        super();
        this.startingRoom = startingRoom;
        this.endingRoom = endingRoom;
        this.rooms = rooms;
    }

    @JsonProperty("startingRoom")
    public String getStartingRoom() {
        return startingRoom;
    }

    @JsonProperty("startingRoom")
    public void setStartingRoom(String startingRoom) {
        this.startingRoom = startingRoom;
    }

    public Layout withStartingRoom(String startingRoom) {
        this.startingRoom = startingRoom;
        return this;
    }

    @JsonProperty("endingRoom")
    public String getEndingRoom() {
        return endingRoom;
    }

    @JsonProperty("endingRoom")
    public void setEndingRoom(String endingRoom) {
        this.endingRoom = endingRoom;
    }

    public Layout withEndingRoom(String endingRoom) {
        this.endingRoom = endingRoom;
        return this;
    }

    @JsonProperty("rooms")
    public List<Room> getRooms() {
        return rooms;
    }

    @JsonProperty("rooms")
    public void setRooms(List<Room> rooms) {
        this.rooms = rooms;
    }

    public Layout withRooms(List<Room> rooms) {
        this.rooms = rooms;
        return this;
    }

    @JsonAnyGetter
    public Map<String, Object> getAdditionalProperties() {
        return this.additionalProperties;
    }

    @JsonAnySetter
    public void setAdditionalProperty(String name, Object value) {
        this.additionalProperties.put(name, value);
    }

    public Layout withAdditionalProperty(String name, Object value) {
        this.additionalProperties.put(name, value);
        return this;
    }

    @Override
    public String toString() {
        String roomString = "\n \t";
        for (Room r : rooms) {
            roomString += r.toString() + "\n \t";
        }
        StringBuilder sB = new StringBuilder();
        sB.append("startingRoom: ").append(startingRoom).append("\n").append("endingRoom: ").append(endingRoom).append("\n")
                .append("rooms: ").append(roomString).append("\n").append("additionalProperties: ").append(additionalProperties).toString();
        return sB.toString();
    }

}
