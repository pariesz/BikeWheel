#include <iostream>
#include <fstream>
#include "Export.h"

namespace Export {
    using namespace std;
    char const hex_chars[] = "0123456789ABCDEF";

    void write_hex(ofstream& stream, uint8_t val) {
        stream << "0x"
            << hex_chars[(val & 0xF0) >> 4]
            << hex_chars[(val & 0x0F)];
    }

    void write_hex(ofstream& stream, uint16_t val) {
        stream << "0x"
            << hex_chars[(val & 0xF000) >> 12]
            << hex_chars[(val & 0x0F00) >> 8]
            << hex_chars[(val & 0x00F0) >> 4]
            << hex_chars[(val & 0x000F)];
    }

    void write_hex(ofstream& stream, uint32_t val) {
        stream << "0x"
            << hex_chars[(val & 0xF0000000) >> 28]
            << hex_chars[(val & 0x0F000000) >> 24]
            << hex_chars[(val & 0x00F00000) >> 20]
            << hex_chars[(val & 0x000F0000) >> 16]
            << hex_chars[(val & 0x0000F000) >> 12]
            << hex_chars[(val & 0x00000F00) >> 8]
            << hex_chars[(val & 0x000000F0) >> 4]
            << hex_chars[(val & 0x0000000F)];
    }

    void write_int8_array(std::ofstream& stream, std::string name, uint8_t* arr, int len) {
        stream << "\tconst uint8_t " << name.c_str() << "[] PROGMEM {";
        stream << "\t\t";

        for (int i = 0; i < len; i++) {
            stream << (i > 0 ? ", " : "");

            if (!(i % 10)) {
                stream << endl << "\t\t";
            }

            write_hex(stream, arr[i]);
        }

        stream << endl << "\t}; // " << len << " bytes" << endl;
    }

    void write_int16_array(std::ofstream& stream, std::string name, uint16_t* arr, int len) {
        stream << "\tconst uint16_t " << name.c_str() << "[] PROGMEM {";
        stream << "\t\t";

        for (int i = 0; i < len; i++) {
            stream << (i > 0 ? ", " : "");
            
            if (!(i % 8)) {
                stream << endl << "\t\t";
            }

            write_hex(stream, arr[i]);
        }

        stream << endl << "\t}; // " << (len * 2) << " bytes" << endl;
    }

    void write_int32_array(std::ofstream& stream, std::string name, uint32_t* arr, int len) {
        stream << "\tconst uint32_t " << name.c_str() << "[] PROGMEM {";
        stream << "\t\t";

        for (int i = 0; i < len; i++) {
            stream << (i > 0 ? ", " : ""); 
            
            if (!(i % 6)) {
                stream << endl << "\t\t";
            }

            write_hex(stream, arr[i]);
        }

        stream << endl << "\t}; // " << (len * 4) << " bytes" << endl;
    }

    void write_int8(std::ofstream& stream, std::string name, uint8_t value) {
        stream << "\tconst uint8_t " << name.c_str() << " = ";
        write_hex(stream, value);
        stream << ";" << endl;
    }

    void write_int16(std::ofstream& stream, std::string name, uint16_t value) {
        stream << "\tconst uint16_t " << name.c_str() << " = ";
        write_hex(stream, value);
        stream << ";" << endl;
    }
}