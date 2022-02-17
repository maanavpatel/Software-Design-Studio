
package student.adventure;

import java.util.HashMap;
import java.util.Map;
import com.fasterxml.jackson.annotation.JsonAnyGetter;
import com.fasterxml.jackson.annotation.JsonAnySetter;
import com.fasterxml.jackson.annotation.JsonIgnore;
import com.fasterxml.jackson.annotation.JsonInclude;
import com.fasterxml.jackson.annotation.JsonProperty;
import com.fasterxml.jackson.annotation.JsonPropertyOrder;

@JsonInclude(JsonInclude.Include.NON_NULL)
@JsonPropertyOrder({
    "directionName",
    "room"
})
public class Direction {

    @JsonProperty("directionName")
    private String directionName;
    @JsonProperty("room")
    private String room;
    @JsonIgnore
    private Map<String, Object> additionalProperties = new HashMap<String, Object>();

    /**
     * No args constructor for use in serialization
     * 
     */
    public Direction() {
    }

    /**
     * 
     * @param directionName
     * @param room
     */
    public Direction(String directionName, String room) {
        super();
        this.directionName = directionName;
        this.room = room;
    }

    @JsonProperty("directionName")
    public String getDirectionName() {
        return directionName;
    }

    @JsonProperty("directionName")
    public void setDirectionName(String directionName) {
        this.directionName = directionName;
    }

    public Direction withDirectionName(String directionName) {
        this.directionName = directionName;
        return this;
    }

    @JsonProperty("room")
    public String getRoom() {
        return room;
    }

    @JsonProperty("room")
    public void setRoom(String room) {
        this.room = room;
    }

    public Direction withRoom(String room) {
        this.room = room;
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

    public Direction withAdditionalProperty(String name, Object value) {
        this.additionalProperties.put(name, value);
        return this;
    }

    @Override
    public String toString() {
        StringBuilder sB = new StringBuilder();
        sB.append("directionName: ").append(directionName).append("\t").append("room: ").append(room)
                .append("\t");
        return sB.toString();
    }

}
