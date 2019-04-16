#pragma once
#define OPTIMIZE __attribute__((optimize("O3")))

namespace HallSensor {
    extern uint16_t angle;
    extern long interval_micros;
    void init(uint16_t offet);
    void update(void) OPTIMIZE;
}
