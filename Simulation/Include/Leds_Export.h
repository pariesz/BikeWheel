#include <string>

#define PIXELS_PER_STRIP 36  // The number of LEDs in each strip including first and last.
#define NUM_PIXEL_STRIPS 4   // The number of strip

namespace Leds_Export {
    void export_code(std::string filename, float strips[4][NUM_PIXEL_STRIPS]);
};