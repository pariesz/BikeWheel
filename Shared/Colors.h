#pragma once
#include "Mocks/Arduino_Mock.h"
#include "Mocks/Adafruit_DotStar_Mock.h"

#define COLOR_BLACK 0
#define COLOR_BLUE 0xFF
#define COLOR_GREEN 0xFF00
#define COLOR_AQUA 0xFFFF
#define COLOR_RED 0xFF0000
#define COLOR_PURPLE 0xCC0066
#define COLOR_ORANGE 0xCC6600
#define COLOR_CYAN 0x6600CC
#define COLOR_YELLOW 0x999900
#define COLOR_WHITE 0xFFFFFF

namespace Colors {
    // convert hue, saturation and brightness ( HSB/HSV ) to RGB
    // The dim_curve is used only on brightness/value and on saturation (inverted).
    // This looks the most natural.
    uint32_t HslToRgb(uint8_t h, uint8_t s, uint8_t l) __attribute__((optimize("O3")));

    inline uint32_t RandomHue() {
        return Adafruit_DotStar::ColorHSV(random(0, 0xFFFF), 255, 0xFF);
    }

}