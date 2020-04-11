#pragma once
#include "./Leds.h"
#include "./Image.h"
#include "./Logging.h"

void Image::Initialise() {
    for (int i = 0; i < LEDS_COUNT; i++) {
        uint8_t row_index = i % LEDS_PER_STRIP;
        iterators[i] = get_row_end(row_index);
        Leds::set_color(i, get_color(get_arc(iterators[i])));
    }
}

inline uint32_t Image::get_led_color(uint8_t index, uint8_t y, uint16_t angle) {
    uint16_t end = get_row_end(y);
    uint16_t arc = get_arc(iterators[index]);

    if (angle < get_angle(arc)) {
        // angle has wrapped around to start
        if (y == 0) {
            arc = get_arc(iterators[index] = 0);
        } else {
            arc = get_arc(iterators[index] = get_row_end(y - 1) + 1);
        }
    }

    // iterate forwards till the next_arc angle is bigger
    // than the current angle
    do {
        if (iterators[index] == end) {
            return get_color(arc);
        }

        uint16_t next_arc = get_arc(iterators[index] + 1);

        if (angle <= get_angle(next_arc)) {
            return get_color(arc);
        }

        ++iterators[index];

        arc = next_arc;
    } while (true);
}

void Image::update(uint16_t frame_count, int32_t rotation_rate) {
    reverse = rotation_rate < 0;
}

void Image::render(uint16_t zero_angle) {
    uint8_t* pixels = Leds::leds.getPixels();

    for (uint8_t i = 0, y = 0; i < LEDS_COUNT; i++, y++) {
        if (y == LEDS_PER_STRIP) y = 0;

        uint16_t angle = zero_angle + Leds::get_angle(i);

        uint32_t color = get_led_color(i, y, reverse ? ~angle : angle);
        
        memcpy(&pixels[i * 3], &color, 3);
    }
};