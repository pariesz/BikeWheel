#include <math.h>
#include <iostream>
#include <fstream>
#include "Mocks/Arduino_Mock.h"
#include "Export.h"
#include "Leds_Export.h"

namespace Leds_Export {
    void export_code(std::string filename, float strips[4][LEDS_STRIPS_COUNT]) {
        using namespace std;
        using namespace Export;

        uint8_t dist_min = 0xFF;
        
        uint16_t angles[LEDS_COUNT];

        uint8_t distances[LEDS_COUNT];

        float dist_max = 0;

        for (int si = 0; si < LEDS_STRIPS_COUNT; si++) {
            float x1 = strips[si][2];
            float y1 = strips[si][3];

            uint16_t dist = sqrtf(sq(x1) + sq(y1));

            dist_max = max(dist_max, dist);
        }

        int led_count = 0;

        for (int si = 0; si < LEDS_STRIPS_COUNT; si++) {
            float x0 = strips[si][0];
            float y0 = strips[si][1];
            float x1 = strips[si][2];
            float y1 = strips[si][3];

            int i = 0;
            int xLength = x1 - x0;
            int yLength = y1 - y0;

            double x = 0.0f, y = 0.0f;

            for (i = 0; i < LEDS_PER_STRIP; i++) {
                // calculate the x/y for the pixel
                x = x0 + ((xLength * i) / (float)(LEDS_PER_STRIP - 1));
                y = y0 + ((yLength * i) / (float)(LEDS_PER_STRIP - 1));

                // use pythagorases theorm to calculate the hypotenuse
                // (the distance from the first pixel in the strip)
                // and convert to the scale of uint8
                distances[led_count] = (sqrtf(sq(x) + sq(y)) / dist_max) * 0xFF;

                // use trig tan to calculate the angle and scale to uint16
                // angle is from the y-axis (0) clockwise away from bike to max uint16
                angles[led_count] = (uint16_t)(atan2(x, y) * (0x8000 / (float)PI));

                dist_min = min(dist_min, distances[led_count]);

                led_count++;
            }
        }

        ofstream stream;

        stream.open(filename);
        stream << "#pragma once" << endl
            << "#include \"Adafruit_DotStar_Mock.h\"" << endl
            << "#include \"Leds.h\"" << endl
            << endl
            << "namespace Leds {" << endl;

        stream << "\tAdafruit_DotStar leds = Adafruit_DotStar(LEDS_COUNT, DOTSTAR_BGR);" << endl;

        stream << endl;
        write_int8(stream, "min_dist", dist_min);

        stream << endl;
        write_int16_array(stream, "angles", angles, LEDS_COUNT);

        stream << endl;
        write_int8_array(stream, "distances", distances, LEDS_COUNT);

        stream << "}" << endl;
        stream.close();
    }
};