#pragma once
#include "../Program.h"

class RainbowText : public Program {

private:
    uint8_t label_len;
    const char *label;

public:
    RainbowText(uint8_t label_length, const char *label)
        : label(label)
        , label_len(label_length) {
    }

    void render(uint16_t zero_angle, int32_t rotation_rate) {
        const uint8_t min_y = (FONT_HEIGHT - 1);

        // transition colors based off rotation_rate
        uint32_t color = Colors::HslToRgb(millis() >> 5, 255, 255);

        for (int i = 0, y = PIXELS_PER_STRIP - 1; i < NUM_PIXELS; i++, y--) {
            if (y > min_y) {
                Leds::set_color(i, Colors::black);
                continue;
            }

            uint16_t angle = zero_angle + Leds::get_angle(i);

            uint16_t x = ((uint32_t)angle * (label_len << FONT_WIDTH_SHIFT)) >> 16;

            uint8_t ch_x = x & (FONT_WIDTH - 1);

            uint8_t ch_num = x >> FONT_WIDTH_SHIFT;

            // repeat the word
            if (ch_num >= label_len) {
                ch_num %= label_len;
            }

            uint8_t ch = label[ch_num];

            if (((pgm_read_byte(&(fontdata_8x8[(uint16_t)ch * FONT_HEIGHT + y])) >> ((FONT_WIDTH - 1) - ch_x)) & 1)) {
                Leds::set_color(i, color);
            } else {
                Leds::set_color(i, Colors::black);
            }

            if (y == 0) {
                y = PIXELS_PER_STRIP;
            }
        }
    }
};