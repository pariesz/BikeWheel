#pragma once
namespace Export {
    using namespace std;
    void write_hex(ofstream& stream, uint8_t val);
    void write_hex(ofstream& stream, uint16_t val);
    void write_hex(ofstream& stream, uint32_t val);
    void write_int8_array(std::ofstream& stream, std::string name, uint8_t* arr, int len);
    void write_int16_array(std::ofstream& stream, std::string name, uint16_t* arr, int len);
    void write_int32_array(std::ofstream& stream, std::string name, uint32_t* arr, int len);
    void write_int8(std::ofstream& stream, std::string name, uint8_t value);
    void write_int16(std::ofstream& stream, std::string name, uint16_t value);
}