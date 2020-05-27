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

    private int battery = 1023; // 0-5v = 0-1023
    private int rotationRate = 100000; // 16bit angle per second
    private int movingProgram = 0; // program id (not index!)
    private int movingRotationRate = 80000; // 16bit angle per second
    private int stationaryProgram = 0; // program id (not index!)
    private int stationaryRotationRate = 60000; // 16bit angle per second
    private int brightness = 20; // 0-100
    private int angle = 0; // 16bit angle: 0-65535 = 0-360 degrees
    private int wheelCircumference = 2299; // mm

    public MockSocket() throws IOException {
        out = new PipedOutputStream();
        inputStream = new PipedInputStream(out);
    }

    private void mockTransmit(String text) throws IOException {
        //Log.d(TAG, "tx:" + text);
        WheelMessage message = new WheelMessage(text, true);
        String cmd = message.getCommand();

        if (message.getValue() != null) {
            try {
                setValue(cmd, message.getInt());
            } catch (NumberFormatException ex) {
                Log.e(TAG, "Invalid int value.", ex);
            }
        }

        try {
            mockReceive(cmd + ":" + getValue(cmd) + "\n");
        } catch (Exception ex) {
            mockReceive(cmd + ":" + ex.getMessage() + "\n");
        }
    }

    private void mockReceive(String text) throws IOException {
        //Log.d(TAG, "rx:" + text);
        out.write(text.getBytes(StandardCharsets.US_ASCII));
    }

    private int getValue(String command) throws Exception {
        switch (command) {
            case WheelService.CMD_BATTERY: return battery -= 100; // battery is requested evey minute
            case WheelService.CMD_MOVING_PROGRAM: return movingProgram;
            case WheelService.CMD_STATIONARY_PROGRAM: return stationaryProgram;
            case WheelService.CMD_ROTATION_RATE: return rotationRate += (Math.random() - 0.5) * 3000;
            case WheelService.CMD_MOVING_ROTATION_RATE: return movingRotationRate;
            case WheelService.CMD_STATIONARY_ROTATION_RATE: return stationaryRotationRate;
            case WheelService.CMD_ANGLE: {
                if (millis == 0) {
                    millis = System.currentTimeMillis();

                } else {
                    long elapsed = System.currentTimeMillis() - millis;

                    millis = System.currentTimeMillis();

                    angle += elapsed * rotationRate / 1000;

                    while(angle > 65535) {
                        angle -= 65535;
                    }
                }
                return angle;
            }
            case WheelService.CMD_BRIGHTNESS: return brightness;
            case WheelService.CMD_CIRCUMFERENCE: return wheelCircumference;
            default: throw new Exception("unrecognised command");
        }
    }

    private void setValue(String command, int value) {
        switch (command) {
            case WheelService.CMD_MOVING_PROGRAM: movingProgram = value; return;
            case WheelService.CMD_STATIONARY_PROGRAM: stationaryProgram = value; return;
            case WheelService.CMD_BRIGHTNESS: brightness = value; return;
            case WheelService.CMD_MOVING_ROTATION_RATE: movingRotationRate = value; return;
            case WheelService.CMD_STATIONARY_ROTATION_RATE: stationaryRotationRate = value; return;
            case WheelService.CMD_CIRCUMFERENCE: wheelCircumference = value; return;
        }
    }

    public OutputStream outputStream = new OutputStream() {
        private ByteBuffer buffer = ByteBuffer.allocate(1024);

        @Override
        public void write(int b) throws IOException {
            if (b == 0) {
                // transmit null to end the message
                buffer.flip();
                String text = CHARSET.decode(buffer).toString();
                mockTransmit(text);
                buffer.clear();
            } else {
                buffer.put((byte)b);
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
