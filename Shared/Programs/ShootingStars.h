#pragma once
#include "Program.h"

#define NUM_STARS 16

struct Star {
    uint16_t angle = 0;
    uint16_t length = 0;
    uint8_t y = 0;
    uint8_t hue = 0;
};

class ShootingStars : public Program {

private:
    uint8_t index = 0;
    Star stars[NUM_STARS];
    uint8_t color_offset;

public:
    ShootingStars()
        : color_offset(0) {
    }

    ShootingStars(uint8_t color_offset) 
        : color_offset(color_offset) {
    }

    void update_index(uint8_t new_index) {
        if (new_index == index) {
            return;
        }

        // create a new star
        index = new_index;

        Star* star = &stars[index];
        
        star->angle = random(0, 0xFFFF);
        star->hue = random(0, 0x1F) + color_offset;
        star->y = random(0, PIXELS_PER_STRIP - 1);
        star->length = 0;
    }

    void render(uint16_t zero_angle, int32_t rotation_rate) {
        // timing
        uint32_t ms = millis();
        static uint32_t ms_prev = ms;
        uint8_t ms_diff = ms - ms_prev;
        ms_prev = ms;

        // update stars
        update_index((ms >> 9) & NUM_STARS);

        for (uint8_t i = 0; i < NUM_STARS; i++) {
            Star* star = &stars[i];
            star->length += ms_diff << 3;
        }

        // update leds
        for (uint16_t i = 0, y = 0; i < NUM_PIXELS; i++, y++) {
            if (y == PIXELS_PER_STRIP) {
                y = 0;
            }

            uint16_t angle = zero_angle + Leds::get_angle(i);

            bool found = false;

            for (uint8_t k = 0; k < NUM_STARS; k++) {
                Star star = stars[k];

                if (star.y != y) {
                    continue;
                }

                uint16_t max = star.angle + star.length;
                
                // handle overflow
                if (max > star.angle) {
                    if (angle < star.angle || angle > max) {
                        continue;
                    }
                } else {
                    if (angle < star.angle && angle > max) {
                        continue;
                    }
                }
                
                // brighter towards the front of the star but darker the longer it gets
                uint32_t color = Colors::HslToRgb(star.hue, 0xFF, 0xFF - (max - angle + star.length) >> 6);
                Leds::set_color(i, color);
                found = true;
                break;
            }

            if (!found) {
                Leds::set_color(i, Colors::black);
            }
        }
    }
};