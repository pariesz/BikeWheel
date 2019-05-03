#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include "Leds.h"
#include "Export.h"

using namespace std;

class Image_Base {

private:
    uint16_t* arcs;
    uint16_t row_ends[PIXELS_PER_STRIP];
    uint16_t iterators[PIXELS_PER_STRIP];

protected:
    virtual uint16_t get_angle(uint16_t arc) = 0;

    virtual uint32_t get_color(uint16_t arc) = 0;

    virtual void export_data(std::ofstream& stream) {
        stream << "\tconst uint16_t arcs[] PROGMEM {" << endl;

        int k = 0;
        for (int i = 0; i < PIXELS_PER_STRIP; i++) {
            stream << "\t\t";

            for (; k <= row_ends[i]; k++) {
                stream << (k > 0 ? ", " : "  ");
                Export::write_hex(stream, arcs[k]);
            }

            stream << endl;
        }
        stream << "\t}; // " << (k * 2) << " bytes" << endl;

        stream << endl;
        Export::write_int16_array(stream, "row_ends", row_ends, PIXELS_PER_STRIP);
    }

    virtual void export_class(std::ofstream& stream, const std::string& data_ns) {
        stream << "protected:";

        stream << endl
               << "\tinline uint16_t get_arc(uint16_t i) override {" << endl
               << "\t\treturn pgm_read_word(&" << data_ns.c_str() << "::arcs[i]);" << endl
               << "\t}" << endl;

        stream << endl
               << "\tinline uint16_t get_row_end(uint8_t row_index) override {" << endl
               << "\t\treturn pgm_read_word(&" << data_ns.c_str() << "::row_ends[row_index]);" << endl
               << "\t}" << endl;
    }

    uint32_t get_color_diff(uint32_t c1, uint32_t c2) {
        int r = abs((int)((c1 & 0x00ff0000) - (c2 & 0x00ff0000)));
        int g = abs((int)((c1 & 0x0000ff00) - (c2 & 0x0000ff00)));
        int b = abs((int)((c1 & 0x000000ff) - (c2 & 0x000000ff)));
        return r + g + b;
    }

    uint32_t average_colors(const vector<int>* colors) {
        // Average the color of all pixels within the x,y space of the arclet 
        auto size = colors->size();
        auto it = colors->begin();

        unsigned char r = (*it & 0x00ff0000) >> 16;
        unsigned char g = (*it & 0x0000ff00) >>  8;
        unsigned char b = (*it & 0x000000ff) >>  0;

        float combine_scale = 1.0f - (1.0f / size);

        for (++it; it != colors->end(); it++) {
            r = (r * combine_scale) + (((*it & 0x00ff0000) >> 16) / (float)size);
            g = (g * combine_scale) + (((*it & 0x0000ff00) >>  8) / (float)size);
            b = (b * combine_scale) + (((*it & 0x000000ff) >>  0) / (float)size);
        }

        return ((uint32_t)r << 16) + ((uint16_t)g << 8) + b;
    }

    void Initialize(vector<uint16_t>* rows) {
        int size = 0;

        for (int i = 0; i < PIXELS_PER_STRIP; i++) {
            vector<uint16_t> row = rows[i];

            for (auto arc = row.begin(); arc != row.end(); arc++) {
                size++;
            }
        }

        arcs = new uint16_t[size];

        int k = -1;
        for (int i = 0; i < PIXELS_PER_STRIP; i++) {
            vector<uint16_t> row = rows[i];

            for (auto arc = row.begin(); arc != row.end(); arc++) {
                arcs[++k] = *arc;
            }

            row_ends[i] = k;

            // init iterators
            iterators[i] = 0;
        }
    }

public:
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

    void export_code(std::string& filename, std::string& ns) {
        std::ofstream stream;

        stream.open(filename);
        stream << "#pragma once" << endl
               << "#ifdef SIMULATION"
               << "#include \"Arduino_Mock.h\"" << endl
               << "#else" << endl
               << "#include <avr/pgmspace.h>" << endl
               << "#endif" << endl
               << endl
               << "#include \"../Image.h\"" << endl
               << endl
               << "namespace " << ns.c_str() << "_data {" << endl;

        export_data(stream);

        stream << "}" << endl;

        stream << endl
               << "class " << ns.c_str() << " : public Image {" << endl;

        export_class(stream, ns + "_data");

        stream << "};" << endl;
        stream.close();
    }

    void render(uint16_t zero_angle, uint32_t rotation_rate) {
        for (uint8_t i = 0; i < NUM_PIXELS; i++) {
            uint16_t angle = zero_angle + Leds::get_angle(i);
            Leds::set_color(i, get_color(i % PIXELS_PER_STRIP, angle, rotation_rate));
        }
    }

    ~Image_Base() {
        delete arcs;
    }
};