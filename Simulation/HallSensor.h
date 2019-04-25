#pragma once
#include <chrono>
#include <iostream>
#include "arduino.h"
#include "SensorData.h"

namespace HallSensor {
    uint16_t angle = 0;

    long long interval_micros = 0;

    static uint16_t angle_offset = 0;
    
    int hallVal = HIGH; // This is where we record the OH137 Input

    static unsigned long long time_micros = 0;

    using namespace std::chrono;
    static time_point<steady_clock> start;
    long long micros() {
        auto elapsed = high_resolution_clock::now() - start;
        auto ms = duration_cast<microseconds>(elapsed);
        return ms.count();
    }

    void init(uint16_t offet) {
        start = high_resolution_clock::now();
        angle_offset = offet;
        time_micros = micros();
    }

    void update(void) {
        int val = SensorData::get().hall; // read OH137 Value

        if (hallVal == LOW && val == HIGH) {  // means magnetic field detected
            interval_micros = micros() - time_micros;
            time_micros = micros();
            angle = 0;

            //std::cout << "interval: " << interval_micros << std::endl;

            hallVal = HIGH;
            return;
        }

        if (hallVal == HIGH && val == LOW) {
            hallVal = val;
        }

        auto time_diff = micros() - time_micros;

        if (time_diff > interval_micros) {
            // Slowing down
            interval_micros = time_diff;
            angle = 65535;
            return;
        }

        angle = (
            (
                time_diff / (float)interval_micros // divide the difference to get a factor reperesenting the rotation
            ) * 65535 // scale the angle factor by uint16
        ) + angle_offset; // offset the rotation relative to the y axis
    }
}
