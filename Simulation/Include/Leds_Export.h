#include <string>
#include "Leds.h"

namespace Leds_Export {
    void export_code(std::string filename, float strips[4][LEDS_STRIPS_COUNT]);
};