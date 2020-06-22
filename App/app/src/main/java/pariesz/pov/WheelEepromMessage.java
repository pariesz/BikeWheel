package pariesz.pov;

import androidx.annotation.NonNull;

import java.io.IOException;
import java.io.OutputStream;
import java.nio.charset.StandardCharsets;

public class WheelEepromMessage extends WheelMessage {
    private short address;
    private byte[] value;
    private byte length;

    public WheelEepromMessage(byte command, short address, byte length) {
        super(command, true);
        this.address = address;
        this.length = length;
    }

    public WheelEepromMessage(byte command, short address, byte[] value, boolean transmit) {
        super(command, transmit);
        this.address = address;

        if(value != null) {
            this.length = (byte) value.length;
            this.value = value;
        }
    }

    public short getAddress() {
        return address;
    }

    public byte getLength() {
        return length;
    }

    public byte[] getValueBytes() {
        return value;
    }

    public String getValueString() {
        StringBuilder builder = new StringBuilder(value.length);

        for(int i=0; i<value.length; i++) {
            // deal with NUL terminated strings
            if(value[i] == 0) {
                break;
            }

            builder.append((char)value[i]);
        }
        return builder.toString();
    }

    public int getValueInt() {
        int result = 0;

        // Bytes are sent in host order, Arduino uses little-edian
        for(int i=value.length-1; i>=0; i--) {
            result = (result << 8) | (value[i] & 0xFF);
        }
        return result;
    }

    @Override
    public void write(OutputStream stream) throws IOException {
        super.write(stream);

        // Bytes are sent in host order, Arduino uses little-edian
        stream.write(address); // The byte to be written is the eight low-order bits
        stream.write(address  >> 8);

        stream.write(length);

        if(value != null) {
            stream.write(value);
        }
    }

    @NonNull
    @Override
    public String toString() {
        if(value == null) {
            return super.toString() + " address:" + address + " len:" + length;
        } else {
            return super.toString() + " address:" + address + " len:" + length + " data: 0x" + Utilities.bytesToHex(value);
        }
    }
}
