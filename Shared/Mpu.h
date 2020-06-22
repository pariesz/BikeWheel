#pragma once
#include "Mocks/MPU6050_Mock.h"
#include "Logging.h"

class Mpu {
private:
    uint16_t angle;
    int32_t rotation_rate;
    MPU6050 mpu;
    uint8_t mpu_radius;
    boolean connected;

public:
    Mpu();
    void setup(int16_t offsets[6]);
    void update() __attribute__((optimize("O3")));
    uint16_t get_angle();
    int32_t get_rotation_rate();

private:
    inline uint16_t get_rotation_rate_angle(uint32_t time_diff) __attribute__((optimize("O3")));
    inline uint16_t get_acc_angle(int16_t* acc) __attribute__((optimize("O3")));
};