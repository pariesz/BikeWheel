#pragma once

// used by implementations
#if defined(ARDUINO) && ARDUINO >= 100
    #include "arduino.h"
    #include <avr/pgmspace.h>
#else
    #include "Arduino_Mock.h"
#endif

#include "Leds.h"
#include "Colors.h"
#include "Font.h"

class Program {
public:
    virtual void render(uint16_t zero_angle, int32_t rotation_rate) __attribute__((optimize("O3"))) = 0;
};