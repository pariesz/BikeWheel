#include <math.h>
#include <iostream>
#include <fstream>
#include "Export.h"
#include "Arduino_Mock.h"
#include "Leds_Export.h"

#define PIXELS_PER_STRIP 36  // The number of LEDs in each strip including first and last.
#define NUM_PIXEL_STRIPS 4   // The number of strip

namespace Leds_Export {
    void export_code(std::string filename, float strips[4][NUM_PIXEL_STRIPS]) {
        using namespace std;
        using namespace Export;

        const int num_pixels = NUM_PIXEL_STRIPS * PIXELS_PER_STRIP;

        uint8_t min_dist = 255;
        uint16_t angles[num_pixels];
        uint8_t distances[num_pixels];

        float distMax = 0;

        for (int si = 0; si < NUM_PIXEL_STRIPS; si++) {
            float x1 = strips[si][2];
            float y1 = strips[si][3];

            uint16_t dist = sqrtf(sq(x1) + sq(y1));

            distMax = max(distMax, dist);
        }

        int led_count = 0;

        for (int si = 0; si < NUM_PIXEL_STRIPS; si++) {
            float x0 = strips[si][0];
            float y0 = strips[si][1];
            float x1 = strips[si][2];
            float y1 = strips[si][3];

            int i = 0;
            int xLength = x1 - x0;
            int yLength = y1 - y0;

            double x = 0.0f, y = 0.0f;

            for (i = 0; i < PIXELS_PER_STRIP; i++) {
                // calculate the x/y for the pixel
                x = x0 + ((xLength * i) / (float)(PIXELS_PER_STRIP - 1));
                y = y0 + ((yLength * i) / (float)(PIXELS_PER_STRIP - 1));

                // use pythagorases theorm to calculate the hypotenuse
                // (the distance from the first pixel in the strip)
                // and convert to the scale of uint8
                distances[led_count] = (sqrtf(sq(x) + sq(y)) / distMax) * 255;

                // use trig tan to calculate the angle and scale to uint16
                // angle is from the y-axis (0) clockwise away from bike to max uint16
                angles[led_count] = (uint16_t)(atan2(x, y) * (32768.0f / PI));

                min_dist = min(min_dist, distances[led_count]);

                led_count++;
            }
        }

        ofstream stream;

        stream.open(filename);
        stream << "#pragma once" << endl
            << endl
            << "#ifdef SIMULATION" << endl
            << "#include \"Arduino_Mock.h\"" << endl
            << "#include \"Adafruit_DotStar_Mock.h\"" << endl
            << "#else" << endl
            << "#include <avr/pgmspace.h>" << endl
            << "#include <Adafruit_DotStar.h>" << endl
            << "#endif" << endl
            << endl
            << "#include \"Leds.h\"" << endl
            << endl
            << "namespace Leds {" << endl;

        stream << "\tAdafruit_DotStar leds = Adafruit_DotStar(" << num_pixels << ", DOTSTAR_BGR);" << endl;

        stream << endl;
        write_int8(stream, "min_dist", min_dist);

        stream << endl;
        write_int16_array(stream, "angles", angles, num_pixels);

        stream << endl;
        write_int8_array(stream, "distances", distances, num_pixels);

        stream << "}" << endl;
        stream.close();
    }
};