#pragma once
#include "Mocks/Arduino_Mock.h"
#include "SensorData.h"

class MockData : public SensorData {
private:
    uint16_t angle = 0;
    int16_t gyro_y = -8000; // Mock sensor in reverse
    int8_t acceleration;

public:
    MockData(int8_t acceleration = 0)
        : acceleration(acceleration) {
    }

    bool try_get_next(DataLine &dl) override {
        static int us_prev = micros();
        int us = micros();
        int diff = us - us_prev;
        us_prev = us;

        gyro_y += acceleration;

        angle += gyro_y
            * ((float)diff / 1000000) // us to seconds
            * (2000 / 360.0f)         // MPU +-2000 scale to 1 rotation
            * 2;                      // signed 15 bit to unsigned 16 bit

        float radians = (angle / (float)65535) * TWO_PI;

        dl.us = 6000;
        dl.hall = angle < 500 ? LOW : HIGH;
        dl.acc_x = sin(radians) * ((1 << 12) - 1);
        dl.acc_y = 0;
        dl.acc_z = ~(uint16_t)(cos(radians) * ((1 << 12) - 1));
        dl.gyro_x = 0;
        dl.gyro_y = gyro_y;
        dl.gyro_z = 0;

        return true;
    }
};