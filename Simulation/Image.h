#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include "Pixels.h"

using namespace std;

class Image {

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
                write_hex(stream, arcs[k]);
            }

            stream << endl;
        }
        stream << "\t}; // " << (k * 2) << " bytes" << endl;

        stream << endl;
        export_int16_array(stream, "row_ends", row_ends, PIXELS_PER_STRIP);
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

    virtual void export_int16_array(std::ofstream& stream, std::string name, uint16_t* arr, int len) {
        stream << "\tconst uint16_t " << name.c_str() << "[] PROGMEM {" << endl;
        stream << "\t\t";

        for (int i = 0; i < len; i++) {
            stream << (i > 0 ? ", " : "");
            write_hex(stream, arr[i]);
        }

        stream << endl << "\t}; // " << (len * 2) << " bytes" << endl;
    }

    void export_int32_array(std::ofstream& stream, std::string name, uint32_t* arr, int len) {
        stream << "\tconst uint32_t " << name.c_str() << "[] PROGMEM {" << endl;
        stream << "\t\t";

        for (int i = 0; i < len; i++) {
            stream << (i > 0 ? ", " : "");
            write_hex(stream, arr[i]);
        }

        stream << endl << "\t}; // " << (len * 4) << " bytes" << endl;
    }

    void export_int16(std::ofstream& stream, std::string name, uint16_t value) {
        stream << "\tconst uint32_t " << name.c_str() << " = ";
        write_hex(stream, value);
        stream << ";" << endl;
    }

    void write_hex(ofstream& stream, uint16_t val) {
        char const hex_chars[] = "0123456789ABCDEF";
        stream << "0x" 
               << hex_chars[(val & 0xF000) >> 12]
               << hex_chars[(val & 0x0F00) >>  8]
               << hex_chars[(val & 0x00F0) >>  4] 
               << hex_chars[(val & 0x000F)];
    } 

    void write_hex(ofstream& stream, uint32_t val) {
        char const hex_chars[] = "0123456789ABCDEF";
        stream << "0x" 
               << hex_chars[(val & 0xF0000000) >> 28]
               << hex_chars[(val & 0x0F000000) >> 24]
               << hex_chars[(val & 0x00F00000) >> 20]
               << hex_chars[(val & 0x000F0000) >> 16]
               << hex_chars[(val & 0x0000F000) >> 12] 
               << hex_chars[(val & 0x00000F00) >>  8]
               << hex_chars[(val & 0x000000F0) >>  4] 
               << hex_chars[(val & 0x0000000F)];
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

        return (r << 16) + (g << 8) + b;
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
               << "#include <avr/pgmspace.h>" << endl
               << "#include \"Image.h\"" << endl
               << "namespace " << ns.c_str() << "_data {" << endl;

        export_data(stream);

        stream << "}" << endl;

        stream << endl
               << "class " << ns.c_str() << " : public Image {" << endl;

        export_class(stream, ns + "_data");

        stream << "};" << endl;
        stream.close();
    }

    ~Image() {
        delete arcs;
    }
};