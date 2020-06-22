package pariesz.pov;

import android.annotation.SuppressLint;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.os.Handler;
import android.os.Message;
import android.util.Log;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.UUID;

public class WheelService {
    private static final String TAG = "WheelService";
    private static final UUID SERIAL_UUID = UUID.fromString("00001101-0000-1000-8000-00805f9b34fb");

    private static int MAX_MESSAGE_SIZE = 30;

    public static final float VOLTAGE_MIN = 5.0f;
    public static final float VOLTAGE_MAX = 12.0f;

    public static final short EEPROM_WHEEL_CIRCUMFERENCE = 0; // int16
    public static final short EEPROM_MOVING_RATE = 2; // int32
    public static final short EEPROM_STATIONARY_RATE = 6; // int32
    public static final short EEPROM_BRIGHTNESS = 10; // int8
    public static final short EEPROM_EXPLODING_TEXT = 11; // 39 byte string (with NUL terminator)
    public static final short EEPROM_TIMER_FRAMES = 50; // int16

    public static final byte CMD_SET_EEPROM = 1;
    public static final byte CMD_GET_EEPROM = 2;
    public static final byte CMD_BATTERY = 3;
    public static final byte CMD_ANGLE = 4;
    public static final byte CMD_ROTATION_RATE = 5;
    public static final byte CMD_SET_MOVING_PROGRAM = 6;
    public static final byte CMD_GET_MOVING_PROGRAM = 7;
    public static final byte CMD_SET_STATIONARY_PROGRAM = 8;
    public static final byte CMD_GET_STATIONARY_PROGRAM = 9;

    public static final int STATUS_DISCONNECTED = 0;
    public static final int STATUS_CONNECTING = 1;
    public static final int STATUS_CONNECTED = 2;

    private int status = STATUS_DISCONNECTED;

    private String deviceName;
    private WheelThread thread;
    private List<OnMessageReceivedListener> registeredReceivedListeners = new ArrayList<>();
    private List<OnMessageSentListener> registeredSentListeners = new ArrayList<>();
    private List<OnStatusChangeListener> registeredStatusChangeListeners = new ArrayList<>();
    private Queue<WheelMessage> messages = new LinkedList<>();

    public interface OnMessageReceivedListener {
        void onMessageReceived(WheelMessage message);
    }
    public interface OnMessageSentListener {
        void onMessageSent(WheelMessage message);
    }
    public interface OnStatusChangeListener {
        void onStatusChange(int status, String message);
    }
    public void addOnMessageReceivedListener(OnMessageReceivedListener listener) {
        registeredReceivedListeners.add(listener);
    }
    public void addOnMessageSentListener(OnMessageSentListener listener) {
        registeredSentListeners.add(listener);
    }
    public void addOnStatusChangeListener(OnStatusChangeListener listener) {
        registeredStatusChangeListeners.add(listener);
    }
    public void removeOnMessageReceivedListener(OnMessageReceivedListener listener) {
        registeredReceivedListeners.remove(listener);
    }
    public void removeOnMessageSentListener(OnMessageSentListener listener) {
        registeredSentListeners.remove(listener);
    }
    public void removeOnStatusChangeListener(OnStatusChangeListener listener) {
        registeredStatusChangeListeners.add(listener);
    }
    public String getDeviceName() {
        return deviceName;
    }

    private void setStatus(int status, String message) {
        this.status = status;
        for(OnStatusChangeListener listener: registeredStatusChangeListeners) {
            listener.onStatusChange(status, message);
        }
    }

    public Iterable<WheelMessage> getMessages() {
        return messages;
    }

    public void connect(ISocket socket, String deviceName) {
        if (thread != null) {
            Log.e(TAG, "Cancelling thread.");
            thread.cancel();
        }

        this.deviceName = deviceName;

        setStatus(STATUS_CONNECTING, deviceName + " connecting.");
        thread = new WheelThread(socket, threadHandler);
        thread.start();
    }

    public void connect(BluetoothDevice device) {
        try {
            String uuid = device.getUuids()[0].toString();
            BluetoothSocket btSocket = device.createInsecureRfcommSocketToServiceRecord(UUID.fromString(uuid));
            connect(new BluetoothSocketWrapper(btSocket), device.getName());
        } catch (Exception ex) {
            Log.e(TAG,"Error creating Insecure RF Comm Socket.", ex);
            return;
        }
    }

    @SuppressLint("HandlerLeak")
    private Handler threadHandler = new Handler() {

        @Override
        public void handleMessage(Message msg) {
        switch (msg.what) {
            case WheelThread.MESSAGE_RECEIVED:
                receive((WheelMessage)msg.obj);
                break;

            case WheelThread.MESSAGE_DISCONNECTED:
                Log.d(TAG, "Disconnected: " + msg.obj);
                setStatus(STATUS_DISCONNECTED, (String)msg.obj);
                break;

            case WheelThread.MESSAGE_CONNECTED:
                Log.d(TAG, "Connected: " + deviceName);
                setStatus(STATUS_CONNECTED, deviceName + " connected");
                break;
        }
        }
    };

    public int getStatus() {
        return status;
    }

    public void getEeprom(short address, int length) {
        command(new WheelEepromMessage(CMD_GET_EEPROM, address, (byte) length));
    }

    public void setEeprom(short address, byte value) {
        command(new WheelEepromMessage(CMD_SET_EEPROM, address, new byte[] { value }, true));
    }

    public void setEeprom(short address, short value) {
        command(new WheelEepromMessage(CMD_SET_EEPROM, address, ByteBuffer.allocate(2).order(ByteOrder.LITTLE_ENDIAN).putShort(value).array(), true));
    }

    public void setEeprom(short address, int value) {
        command(new WheelEepromMessage(CMD_SET_EEPROM, address, ByteBuffer.allocate(4).order(ByteOrder.LITTLE_ENDIAN).putInt(value).array(), true));
    }

    public void setEeprom(short address, String value) {
        byte[] bytes = value.getBytes(StandardCharsets.US_ASCII);

        // Add the c++ null terminator
        final int length = bytes.length;
        bytes = Arrays.copyOf(bytes, length + 1);
        bytes[length] = 0;

        command(new WheelEepromMessage(CMD_SET_EEPROM, address, bytes, true));
    }

    public void command(byte command) {
        command(new WheelMessage(command, true));
    }

    public void command(byte command, byte value) throws IOException {
        command(new WheelByteMessage( command, value, true));
    }

    public void command(WheelMessage message) {
        if(status != STATUS_CONNECTED) {
            Log.e(TAG, "Not connected, cannot write: " + message);
            return;
        }

        //Log.d(TAG, "tx:" + text);

        enqueueMessage(message);

        thread.transmitMessage(message);

        for(OnMessageSentListener listener: registeredSentListeners) {
            listener.onMessageSent(message);
        }
    }

    private void receive(WheelMessage message) {
        enqueueMessage(message);
        for(OnMessageReceivedListener listener: registeredReceivedListeners) {
            listener.onMessageReceived(message);
        }
    }

    private void enqueueMessage(WheelMessage message) {
        messages.add(message);
        while (messages.size() > MAX_MESSAGE_SIZE) {
            messages.remove();
        }
    }
}
