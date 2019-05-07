#pragma once
#include <vector>
#include "Leds.h"
#include "Image_Base.h"
#include "Image_Pixels.h"

using namespace std;

class Image_6BitColor : public Image_Base {

private:
    unsigned char average_colors(unsigned char a, unsigned char b) {
        return (((a & 0x30) >> 1) + ((b & 0x30) >> 1))
             + (((a & 0x0C) >> 1) + ((b & 0x0C) >> 1))
             + (((a & 0x03) >> 1) + ((b & 0x03) >> 1));
    }

    inline uint8_t rgb_to_6bit(uint32_t rgb) {
        return ((rgb & 0x00C00000) >> 18)
             + ((rgb & 0x0000C000) >> 12)
             + ((rgb & 0x000000C0) >> 6);
    }

    inline uint8_t get_color_6bit(uint16_t arc) {
        return arc & 0x003f;
    }

    inline uint16_t get_arc(uint16_t angle, uint8_t color) {
        return (angle & 0xffc0) + color;
    }

protected:
    uint16_t get_angle(uint16_t arc) override {
        return arc & 0xffc0;
    }

    uint32_t get_color(uint16_t arc) override {
        return ((arc & 0x0030) << 18)
             + ((arc & 0x000C) << 12)
             + ((arc & 0x0003) << 6);
    }

    void export_class(std::ofstream& stream, const std::string& data_ns) override {
        Image_Base::export_class(stream, data_ns);

        stream << endl
            << "protected:" << endl;

        stream
            << "\tinline uint16_t get_angle(uint16_t arc) override {" << endl
            << "\t\treturn arc & 0xFFC0;" << endl
            << "\t}" << endl;

        stream << endl
            << "\tinline uint32_t get_color(uint16_t arc) override {" << endl
            << "\t\treturn ((arc & 0x0030) << 18) + ((arc & 0x000C) << 12) + ((arc & 0x0003) << 6);" << endl
            << "\t}" << endl;
    }

public:
    Image_6BitColor(Image_Pixels& arc_pixels) {
        vector<uint16_t> rows[PIXELS_PER_STRIP];

        for (int i = 0; i < PIXELS_PER_STRIP; i++) {
            int res = arc_pixels.get_resolution(i);
            
            int edge_threshold = ((1 << 16) / res) * 3;

            auto pixel_row = arc_pixels.arcs->at(i);

            vector<uint16_t> row;

            for (int j = 0; j < res; j++) {
                auto pixel_arc = pixel_row->at(j);
                uint16_t angle = (j / (float)res) * 0xFFFF;

                if (!pixel_arc->empty()) {
                    uint32_t color32 = Image_Base::average_colors(pixel_arc);
                    
                    uint8_t color6 = rgb_to_6bit(color32);

                    size_t size = row.size();
                    if (size > 0) {
                        // Compression: combine adjacent arclets of the same color
                        uint16_t back = row.back();
                        uint8_t backColor = get_color_6bit(back);

                        if (backColor == color6) {
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
                                    uint8_t back2Color = get_color_6bit(back2);

                                    if (back2Color != color6) {
                                        uint8_t avgColor = average_colors(color6, back2Color);

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
                    row.push_back(get_arc(angle, color6));
                }
            }
            rows[i] = row;
        }
        Initialize(rows);
    }
};
