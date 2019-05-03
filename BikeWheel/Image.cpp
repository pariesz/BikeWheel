#pragma once
#include "./Leds.h"
#include "./Image.h"

Image::Image() {
    // init iterators
    for (int i = 0; i < PIXELS_PER_STRIP; i++) {
        iterators[i] = 0;
    }
}

uint32_t Image::get_color(uint8_t row_index, uint16_t angle, uint32_t rotation_rate) {
    uint16_t i = iterators[row_index];
    uint16_t end = get_row_end(row_index);
    uint16_t start = i = row_index == 0 ? 0 : get_row_end(row_index - 1) + 1;
    uint16_t arc = get_arc(i);

    if (rotation_rate < 0) {
        if (i != end && angle > get_angle(get_arc(++i))) {
            // angle has wrapped around to end
            i = end;
        }

        // iterate backwards till the arc angle is smaller
        // than the current angle
        while (true) {
            if (i == start) {
                break;
            }

            uint16_t arc = get_arc(--i);
            if (angle > get_angle(arc)) {
                break;
            }
        }

    } else {
        if (angle < get_angle(arc)) {
            // angle has wrapped around to start
            i = start;
        }
        // iterate forwards till the next_arc angle is bigger
        // than the current angle
        while (true) {
            if (i == end) {
                break;
            }

            uint16_t next_arc = get_arc(++i);
            if (angle < get_angle(next_arc)) {
                --i; break;
            }

            arc = next_arc;
        }
    }

    iterators[row_index] = i;

    return get_color(arc);
}

void Image::render(uint16_t zero_angle, uint32_t rotation_rate) {
    for (uint8_t i = 0; i < NUM_PIXELS; i++) {
        uint16_t angle = zero_angle + Leds::get_angle(i);
        Leds::set_color(i, get_color(i % PIXELS_PER_STRIP, angle, rotation_rate));
    }
};

