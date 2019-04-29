#pragma once
#include "Adafruit_DotStar.h"
#include "Arduino.h"
#include "Vector.h"

#define PIXELS_PER_STRIP 36

#define PIXELS_PER_METER 144

// The number of strips
#define NUM_PIXEL_STRIPS 4

#define NUM_PIXELS PIXELS_PER_STRIP * NUM_PIXEL_STRIPS

namespace Pixels {
    struct Pixel_Position {
        // distance from the wheel center
        uint8_t dist;

        // The inital angle from the vertical axis 
        // (bike's up-down and forward-back)
        // from 0 to uint16_t max value
        uint16_t angle;

        Pixel_Position();
    };

    // Wheel is in a "zero" position, LED coordinates are in the wheel's
    // plane, X being the horizontal axis (bike's forward-back), Y the
    // vertical axis (bike's up-down), in milimeters.
    struct Strip {
        Vector2<int16_t> first, last;
        Strip(int16_t x0, int16_t y0, int16_t x1, int16_t y1);
    };

    extern int min_dist;

    extern Pixel_Position positions[NUM_PIXELS];

    extern Adafruit_DotStar leds;

    void init(Strip* strips);
};
