#pragma once

#ifdef SIMULATION
#include "MPU6050_Mock.h"
#else
#include <MPU6050.h>
#endif

#include "Helpers.h"

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
    void loop() OPTIMIZE;

private:
    inline uint16_t get_rotation_rate_angle(uint32_t time_diff) OPTIMIZE;
    inline uint16_t get_acc_angle(int16_t* acc) OPTIMIZE;
};