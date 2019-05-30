#pragma once
#include "Program.h"

class Specs : public Program {
public:
    void render(uint16_t zero_angle) {
        uint8_t spec_index = random(0, LEDS_COUNT - 1);

        for (uint8_t i = 0; i < LEDS_COUNT; i++) {
            Leds::set_color(i, i == spec_index ? COLOR_WHITE : COLOR_BLACK);
        }
    }
};
