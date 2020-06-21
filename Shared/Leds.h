#pragma once
#include "Mocks/Arduino_Mock.h"
#include "Mocks/Adafruit_DotStar_Mock.h"

#define LEDS_PER_STRIP 36   // The number of LEDs in each strip including first and last.
#define LEDS_STRIPS_COUNT 4 // The number of strips
#define LEDS_COUNT 144      // PIXELS_PER_STRIP * NUM_PIXEL_STRIPS

namespace Leds {
    extern const uint8_t min_dist;
    extern const uint16_t angles[LEDS_COUNT];
    extern const uint8_t distances[LEDS_COUNT];
    extern Adafruit_DotStar leds;

    inline uint16_t get_angle(const uint16_t index) {
        return pgm_read_word(&(angles[index]));
    }
    inline uint8_t get_distance(const uint16_t index) {
        return pgm_read_byte(&(distances[index]));
    }
    inline void set_color(uint16_t index, uint32_t color) {
        leds.setPixelColor(index, color);
    }
    inline uint8_t get_brightness() {
        return leds.getBrightness();
    }
    inline void set_brightness(uint8_t value) {
        leds.setBrightness(value);
    }
    inline void clear() {
        leds.clear();
    }

    inline void setup(uint16_t number, uint8_t dataPin, uint8_t clockPin, uint8_t o) {
        leds = Adafruit_DotStar(number, dataPin, clockPin, o);
        leds.setBrightness(20);
        leds.begin();
        leds.clear();
        leds.show();
    }
};