#pragma once
#include "Program.h"

#define STAR_GROWTH_RATE(ms_diff) ((ms_diff) << 3)
#define STAR_FADE(length) (length) >> 7
#define STAR_HUE_CHANGE_RATE 3
#define STAR_LIFETIME 15
#define STAR_MAX_LENGTH 0x7FFF
#define STAR_TIME(ms) (((ms) >> 8) & 0xFFFF)

class Star {
    private:
        uint16_t created;
        uint16_t start_angle = random(0, 0xFFFF);
        uint16_t length = 0;
        uint8_t hue = 0;

        inline uint32_t get_color(uint16_t length) {
            uint8_t fade = STAR_FADE(length);
            if (fade >= 0xFF) {
                return 0;
            } else if (fade > 0x7F) {
                return Colors::HslToRgb(hue, 0xFF, 0xFF - (fade << 1));
            } else if(fade < 0x3F) {
                return Colors::HslToRgb(hue, fade << 2, 0xFF);
            } else {
                return Colors::HslToRgb(hue, 0xFF, 0xFF);
            }
        }

    public:
        Star() 
            : created(0) {
        }

        Star(uint8_t hue, uint16_t time) 
            : hue(hue)
            , created(time) {
        }

        void update(uint8_t ms) {
            if (length > STAR_MAX_LENGTH) {
                start_angle += STAR_GROWTH_RATE(ms);;
            } else {
                length += STAR_GROWTH_RATE(ms);
            }
        }

        inline bool isDead(uint16_t seconds) {
            return seconds - created > STAR_LIFETIME;
        }

        bool show(uint16_t angle, uint32_t &out_color) {
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

            return false;
        }
};

class ShootingStars : public Program {

private:
    Star stars[LEDS_PER_STRIP];
    uint8_t index = 0;
    uint8_t hue = random(0, 0xFF);

public:
    void render(uint16_t zero_angle, int32_t rotation_rate) {
        // timing
        uint32_t ms = millis();
        uint16_t time = STAR_TIME(ms);
        static uint16_t time_prev = time;

        // create new stars
        if (time - time_prev) {
            time_prev = time;

            while (true) {
                uint8_t create_index = random(0, LEDS_PER_STRIP - 1);

                if (stars[create_index].isDead(time)) {
                    stars[create_index] = Star(hue += STAR_HUE_CHANGE_RATE, time);
                    break;
                }
            }
        }

        // update existing stars
        static uint32_t ms_prev = ms;
        uint8_t ms_diff = ms - ms_prev;
        ms_prev = ms;

        for (uint8_t i = 0; i < LEDS_PER_STRIP; i++) {
            stars[i].update(ms_diff);
        }

        // update leds
        for (uint8_t i = 0, y = 0; i < LEDS_COUNT; i++, y++) {
            if (y == LEDS_PER_STRIP) y = 0;

            Star* star = &stars[y];

            if (star->isDead(time)) {
                Leds::set_color(i, 0);
                continue;
            }
            
            uint32_t color = 0;

            Leds::set_color(i, star->show(zero_angle + Leds::get_angle(i), color) ? color : 0);
        }
    }
};