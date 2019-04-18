#include <math.h>
#include "./Pixels.h"
#include "Programs.h"

using namespace Pixels;

namespace Programs {
    void set_color(uint32_t color) {
        for (uint16_t i = 0; i < NUM_PIXELS; i++) {
            leds.setPixelColor(i, color);
        }
    }

    void set_half_color(uint32_t color, uint16_t angle) {
        for (uint8_t i = 0; i < NUM_PIXELS; i++) {
            uint16_t pixel_angle = angle + positions[i].angle;
            leds.setPixelColor(i, pixel_angle > 16384 && pixel_angle < 49152 ? color : 0);
        }
    }
}