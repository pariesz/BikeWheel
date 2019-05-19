#pragma once
#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "Arduino_Mock.h"
#endif

#include "Helpers.h"

namespace Programs {
    void set_color(uint32_t color);
    void spiral(uint16_t zero_angle) OPTIMIZE;
    void kaleidoscope(uint16_t zero_angle) OPTIMIZE;
    void radioactive(uint16_t zero_angle) OPTIMIZE;
    void rainbow_text(uint16_t zero_angle, uint8_t label_len, const char *label) OPTIMIZE;
    void masa_critica(uint16_t zero_angle) OPTIMIZE;
    void velocity(uint16_t zero_angle, int32_t rotation_rate) OPTIMIZE;
};