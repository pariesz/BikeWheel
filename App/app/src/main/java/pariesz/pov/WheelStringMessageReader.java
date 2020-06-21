package pariesz.pov;

import androidx.annotation.NonNull;

import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;

public class WheelStringMessageReader implements WheelMessageReader {
    private ByteBuffer buffer = ByteBuffer.allocate(1024);
    private byte command;
    private boolean flipped;

    public WheelStringMessageReader(byte command) throws IllegalArgumentException {
        switch (command) {
            case 0:
            case WheelService.CMD_GET_EEPROM:
            case WheelService.CMD_SET_EEPROM:
                throw new IllegalArgumentException("Invalid command: " + command);
        }

        this.command = command;
    }

    @Override
    public boolean consume(byte ch) {
        // Arduino Serial.println
        // Prints data to the serial port as human-readable ASCII text followed by
        // a carriage return character (ASCII 13, or '\r')
        // and a newline character (ASCII 10, or '\n').

        if (ch == '\r') {
            return false;
        }

        if (ch == '\n') {
            buffer.flip();
            flipped = true;
            return true;
        }

        buffer.put((byte) ch);
        return false;
    }

    @Override
    public WheelMessage getMessage() {
        ByteBuffer b = buffer;

        if(!flipped) {
            b = b.duplicate();
            b.flip();
        }

        return new WheelStringMessage(command, StandardCharsets.US_ASCII.decode(b).toString(), false);
    }

    @NonNull
    @Override
    public String toString() {
        return getMessage().toString();
    }
}
