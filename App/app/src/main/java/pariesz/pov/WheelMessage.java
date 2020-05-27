package pariesz.pov;

import androidx.annotation.NonNull;

import java.time.LocalDateTime;

public class WheelMessage {
    private String message;
    private LocalDateTime date = LocalDateTime.now();
    private boolean transmit;

    public WheelMessage(String message, boolean transmit) {
        this.message = message;
        this.transmit = transmit;
    }

    public  String getCommand() {
        if(message.length() >= 3) {
            return message.substring(0, 3);
        } else {
            return null;
        }
    }

    public String getValue() {
        if(message.length() > 4) {
            return message.substring(4);
        } else {
            return null;
        }
    }

    public int getInt() throws StringIndexOutOfBoundsException, NumberFormatException {
        return Integer.parseInt(message.substring(4));
    }

    public String getMessage() {
        return message;
    }

    public  LocalDateTime getDate() {
        return date;
    }

    public  boolean getTransmit() {
        return transmit;
    }

    @NonNull
    @Override
    public String toString() {
        return message;
    }
}
