#ifdef SIMULATION
#include "Arduino_Mock.h"
#endif

#include "Font.h"
#include "Image.h"
#include "Leds.h"
#include "Colors.h"
#include "Programs.h"

namespace Programs {
    using namespace Colors;

    void set_color(uint32_t color) {
        for (uint16_t i = 0; i < NUM_PIXELS; i++) {
            Leds::set_color(i, color);
        }
    }

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

    void kaleidoscope(uint16_t zero_angle) {

        uint16_t ms = millis();
        zero_angle -= ms;

        uint8_t angle_shift = (ms >> 9) & 0xF;
        if (angle_shift > 8) {
            angle_shift ^= 0xF;
        }
        angle_shift += 1;

        uint8_t segment_shift = (ms >> 10) & 0xF;
        if (segment_shift > 8) {
            segment_shift ^= 0xF;
        }

        for (int i = 0; i < NUM_PIXELS; i++) {
            uint16_t angle = zero_angle + Leds::get_angle(i);

            uint16_t segment_angle = angle & ((1 << 13) - 1);

            uint8_t inverse_dist = (uint8_t)~Leds::get_distance(i);

            // set black space between petals
            if (segment_angle < ((uint16_t)(inverse_dist) << segment_shift)) {
                Leds::set_color(i, black);
                continue;
            }

            // lower and raise petal angle
            if (segment_angle & (1 << 12)) {
                segment_angle = segment_angle - (1 << 12);
            } else {
                segment_angle = (1 << 12) - segment_angle;
            }
            if ((segment_angle >> angle_shift) > inverse_dist) {
                Leds::set_color(i, black);
                continue;
            }

            // set color of each petal
            switch ((angle >> 13) & 0x07) {
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

    void radioactive(uint16_t zero_angle) {
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

    const uint8_t ch_width = 8;
    const uint8_t ch_width_shift = 3;
    const uint8_t ch_height = 8;

    void rainbow_text(uint16_t zero_angle, uint8_t label_len, const char *label) {
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

    void masa_critica(uint16_t zero_angle) {
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

    void velocity(uint16_t zero_angle, int32_t rotation_rate) {
        const uint8_t number_len = 4; // ##.#
        const uint8_t unit_len = 4; // km/h
        char number[6]; // one extra for NUL
        const char* unit = "km/h";

        // c (wheel circumference) for 29in rim * 2.1 tire = 2288mm
        // v = rotation_rate * c
        // kmh (conversion) = 60sec * 60min * v / int16_max * 1000mm * 1000m
        // v = rotation_rate * (60 * 60 * 2288) / (1 << 16) * 1000 * 1000
        float v = abs(rotation_rate) / 7956.48795648795f;

        // 5 char width, 1 decimal precision
        dtostrf(v, number_len, 1, number);

        // rotate -67.5 degrees
        zero_angle += 12288;

        uint32_t color = HslToRgb(v * 20, 255, 255);

        for (int i = 0, y = PIXELS_PER_STRIP - 1; i < NUM_PIXELS; i++, y--) {
            if (y < 0) {
                y = PIXELS_PER_STRIP - 1;
            }
            if (y > (ch_height << 1) - 1) {
                Leds::set_color(i, black);
                continue;
            }

            uint16_t angle = zero_angle + Leds::get_angle(i);

           if (angle > 24576) {
               Leds::set_color(i, black);
               continue;
           }

           if (angle > (1 << 14)) {

               // offset 8px down
               if (y < ch_height) {
                   Leds::set_color(i, black);
                   continue;
               }

               // 4 chars over 45 degrees
               uint16_t x = (((uint32_t)angle - (1 << 14)) * (unit_len << ch_width_shift)) >> 13;
               uint8_t ch_x = x & (ch_width - 1);
               uint8_t ch_num = x >> ch_width_shift;
               char ch = unit[ch_num];

               if (((pgm_read_byte(&(fontdata_8x8[(uint16_t)ch * ch_height + y - ch_height])) >> ((ch_width - 1) - ch_x)) & 1)) {
                   Leds::set_color(i, white);
                   continue;
               }
           } else {

               // 3 chars over 9 degrees
               uint16_t x = ((uint32_t)angle * (number_len << ch_width_shift)) >> 14;
               uint8_t ch_x = x & (ch_width - 1);
               uint8_t ch_num = x >> ch_width_shift;
               char ch = number[ch_num];

               if (((pgm_read_byte(&(fontdata_8x8[(uint16_t)ch * ch_height + (y >> 1)])) >> ((ch_width - 1) - ch_x)) & 1)) {
                   Leds::set_color(i, color);
                   continue;
               }
           }

           Leds::set_color(i, black);
        }
    }
}