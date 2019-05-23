#pragma once

// used by implementations
#include "Mocks/Arduino_Mock.h"
#include "Leds.h"
#include "Colors.h"
#include "Font.h"

class Program {
public:
    virtual void render(uint16_t zero_angle, int32_t rotation_rate) __attribute__((optimize("O3"))) = 0;
    virtual ~Program() = default;
};