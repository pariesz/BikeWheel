#include "Adafruit_DotStar_Mock.h"
#include "Arduino_Mock.h"
#include "Graphics.h"
#include "Leds.h"
#include "Wheel_Sensors.h"

uint8_t* Adafruit_DotStar::vertices;

Adafruit_DotStar::Adafruit_DotStar(uint16_t num_pixels, uint8_t mode) {
    vertices = new uint8_t[num_pixels * 3];
}

void Adafruit_DotStar::setPixelColor(uint16_t index, uint32_t color) {
    int addr = index * 3;
    vertices[addr + 2] = (color & 0x000000ff) >> 0;
    vertices[addr + 1] = (color & 0x0000ff00) >> 8;
    vertices[addr + 0] = (color & 0x00ff0000) >> 16;
}

void Adafruit_DotStar::setPixelColor(uint16_t index, uint8_t r, uint8_t g, uint8_t b) {
    int addr = index * 3;
    vertices[addr + 2] = b;
    vertices[addr + 1] = g;
    vertices[addr + 0] = r;
}

void Adafruit_DotStar::setBrightness(uint8_t b) {

}

void Adafruit_DotStar::begin() {

}

inline float uint16ToRadians(uint16_t angle) {
    return  (angle / (float)65535) * 2 * PI;
}

void Adafruit_DotStar::show() {
    for (int i = 0; i < NUM_PIXELS; i++) {
        int addr = i * 5;
        int vert = i * 3;
        auto rads = uint16ToRadians(Leds::get_angle(i) + Wheel_Sensors::angle);

        // cos and sin are reversed as angle is 0 on y-axis
        Graphics::vertices[addr + 0] = Leds::get_distance(i) * (float)sin(rads) / (float)255; // x
        Graphics::vertices[addr + 1] = Leds::get_distance(i) * (float)cos(rads) / (float)255; // y

        Graphics::vertices[addr + 2] = vertices[vert + 0] / (float)255; // r
        Graphics::vertices[addr + 3] = vertices[vert + 1] / (float)255; // g
        Graphics::vertices[addr + 4] = vertices[vert + 2] / (float)255; // b
    }
}

Adafruit_DotStar::~Adafruit_DotStar() {
    delete vertices;
}
