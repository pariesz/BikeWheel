#pragma once
#include "Program.h"

#define LINE_FRAME_SKIP 3
#define LINE_MIN_WIDTH 0x1FFF
#define LINE_MAX_WIDTH 0x2FFF
#define LINE_COLOR_CHANGE_RATE 765
#define LINE_ROTATION_RATE 100

class Line {
    private:
        uint16_t start_angle = random(0, 0xFFFF);
        uint16_t end_angle = start_angle + random(LINE_MIN_WIDTH, LINE_MAX_WIDTH);
        uint32_t color;

    public:
        Line() 
            : color(0) { 
        }

        Line(uint16_t hue) 
            : color(Adafruit_DotStar::ColorHSV(hue)) {
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
        uint16_t color_offset = random(0, 0xFFFF);
        uint16_t angle_offset = 0;
        uint32_t ms_prev = millis();

    public:
        void update(uint16_t frame_count, int32_t rotation_rate) override {
            angle_offset += LINE_ROTATION_RATE;

            // create new stars
            if (frame_count % LINE_FRAME_SKIP == 0) {
                if (++index == LEDS_PER_STRIP) {
                    index = 0;
                }
                lines[index] = Line(color_offset += LINE_COLOR_CHANGE_RATE);
            }
        }

        void render(uint16_t zero_angle) {
            zero_angle += angle_offset;

            Leds::clear();

            // update leds
            for (uint8_t i = 0, y = 0; i < LEDS_COUNT; i++, y++) {
                if (y == LEDS_PER_STRIP) y = 0;

                int8_t i_star = y - index;

                if (i_star < 0) {
                    i_star = LEDS_PER_STRIP + i_star;
                }

                Line line = lines[i_star];

                if (line.show(zero_angle + Leds::get_angle(i))) {
                    Leds::set_color(i, line.get_color());
                }
            }
        }
};