#pragma once
#include "../Images/Space.h"
#include "../Images/Rocket.h"
#include "../Program.h"

class LaPandora : public Program {

private:
    Space space;
    Rocket rocket;

public:
    void render(uint16_t zero_angle, int32_t rotation_rate) {
        bool reverse = rotation_rate < 0;

        uint16_t space_angle = zero_angle - (millis() << 2);
        uint8_t star_index = random(0, LEDS_COUNT - 1);

        for (uint8_t i = 0; i < LEDS_COUNT; i++) {
            uint16_t led_angle = Leds::get_angle(i);
            uint16_t angle = zero_angle + led_angle;
            uint32_t color = rocket.get_led_color(i, reverse ? ~angle : angle);
            

            if (color == 0) {
                angle = space_angle + led_angle;
                color = space.get_led_color(i, reverse ? ~angle : angle);

                if (color == 0 && i == star_index) {
                    color = COLOR_WHITE;
                }
            }

            Leds::set_color(i, color);
        }
    }
};