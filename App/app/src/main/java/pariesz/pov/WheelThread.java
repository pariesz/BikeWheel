package pariesz.pov;

import android.os.Handler;
import android.os.Message;
import android.util.Log;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

public class WheelThread extends Thread {
    private static final String TAG = "WheelThread";

    public static final int MESSAGE_CONNECTED = 1;
    public static final int MESSAGE_RECEIVED = 2;
    public static final int MESSAGE_DISCONNECTED = 3;

    private ISocket socket;
    private InputStream inStream;
    private OutputStream outStream;
    private Handler handler;
    private WheelMessageReader reader;

    public WheelThread(ISocket socket, Handler handler) {
        this.setName("WheelThread");
        this.socket = socket;
        this.handler = handler;
    }

    @Override
    public void run() {
        Log.d(TAG, "Connecting");
        try {
            socket.connect();
            inStream = socket.getInputStream();
            outStream = socket.getOutputStream();
            handler.sendEmptyMessage(MESSAGE_CONNECTED);

            while (true) {
                try {
                    if (inStream.available() > 0) {
                        byte ch = (byte) inStream.read();
                        if (ch == -1) {
                            continue;
                        }

                        if (reader == null) {
                            switch (ch) {
                                case 0:
                                    throw new Exception("Invalid command: " + ch);
                                case WheelService.CMD_SET_EEPROM:
                                case WheelService.CMD_GET_EEPROM:
                                    reader = new WheelEepromMessageReader(ch);
                                    break;
                                default:
                                    reader = new WheelStringMessageReader(ch);
                                    break;
                            }
                        } else {
                            if (reader.consume(ch)) {
                                Message message = new Message();
                                message.what = MESSAGE_RECEIVED;
                                message.obj = reader.getMessage();
                                Log.d(TAG, message.obj.toString());
                                handler.sendMessage(message);
                                reader = null;
                            }
                        }
                    }
                } catch (IOException ex) {
                    Log.e(TAG, "rx error", ex);
                    handleIOException(ex);
                    break;

                } catch (Exception ex) {
                    reader = null;
                    Log.e(TAG, "error", ex);
                }
            }

        } catch (IOException ex) {
            Log.e(TAG, "rx error", ex);
            handleIOException(ex);
        }
    }

    public void transmitMessage(WheelMessage message) {
        Log.d(TAG, message.toString());

        try {
            message.write(outStream);
        } catch (IOException ex) {
            Log.e(TAG, "transmitMessage error: " + message, ex);
            handleIOException(ex);
        }
    }

    private void handleIOException(IOException ex) {
        cancel();

        Message message = new Message();
        message.what = MESSAGE_DISCONNECTED;
        message.obj = ex.getMessage();

        handler.sendMessage(message);
    }

    public void cancel() {
        try {
            reader = null;

            if(inStream != null) {
                inStream.close();
            }
            if(outStream != null) {
                outStream.close();
            }
            if(socket != null) {
                socket.close();
            }
        } catch (IOException ex) {
            Log.d(TAG, "Cancel error", ex);
        }
    }
}