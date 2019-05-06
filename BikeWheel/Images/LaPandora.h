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

        uint16_t rocket_angle = zero_angle + (millis() << 2);

        for (uint8_t i = 0; i < NUM_PIXELS; i++) {
            uint16_t led_angle = Leds::get_angle(i);

            uint32_t color = rocket_img.get_led_color(i, rocket_angle + led_angle, reverse);

            if (color == 0) {
                color = space_img.get_led_color(i, zero_angle + led_angle, reverse);
            }

            Leds::set_color(i, color);
        }
    }
};