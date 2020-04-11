#pragma once
#include "../Program.h"

class Kaleidoscope : public Program {

public:
    void render(uint16_t zero_angle) {
        uint16_t ms = millis();
        zero_angle -= ms;

        uint8_t angle_shift = 4 + ((ms >> 9) & 0x7);
        if (angle_shift > 8) {
            angle_shift = 12 - angle_shift;
        }

        uint8_t segment_shift = 4 + ((ms >> 9) & 0x7);
        if (segment_shift > 8) {
            segment_shift = 12 - segment_shift;
        }

        for (int i = 0; i < LEDS_COUNT; i++) {
            uint16_t angle = zero_angle + Leds::get_angle(i);

            uint16_t segment_angle = angle & ((1 << 13) - 1);

            uint8_t inverse_dist = (uint8_t)~Leds::get_distance(i);

            // set black space between petals
            if (segment_angle < ((uint16_t)(inverse_dist) << segment_shift)) {
                Leds::set_color(i, COLOR_BLACK);
                continue;
            }

            // lower and raise petal angle
            if (segment_angle & (1 << 12)) {
                segment_angle = segment_angle - (1 << 12);
            } else {
                segment_angle = (1 << 12) - segment_angle;
            }

            if ((segment_angle >> angle_shift) > inverse_dist) {
                Leds::set_color(i, COLOR_BLACK);
                continue;
            }

            // set color of each petal
            switch ((angle >> 13) & 0x07) {
                case 0: Leds::set_color(i, COLOR_RED); break;
                case 1: Leds::set_color(i, COLOR_ORANGE); break;
                case 2: Leds::set_color(i, COLOR_YELLOW); break;
                case 3: Leds::set_color(i, COLOR_GREEN); break;
                case 4: Leds::set_color(i, COLOR_AQUA); break;
                case 5: Leds::set_color(i, COLOR_BLUE); break;
                case 6: Leds::set_color(i, COLOR_CYAN); break;
                case 7: Leds::set_color(i, COLOR_PURPLE); break;
            }
        }
    }
};