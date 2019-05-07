#pragma once
#include "space.h"
#include "rocket.h"

class LaPandora {

private:
    space space_img;
    rocket rocket_img;

public:
    void initialize() {
        space_img.Initialize();
        rocket_img.Initialize();
    }

    void render(uint16_t zero_angle, int32_t rotation_rate) {
        bool reverse = rotation_rate < 0;

        uint16_t space_angle = zero_angle - (millis() << 2);

        for (uint8_t i = 0; i < NUM_PIXELS; i++) {
            uint16_t led_angle = Leds::get_angle(i);
            uint16_t angle = zero_angle + led_angle;
            uint32_t color = rocket_img.get_led_color(i, reverse ? ~angle : angle);

            if (color == 0) {
                angle = space_angle + led_angle;
                color = space_img.get_led_color(i, reverse ? ~angle : angle);
            }

            Leds::set_color(i, color);
        }
    }
};