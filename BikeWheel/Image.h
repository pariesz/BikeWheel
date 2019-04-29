#pragma once
#include "Pixels.h"

class Image_IndexedColor {
private:
    const uint16_t* arcs = nullptr;
    const uint16_t* row_ends = nullptr;
    const uint32_t* colors = nullptr;
    const uint16_t angle_mask;
    const uint16_t color_mask;

    uint16_t iterators[PIXELS_PER_STRIP];

    inline uint16_t get_angle(uint16_t arc) {
        return arc & angle_mask;
    }

    inline uint32_t get_color(uint16_t arc) {
        return colors[arc & color_mask];
    }

    uint32_t get_color(uint8_t row_index, uint16_t angle, uint32_t rotation_rate) {
        uint16_t i = iterators[row_index];
        uint16_t end = row_ends[row_index];
        uint16_t start = i = row_index == 0 ? 0 : row_ends[row_index - 1] + 1;
        uint16_t arc = arcs[i];

        if (rotation_rate < 0) {
            if (i != end && angle > get_angle(arcs[++i])) {
                // angle has wrapped around to end
                i = end;
            }

            // iterate backwards till the arc angle is smaller
            // than the current angle
            while (true) {
                if (i == start) {
                    break;
                }

                uint16_t arc = arcs[--i];
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

                uint16_t next_arc = arcs[++i];
                if (angle < get_angle(next_arc)) {
                    --i; break;
                }

                arc = next_arc;
            }
        }

        iterators[row_index] = i;

        return get_color(arc);
    }

public:
    Image_IndexedColor(
        const uint16_t* arcs,
        const uint16_t* row_ends,
        const uint32_t* colors,
        const uint8_t colors_bits)
        : arcs(arcs)
        , row_ends(row_ends)
        , colors(colors)
        , color_mask((1 << colors_bits) - 1)
        , angle_mask(~((1 << colors_bits) - 1)) {

        // init iterators
        for (int i = 0; i < PIXELS_PER_STRIP; i++) {
            iterators[i] = 0;
        }
    }

    void render(uint16_t zero_angle, uint32_t rotation_rate) {
        for (uint8_t i = 0; i < NUM_PIXELS; i++) {
            uint16_t angle = zero_angle + Pixels::positions[i].angle;
            Pixels::leds.setPixelColor(i, get_color(i % PIXELS_PER_STRIP, angle, rotation_rate));
        }
    }
};