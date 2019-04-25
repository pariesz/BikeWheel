#include <math.h>
#include "Adafruit_DotStar.h"
#include "Pixels.h"
#include "arduino.h"

namespace Pixels {
    int min_dist = 0;

    Pixel_Position positions[NUM_PIXELS];

    Adafruit_DotStar leds = Adafruit_DotStar(NUM_PIXELS, DOTSTAR_BGR);

    /* LED count and placement data */
    void init(Strip* strips) {
        float distMax = 0;

        /* Precalculate angles, Initilise strip */
        for (int si = 0; si < NUM_PIXEL_STRIPS; si++) {
            Pixels::Strip s = strips[si];
            uint16_t dist = sqrtf(sq(s.last.x) + sq(s.last.y));
            distMax = max(distMax, dist);
        }

        //std::cout << "distmax: " << distMax << std::endl;

        int led_count = 0;

        for (int si = 0; si < NUM_PIXEL_STRIPS; si++) {
            Pixels::Strip s = strips[si];
            uint8_t i = 0;
            int16_t xLength = s.last.x - s.first.x;
            int16_t yLength = s.last.y - s.first.y;
            double x = 0.0f, y = 0.0f;

            for (i = 0; i < PIXELS_PER_STRIP; i++) {
                // calculate the x/y for the pixel
                x = s.first.x + ((xLength * i) / (float)(PIXELS_PER_STRIP - 1));
                y = s.first.y + ((yLength * i) / (float)(PIXELS_PER_STRIP - 1));

                // use pythagorases theorm to calculate the hypotenuse
                // (the distance from the first pixel in the strip)
                // and convert to the scale of uint8
                positions[led_count].dist = (sqrtf(sq(x) + sq(y)) / distMax) * 255;

                // use trig tan to calculate the angle and scale to uint16
                // angle is from the y-axis (0) clockwise away from bike to max uint16
                positions[led_count].angle = (uint16_t)(atan2(x, y) * (32768.0f / M_PI));

                min_dist = min(min_dist, positions[led_count].dist);

                //std::cout << (int)i << ": " << positions[led_count].angle << ", " << (int)positions[led_count].dist << std::endl;

                led_count++;
            }
        }

        leds.begin();
        leds.show();
    }

    Strip::Strip(int16_t x0, int16_t y0, int16_t x1, int16_t y1)
        : first(x0, y0), last(x1, y1) {
    }

    Pixel_Position::Pixel_Position()
        : dist(0), angle(0) {
    }
}