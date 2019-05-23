#pragma once
#include "../Program.h"

class TestSegments : public Program {
public:
    void render(uint16_t zero_angle, int32_t rotation_rate) {
        using namespace Colors;
        using namespace Leds;

        for (uint8_t i = 0; i < LEDS_COUNT; i++) {
            int num = i + 1;

            if (num <= 34) {
                set_color(i, white);
                continue;
            }
            if (num % 36 && (num + 1) % 36) {
                set_color(i, black);
                continue;
            }
            //if (hallVal == LOW) {
            //    set_color(i, white);
            //    continue;
            //}

            uint16_t angle = zero_angle + get_angle(i);

            switch (angle >> 14) {
                case 0:  set_color(i, red); break;
                case 1:  set_color(i, green); break;
                case 2:  set_color(i, blue); break;
                default: set_color(i, black); break;
            }
        }
    }
};