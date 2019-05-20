#pragma once
#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#endif

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