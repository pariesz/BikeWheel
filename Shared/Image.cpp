#pragma once
#include "./Leds.h"
#include "./Image.h"

void Image::Initialise() {
    for (int i = 0; i < NUM_PIXELS; i++) {
        uint8_t row_index = i % PIXELS_PER_STRIP;
        iterators[i] = get_row_end(row_index);
    }
}

uint32_t Image::get_led_color(uint8_t index, uint16_t angle) {
    uint8_t row_index = index % PIXELS_PER_STRIP;
    uint16_t end = get_row_end(row_index);
    uint16_t start = row_index == 0 ? 0 : get_row_end(row_index - 1) + 1;
    uint16_t i = iterators[index];
    uint16_t arc = get_arc(i);

    if (angle < get_angle(arc)) {
        // angle has wrapped around to start
        arc = get_arc(i = start);
    }

    // iterate forwards till the next_arc angle is bigger
    // than the current angle
    while (true) {
        if (i == end) {
            break;
        }

        uint16_t next_arc = get_arc(++i);

        if (angle <= get_angle(next_arc)) {
            --i; break;
        }

        arc = next_arc;
    }

    iterators[index] = i;

    return get_color(arc);
}

void Image::render(uint16_t zero_angle, int32_t rotation_rate) {
    for (uint8_t i = 0; i < NUM_PIXELS; i++) {
        uint16_t angle = zero_angle + Leds::get_angle(i);
        Leds::set_color(i, get_led_color(i, rotation_rate < 0 ? ~angle : angle));
    }
};