package pariesz.pov;

import android.annotation.SuppressLint;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.os.Handler;
import android.os.Message;
import android.util.Log;

import java.io.IOException;
import java.util.ArrayList;
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

    public static final String CMD_BATTERY = "BAT";
    public static final String CMD_MOVING_PROGRAM = "PMO";
    public static final String CMD_STATIONARY_PROGRAM = "PST";
    public static final String CMD_ROTATION_RATE = "ROT";
    public static final String CMD_ANGLE = "ANG";
    public static final String CMD_BRIGHTNESS = "BRI";
    public static final String CMD_MOVING_ROTATION_RATE = "VMO";
    public static final String CMD_STATIONARY_ROTATION_RATE = "VST";
    public static final String CMD_CIRCUMFERENCE = "CER";

    public static final int STATUS_DISCONNECTED = 0;
    public static final int STATUS_CONNECTING = 1;
    public static final int STATUS_CONNECTED = 2;

    private int status = STATUS_DISCONNECTED;

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
        void onStatusChange(int status);
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

    private void setStatus(int status) {
        this.status = status;
        for(OnStatusChangeListener listener: registeredStatusChangeListeners) {
            listener.onStatusChange(status);
        }
    }

    public Iterable<WheelMessage> getMessages() {
        return messages;
    }

    public void connect(ISocket socket) {
        if (thread != null) {
            thread.cancel();
        }

        setStatus(STATUS_CONNECTING);
        thread = new WheelThread(socket, threadHandler);
        thread.start();
    }

    public void connect(BluetoothDevice device) {
        try {
            String uuid = device.getUuids()[0].toString();
            BluetoothSocket btSocket = device.createInsecureRfcommSocketToServiceRecord(UUID.fromString(uuid));
            connect(new BluetoothSocketWrapper(btSocket));
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
                readMessage((String)msg.obj);
                break;

            case WheelThread.MESSAGE_ERROR:
                setStatus(STATUS_DISCONNECTED);
                break;

            case WheelThread.MESSAGE_CONNECTED:
                setStatus(STATUS_CONNECTED);
                break;
        }
        }
    };

    public int getStatus() {
        return status;
    }


    public void writeMessage(String command, int value) throws IOException {
        writeMessage(command + ":" + value);
    }

    public void writeMessage(String command, String value) throws IOException {
        writeMessage(command + ":" + value);
    }

    public void writeMessage(String text) throws IOException {
        if(status != STATUS_CONNECTED) {
            Log.e(TAG, "Not connected, cannot write: " + text);
            return;
        }

        //Log.d(TAG, "tx:" + text);

        WheelMessage message = enqueueMessage(text, true);

        thread.transmitMessage(text);

        for(OnMessageSentListener listener: registeredSentListeners) {
            listener.onMessageSent(message);
        }
    }

    private void readMessage(String text) {
        WheelMessage message = enqueueMessage(text, false);

        //Log.d(TAG, "rx:" + text);

        for(OnMessageReceivedListener listener: registeredReceivedListeners) {
            listener.onMessageReceived(message);
        }
    }

    private WheelMessage enqueueMessage(String text, boolean transmit) {
        WheelMessage result = new WheelMessage(text, transmit);

        messages.add(result);

        while (messages.size() > MAX_MESSAGE_SIZE) {
            messages.remove();
        }

        return result;
    }
}
