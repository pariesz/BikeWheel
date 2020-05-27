package pariesz.pov;

import android.bluetooth.BluetoothSocket;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

public interface ISocket {
    void connect() throws IOException;
    void close() throws IOException;
    InputStream getInputStream() throws IOException;
    OutputStream getOutputStream() throws IOException;
}

