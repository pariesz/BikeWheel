/*
* Author: Manash Kumar Mandal
* Modified Library introduced in Arduino Playground which does not work
* This works perfectly
* LICENSE: MIT
*/

#include "SerialPort.h"

SerialPort::SerialPort(const char *portName, int baudRate) {
    printf("CONNECTING...");

    this->connected = false;

    this->handler = CreateFileA(
        static_cast<LPCSTR>(portName),
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    if (this->handler == INVALID_HANDLE_VALUE) {
        auto error = GetLastError();

        if (error == ERROR_FILE_NOT_FOUND) {
            printf("Handle was not attached. Reason: %s not available\n", portName);
        }
        else {
            printf("Error: %d\n", error);
        }

        return;
    }

    DCB dcbSerialParameters = { 0 };

    if (!GetCommState(this->handler, &dcbSerialParameters)) {
        printf("Failed to get current serial parameters\n");
        return;
    }

    dcbSerialParameters.BaudRate = baudRate;
    dcbSerialParameters.ByteSize = 8;
    dcbSerialParameters.StopBits = ONESTOPBIT;
    dcbSerialParameters.Parity = NOPARITY;
    dcbSerialParameters.fDtrControl = DTR_CONTROL_ENABLE;

    if (!SetCommState(handler, &dcbSerialParameters)) {
        printf("Could not set Serial port parameters\n");
        return;
    }

    COMMTIMEOUTS timeouts = { 0 };

    timeouts.ReadIntervalTimeout = 50; // in milliseconds
    timeouts.ReadTotalTimeoutConstant = 50; // in milliseconds
    timeouts.ReadTotalTimeoutMultiplier = 10; // in milliseconds
    timeouts.WriteTotalTimeoutConstant = 50; // in milliseconds
    timeouts.WriteTotalTimeoutMultiplier = 10; // in milliseconds

    if (!SetCommTimeouts(handler, &timeouts)) {
        printf("Could not set Serial port timeoouts\n");
        return;
    }

    this->connected = true;
    PurgeComm(this->handler, PURGE_RXCLEAR | PURGE_TXCLEAR);
    Sleep(ARDUINO_WAIT_TIME);
    printf("Connected\n");
}

SerialPort::~SerialPort() {
    if (this->connected) {
        this->connected = false;
        CloseHandle(this->handler);
        printf("Disconnected\n");
    }
}

int SerialPort::readSerialPort(char *buffer, unsigned int buf_size) {
    DWORD bytesRead;

    ClearCommError(this->handler, &this->errors, &this->status);

    memset(buffer, 0, buf_size);

    if (this->status.cbInQue == 0) {
        return true;
    }
    
    if (ReadFile(this->handler, buffer, min(buf_size, this->status.cbInQue), &bytesRead, NULL)) {
        return true;
    }

    return false;
}

bool SerialPort::writeSerialPort(char *buffer, unsigned int buf_size) {
    DWORD bytesSend;

    if (!WriteFile(this->handler, (void*)buffer, buf_size, &bytesSend, 0)) {
        ClearCommError(this->handler, &this->errors, &this->status);
        return false;
    }
    else {
        return true;
    }
}

bool SerialPort::isConnected() {
    if (!ClearCommError(this->handler, &this->errors, &this->status)) {
        this->connected = false;
    }
    return this->connected;
}
