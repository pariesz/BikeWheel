#pragma once
#include "Program.h"

#define RAY_COUNT 4
#define RAY_FRAME_RATE 50 // rays move one led every x ms
#define RAY_MAX_WIDTH 0xFFF
#define RAY_MIN_WIDTH 0x7FF
#define RAY_COLOR_VARIATION 0x2F
#define RAY_BIRTH_RATE 10 // number of frames between creating new rays
#define RAY_EXPANSION -20
#define RAY_FADE_RATE 10

class Ray {

    private:
        uint16_t start_angle = random(0, 0xFFFF);
        uint16_t end_angle = start_angle + random(RAY_MIN_WIDTH, RAY_MAX_WIDTH);
        uint8_t end_y = 0;
        uint8_t hue;
        uint8_t brightness = 0xFF;
        uint32_t color = Colors::HslToRgb(hue, 0xFF, brightness);

    public:
        Ray() : hue(0) { }

        Ray(uint8_t hue) : hue(hue) {}

        void set_brightness(uint8_t value) {
            brightness = value;
        }

        void set_hue(uint8_t value) {
            hue = value;
        }

        void update() {
            if (end_y < LEDS_PER_STRIP) {
                end_y++;
            }
            
            brightness -= RAY_FADE_RATE;
            start_angle -= RAY_EXPANSION;
            end_angle += RAY_EXPANSION;
            color = Colors::HslToRgb(hue, 0xFF, brightness);
        }

        bool show(uint8_t y, uint16_t angle, uint32_t &color) {
            if (end_y >= y) {
                if (start_angle > end_angle) {
                    // overflow
                    if (angle > start_angle || angle < end_angle) {
                        color = this->color;
                        return true;
                    }
                } else {
                    if (angle > start_angle && angle < end_angle) {
                        color = this->color;
                        return true;
                    }
                }
            }

            return false;
        }
};

class Rays : public Program {

    private:
        Ray rays[RAY_COUNT];
        uint8_t hue = random(0, 0xFF);
        uint32_t ms_prev = millis();
        uint8_t created_index = 0;
        uint8_t frame_count = 0;

    public:
        Rays() {
            for (uint8_t i = 0; i < RAY_COUNT; i++) {
                rays[i].set_brightness(0);
                rays[i].set_hue(hue);
            }
        }

        void render(uint16_t zero_angle, int32_t rotation_rate) {
            // update rays
            if (millis() - ms_prev > RAY_FRAME_RATE) {
                ms_prev = millis();

                // create new rays
                if (++frame_count > RAY_BIRTH_RATE) {
                    frame_count = 0;

                    // loop back around
                    if (++created_index == RAY_COUNT) {
                        created_index = 0;
                    }

                    rays[created_index] = Ray(hue += 3);
                }

                // update existing rays
                for (uint8_t i = 0; i < RAY_COUNT; i++) {
                    rays[i].update();
                }
            }

            // update leds
            for (uint16_t i = 0, y = 0; i < LEDS_COUNT; i++, y++) {
                if (y == LEDS_PER_STRIP) y = 0;

                uint16_t angle = zero_angle + Leds::get_angle(i);

                // lightning streaks
                if (y > 20) {
                    angle += 2000;
                } else if (y > 10) {
                    angle += 1000;
                }

                // update from index backward so the new rays are on-top.
                uint8_t ray_index = created_index;

                uint32_t color = 0;
                do {
                    if (rays[ray_index].show(y, angle, color)) {
                        break;
                    }
                    if (--ray_index == 0xFF) {
                        ray_index = RAY_COUNT - 1;
                    }
                } while (ray_index != created_index);

                Leds::set_color(i, color);
            }
        }
};