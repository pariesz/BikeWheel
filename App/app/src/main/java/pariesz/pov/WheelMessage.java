package pariesz.pov;

import androidx.annotation.NonNull;

import java.io.IOException;
import java.io.OutputStream;
import java.time.LocalDateTime;

public class WheelMessage {
    private byte command;
    private boolean transmit;
    private LocalDateTime date = LocalDateTime.now();

    public WheelMessage(byte command, boolean transmit) throws IllegalArgumentException {
        if(command == 0) {
            throw new IllegalArgumentException("Invalid command: " + 0);
        }

        this.command = command;
        this.transmit = transmit;
    }

    public byte getCommand() {
        return command;
    }

    public LocalDateTime getDate() {
        return date;
    }

    public boolean getTransmit() {
        return transmit;
    }

    public String getValueString() {
        return null;
    }

    public int getValueInt() {
        throw new UnsupportedOperationException();
    }

    public void write(OutputStream stream) throws IOException {
        stream.write(command);
    }

    @NonNull
    @Override
    public String toString() {
        return (transmit ? ">" : "<") + " cmd:" + command;
    }
}
