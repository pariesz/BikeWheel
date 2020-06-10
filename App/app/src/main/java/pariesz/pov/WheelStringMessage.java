package pariesz.pov;

import androidx.annotation.NonNull;

import java.io.IOException;
import java.io.OutputStream;
import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;
import java.time.LocalDateTime;

public class WheelStringMessage extends WheelMessage {
    private String value;

    public WheelStringMessage(byte command, String value, boolean transmit) {
        super(command, transmit);
        this.value = value;
    }

    @Override
    public String getValueString() {
        return value;
    }

    @Override
    public int getValueInt() {
        return Integer.parseInt(value);
    }

    @Override
    public void write(OutputStream stream) throws IOException {
        super.write(stream);
        stream.write(value.getBytes(StandardCharsets.US_ASCII));
        stream.write(0); // NUL: null
    }

    @NonNull
    @Override
    public String toString() {
        return super.toString() + " data:" + value;
    }
}
