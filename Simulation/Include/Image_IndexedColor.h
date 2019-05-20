#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include "Leds.h"
#include "Image_Base.h"
#include "Image_Pixels.h"
#include "Export.h"

using namespace std;

class Image_IndexedColor : public Image_Base {

private:
    uint32_t* colors = nullptr;
    uint8_t num_colors = 0;
    uint16_t angle_mask = 0;
    uint16_t color_mask = 1;

    uint8_t get_index_from_rgb(uint32_t rgb) {
        uint8_t index = 0;

        for (int i = 1; i < num_colors; i++) {
            if (get_color_diff(rgb, colors[i]) < get_color_diff(rgb, colors[index])) {
                index = i;
            }
        }

        return index;
    }

    inline uint16_t get_arc(uint16_t angle, uint8_t color) {
        return (angle & angle_mask) + color;
    }

protected:
    uint16_t get_angle(uint16_t arc) override {
        return arc & angle_mask;
    }

    uint8_t get_color_index(uint16_t arc) {
        return arc & color_mask;
    }

    uint32_t get_color(uint16_t arc) override {
        return colors[get_color_index(arc)];
    }

    void export_data(std::ofstream& stream) override {
        Image_Base::export_data(stream);

        stream << endl;
        Export::write_int32_array(stream, "colors", colors, num_colors);
    }

    void export_class(std::ofstream& stream, const std::string& data_ns) override {
        Image_Base::export_class(stream, data_ns);

        stream << endl 
               << "protected:" << endl;

        Export::write_int16(stream, "angle_mask", angle_mask);
        Export::write_int16(stream, "color_mask", color_mask);

        stream << endl
               << "\tinline uint16_t get_angle(uint16_t arc) override {" << endl
               << "\t\treturn arc & angle_mask;" << endl
               << "\t}" << endl;
        
        stream << endl
               << "\tinline uint32_t get_color(uint16_t arc) override {" << endl
               << "\t\treturn pgm_read_dword(&(" << data_ns.c_str() << "::colors[arc & color_mask]));" << endl
               << "\t}" << endl;
    }

public:
    Image_IndexedColor(Image_Pixels& arc_pixels, uint32_t* colors, uint8_t num_colors)
        : colors(colors)
        , num_colors(num_colors)
        , color_mask(1)
        , angle_mask(0) {

        color_mask = (1 << (((uint8_t)log2(num_colors)) + 1)) - 1;
        angle_mask = ~color_mask;
        
        vector<uint16_t> rows[PIXELS_PER_STRIP];

        for (int i = 0; i < PIXELS_PER_STRIP; i++) {
            int res = arc_pixels.get_resolution(i);

            int edge_threshold = ((1 << 16) / res) * 3;

            auto pixel_row = arc_pixels.arcs->at(i);

            vector<uint16_t> row;

            for (int j = 0; j < res; j++) {
                auto pixel_arc = pixel_row->at(j);
                uint16_t angle = (j / (float)res) * (1 << 16);

                if (!pixel_arc->empty()) {
                    uint32_t color = average_colors(pixel_arc);

                    uint8_t color_index = get_index_from_rgb(color);

                    size_t size = row.size();
                    if (size > 0) {
                        // Compression: combine adjacent arclets of the same color
                        uint16_t back = row.back();

                        if (get_color_index(back) == color_index) {
                            continue;
                        }

                        // Simple edge detection compression: if the previous arc is an average
                        // of this arc and the one before and has a an angle equal to the resolution
                        // we can assume it was an edge
                        if (size > 1) {
                            uint16_t backAngle = get_angle(back);

                            if (angle - backAngle <= edge_threshold) {
                                uint16_t back2 = row.at(row.size() - 2);

                                if (backAngle - get_angle(back2) > edge_threshold) {
                                    // the arc is sandwiched at minimum size between 2 large arcs
                                    uint8_t back2Color = get_color_index(back2);

                                    if (back2Color != color_index) {
                                        //uint8_t avgColor = average_colors(color6, back2Color);

                                        //if (avgColor == backColor) {
                                            // the back arc has an average color of the arcs it is sandwiched between
                                            // and we can assume its and edge
                                        row.pop_back();
                                        size--;
                                        //}
                                    }
                                }
                            }
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
