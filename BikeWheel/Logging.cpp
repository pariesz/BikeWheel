#pragma once

#ifdef SIMULATION
#include "Arduino_Mock.h"
#endif

#include "Colors.h"
#include "Leds.h"
#include "Logging.h"

#ifdef LOGGING
namespace Logging {
    inline void log_fps() {
        static unsigned int fps = 0;
        static unsigned long fps_millis = millis();

        if (millis() - fps_millis > 1000) {
            LOG_VAL("fps", fps);
            fps_millis = millis();
            fps = 0;
        }

        fps++;
    }

    void test_segments(uint16_t zero_angle, bool hallVal) {
        using namespace Colors;
        using namespace Leds;

        for (uint8_t i = 0; i < NUM_PIXELS; i++) {
            if (get_distance(i) < 250) {
                set_color(i, black);
                continue;
            }

            if (hallVal == LOW) {
                set_color(i, white);
                continue;
            }

            uint16_t angle = zero_angle + get_angle(i);

            switch (angle >> 14) {
                case 0:  set_color(i, red); break;
                case 1:  set_color(i, green); break;
                case 2:  set_color(i, blue); break;
                default: set_color(i, black); break;
            }
        }
    }
}
#endif