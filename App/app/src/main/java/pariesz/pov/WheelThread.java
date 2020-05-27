package pariesz.pov;

import android.os.Handler;
import android.os.Message;
import android.util.Log;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.nio.ByteBuffer;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;

public class WheelThread extends Thread {
    private static final String TAG = "WheelThread";
    private static final Charset CHARSET = StandardCharsets.US_ASCII;

    public static final int MESSAGE_CONNECTED = 1;
    public static final int MESSAGE_RECEIVED = 2;
    public static final int MESSAGE_ERROR = 3;

    private ISocket socket;
    private InputStream inStream;
    private OutputStream outStream;
    //private InputStreamReader reader;
    //private BufferedReader bufferedReader;
    private Handler handler;
    private ByteBuffer buffer = ByteBuffer.allocate(1024);

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
                if (inStream.available() > 0) {
                    int b = inStream.read();
                    if (b == -1) {
                        continue;

                    } else if (b == '\n') {
                        buffer.flip();
                        Message message = new Message();
                        message.what = MESSAGE_RECEIVED;
                        message.obj = CHARSET.decode(buffer).toString();

                        //Log.d(TAG, "rx:" + message.obj.toString());

                        handler.sendMessage(message);
                        buffer.clear();

                    } else {
                        buffer.put((byte) b);
                    }
                }
            }
        } catch (IOException ex) {
            Log.d(TAG, "error", ex);
            cancel();

            Message message = new Message();
            message.what = MESSAGE_ERROR;
            message.obj = ex.getMessage();

            handler.sendMessage(message);
        }
    }

    public void transmitMessage(String text) throws IOException {
        //Log.d(TAG, "tx:" + text);
        outStream.write(text.getBytes(CHARSET));
        outStream.write(0); // NUL: null
    }

    public void cancel() {
        try {
            inStream.close();
            outStream.close();
            socket.close();
        } catch (IOException ex) {
            Log.d(TAG, "Cancel error", ex);
        }
    }
}