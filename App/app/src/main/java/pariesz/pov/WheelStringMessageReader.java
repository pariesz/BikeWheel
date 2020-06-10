package pariesz.pov;

import androidx.annotation.NonNull;

import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;

public class WheelStringMessageReader implements WheelMessageReader {
    private ByteBuffer buffer = ByteBuffer.allocate(1024);
    private byte command;
    private char terminator;

    public WheelStringMessageReader(byte command, char terminator) throws IllegalArgumentException {
        switch (command) {
            case 0:
            case WheelService.CMD_GET_EEPROM:
            case WheelService.CMD_SET_EEPROM:
                throw new IllegalArgumentException("Invalid command: " + command);
        }

        this.command = command;
        this.terminator = terminator;
    }

    @Override
    public boolean consume(byte ch) {
        if (ch == terminator) {
            buffer.flip();
            return true;

        } else {
            buffer.put((byte) ch);
            return false;
        }
    }

    @Override
    public WheelMessage getMessage() {
        return new WheelStringMessage(command, StandardCharsets.US_ASCII.decode(buffer).toString(), false);
    }

    @NonNull
    @Override
    public String toString() {
        return Byte.toString(command);
    }
}
