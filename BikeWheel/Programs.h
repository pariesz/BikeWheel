/*
    These functions below animate the LEDs in different ways as the wheel turns.
    Only one program is active at any time.
*/
#pragma once
#include ".\Pixels.h"
#define OPTIMIZE __attribute__((optimize("O3")))

namespace Programs {
    void spiral(uint16_t angle) OPTIMIZE;
    void set_color(uint32_t color) OPTIMIZE;
    void set_half_color(uint32_t color, uint16_t angle) OPTIMIZE;

#if 0
    void text12(const char *label) opts;
    void off() opts;
    void on() opts;
    void pacman() opts;
    void globe() opts;
    void signal(Pixels::RGB& signal) opts;
#endif
}

