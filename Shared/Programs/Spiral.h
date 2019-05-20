#pragma once
#include "../Program.h"

class Spiral : public Program {

public:
    void render(uint16_t zero_angle, int32_t rotation_rate) {
        uint32_t ms = millis();
        uint16_t spiral_angle = zero_angle + (ms << 4);
        uint16_t color_angle = zero_angle - (ms << 3);

        for (uint8_t i = 0; i < NUM_PIXELS; i++) {
            uint16_t pos = spiral_angle + Leds::get_angle(i) - ((uint16_t)Leds::get_distance(i) << 9);

            uint8_t brightness = pos >> 6;

            if (pos & (1 << 14)) {
                // invert the brightness
                brightness ^= 255;
            }

            // mix angle and dist
            //uint8_t hue = (angle >> 8) + ((pos >> 9) & 0xC0);

            uint32_t color = Colors::HslToRgb((color_angle + Leds::get_angle(i)) >> 8, 255, brightness);
            Leds::set_color(i, color);
        }
    }
};