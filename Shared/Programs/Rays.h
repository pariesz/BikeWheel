#pragma once
#include "Program.h"

#define RAY_COUNT 8
#define RAY_FRAME_RATE 50 // rays move one led every x ms
#define RAY_MAX_WIDTH 0x8FF
#define RAY_MIN_WIDTH 0x1FF
#define RAY_COLOR_VARIATION 0x2F
#define RAY_BIRTH_RATE 10 // number of frames between creating new rays
#define RAY_EXPANSION 30

class Rays : public Program {

private:
    struct Ray {
        uint32_t color = 0;
        uint16_t start_angle = 0;
        uint16_t end_angle = 0;
        uint8_t end_y = 0;
        uint8_t start_y = 0;
    };

    Ray rays[RAY_COUNT];

public:
    void render(uint16_t zero_angle, int32_t rotation_rate) {
        // timing
        uint32_t ms = millis();
        static uint32_t ms_prev = ms;
        static uint8_t frame_count = 0;
        static uint8_t index = 0; 
        static uint8_t color_offset = random(0, 0xFF);

        // update rays
        if (ms - ms_prev > RAY_FRAME_RATE) {
            ms_prev = ms;

            // create new rays
            if (++frame_count > RAY_BIRTH_RATE) {
                frame_count = 0;

                if (++index == RAY_COUNT) {
                    index = 0;
                }

                Ray* ray = &rays[index];

                ray->start_angle = random(0, 0xFFFF);
                ray->end_angle = ray->start_angle + random(RAY_MIN_WIDTH, RAY_MAX_WIDTH);
                ray->color = Colors::HslToRgb(random(0, RAY_COLOR_VARIATION) + (color_offset += 3), 0xFF, 0xFF);
                ray->end_y = 0;
                ray->start_y = 0;
            }

            // update existing rays
            for (uint8_t i = 0; i < RAY_COUNT; i++) {
                Ray* ray = &rays[i];

                if (ray->end_y < PIXELS_PER_STRIP) {
                    ray->end_y++;
                } else if (ray->start_y < PIXELS_PER_STRIP) {
                    ray->start_y++;
                }
                ray->start_angle -= RAY_EXPANSION;
                ray->end_angle += RAY_EXPANSION;
            }
        }

        // update leds
        for (uint16_t i = 0, y = 0; i < NUM_PIXELS; i++, y++) {
            if (y == PIXELS_PER_STRIP) y = 0;

            uint16_t angle = zero_angle + Leds::get_angle(i);
            uint32_t color = 0;
            uint8_t render_index = index;

            do {
                Ray ray = rays[render_index];

                if (ray.end_y >= y && ray.start_y <= y) {
                    if (ray.start_angle > ray.end_angle) {
                        // overflow
                        if (angle > ray.start_angle || angle < ray.end_angle) {
                            color = ray.color;
                            break;
                        }
                    } else {
                        if (angle > ray.start_angle && angle < ray.end_angle) {
                            color = ray.color;
                            break;
                        }
                    }
                }
                // update from index backward so the new rays are on-top.
                if (--render_index == 0xFF) {
                    render_index = RAY_COUNT - 1;
                }
            } while (render_index != index);

            Leds::set_color(i, color);
        }
    }
};