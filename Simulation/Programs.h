#pragma once
#include "Arduino.h"
#include "Timers.h"
#include "Font.h"

#define DEGS_TO_ANGLE(x) (uint16_t)((x) / 360.0f * (1uL << 16))
#define DEGS_PER_S_TO_RATE(x) (uint16_t)((x) * 16.4f)

namespace Programs {
    using namespace Pixels;

    void rainbow_pixel(uint8_t i, uint16_t angle);

    void set_color(uint32_t color) {
        for (uint16_t i = 0; i < NUM_PIXELS; i++) {
            leds.setPixelColor(i, color);
        }
    }

    void set_half_color(uint32_t color, uint16_t angle) {
        for (uint8_t i = 0; i < NUM_PIXELS; i++) {
            uint16_t pixel_angle = angle + positions[i].angle;
            leds.setPixelColor(i, pixel_angle > 16384 && pixel_angle < 49152 ? color : 0);
        }
    }

    /* Moving spiral shape */
    void spiral(uint16_t zero_angle) {
        uint16_t millis = Timers::millis();

        for (uint8_t i = 0; i < NUM_PIXELS; i++) {
            uint16_t angle = zero_angle - positions[i].angle;


            int pos = angle - millis + ((uint32_t)positions[i].dist << 17) / 255;

            uint8_t brightness = pos >> 6;

            if (pos & (1 << 14)) {
                // invert the brightness
                brightness ^= 255;
            }

            leds.setPixelColor(i, 0, 0, brightness);
        }
    }

    static void pacman(uint16_t zero_angle) {
        uint16_t subsec = Timers::millis() >> 5;
        uint8_t halfsec = subsec >> 4;
        bool open = halfsec & 1;

        if (open) {
            /* Pacman mouth open */
            for (uint8_t i = 0, x = 0; i < NUM_PIXELS; i++, x++) {
                uint16_t angle = zero_angle + positions[i].angle;

                if (x == 15)
                    x = 0;

                if (angle > DEGS_TO_ANGLE(330) || angle < DEGS_TO_ANGLE(40)) {
                    uint8_t dist = x - (15 - ((subsec + 8) & 15));
                    uint16_t adist = 32768 / ((positions[i].dist >> 3) + 1);
                    uint16_t y = angle - (DEGS_TO_ANGLE(0) - adist);
                    
                    if (dist < 3 && y < adist) {
                        leds.setPixelColor(i, 255, 255, 255);
                    }
                    else {
                        leds.setPixelColor(i, 0, 0, 0);
                    }
                }
                else {
                    leds.setPixelColor(i, 255, 255, 0);
                }
            }
        } else {
            /* Pacman mouth closed */
            for (uint8_t i = 0; i < NUM_PIXELS; i++) {
                uint16_t angle = zero_angle + positions[i].angle;

                if (angle > DEGS_TO_ANGLE(352) || angle < DEGS_TO_ANGLE(8)) {
                    leds.setPixelColor(i, 0, 0, 0);
                }
                else {
                    leds.setPixelColor(i, 255, 255, 0);
                }
            }
        }
    }

    static void rainbow(uint16_t zero_angle) {
        //uint16_t offset = Timers::millis() << 4;

        for (uint8_t i = 0; i < NUM_PIXELS; i++) {
            uint16_t angle = zero_angle + positions[i].angle; // +offset;
            rainbow_pixel(i, angle);
        }
    }

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

    /* Display hardcoded text */
    static void text(uint16_t zero_angle, uint8_t label_len, const char *label) {
        static const int ch_width = 8;
        static const int ch_width_shift = 3;
        static const int ch_height = 8;

        uint16_t color_offset = (uint16_t)Timers::millis() << 2;

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

            if (((pgm_read_byte(fontdata_8x8[(uint16_t)ch * ch_height + ch_y]) >> ((ch_width - 1) - ch_x)) & 1)) {
                rainbow_pixel(i, angle + color_offset);
            }
            else {
                leds.setPixelColor(i, 0, 0, 0);
            }
        }
    }

    static void sensorTest(uint16_t zero_angle, int hallVal) {
        for (uint8_t i = 0; i < NUM_PIXELS; i++) {
            if (positions[i].dist < 250) {
                leds.setPixelColor(i, 0, 0, 0);
                continue;
            }

            if (hallVal == LOW) {
                leds.setPixelColor(i, 255, 255, 255);
                continue;
            }

            uint16_t angle = zero_angle + positions[i].angle;

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
    }
}
