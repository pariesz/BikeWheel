package pariesz.pov;

import androidx.annotation.NonNull;

import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;

public class WheelByteMessageReader implements WheelMessageReader {
    private byte value;
    private byte command;

    public WheelByteMessageReader(byte command) {
        this.command = command;
    }

    @Override
    public boolean consume(byte ch) {
        value = ch;
        return true;
    }

    @Override
    public WheelMessage getMessage() {
        return new WheelByteMessage(command, value, false);
    }

    @NonNull
    @Override
    public String toString() {
        return getMessage().toString();
    }
}
