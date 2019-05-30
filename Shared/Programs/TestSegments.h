#pragma once
#include "../Program.h"

class TestSegments : public Program {
public:
    void render(uint16_t zero_angle) {
        for (uint8_t i = 0; i < LEDS_COUNT; i++) {
            int num = i + 1;

            if (num <= 34) {
                Leds::set_color(i, COLOR_WHITE);
                continue;
            }
            if (num % 36 && (num + 1) % 36) {
                Leds::set_color(i, COLOR_BLACK);
                continue;
            }
            //if (hallVal == LOW) {
            //    set_color(i, white);
            //    continue;
            //}

            uint16_t angle = zero_angle + Leds::get_angle(i);

            switch (angle >> 14) {
                case 0:  Leds::set_color(i, COLOR_RED); break;
                case 1:  Leds::set_color(i, COLOR_GREEN); break;
                case 2:  Leds::set_color(i, COLOR_BLUE); break;
                default: Leds::set_color(i, COLOR_BLACK); break;
            }
        }
    }
};