#pragma once

// used by implementations
#if defined(ARDUINO) && ARDUINO >= 100
#include <avr/pgmspace.h>
#else
#include "Arduino_Mock.h"
#endif

#include "Leds.h"
#include "Helpers.h"

class Image {
private:
    uint16_t iterators[NUM_PIXELS];
protected:
    virtual inline uint16_t get_arc(uint16_t i) = 0;
    virtual inline uint16_t get_row_end(uint8_t row_index) = 0;
    virtual inline uint16_t get_angle(uint16_t arc) = 0;
    virtual inline uint32_t get_color(uint16_t arc) = 0;
public:
    void Initialise();
    uint32_t get_led_color(uint8_t index, uint16_t angle) OPTIMIZE;
    void render(uint16_t zero_angle, int32_t rotation_rate) OPTIMIZE;
};