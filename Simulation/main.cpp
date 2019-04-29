#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include "Pixels.h"
#include "Graphics.h"
#include "Programs.h"
#include "Mpu.h"
#include "HallSensor.h"
#include "SensorData.h"
#include "Adafruit_DotStar.h"
#include "Bmp.h"
#include "Image_6BitColor.h"
#include "Image_IndexedColor.h"
#include "Image_Grayscale.h"

bool off = true; // clear all pixels

float vertices[NUM_PIXELS * 5];

float radians(uint16_t angle) {
    return  (angle / (float)65535) * 2 * M_PI;
}

void updateVertices(uint16_t angle) {
    for (int i = 0; i < NUM_PIXELS; i++) {
        auto pos = Pixels::positions[i];
        int addr = i * 5;
        int vert = i * 3;
        auto rads = radians(pos.angle + angle);

        // cos and sin are reversed as angle is 0 on y-axis
        vertices[addr + 0] = pos.dist * (float)sin(rads) / (float)255; // x
        vertices[addr + 1] = pos.dist * (float)cos(rads) / (float)255; // y

        vertices[addr + 2] = Adafruit_DotStar::vertices[vert + 0] / (float)255; // r
        vertices[addr + 3] = Adafruit_DotStar::vertices[vert + 1] / (float)255; // g
        vertices[addr + 4] = Adafruit_DotStar::vertices[vert + 2] / (float)255; // b
    }
}

int main() {
    SensorData::init();

    Pixels::Strip strips[] = {
        Pixels::Strip(
           59,   9,
          262, 140
        ),
        Pixels::Strip(
            9,  -59,
          140, -262
        ),
        Pixels::Strip(
            -59,  -9,
           -262,-140
        ),
        Pixels::Strip(
             -9,  59,
           -140, 262
        )
    };

    Pixels::init(strips);

    Mpu::init();

    std::string imageName("rocket");
    Bmp bmp("Images/" + imageName + ".bmp");
    Image_Pixels pixels(bmp, Pixels::min_dist);

    uint32_t colors[] = { 
          0x000000, 0xFF0000, 0xFFFFFF
        , 0x333333, 0x666666, 0x999999, 0xCCCCCC
        , 0x330000, 0x660000, 0x990000, 0xCC0000
        , 0xFF3333, 0xFF6666, 0xFF9999, 0xFFCCCC
    };

    Image *image = new Image_IndexedColor(pixels, colors, 15);
    
    //Image *image = new Image_Grayscale(pixels);
    
    image->export_code(std::string("../BikeWheel/").append(imageName).append(".h"), imageName);
    return 0;

    if (!Graphics::init()) {
        return -1;
    }

    do {
        if (SensorData::get_ended()) {
            Graphics::clear();
            SensorData::reset();
            Mpu::init();
        }

        SensorData::update();
        
        Mpu::update();

        HallSensor::update();

        //uint16_t angle = HallSensor::angle;
        uint16_t angle = Mpu::angle;
        uint32_t rotation_rate_abs = abs(Mpu::rotation_rate);

        //std::cout << Mpu::angle << std::endl;

        if (rotation_rate_abs < 5000) {
            off = true;
        }
        else if (rotation_rate_abs > 15000) {
            off = false;
        }

        if (off) {
            Programs::set_color(0x000000);
        }
        else {
            //Programs::color_segments(Mpu::angle);
            //Programs::spiral(angle);
            //Programs::rainbow(angle);
            //Programs::text(Mpu::angle, 15, "MASA CRITICA ");
            Programs::image(Mpu::angle, Mpu::rotation_rate, image);
        }

        updateVertices(angle);

        //Sleep(100);

    } while (Graphics::render(sizeof(vertices), (void*)vertices));

    Graphics::terminate();

    return 0;
}