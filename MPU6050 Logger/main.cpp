#include <iostream>
#include <fstream>
#include <chrono>
#include <stdio.h>
#include <string.h>
#include "SerialPort.h"

int main() {
    using namespace std;
    using namespace std::chrono;

    char buffer[2048];
    time_point<steady_clock> *start = nullptr;
    SerialPort *arduino = nullptr;

    // open a file in write mode.
    ofstream fout;
    fout.open("output.csv");

    // csv header
    fout << "ms,hall,acc_x,acc_y,acc_z,gyro_x,gyro_y,gyro_z";

    while(true) {
        // connect / reconnect
        arduino = new SerialPort("\\\\.\\COM8", CBR_57600);

        if (arduino->isConnected()) {
            while (arduino->readSerialPort(buffer, sizeof(buffer))) {

                for (char *p = buffer; *p != NULL; p++) {
                    cout << *p;

                    if (*p >= 0x2D && *p <= 0x39) {
                        // only accept 0-9, minus
                        if (start) fout << *p;
                    }
                    else if (*p == '\t') {
                        // convert tabs to commas for csv
                        if (start) fout << ',';
                    }
                    else if (*p == '\n') {
                        // start no first new line
                        if (!start) start = &high_resolution_clock::now();
                        fout << *p;

                        // track time when newlines are read
                        //auto elapsed = high_resolution_clock::now() - *start;
                        //auto ms = duration_cast<microseconds>(elapsed).count();
                        //fout << *p << ms << ',';
                        //cout << ms << '\t';
                    }
                }
            }
        }

        // Disconnected, wait a second to recover
        Sleep(1000);
    }

    fout.close();

    return 0;
}