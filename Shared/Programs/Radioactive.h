#pragma once
#include "../Program.h"

class Radioactive : public Program {

public:
    void render(uint16_t zero_angle) {
        for (int i = 0; i < LEDS_COUNT; i++) {
            if (Leds::get_distance(i) < Leds::min_dist + 20 || Leds::get_distance(i) > 235) {
                Leds::set_color(i, COLOR_YELLOW);
                continue;
            }

            uint16_t angle = zero_angle + Leds::get_angle(i);

            if ((angle > 0x1555 && angle < 0x3FFF)
            ||  (angle > 0x6AA9 && angle < 0x9553)
            ||  (angle > 0xBFFD && angle < 0xEAA7)) {
                Leds::set_color(i, COLOR_BLACK);

            } else {
                Leds::set_color(i, COLOR_YELLOW);
            }
        }
    }
};