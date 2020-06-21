#pragma once

// used by implementations
#include "Mocks/Arduino_Mock.h"
#include "Mocks/Adafruit_DotStar_Mock.h"
#include "Leds.h"
#include "Colors.h"
#include "Font.h"

class Program {
public:
    virtual void configure() { }
    virtual void update(int32_t rotation_rate) { };
    virtual void render(uint16_t zero_angle) __attribute__((optimize("O3"))) { };
    virtual ~Program() = default;
};