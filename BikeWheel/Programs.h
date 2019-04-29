#pragma once
#include <math.h>
#include <avr/pgmspace.h>
#include "./Timers.h"
#include "./Pixels.h"
#include "./Programs.h"
#include "./Debug.h"
#include "./Font.h"

#define DEGS_TO_ANGLE(x) (uint16_t)((x) / 180.0f * (1uLL << 15))
#define DEGS_PER_S_TO_RATE(x) (uint16_t)((x) * 16.4f)

namespace Programs {
    using namespace Pixels;

    void set_color(uint32_t color) {
        for (uint16_t i = 0; i < NUM_PIXELS; i++) {
            leds.setPixelColor(i, color);
        }
    }

#ifdef DEBUG
    void color_segments(uint16_t zero_angle) {
        for (uint8_t i = 0; i < NUM_PIXELS; i++) {
            uint16_t angle = zero_angle + positions[i].angle;

            switch (angle >> 14) {
                case 0:
                    leds.setPixelColor(i, 0xFF0000);
                    break;
                case 1:
                    leds.setPixelColor(i, 0x00FF00);
                    break;
                case 2:
                    leds.setPixelColor(i, 0x0000FF);
                    break;
                default:
                    leds.setPixelColor(i, 0x000000);
                    break;
            }
        }
    }

    /* Moving spiral shape */
    void spiral(uint16_t zero_angle) {
        uint16_t millis = Timers::millis();

        for (uint8_t i = 0; i < NUM_PIXELS; i++) {
            uint16_t angle = zero_angle + positions[i].angle;


            int pos = angle - millis + ((uint32_t)positions[i].dist << 17) / 255;

            uint8_t brightness = pos >> 6;

            if (pos & (1 << 14)) {
                // invert the brightness
                brightness ^= 255;
            }

            leds.setPixelColor(i, 0, 0, brightness);
        }
    }
#endif

    static void rainbow_pixel(uint8_t i, uint16_t angle) {
        if (angle < 21845) {
            uint16_t color = (((uint32_t)angle) << 8) / 21845;
            leds.setPixelColor(i, 255 - color, color, 0);

        }
        else if (angle < 43690) {
            uint16_t color = (((uint32_t)angle - 21845) << 8) / 21845;
            leds.setPixelColor(i, 0, 255 - color, color);

        }
        else if (angle < 65535) {
            uint16_t color = (((uint32_t)angle - 43690) << 8) / 21845;
            leds.setPixelColor(i, color, 0, 255 - color);
        }
    }

    static void rainbow(uint16_t zero_angle) {
        //uint16_t offset = Timers::millis() << 4;
        for (uint8_t i = 0; i < NUM_PIXELS; i++) {
            uint16_t angle = zero_angle + positions[i].angle; // +offset;
            rainbow_pixel(i, angle);
        }
    }

    /* Display hardcoded text */
    static void text(uint16_t zero_angle, uint8_t label_len, const char *label) {
        static const int ch_width = 8;
        static const int ch_width_shift = 3;
        static const int ch_height = 8;

        uint16_t color_offset = (uint16_t)millis() << 2;

        for (uint8_t i = 0, y = 0; i < NUM_PIXELS; i++, y++) {
            uint8_t ch_y = ~((y % PIXELS_PER_STRIP) - PIXELS_PER_STRIP);

            if (ch_y > (ch_height - 1)) {
                leds.setPixelColor(i, 0, 0, 0);
                continue;
            }

            uint16_t angle = zero_angle + positions[i].angle;

            /* For len == 12 could use two shifts and a sum... */
            /* Except shifts on AVR kinda suck too. */
            uint16_t x = ((uint32_t)angle * (label_len << ch_width_shift)) >> 15;

            uint8_t ch_x = x & (ch_width - 1);

            uint8_t ch_num = x >> ch_width_shift;

            // repeat the word
            if (ch_num >= label_len) {
                ch_num %= label_len;
            }

            uint8_t ch = label[ch_num];

            if (((pgm_read_byte(&fontdata_8x8[(uint16_t)ch * ch_height + ch_y]) >> ((ch_width - 1) - ch_x)) & 1)) {
                rainbow_pixel(i, angle + color_offset);
            }
            else {
                leds.setPixelColor(i, 0, 0, 0);
            }
        }
    }
}

