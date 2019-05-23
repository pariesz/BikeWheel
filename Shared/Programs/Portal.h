#pragma once
#include "Program.h"

#define LINE_FRAME_MS 200
#define LINE_MIN_WIDTH 0x1FFF
#define LINE_MAX_WIDTH 0x2FFF
#define LINE_COLOR_CHANGE_RATE 3
#define LINE_ROTATION_RATE(ms) ms << 2

class Line {
    private:
        uint16_t start_angle = 0;
        uint16_t end_angle = 0;
        uint32_t color = 0;

    public:
        void reset(uint8_t hue) {
            start_angle = random(0, 0xFFFF);
            end_angle = start_angle + random(LINE_MIN_WIDTH, LINE_MAX_WIDTH);
            color = Colors::HslToRgb(hue, 0xFF, 0xFF);
        }

        bool show(uint16_t angle) {
            if (end_angle < start_angle) {
                // overflow
                if (angle > start_angle || angle < end_angle) {
                    return true;
                }
            } else {
                if (angle > start_angle && angle < end_angle) {
                    return true;
                }
            }
            return false;
        }

        inline uint32_t get_color() {
            return color;
        }
};

class Portal : public Program {
    private:
        Line lines[LEDS_PER_STRIP];
        uint8_t index = 0;
        uint8_t color_offset = random(0, 0xFF);

    public:
        void render(uint16_t zero_angle, int32_t rotation_rate) {
            uint32_t ms = millis();
            zero_angle -= LINE_ROTATION_RATE(ms);

            // timing
            static uint32_t ms_prev = ms;

            // create new stars
            if (ms - ms_prev > LINE_FRAME_MS) {
                ms_prev = ms;
            
                if (++index == LEDS_PER_STRIP) {
                    index = 0;
                }

                lines[index].reset(color_offset += LINE_COLOR_CHANGE_RATE);
            }

            // update leds
            for (uint8_t i = 0, y = 0; i < LEDS_COUNT; i++, y++) {
                if (y == LEDS_PER_STRIP) y = 0;

                int8_t i_star = y - index;

                if (i_star < 0) {
                    i_star = LEDS_PER_STRIP + i_star;
                }

                Line line = lines[i_star];

                Leds::set_color(i, line.show(zero_angle + Leds::get_angle(i)) ? line.get_color() : 0);
            }
        }
};