#pragma once
#include "Program.h"

#define STAR_COUNT 16
#define STAR_BIRTH_INDEX(ms) (((ms) >> 9) & 0xF) // bitmask needs to be same size as STAR_COUNT
#define STAR_GROWTH_RATE(ms_diff) ((ms_diff) << 3)
#define STAR_FADE(length) (length) >> 7
#define STAR_COLOR_CHANGE_RATE 3

class Star {
    private:
        uint16_t start_angle = random(0, 0xFFFF);
        uint16_t length = 0;
        uint8_t y = random(0, LEDS_PER_STRIP - 1);
        uint8_t hue = 0;

        inline uint32_t get_color(uint16_t length) {
            uint8_t fade = STAR_FADE(length);
            return fade >= 0xFF ? 0 : Colors::HslToRgb(hue, 0xFF, 0xFF - fade);
        }

    public:
        Star() 
            : y(0xFF) {
        }

        Star(uint8_t hue) 
            : hue(hue) {
        }

        void update(uint8_t ms) {
            length += STAR_GROWTH_RATE(ms);
        }

        bool show(uint8_t y, uint16_t angle, uint32_t &out_color) {
            if (this->y == y) {
                uint32_t end_angle = start_angle + (uint32_t)length;

                if (end_angle > 0xFFFF) {
                    // overflow
                    if (angle > start_angle) {
                        out_color = get_color(end_angle - angle);
                        return true;

                    } else if (angle < (uint16_t)end_angle) {
                        out_color = get_color((uint16_t)end_angle - angle);
                        return true;
                    }
                } else {
                    if (angle > start_angle && angle < end_angle) {
                        out_color = get_color(end_angle - angle);
                        return true;
                    }
                }
            }
            return false;
        }
};

class ShootingStars : public Program {

private:
    Star stars[STAR_COUNT];
    uint8_t index = 0;
    uint8_t color_offset = random(0, 0xFF);

public:
    void render(uint16_t zero_angle, int32_t rotation_rate) {
        // timing
        uint32_t ms = millis();
        static uint32_t ms_prev = ms;
        uint8_t ms_diff = ms - ms_prev;
        ms_prev = ms;

        // create new stars
        if (index != STAR_BIRTH_INDEX(ms)) {
            stars[index = STAR_BIRTH_INDEX(ms)] = Star(color_offset += STAR_COLOR_CHANGE_RATE);
        }

        // update existing stars
        for (uint8_t i = 0; i < STAR_COUNT; i++) {
            stars[i].update(ms_diff);
        }

        // update leds
        for (uint8_t i = 0, y = 0; i < LEDS_COUNT; i++, y++) {
            if (y == LEDS_PER_STRIP) y = 0;

            uint8_t render_index = index;
            uint16_t angle = zero_angle + Leds::get_angle(i);
            uint32_t color = 0;

            do {
                if (stars[render_index].show(y, angle, color)) {
                    break;
                }
                // update from index backward so the new stars are on-top.
                if (--render_index == 0xFF) {
                    render_index = STAR_COUNT - 1;
                }
            } while (render_index != index);

            Leds::set_color(i, color);
        }
    }
};