package pariesz.pov;

import androidx.annotation.NonNull;

import java.io.IOException;
import java.io.OutputStream;

public class WheelByteMessage extends WheelMessage {
    private byte value;

    public WheelByteMessage(byte command, byte value, boolean transmit) {
        super(command, transmit);
        this.value = value;
    }

    @Override
    public String getValueString() {
        return Integer.toString(getValueInt());
    }

    @Override
    public int getValueInt() {
        return Byte.toUnsignedInt(value);
    }

    @Override
    public void write(OutputStream stream) throws IOException {
        super.write(stream);
        stream.write(value);
    }

    @NonNull
    @Override
    public String toString() {
        return super.toString() + " data:" + getValueString();
    }
}
