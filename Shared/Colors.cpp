#include "Colors.h"

namespace Colors {
    // dim_curve 'lookup table' to compensate for the nonlinearity of human vision.
    // Used in the getRGB function on saturation and brightness to make 'dimming' look more natural.
    // Exponential function used to create values below :
    // x from 0 - 255 : y = round(pow( 2.0, x+64/40.0) - 1)
    const uint8_t dim_curve[] PROGMEM = {
        0,   1,   1,   2,   2,   2,   2,   2,   2,   3,   3,   3,   3,   3,   3,   3,
        3,   3,   3,   3,   3,   3,   3,   4,   4,   4,   4,   4,   4,   4,   4,   4,
        4,   4,   4,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   6,   6,   6,
        6,   6,   6,   6,   6,   7,   7,   7,   7,   7,   7,   7,   8,   8,   8,   8,
        8,   8,   9,   9,   9,   9,   9,   9,   10,  10,  10,  10,  10,  11,  11,  11,
        11,  11,  12,  12,  12,  12,  12,  13,  13,  13,  13,  14,  14,  14,  14,  15,
        15,  15,  16,  16,  16,  16,  17,  17,  17,  18,  18,  18,  19,  19,  19,  20,
        20,  20,  21,  21,  22,  22,  22,  23,  23,  24,  24,  25,  25,  25,  26,  26,
        27,  27,  28,  28,  29,  29,  30,  30,  31,  32,  32,  33,  33,  34,  35,  35,
        36,  36,  37,  38,  38,  39,  40,  40,  41,  42,  43,  43,  44,  45,  46,  47,
        48,  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,
        63,  64,  65,  66,  68,  69,  70,  71,  73,  74,  75,  76,  78,  79,  81,  82,
        83,  85,  86,  88,  90,  91,  93,  94,  96,  98,  99,  101, 103, 105, 107, 109,
        110, 112, 114, 116, 118, 121, 123, 125, 127, 129, 132, 134, 136, 139, 141, 144,
        146, 149, 151, 154, 157, 159, 162, 165, 168, 171, 174, 177, 180, 183, 186, 190,
        193, 196, 200, 203, 207, 211, 214, 218, 222, 226, 230, 234, 238, 242, 248, 255,
    };

    inline uint32_t rgb(uint8_t r, uint8_t g, uint8_t b) {
        return ((uint32_t)r << 16) + ((uint16_t)g << 8) + b;
    }

    // convert hue, saturation and brightness ( HSB/HSV ) to RGB
    // The dim_curve is used only on brightness/value and on saturation (inverted).
    // This looks the most natural.
    uint32_t HslToRgb(uint8_t h, uint8_t s, uint8_t l) {

        l = pgm_read_byte(&dim_curve[l]);
        if (l == 0) return 0;

        s = 255 - pgm_read_byte(&dim_curve[255 - s]);
        if (s == 0) return rgb(l, l, l);

        uint8_t mod = h % 43;
        uint8_t p = ((uint16_t)l * (255 - s)) >> 8;
        uint8_t q = ((uint16_t)((l - p) * (43 - mod)) / 43) + p;
        uint8_t t = ((uint16_t)((l - p) * mod) / 43) + p;

        switch (h / 43) {
            case 0:  return rgb(l, t, p);
            case 1:  return rgb(q, l, p);
            case 2:  return rgb(p, l, t);
            case 3:  return rgb(p, q, l);
            case 4:  return rgb(t, p, l);
            default: return rgb(l, p, q);
        }
    }
}