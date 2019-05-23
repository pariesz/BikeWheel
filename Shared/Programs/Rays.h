#pragma once
#include "Program.h"

#define RAY_COUNT 4
#define RAY_FRAME_RATE 50 // rays move one led every x ms
#define RAY_MAX_WIDTH 0xFFF
#define RAY_MIN_WIDTH 0x7F
#define RAY_COLOR_VARIATION 0x2F
#define RAY_BIRTH_RATE 10 // number of frames between creating new rays
#define RAY_EXPANSION 50
#define RAY_SATURATE_RATE 20
#define RAY_FADE_RATE 10

class Ray {

    private:
        uint16_t start_angle = 0;
        uint16_t end_angle = 0;

        uint8_t end_y = 0;
        uint8_t start_y = 0;
    
        uint8_t hue = 0;
        uint8_t brightness = 0;
        uint8_t saturation = 0;
    
        uint32_t color = 0;

    public:
        void reset() {
            start_angle = random(0, 0xFFFF);
            end_angle = start_angle + random(RAY_MIN_WIDTH, RAY_MAX_WIDTH);
            end_y = 0;
            start_y = 0;
            hue = random(0, 0xFF);
            brightness = 0xFF;
            saturation = 0x00;
            color = Colors::HslToRgb(hue, saturation, brightness);
        }

        void update() {
            if (end_y < LEDS_PER_STRIP) {
                end_y++;

            } else if (start_y < LEDS_PER_STRIP) {
                start_y++;
            }

            if (end_y > 10) {
                if (saturation <= (0xFF - RAY_SATURATE_RATE)) {
                    saturation += RAY_SATURATE_RATE;
                } else {
                    saturation = 0xFF;

                    if (brightness >= RAY_FADE_RATE) {
                        brightness -= RAY_FADE_RATE;
                    } else {
                        brightness = 0;
                    }
                }
            }

            start_angle -= RAY_EXPANSION;
            end_angle += RAY_EXPANSION;
            color = Colors::HslToRgb(hue, saturation, brightness);
        }

        bool show(uint8_t y, uint16_t angle, uint32_t &color) {
            if (end_y >= y && start_y <= y) {
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

    public:
        void render(uint16_t zero_angle, int32_t rotation_rate) {
            static uint32_t ms_prev = millis();
            static uint8_t created_index = 0;

            // update rays
            if (millis() - ms_prev > RAY_FRAME_RATE) {
                ms_prev = millis();

                // create new rays
                static uint8_t frame_count = 0;
                if (++frame_count > RAY_BIRTH_RATE) {
                    frame_count = 0;

                    if (++created_index == RAY_COUNT) {
                        created_index = 0;
                    }

                    rays[created_index].reset();
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
                uint32_t color = 0;

                // update from index backward from the last created ray
                // so the new rays are on-top.
                uint8_t ray_index = created_index;

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