#pragma once
#include "../Images/NyanCat1.h"
#include "../Images/NyanCat2.h"
#include "../Program.h"

class NyanCat : public Program {

private:
    NyanCat1 frame1;
    NyanCat2 frame2;

public:
    void render(uint16_t zero_angle, int32_t rotation_rate) {
        uint8_t star_index = random(0, LEDS_COUNT - 1);

        Image* frame = millis() & (1 << 9) ? (Image*)&frame1 : &frame2;

        for (uint8_t i = 0; i < LEDS_COUNT; i++) {
            uint16_t angle = zero_angle + Leds::get_angle(i);

            uint32_t color = frame->get_led_color(i, rotation_rate < 0 ? ~angle : angle);

            if (i == star_index && color == 0) {
                double radians = (angle / (float)0xFFFF) * TWO_PI;

                int16_t y = Leds::get_distance(i) * cos(radians);

                // don't add stars over the cats body
                if (y < -0x70 || y > 0x80) {
                    color = COLOR_WHITE;
                }
            }

            Leds::set_color(i, color);
        }
    }
};