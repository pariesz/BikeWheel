#pragma once
#include "Arduino.h"
#include "Helpers.h"

namespace HallSensor {
    extern uint16_t angle;
    extern long interval_micros;
    extern int hallVal;
    void init(uint16_t offet);
    void update(void) OPTIMIZE;
}
