#pragma once
#include "Mocks/Arduino_Mock.h"

#define HALL_PIN 3
#define HALL_OFFSET 0

class HallSensor {
private:
    uint32_t us_rotation;
public:
    uint8_t value;  // This is where we record the OH137 Input
    uint16_t angle;
    int32_t rotation_rate; // number of uint16 rotations per second
public:
    HallSensor();
    void setup();
    void loop(bool reverse, uint32_t us, uint32_t us_diff) __attribute__((optimize("O3")));
};