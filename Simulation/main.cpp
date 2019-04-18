#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include "Pixels.h"
#include "Shaders.h"
#include "Graphics.h"
#include "Programs.h"
#include "Mpu.h"
#include "SensorData.h"
#include "Adafruit_DotStar.h"

float vertices[NUM_PIXELS * 5];

float radians(uint16_t angle) {
    return (angle / (float)65535) * 360 * (M_PI / (float)180);
}

void updateVertices(uint16_t angle) {
    for (int i = 0; i < NUM_PIXELS; i++) {
        auto pos = Pixels::positions[i];
        int addr = i * 5;
        int vert = i * 3;
        auto rads = radians(pos.angle + angle);

        vertices[addr + 0] = pos.dist * (float)cos(rads) / (float)255; // x
        vertices[addr + 1] = pos.dist * (float)sin(rads) / (float)255; // y

        vertices[addr + 2] = Adafruit_DotStar::vertices[vert + 0] / (float)255;      // r
        vertices[addr + 3] = Adafruit_DotStar::vertices[vert + 1] / (float)255;      // g
        vertices[addr + 4] = Adafruit_DotStar::vertices[vert + 2] / (float)255;      // b
    }
}

int main() {
    Pixels::Strip strips[] = {
        Pixels::Strip(
             -9,  44,
           -173, 219
        ),
        Pixels::Strip(
             47,   6,
            217, 179
        ),
        Pixels::Strip(
              9, -44,
            188,-220
        ),
        Pixels::Strip(
            -48,  -6,
           -234,-183
        )
    };

    Pixels::init(strips);

    SensorData::init();

    if (!Graphics::init()) {
        return -1;
    }

    do {
        SensorData::update();
        Mpu::update();

        Programs::set_half_color(0x00FF00, Mpu::angle);
        updateVertices(Mpu::angle);

    } while (Graphics::render(sizeof(vertices), (void*)vertices));

    Graphics::terminate();
    return 0;
}