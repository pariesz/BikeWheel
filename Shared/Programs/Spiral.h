#pragma once
#include "../Program.h"

class Spiral : public Program {

private:
    uint16_t spiral_offset = 0;

public:
    void update(uint16_t frame_count, int32_t rotation_rate) override {
        spiral_offset += rotation_rate >> 8;
    }

    inline uint8_t get_brightness(uint16_t pos) {
        if (pos & (1 << 14)) {
            // invert the brightness
            return Adafruit_DotStar::gamma8(pos >> 6 ^ 255);
        } else {
            return Adafruit_DotStar::gamma8(pos >> 6);
        }
    }

    void render(uint16_t zero_angle) {
        uint32_t ms = millis();
        uint16_t spiral_angle = zero_angle + spiral_offset;
        uint16_t color_angle = zero_angle - (ms << 1);

        for (uint8_t i = 0; i < LEDS_COUNT; i++) {
            uint16_t pos = spiral_angle + Leds::get_angle(i) - ((uint16_t)Leds::get_distance(i) << 9);
            uint32_t color = Adafruit_DotStar::ColorHSV(color_angle + Leds::get_angle(i), 255, get_brightness(pos));
            Leds::set_color(i, color);
        }
    }
};