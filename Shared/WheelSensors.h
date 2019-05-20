#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
#include <MPU6050.h>
#else
#include "MPU6050_Mock.h"
#endif

class WheelSensors {
public:
    uint16_t angle;
    int32_t rotation_rate;

private:
    MPU6050 mpu;
    uint8_t mpu_radius;

public:
    WheelSensors();
    void setup();
    void update() __attribute__((optimize("O3")));

private:
    inline uint16_t get_rotation_rate_angle(uint32_t time_diff) __attribute__((optimize("O3")));
    inline uint16_t get_acc_angle(int16_t* acc) __attribute__((optimize("O3")));
};