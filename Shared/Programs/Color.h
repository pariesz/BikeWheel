#pragma once
#include "../Program.h"

class Color : public Program {

private:
    uint32_t color;

public:
    Color(uint32_t color) 
        : color(color) {
    }

    void render(uint16_t zero_angle, int32_t rotation_rate) {
        for (uint16_t i = 0; i < LEDS_COUNT; i++) {
            Leds::set_color(i, color);
        }
    }
};