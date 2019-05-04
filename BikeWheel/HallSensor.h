#pragma once
#ifdef SIMULATION
#include "Arduino_Mock.h"
#else
#include "Arduino.h"
#endif
#include "Helpers.h"

class HallSensor {
private:
    uint32_t frame_us;
    uint32_t rotation_us;
    uint16_t offset; // offset the rotation relative to the y axis
    uint8_t value;  // This is where we record the OH137 Input
public:
    uint16_t angle;
    uint16_t rotations; // The number of 'accurate' rotations
    int32_t rotation_rate; // number of uint16 rotations per second
public:
    HallSensor(uint16_t offset);
    void setup();
    void loop(bool reverse) OPTIMIZE;
};