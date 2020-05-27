#pragma once
#include "Program.h"

class Image : public Program {
private:
    uint16_t iterators[LEDS_COUNT];
    bool reverse = 0;

protected:
    virtual uint16_t get_arc(uint16_t i) = 0;
    virtual uint16_t get_row_end(uint8_t row_index) = 0;
    virtual uint16_t get_angle(uint16_t arc) = 0;
    virtual uint32_t get_color(uint16_t arc) = 0;

public:
    void Initialise();
    
    inline bool get_reverse() {
        return reverse;
    }

    uint32_t get_led_color(uint8_t index, uint8_t y, uint16_t angle) __attribute__((optimize("O3")));
    
    void update(uint16_t frame_count, int32_t rotation_rate);

    void render(uint16_t zero_angle) __attribute__((optimize("O3")));
    
    virtual ~Image() = default;
};