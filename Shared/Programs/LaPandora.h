#pragma once
#include "../Images/Space.h"
#include "../Images/Rocket.h"
#include "../Program.h"

#define FRAME() ((millis() >> 5) & 0xFFFF)

class LaPandora : public Program {

private:
    //Space space;
    Rocket rocket;
    uint8_t star_index;
    uint32_t star_color;
    //uint16_t space_angle = 0;

public:
    void update(uint16_t frame_count, int32_t rotation_rate) override {
        if (frame_count & 0b1) {
            star_index = random(0, LEDS_COUNT - 1);

            //space_angle += rotation_rate >> 10;
            //uint8_t dist = Leds::get_distance(star_index);

            star_color = Adafruit_DotStar::ColorHSV(0xC000, random(0x00, 0xFF), random(0x00, 0xFF));
        }

        rocket.update(frame_count, rotation_rate);
    }

    void render(uint16_t zero_angle) {
        Leds::leds.clear();

        uint8_t* pixels = Leds::leds.getPixels();

        for (uint8_t i = 0, y = 0; i < LEDS_COUNT; i++, y++) {
            if (y == LEDS_PER_STRIP) y = 0;
            
            uint16_t angle = zero_angle + Leds::get_angle(i);

            uint32_t color = rocket.get_led_color(i, y, rocket.get_reverse() ? ~angle : angle);

            //if (color == 0) {
            //    angle += space_angle;
            //    color = space.get_led_color(i, y, reverse ? ~angle : angle);
            //}

            if (color != 0) {
                memcpy(&pixels[i * 3], &color, 3);
            } else if (i == star_index) {
                memcpy(&pixels[i * 3], &star_color, 3);
            }
        }
    }
};