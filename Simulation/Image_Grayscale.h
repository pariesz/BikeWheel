#pragma once
#include "Image.h"
#include "Image_Pixels.h"

using namespace std;

class Image_Grayscale : public Image {

private:
    uint8_t get_grayscale_from_rgb(uint32_t rgb) {
        uint8_t r = (rgb & 0x00ff0000) >> 16;
        uint8_t g = (rgb & 0x0000ff00) >> 8;
        uint8_t b = (rgb & 0x000000ff) >> 0;
        return (15 * (r + g + b)) / (255 * 3);
    }

    inline uint16_t get_arc(uint16_t angle, uint8_t color) {
        return (angle & 0xFFF0) + color;
    }

protected:
    uint16_t get_angle(uint16_t arc) override {
        return arc & 0xFFF0;
    }

    uint32_t get_color(uint16_t arc) override {
        uint8_t i = ((arc & 0xF) << 4) + (arc & 0xF);
        
        uint8_t rgba[] = { i, i, i, 0 }; // bits are stored in reverse order

        return *(uint32_t*)rgba; // type punning
    }

public:
    Image_Grayscale(Image_Pixels& arc_pixels) {
        vector<uint16_t> rows[PIXELS_PER_STRIP];

        for (int i = 0; i < PIXELS_PER_STRIP; i++) {
            int res = arc_pixels.get_resolution(i);

            auto pixel_row = arc_pixels.arcs->at(i);

            vector<uint16_t> row;

            for (int j = 0; j < res; j++) {
                auto pixel_arc = pixel_row->at(j);
                uint16_t angle = (j / (float)res) * (1 << 16);

                if (!pixel_arc->empty()) {
                    uint32_t color = average_colors(pixel_arc);

                    uint8_t color_index = get_grayscale_from_rgb(color);

                    if (row.size() > 0) {
                        // Combine adjacent arclets of the same color
                        if ((row.back() & 0xF) == color_index) {
                            continue;
                        }
                    }
                    row.push_back(get_arc(angle, color_index));
                }
            }
            rows[i] = row;
        }
        Initialize(rows);
    }
};