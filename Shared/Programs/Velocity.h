#pragma once
#include "../Program.h"

class Velocity : public Program {

public:
    void render(uint16_t zero_angle, int32_t rotation_rate) {
        const uint8_t number_len = 2;  // ##
        const uint8_t decimal_len = 6; // .# KMH
        char number[6];                // ##.# + one extra for NUL
        char decimal[] = ".0 KMH";

        // c (wheel circumference) for 29in rim + 2.1in tire = 2288mm
        // v = rotation_rate * c
        // v(kmh) = (rotation_rate / 0xFFFF) * 2288mm * 60sec * 60min / (1000mm * 1000m)
        float v = abs(rotation_rate) / 7956.48795648795f;

        // ##.# (4 char width, 1 decimal precision)
        dtostrf(v, 4, 1, number);

        // Move the decimal digit
        decimal[1] = number[3];

        // rotate image
        zero_angle += 0x3000;

        uint32_t color = Colors::HslToRgb(v * 20, 255, 255);

        for (int i = 0, y = LEDS_PER_STRIP - 1; i < LEDS_COUNT; i++, y--) {
            if (y < 0) {
                y = LEDS_PER_STRIP - 1;
            }
            if (y > (FONT_HEIGHT << 1) - 1) {
                Leds::set_color(i, COLOR_BLACK);
                continue;
            }

            uint16_t angle = zero_angle + Leds::get_angle(i);

            // clear after the fisrt 135deg
            if (angle > 0x6000) {
                Leds::set_color(i, COLOR_BLACK);
                continue;
            }

            if (angle < 0x2000) {
                // render number in first 45deg (2ch per 45deg)
                uint16_t x = ((uint32_t)angle * (number_len << FONT_WIDTH_SHIFT)) >> 13;
                uint8_t ch_x = x & (FONT_WIDTH - 1);
                uint8_t ch_num = x >> FONT_WIDTH_SHIFT;
                char ch = number[ch_num];

                if (((pgm_read_byte(&(fontdata_8x8[(uint16_t)ch * FONT_HEIGHT + (y >> 1)])) >> ((FONT_WIDTH - 1) - ch_x)) & 1)) {
                    Leds::set_color(i, color);
                    continue;
                }

                
            } else {
                // render decimal from 45deg to 135deg (8ch per 90deg)
                // offset 8px down
                if (y < FONT_HEIGHT) {
                    Leds::set_color(i, COLOR_BLACK);
                    continue;
                }

                uint16_t x = (((uint32_t)angle - 0x2000) * (decimal_len << FONT_WIDTH_SHIFT)) >> 14;
                uint8_t ch_x = x & (FONT_WIDTH - 1);
                uint8_t ch_num = x >> FONT_WIDTH_SHIFT;
                char ch = decimal[ch_num];

                if (((pgm_read_byte(&(fontdata_8x8[(uint16_t)ch * FONT_HEIGHT + y - FONT_HEIGHT])) >> ((FONT_WIDTH - 1) - ch_x)) & 1)) {
                    Leds::set_color(i, ch_num < 2 ? color : COLOR_WHITE);
                    continue;
                }
            }

            Leds::set_color(i, COLOR_BLACK);
        }
    }
};