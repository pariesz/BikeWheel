#pragma once
#include "Program.h"

class Image : public Program {
private:
    uint16_t iterators[NUM_PIXELS];
protected:
    virtual inline uint16_t get_arc(uint16_t i) = 0;
    virtual inline uint16_t get_row_end(uint8_t row_index) = 0;
    virtual inline uint16_t get_angle(uint16_t arc) = 0;
    virtual inline uint32_t get_color(uint16_t arc) = 0;
public:
    void Initialise();
    uint32_t get_led_color(uint8_t index, uint16_t angle) __attribute__((optimize("O3")));
    void render(uint16_t zero_angle, int32_t rotation_rate) __attribute__((optimize("O3")));
    virtual ~Image() = default;
};