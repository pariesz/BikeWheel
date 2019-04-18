#include "Adafruit_DotStar.h"

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
void Adafruit_DotStar::setBrightness(uint8_t) {

}
void Adafruit_DotStar::begin() {

}
void Adafruit_DotStar::show() {

}
Adafruit_DotStar::~Adafruit_DotStar() {
    delete vertices;
}