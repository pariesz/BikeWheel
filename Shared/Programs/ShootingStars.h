#pragma once
#include "Program.h"

#define STAR_COUNT 16
#define STAR_BIRTH_INDEX(ms) (((ms) >> 9) & 0xF) // bitmask needs to be same size as STAR_COUNT
#define STAR_GROWTH_RATE(ms_diff) ((ms_diff) << 3)
#define STAR_BRIGHTNESS_SHIFT 7

class ShootingStars : public Program {

private:
    struct Star {
        uint16_t start_angle = 0;
        uint16_t length = 0;
        uint8_t y = 0xFF;
        uint8_t hue = 0;
    };

    Star stars[STAR_COUNT];
    uint8_t index = 0;
    uint8_t color_offset = random(0, 0xFF);

public:


    inline uint32_t get_color(Star &star, uint16_t fade) {
        return fade >= 0xFF ? 0 : Colors::HslToRgb(star.hue, 0xFF, 0xFF - fade);
    }

    void render(uint16_t zero_angle, int32_t rotation_rate) {
        // timing
        uint32_t ms = millis();
        static uint32_t ms_prev = ms;
        uint8_t ms_diff = ms - ms_prev;
        ms_prev = ms;

        // create new stars
        if (index != STAR_BIRTH_INDEX(ms)) {
            index = STAR_BIRTH_INDEX(ms);

            Star* star = &stars[index];

            star->start_angle = random(0, 0xFFFF);
            star->hue = color_offset += 3;
            star->y = random(0, PIXELS_PER_STRIP - 1);
            star->length = 0;
        }

        // update existing stars
        for (uint8_t i = 0; i < STAR_COUNT; i++) {
            Star* star = &stars[i];
            star->length += STAR_GROWTH_RATE(ms_diff);
        }

        // update leds
        for (uint8_t i = 0, y = 0; i < NUM_PIXELS; i++, y++) {
            if (y == PIXELS_PER_STRIP) y = 0;

            uint8_t render_index = index;
            uint16_t angle = zero_angle + Leds::get_angle(i);
            uint32_t color = 0;

            do {
                Star star = stars[render_index];

                if (star.y == y) {
                    uint32_t end_angle = star.start_angle + (uint32_t)star.length;

                    if (end_angle > 0xFFFF) {
                        // overflow
                        if (angle > star.start_angle) {
                            color = get_color(star, (end_angle - angle) >> STAR_BRIGHTNESS_SHIFT);
                            break;

                        } else if (angle < (uint16_t)end_angle) {
                            color = get_color(star, ((uint16_t)end_angle - angle) >> STAR_BRIGHTNESS_SHIFT);
                            break;
                        }
                    } else {
                        if (angle > star.start_angle && angle < end_angle) {
                            color = get_color(star, (end_angle - angle) >> STAR_BRIGHTNESS_SHIFT);
                            break;
                        }
                    }
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