#include <math.h>
#include <SPI.h>
#include <Adafruit_DotStar.h>
#include <avr/power.h>
#include "./Pixels.h"

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
            uint16_t dist = sqrtf(sq((int32_t)s.last.x) + sq((int32_t)s.last.y));
            distMax = max(distMax, dist);
        }

        /*
        Serial.print("distMax: ");
        Serial.println(distMax);
        */

        int led_count = 0;
        
        for (int si = 0; si < NUM_PIXEL_STRIPS; si++) {
            Pixels::Strip s = strips[si];
            uint8_t i = 0;
            int16_t xLength = s.last.x - s.first.x;
            int16_t yLength = s.last.y - s.first.y;
            float x = 0.0f, y = 0.0f;

            for (i = 0; i < PIXELS_PER_STRIP; i++) {
                // calculate the x/y for the pixel
                x = s.first.x + ((xLength * i) / (float)(PIXELS_PER_STRIP - 1));
                y = s.first.y + ((yLength * i) / (float)(PIXELS_PER_STRIP - 1));

                // use pythagorases theorm to calculate the hypotenuse
                // (the distance from the first pixel in the strip)
                // and convert to the scale of uint8
                positions[led_count].dist = (sqrtf(sq((int32_t)x) + sq((int32_t)y)) / distMax) * 255;

                // use trig tan to calculate the angle and scale to uint16
                positions[led_count].angle = (uint16_t)((atan2(x, y) * (32768.0f / M_PI)));

                min_dist = min(min_dist, positions[led_count].dist);
                
                /*
                Serial.print(i);
                Serial.print(": ");
                Serial.print(x);
                Serial.print(", ");
                Serial.print(y);
                Serial.print(", ");
                Serial.print(positions[led_count].angle);
                Serial.print(", ");
                Serial.println(positions[led_count].dist);
                */

                led_count++;
            }
        }

        leds.setBrightness(40);
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