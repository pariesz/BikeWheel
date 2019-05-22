#pragma once
#include "Program.h"

#define STAR_BIRTH_MS 200
#define STAR_GROWTH_RATE(ms_diff) ((ms_diff) << 3)
#define STAR_BRIGHTNESS_SHIFT 7

class Portal : public Program {

private:
    struct Line {
        uint32_t color = 0;
        uint16_t start_angle = 0;
        uint16_t end_angle = 0;
    };

    Line lines[PIXELS_PER_STRIP];
    uint8_t index = 0;
    uint8_t color_offset = random(0, 0xFF);

public:
    void render(uint16_t zero_angle, int32_t rotation_rate) {
        uint32_t ms = millis();
        zero_angle -= ms << 2;

        // timing
        static uint32_t ms_prev_birth = ms;

        // create new stars
        if (ms - ms_prev_birth > STAR_BIRTH_MS) {
            ms_prev_birth = ms;
            
            if (++index == PIXELS_PER_STRIP) {
                index = 0;
            }

            Line* line = &lines[index];

            line->start_angle = random(0, 0xFFFF);
            line->end_angle = line->start_angle + random(0x1FFF, 0x2FFF);
            line->color = Colors::HslToRgb(color_offset += 3, 0xFF, 0xFF);
        }

        // update leds
        for (uint8_t i = 0, y = 0; i < NUM_PIXELS; i++, y++) {
            if (y == PIXELS_PER_STRIP) y = 0;

            int8_t i_star = y - index;

            if (i_star < 0) {
                i_star = PIXELS_PER_STRIP + i_star;
            }

            Line line = lines[i_star];

            uint16_t angle = zero_angle + Leds::get_angle(i);

            if (line.end_angle < line.start_angle) {
                // overflow
                if (angle > line.start_angle || angle < line.end_angle) {
                    Leds::set_color(i, line.color);
                    continue;
                }
            } else {
                if (angle > line.start_angle && angle < line.end_angle) {
                    Leds::set_color(i, line.color);
                    continue;
                }
            }

            Leds::set_color(i, 0);
        }
    }
};