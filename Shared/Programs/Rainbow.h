#pragma once
#include "Program.h"

class Rainbow : public Program {
public:
    void render(uint16_t zero_angle) override {
        uint8_t time = millis() >> 6;

        for (int i = 0; i < LEDS_PER_STRIP; i++) {
            uint32_t color = Adafruit_DotStar::ColorHSV((i - time) * (0xFFFF / LEDS_PER_STRIP), 0xFF, 0xFF);

            for (int strip = 0; strip < LEDS_STRIPS_COUNT; strip++) {
                Leds::set_color((strip * LEDS_PER_STRIP) + i, color);
            }
        }
    }
};