package pariesz.pov;

import android.util.Log;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PipedInputStream;
import java.io.PipedOutputStream;
import java.nio.ByteBuffer;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;

public class MockSocket implements ISocket {
    private static final String TAG = "MockSocket";
    private static final Charset CHARSET = Charset.forName(StandardCharsets.US_ASCII.name());

    private PipedOutputStream out;
    private PipedInputStream inputStream;

    private long millis;

    private short battery = 1023; // 0-5v = 0-1023
    private int rotationRate = 100000; // 16bit angle per second
    private byte movingProgram = 0; // program id (not index!)
    private byte stationaryProgram = 0; // program id (not index!)
    private int angle = 0; // 16bit angle: 0-65535 = 0-360 degrees.  Use int (instead of short) to handle overflow.
    private byte[] eeprom = new byte[4095];

    public MockSocket() {
        out = new PipedOutputStream();

        try {
            inputStream = new PipedInputStream(out);
        } catch (IOException ex) {
            Log.e(TAG, "Error creating PipedInputStream", ex);
        }
    }

    private void mockTransmit(WheelMessage message) {
        Log.d(TAG, message.toString());
        try {
            byte cmd = message.getCommand();
            switch (cmd) {
                case WheelService.CMD_SET_MOVING_PROGRAM:
                    movingProgram = (byte) message.getValueInt();
                    writeCommand(cmd);
                    break;

                case WheelService.CMD_SET_STATIONARY_PROGRAM:
                    stationaryProgram = (byte) message.getValueInt();
                    writeCommand(cmd);
                    break;

                case WheelService.CMD_SET_EEPROM:
                    setEeprom((WheelEepromMessage) message);
                case WheelService.CMD_GET_EEPROM:
                    writeEeprom((WheelEepromMessage) message);
                    break;

                default:
                    writeCommand(cmd);
                    break;
            }
        } catch (Exception ex) {
            Log.e(TAG, "writeEeprom error: " + message, ex);
        }
    }

    private int getValue(byte command) throws Exception {
        switch (command) {
            case WheelService.CMD_BATTERY:
                return battery -= 100; // battery is requested evey minute
            case WheelService.CMD_GET_MOVING_PROGRAM:
            case WheelService.CMD_SET_MOVING_PROGRAM:
                return movingProgram;
            case WheelService.CMD_GET_STATIONARY_PROGRAM:
            case WheelService.CMD_SET_STATIONARY_PROGRAM:
                return stationaryProgram;

            case WheelService.CMD_ROTATION_RATE:
                return rotationRate += (Math.random() - 0.5) * 3000;
            case WheelService.CMD_ANGLE: {
                if (millis == 0) {
                    millis = System.currentTimeMillis();

                } else {
                    long elapsed = System.currentTimeMillis() - millis;

                    millis = System.currentTimeMillis();

                    angle += elapsed * rotationRate / 1000;

                    while (angle > 65535) {
                        angle -= 65535;
                    }
                }
                return angle;
            }
            default:
                throw new Exception("unrecognised command: " + command);
        }
    }

    private void writeCommand(byte command) throws Exception {
        out.write(command);
        try {
            String value = Integer.toString(getValue(command));
            Log.d(TAG, new WheelStringMessage(command, value, true).toString());
            out.write(value.getBytes(StandardCharsets.US_ASCII));
        } catch (Exception ex) {
            out.write(ex.getMessage().getBytes(StandardCharsets.US_ASCII));
        }
        out.write('\n'); // Arduino uses println
    }

    private void writeEeprom(WheelEepromMessage message) throws Exception {
        short address = message.getAddress();

        byte[] value = new byte[message.getLength()];

        for(int i=0; i<value.length; i++) {
            value[i] = eeprom[address + i];
        }

        message = new WheelEepromMessage(message.getCommand(), message.getAddress(), value, true);
        Log.d(TAG, message.toString());
        message.write(out);
    }

    private void setEeprom(WheelEepromMessage message) {
        byte[] bytes = message.getValueBytes();

        short address = message.getAddress();

        for(int i=0; i<bytes.length; i++) {
            eeprom[address + i] = bytes[i];
        }
    }

    public OutputStream outputStream = new OutputStream() {
        private ByteBuffer buffer = ByteBuffer.allocate(1024);
        private WheelMessageReader reader;

        @Override
        public void write(int ch) throws IOException {

            try {
                if (reader == null) {
                    switch (ch) {
                        case WheelService.CMD_SET_EEPROM:
                        case WheelService.CMD_GET_EEPROM:
                            reader = new MockWheelEepromMessageReader((byte)ch);
                            break;
                        case WheelService.CMD_SET_MOVING_PROGRAM:
                        case WheelService.CMD_SET_STATIONARY_PROGRAM:
                            reader = new WheelStringMessageReader((byte)ch, (char)0);
                            break;
                        default:
                            mockTransmit(new WheelMessage((byte)ch, false));
                            break;
                    }
                } else if (reader.consume((byte) ch)) {
                    mockTransmit(reader.getMessage());
                    reader = null;
                }
            } catch (Exception ex) {
                Log.e(TAG, "reader (" + reader + ") error consuming " + ch, ex);
                reader = null;
            }
        }
    };

    @Override
    public void connect() throws IOException {

    }

    @Override
    public void close() throws IOException {

    }

    @Override
    public InputStream getInputStream() throws IOException {
        return inputStream;
    }

    @Override
    public OutputStream getOutputStream() throws IOException {
        return outputStream;
    }
}
