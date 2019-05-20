#pragma once
#include "../Program.h"

class Radioactive : public Program {

public:
    void render(uint16_t zero_angle, int32_t rotation_rate) {
        for (int i = 0; i < NUM_PIXELS; i++) {
            if (Leds::get_distance(i) < Leds::min_dist + 20 || Leds::get_distance(i) > 235) {
                Leds::set_color(i, Colors::yellow);
                continue;
            }

            uint16_t angle = zero_angle + Leds::get_angle(i);

            if ((angle > 5461  && angle < 16384)
            ||  (angle > 27305 && angle < 38227)
            ||  (angle > 49149 && angle < 60071)) {
                Leds::set_color(i, Colors::black);

            } else {
                Leds::set_color(i, Colors::yellow);
            }
        }
    }
};