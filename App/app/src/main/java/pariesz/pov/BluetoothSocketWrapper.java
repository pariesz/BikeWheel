package pariesz.pov;

import android.bluetooth.BluetoothSocket;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

public class BluetoothSocketWrapper implements ISocket {
    private BluetoothSocket socket;

    public BluetoothSocketWrapper(BluetoothSocket socket) {
        this.socket = socket;
    }

    @Override
    public void connect() throws IOException {
        socket.connect();
    }

    @Override
    public void close() throws IOException {
        socket.close();
    }

    @Override
    public InputStream getInputStream() throws IOException {
        return socket.getInputStream();
    }

    @Override
    public OutputStream getOutputStream() throws IOException {
        return socket.getOutputStream();
    }
}
