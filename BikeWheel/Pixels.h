#pragma once
#include <Adafruit_DotStar.h>
#include "./Vector.h"

/* TODO: see what Adafruit_DotStar setBrightness does
 *
 * Max LED brightness to use.  255 is the absolute max value but it
 * seems that even 40 is more than enough at night even with some
 * ambient light.  During daylight a little more may be needed, but
 * at higher values there's less noticeable difference.  255 is probably
 * stronger than needed and very current hungry, generates heat too.
 */
#define MAX_BRIGHTNESS 10

 // The number of LEDs in each strip including first and last.
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

    /*
     * Wheel is in a "zero" position, LED coordinates are in the wheel's
     * plane, X being the horizontal axis (bike's forward-back), Y the
     * vertical axis (bike's up-down), in milimeters.
     */
    struct Strip {
        Vector2<int16_t> first, last;
        Strip(int x0, int y0, int x1, int y1);
    };

    extern int min_dist;
    extern Pixel_Position positions[NUM_PIXELS];
    extern Adafruit_DotStar leds;

    void init(Strip* strips);
};