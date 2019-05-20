#pragma once
#include "../Program.h"

class Kaleidoscope : public Program {

public:
    void render(uint16_t zero_angle, int32_t rotation_rate) {
        using namespace Colors;

        uint16_t ms = millis();
        zero_angle -= ms;

        uint8_t angle_shift = (ms >> 9) & 0xF;
        if (angle_shift > 8) {
            angle_shift ^= 0xF;
        }
        angle_shift += 1;

        uint8_t segment_shift = (ms >> 10) & 0xF;
        if (segment_shift > 8) {
            segment_shift ^= 0xF;
        }

        for (int i = 0; i < NUM_PIXELS; i++) {
            uint16_t angle = zero_angle + Leds::get_angle(i);

            uint16_t segment_angle = angle & ((1 << 13) - 1);

            uint8_t inverse_dist = (uint8_t)~Leds::get_distance(i);

            // set black space between petals
            if (segment_angle < ((uint16_t)(inverse_dist) << segment_shift)) {
                Leds::set_color(i, black);
                continue;
            }

            // lower and raise petal angle
            if (segment_angle & (1 << 12)) {
                segment_angle = segment_angle - (1 << 12);
            } else {
                segment_angle = (1 << 12) - segment_angle;
            }
            if ((segment_angle >> angle_shift) > inverse_dist) {
                Leds::set_color(i, black);
                continue;
            }

            // set color of each petal
            switch ((angle >> 13) & 0x07) {
                case 0: Leds::set_color(i, red); break;
                case 1: Leds::set_color(i, orange); break;
                case 2: Leds::set_color(i, yellow); break;
                case 3: Leds::set_color(i, green); break;
                case 4: Leds::set_color(i, aqua); break;
                case 5: Leds::set_color(i, blue); break;
                case 6: Leds::set_color(i, cyan); break;
                case 7: Leds::set_color(i, purple); break;
            }
        }
    }
};