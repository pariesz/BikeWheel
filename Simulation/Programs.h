#pragma once
#include "arduino.h"

namespace Programs {
    void set_color(uint32_t color) OPTIMIZE;
    void set_half_color(uint32_t color, uint16_t angle) OPTIMIZE;
}
