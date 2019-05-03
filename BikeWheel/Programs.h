#pragma once

#ifdef _DEBUG
#include "Arduino_Mock.h"
#endif

#include "Font.h"
#include "Image.h"
#include "Leds.h"
#include "Colors.h"
#include "Helpers.h"

namespace Programs {
    using namespace Colors;

    void set_color(uint32_t color) {
        for (uint16_t i = 0; i < NUM_PIXELS; i++) {
            Leds::set_color(i, color);
        }
    }

    void spiral(uint16_t zero_angle) OPTIMIZE;
    void spiral(uint16_t zero_angle) {
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

            uint32_t color = HslToRgb((color_angle + Leds::get_angle(i)) >> 8, 255, brightness);

            Leds::set_color(i, color);
        }
    }

    void rainbow(uint16_t zero_angle) OPTIMIZE;
    static void rainbow(uint16_t zero_angle) {
        //uint16_t offset = Timers::millis() << 4;

        for (uint8_t i = 0; i < NUM_PIXELS; i++) {
            uint16_t angle = Leds::get_angle(i) + zero_angle; // +offset;
            uint32_t color = HslToRgb(angle >> 8, 255, 255);
            Leds::set_color(i, color);
        }
    }

    void flower(uint16_t zero_angle) OPTIMIZE;
    static void flower(uint16_t zero_angle) {
        static uint8_t segment_offset = 0;
        static uint8_t prev_segment = (zero_angle - Leds::get_angle(8)) >> 13;

        uint8_t current_segment = (zero_angle - Leds::get_angle(8)) >> 13;

        if (current_segment != prev_segment) {
            prev_segment = current_segment;
            segment_offset++;
        }

        for (int i = 0; i < NUM_PIXELS; i++) {
            uint16_t angle = zero_angle + Leds::get_angle(i);
            uint16_t segment_angle = angle & ((1 << 13) - 1);
            uint8_t inverse_dist = (uint8_t)~Leds::get_distance(i);

            if (segment_angle < ((uint16_t)(inverse_dist) << 4)) {
                Leds::set_color(i, black);
                continue;
            }

            // lower and raise
            if (segment_angle & (1 << 12)) {
                segment_angle = segment_angle - (1 << 12);
            } else {
                segment_angle = (1 << 12) - segment_angle;
            }

            if ((segment_angle >> 5) > inverse_dist) {
                Leds::set_color(i, black);
                continue;
            }

            uint8_t segment = angle >> 13;
            switch ((segment - (segment_offset >> 3)) & 0x07) {
                case 0: Leds::set_color(i, red); break;
                case 1: Leds::set_color(i, orange); break;
                case 2: Leds::set_color(i, yellow); break;
                case 3: Leds::set_color(i, green); break;
                case 4: Leds::set_color(i, aqua); break;
                case 5: Leds::set_color(i, blue); break;
                case 6: Leds::set_color(i, cyan); break;
                case 7: Leds::set_color(i, purple); break;
            }
        }
    }

    void radioactive(uint16_t zero_angle) OPTIMIZE;
    static void radioactive(uint16_t zero_angle) {
        for (int i = 0; i < NUM_PIXELS; i++) {
            if (Leds::get_distance(i) < Leds::min_dist + 20 || Leds::get_distance(i) > 235) {
                Leds::set_color(i, yellow);
                continue;
            }

            uint16_t angle = zero_angle + Leds::get_angle(i);

            if ((angle > 5461 && angle < 16384)
                || (angle > 27305 && angle < 38227)
                || (angle > 49149 && angle < 60071)) {
                Leds::set_color(i, black);
            } else {
                Leds::set_color(i, yellow);
            }
        }
    }

    void umbrella(uint16_t zero_angle) OPTIMIZE;
    static void umbrella(uint16_t zero_angle) {
        zero_angle -= (1 << 12); // rotate 1/16 turn

        for (int i = 0; i < NUM_PIXELS; i++) {
            uint16_t angle = zero_angle + Leds::get_angle(i);
            uint8_t segment = angle >> 13;
            uint16_t segment_angle = angle & ((1 << 13) - 1);
            uint8_t inverse_dist = (uint8_t)~Leds::get_distance(i);

            if (segment_angle < 500 + ((uint16_t)(inverse_dist) << 3)) {
                Leds::set_color(i, black);
                continue;
            }

            if (segment_angle & (1 << 12)) {
                segment_angle = (1 << 13) - segment_angle;
            }

            if ((segment_angle >> 7) > inverse_dist) {
                Leds::set_color(i, black);
                continue;
            }

            Leds::set_color(i, segment & 1 ? white : red);
        }
    }

    void rainbow_text(uint16_t zero_angle, uint8_t label_len, const char *label) OPTIMIZE;
    static void rainbow_text(uint16_t zero_angle, uint8_t label_len, const char *label) {
        const uint8_t ch_width = 8;
        const uint8_t ch_width_shift = 3;
        const uint8_t ch_height = 8;
        const uint8_t min_y = (ch_height - 1);

        // transition colors based off rotation_rate
        uint32_t color = HslToRgb(millis() >> 5, 255, 255);

        for (int i = 0, y = PIXELS_PER_STRIP - 1; i < NUM_PIXELS; i++, y--) {
            if (y > min_y) {
                Leds::set_color(i, black);
                continue;
            }

            uint16_t angle = zero_angle + Leds::get_angle(i);

            uint16_t x = ((uint32_t)angle * (label_len << ch_width_shift)) >> 16;

            uint8_t ch_x = x & (ch_width - 1);

            uint8_t ch_num = x >> ch_width_shift;

            // repeat the word
            if (ch_num >= label_len) {
                ch_num %= label_len;
            }

            uint8_t ch = label[ch_num];

            if (((pgm_read_byte(&(fontdata_8x8[(uint16_t)ch * ch_height + y])) >> ((ch_width - 1) - ch_x)) & 1)) {
                Leds::set_color(i, color);
            } else {
                Leds::set_color(i, black);
            }

            if (y == 0) {
                y = PIXELS_PER_STRIP;
            }
        }
    }

    void masa_critica(uint16_t zero_angle) OPTIMIZE;
    static void masa_critica(uint16_t zero_angle) {
        const uint8_t ch_width = 8;
        const uint8_t ch_width_shift = 3;
        const uint8_t ch_height = 8;
        const char* label = " MASA CRITICA";
        const uint8_t label_len = 13;
        const uint8_t min_y = ((ch_height << 1) - 1);

        zero_angle += (1 << 14); // rotate -90 degrees

        for (int i = 0, y = PIXELS_PER_STRIP - 1; i < NUM_PIXELS; i++, y--) {
            if (y > min_y) {
                Leds::set_color(i, black);
                continue;
            }

            uint16_t angle = zero_angle + Leds::get_angle(i);

            uint16_t x = ((uint32_t)angle * (label_len << ch_width_shift)) >> 16;

            uint8_t ch_x = x & (ch_width - 1);

            uint8_t ch_num = x >> ch_width_shift;

            // repeat the word
            if (ch_num >= label_len) {
                ch_num %= label_len;
            }

            char ch = label[ch_num];

            if (((pgm_read_byte(&(fontdata_8x8[(uint16_t)ch * ch_height + (y >> 1)])) >> ((ch_width - 1) - ch_x)) & 1)) {
                Leds::set_color(i, ch_num > 5 ? white : red);
            } else {
                Leds::set_color(i, black);
            }

            if (y == 0) {
                y = PIXELS_PER_STRIP;
            }
        }
    }
}
