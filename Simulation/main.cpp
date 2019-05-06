#define SIMULATION 1
#define LOGGING 1

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include "Leds.h"
#include "Programs.h"
#include "WheelSensors.h"
#include "Graphics.h"
#include "Logging.h"
#include "SensorData.h"
#include "Bmp.h"
#include "Image_6BitColor.h"
#include "Image_IndexedColor.h"
#include "Image_Grayscale.h"
#include "Leds_Export.h"
#include "LaPandora.h"
#include "rocket.h"

bool on = true;
WheelSensors sensors;
Image_Base *image = nullptr;
LaPandora la_pandora;

void loop() {
    if (!SensorData::update()) {
        // reset sensors and graphics
        Graphics::clear();
        sensors = WheelSensors();
        sensors.setup();
    }

    sensors.loop();

    uint16_t angle = sensors.angle;

    //std::cout << Sensors::angle << std::endl;

    //Logging::test_segments(angle, SensorData::get().hall);
    //Programs::spiral(angle);
    //Programs::rainbow(angle);
    //Programs::masa_critica(angle);
    //Programs::rainbow_text(angle, 37, "- BCN - Critical Mass - Masa Critica");
    //Programs::flower(angle);
    //Programs::umbrella(angle);
    //Programs::radioactive(angle);
    image->render(angle, sensors.rotation_rate);

    Leds::leds.show(sensors.angle);
    //Sleep(100);
}


void export_leds() {
    float led_positions[4][NUM_PIXEL_STRIPS] = {
        {
           59,   9,
          262, 140
        },
        {
            9,  -59,
          140, -262
        },
        {
            -59,  -9,
           -262,-140
        },
        {
             -9,  59,
           -140, 262
        }
    };
    Leds_Export::export_code("../BikeWheel/Leds.cpp", led_positions);
}

int main() {
    //export_leds();
    //return 0;

    // ROCKET
    //std::string imageName("rocket");
    //BMP bmp("Images/" + imageName + ".bmp");
    //Image_Pixels pixels(bmp, Leds::min_dist);
    //uint32_t colors[] = { 0x000000, 0xFF0000, 0x0000FF, 0xFFFFFF };
    //image = new Image_IndexedColor(pixels, colors, 4);

    // SPACE
    //std::string imageName("space");
    //BMP bmp("Images/" + imageName + ".bmp");
    //Image_Pixels pixels(bmp, Leds::min_dist);
    //image = new Image_6BitColor(pixels);

    // FIST
    std::string imageName("fist");
    BMP bmp("Images/" + imageName + ".bmp");
    Image_Pixels pixels(bmp, Leds::min_dist);
    uint32_t colors[] = { 0x000000, 0xFF0000 };
    image = new Image_IndexedColor(pixels, colors, 2);

    //uint32_t mrSplat_colors[] = { 0x000000, 0x00FFFF, 0xFF9900 };
    //Image_Base *image = new Image_IndexedColor(pixels, mrSplat_colors, 3);

    //Image_Base *image = new Image_Grayscale(pixels);

    image->export_code(std::string("../BikeWheel/Images/").append(imageName).append(".h"), imageName);
    return 0;

    la_pandora.initialize();
    SensorData::init();
    sensors.setup();

    if (!Graphics::init()) {
        return -1;
    }
    do {
        loop();
    } while (Graphics::render());

    Graphics::terminate();
    return 0;
}