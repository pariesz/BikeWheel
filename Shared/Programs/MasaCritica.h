#pragma once
#include "../Program.h"

class MasaCritica : public Program {
private:
    uint32_t color;
    
public:
    MasaCritica()
        : color(0xFF0000) {
    }

    MasaCritica(uint8_t hue) 
        : color(Colors::HslToRgb(hue, 0xFF, 0xFF))  {
    }

    void render(uint16_t zero_angle, int32_t rotation_rate) {
        const char* label = " MASA CRITICA";
        const uint8_t label_len = 13;
        const uint8_t min_y = ((FONT_HEIGHT << 1) - 1);

        zero_angle += (1 << 14); // rotate -90 degrees

        for (int i = 0, y = PIXELS_PER_STRIP - 1; i < NUM_PIXELS; i++, y--) {
            if (y > min_y) {
                Leds::set_color(i, Colors::black);
                continue;
            }

            uint16_t angle = zero_angle + Leds::get_angle(i);

            uint16_t x = ((uint32_t)angle * (label_len << FONT_WIDTH_SHIFT)) >> 16;

            uint8_t ch_x = x & (FONT_WIDTH - 1);

            uint8_t ch_num = x >> FONT_WIDTH_SHIFT;

            char ch = label[ch_num];

            if (((pgm_read_byte(&(fontdata_8x8[(uint16_t)ch * FONT_HEIGHT + (y >> 1)])) >> ((FONT_WIDTH - 1) - ch_x)) & 1)) {
                Leds::set_color(i, ch_num > 5 ? Colors::white : color);
            } else {
                Leds::set_color(i, Colors::black);
            }

            if (y == 0) {
                y = PIXELS_PER_STRIP;
            }
        }
    }
};