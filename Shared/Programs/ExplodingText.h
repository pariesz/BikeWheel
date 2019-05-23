#pragma once
#include "../Program.h"

class ExplodingText : public Program {

private:
    uint8_t hue = random(0, 0xFF);
    uint8_t label_length;
    const char *label;

public:
    ExplodingText(uint8_t label_length, const char *label)
        : label(label)
        , label_length(label_length) {
    }

    void render(uint16_t zero_angle, int32_t rotation_rate) {
        const uint32_t ms = millis();

        const int16_t brightness = ((ms >> 7 & 0x3F) << 4) - 350;

        if (brightness <= 0) {
            hue = random(0, 0xFF);
            return;
        }

        const int8_t y_offset = 64 - (ms >> 7 & 0x3F) - FONT_HEIGHT;

        const uint8_t y_min = FONT_HEIGHT + y_offset - 1;

        uint32_t color = Colors::HslToRgb(hue, 255, min(0xFF, brightness));

        zero_angle -= ms << 1;

        for (int i = 0, y = LEDS_PER_STRIP - 1; i < LEDS_COUNT; i++, y--) {
            if (y < 0) {
                y = LEDS_PER_STRIP - 1;
            }
            if (y < y_offset || y > y_min) {
                Leds::set_color(i, COLOR_BLACK);
                continue;
            }

            uint16_t angle = zero_angle + Leds::get_angle(i);

            uint16_t x = ((uint32_t)angle * (label_length << FONT_WIDTH_SHIFT)) >> 16;

            uint8_t ch_x = x & (FONT_WIDTH - 1);
            uint8_t ch_y = y - y_offset;
            uint8_t ch_num = x >> FONT_WIDTH_SHIFT;

            // repeat the word
            if (ch_num >= label_length) {
                ch_num %= label_length;
            }

            char ch = label[ch_num];

            if (((pgm_read_byte(&(fontdata_8x8[(uint16_t)ch * FONT_HEIGHT + ch_y])) >> ((FONT_WIDTH - 1) - ch_x)) & 1)) {
                Leds::set_color(i, color);
            } else {
                Leds::set_color(i, COLOR_BLACK);
            }
        }
    }
};