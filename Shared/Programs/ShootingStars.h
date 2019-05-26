#pragma once
#include "Program.h"

#define STAR_GROWTH_RATE 250
#define STAR_FADE(length) ((length) >> 7)
#define STAR_HUE_CHANGE_RATE 3 // increment hue x every birth
#define STAR_LIFETIME 120 // stars will live for x frames
#define STAR_BIRTH_RATE 8 // a start is born every x frames
#define STAR_MAX_LENGTH 0x7FFF
#define STAR_FRAME(ms) (((ms) >> 5) & 0xFFFF) // 32 frames sec

class Star {
    private:
        uint16_t start_angle = random(0, 0xFFFF);
        uint16_t length = 0;
        uint16_t created_frame;
        uint8_t hue;

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
            : hue(0)
            , created_frame(STAR_FRAME(millis()) - (STAR_LIFETIME + 1)) {
        }

        Star(uint8_t hue, uint16_t frame) 
            : hue(hue)
            , created_frame(frame) {
        }

        inline void update() {
            if (length > STAR_MAX_LENGTH) {
                start_angle += STAR_GROWTH_RATE;
            } else {
                length += STAR_GROWTH_RATE;
            }
        }

        inline bool isDead(uint16_t frame) {
            return frame - created_frame > STAR_LIFETIME;
        }

        inline bool show(uint16_t angle, uint32_t &out_color) {
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
    uint16_t frame_prev = STAR_FRAME(millis());
    uint16_t birth_prev = frame_prev;

public:
    void render(uint16_t zero_angle, int32_t rotation_rate) {
        // timing
        uint32_t ms = millis();
        uint16_t frame = STAR_FRAME(ms);

        // create new stars
        if (frame != frame_prev) {
            frame_prev = frame;

            // update existing star
            for (uint8_t i = 0; i < LEDS_PER_STRIP; i++) {
                stars[i].update();
            }

            if (abs(frame - birth_prev) > STAR_BIRTH_RATE) {
                birth_prev = frame;

                while (true) {
                    uint8_t create_index = random(0, LEDS_PER_STRIP - 1);

                    if (stars[create_index].isDead(frame)) {
                        stars[create_index] = Star(hue += STAR_HUE_CHANGE_RATE, frame);
                        break;
                    }

                    // recalculate frame so the termination condition 
                    // will always eventally pass
                    frame = STAR_FRAME(ms);
                }
            }
        }

        // update leds
        for (uint8_t i = 0, y = 0; i < LEDS_COUNT; i++, y++) {
            if (y == LEDS_PER_STRIP) y = 0;

            Star* star = &stars[y];

            if (star->isDead(frame)) {
                Leds::set_color(i, 0);
                continue;
            }
            
            uint32_t color = 0;

            Leds::set_color(i, star->show(zero_angle + Leds::get_angle(i), color) ? color : 0);
        }
    }
};