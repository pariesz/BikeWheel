#include <math.h>
#include <Adafruit_DotStar.h>
#include "./Timers.h"
#include "./Pixels.h"
#include "./Programs.h"

#define MIN(a,b) ((a)<(b)?(a):(b))
#define DEGS_TO_ANGLE(x) (uint16_t)((x) / 180.0f * (1uLL << 15))
#define DEGS_PER_S_TO_RATE(x) (uint16_t)((x) * 16.4f)

using namespace Pixels;

namespace Programs {
    void set_color(uint32_t color) {
        for (uint16_t i = 0; i < NUM_PIXELS; i++) {
            leds.setPixelColor(i, color);
        }
    }

    void set_half_color(uint32_t color, uint16_t angle) {
        for (uint8_t i = 0; i < NUM_PIXELS; i++) {
            uint16_t pixel_angle = angle - positions[i].angle;
            leds.setPixelColor(i, pixel_angle > 32768 ? color : 0);
        }
    }

    /* Moving spiral shape */
    void spiral(uint16_t angle) {
#if 0
        uint16_t millis = Timers::now() >> 10;

        for (uint8_t i = 0; i < NUM_PIXELS; i++) {
            uint16_t angle = angle - positions[i].angle;

            int pos = angle - millis + ((uint32_t)positions[i].dist << 17) / 255;

            uint8_t brightness = pos >> 6;
            uint8_t blue = pos >> 15;

            if (pos & (1 << 14)) {
                brightness ^= 255;
            }

            /* Decrease "gamma", these LEDs are bright at low values */
            brightness -= MIN(brightness, (brightness ^ 255) / 3);

            pixel->r = blue ? 0 : brightness;
            pixel->g = blue ? 0 : brightness;
            pixel->b = brightness;
        }
#endif
    }

#if 0
    static void prog_pacman_set_leds(uint16_t zero_angle, RGB_t *rgb) {
        uint16_t subsec = Timers::now() >> 19;
        uint8_t halfsec = subsec >> 4;
        bool open = halfsec & 1;

        if (open) {
            /* Pacman mouth open */
            for (uint8_t i = 0, x = 0; i < led_cnt; i++, x++) {
                uint16_t angle = zero_angle - led_angle[i];

                if (x == 15)
                    x = 0;

                if (angle < DEGS_TO_ANGLE(230.0f) ||
                    angle > DEGS_TO_ANGLE(310.0f)) {
                    rgb[i].r = LED_ON;
                    rgb[i].g = LED_ON;
                    rgb[i].b = 0;
                }
                else {
                    uint8_t dist = x - (15 - ((subsec + 8) & 15));
                    uint16_t adist = 32768 / ((led_dist[i] >> 3) + 1);
                    uint16_t y = angle -
                        (DEGS_TO_ANGLE(270.0f) - adist);
                    if (dist < 3 && y < adist) {
                        rgb[i].r = LED_ON;
                        rgb[i].g = LED_ON;
                        rgb[i].b = LED_ON;
                    }
                    else {
                        rgb[i].r = 0;
                        rgb[i].g = 0;
                        rgb[i].b = 0;
                    }
                }
            }
        }
        else {
            /* Pacman mouth closed */
            for (uint8_t i = 0; i < led_cnt; i++) {
#if 0
                rgb[i].r = LED_ON;
                rgb[i].g = LED_ON;
                rgb[i].b = 0;
#else
                uint16_t angle = zero_angle - led_angle[i];

                if (angle < DEGS_TO_ANGLE(262.0f) ||
                    angle > DEGS_TO_ANGLE(278.0f)) {
                    rgb[i].r = LED_ON;
                    rgb[i].g = LED_ON;
                    rgb[i].b = 0;
                }
                else {
                    rgb[i].r = 0;
                    rgb[i].g = 0;
                    rgb[i].b = 0;
                }
#endif
            }
        }
    }
#endif
}
