#pragma once

namespace Colors {
    extern const uint8_t black;
    extern const uint32_t white ;
    extern const uint32_t red   ;
    extern const uint32_t green ;
    extern const uint32_t blue  ;
    extern const uint32_t purple;
    extern const uint32_t orange;
    extern const uint32_t aqua  ;
    extern const uint32_t cyan  ;
    extern const uint32_t yellow;

    // convert hue, saturation and brightness ( HSB/HSV ) to RGB
    // The dim_curve is used only on brightness/value and on saturation (inverted).
    // This looks the most natural.
    uint32_t HslToRgb(uint8_t h, uint8_t s, uint8_t l) __attribute__((optimize("O3")));
}