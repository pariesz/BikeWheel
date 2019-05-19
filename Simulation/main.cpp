#define SIMULATION 1
#define LOGGING 1

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include "Graphics.h"
#include "SensorData.h"
#include "Bmp.h"
#include "Image_6BitColor.h"
#include "Image_IndexedColor.h"
#include "Image_Grayscale.h"
#include "Leds_Export.h"
#include "Shared.h"

bool on = true;

WheelSensors sensors;
Image_Base *image = nullptr;
LaPandora la_pandora;
Hamster hamster;
NyanCat nyan_cat;
Poo poo;

void loop() {
    if (!SensorData::update()) {
        // reset sensors and graphics
        Graphics::clear();
        sensors = WheelSensors();
        sensors.setup();
    }

    sensors.loop();

    uint16_t angle = sensors.angle;

    //Logging::test_segments(angle, SensorData::get().hall);
    //Programs::spiral(angle);
    //Programs::rainbow(angle);
    //Programs::masa_critica(angle);
    //Programs::rainbow_text(angle, 37, "- BCN - Critical Mass - Masa Critica");
    //Programs::kaleidoscope(angle);
    //Programs::umbrella(angle);
    //Programs::radioactive(angle);
    //image->render(angle, sensors.rotation_rate);
    //hamster.render(angle, sensors.rotation_rate);
    poo.render(angle, sensors.rotation_rate);

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
    //std::string imageName("fist");
    //BMP bmp("Images/" + imageName + ".bmp");
    //Image_Pixels pixels(bmp, Leds::min_dist);
    //uint32_t colors[] = { 0x000000, 0xFF0000 };
    //image = new Image_IndexedColor(pixels, colors, 2);

    // HAMSTER
    //std::string imageName("roll2");
    //BMP bmp("Images/" + imageName + ".bmp");
    //Image_Pixels pixels(bmp, Leds::min_dist);
    //uint32_t colors[] = { 
    //    0x000000,
    //    0xFFCC00,
    //    0xFF5555,
    //    0xFFFFFF
    //};
    //image = new Image_IndexedColor(pixels, colors, 5);

    // NYAN CAT
    //std::string imageName("NyanCat1");
    //BMP bmp("Images/" + imageName + ".bmp");
    //Image_Pixels pixels(bmp, Leds::min_dist);
    //uint32_t colors[] = {
    //    0x000000, 0x888888, 0xFFFFFF,
    //    0xff0000, 0x880000,
    //    0xff8800,
    //    0xffff00, 0x888800,
    //    0x00ff00, 0x008800,
    //    0x00ffff, 0x008888,
    //    0xff00ff, 0x880088
    //   
    //};
    //image = new Image_IndexedColor(pixels, colors, 14);
    //image = new Image_6BitColor(pixels);


    // POO
    //std::string imageName("Poo");
    //BMP bmp("Images/" + imageName + ".bmp");
    //Image_Pixels pixels(bmp, Leds::min_dist);
    //uint32_t colors[] = { 
    //    0x000000, 0x999999, 0xFFFFFF,
    //    0x3b1800 ,0x803300, 0xff7f2a, 
    //    0xff0000, 0x660000
    //};
    //image = new Image_IndexedColor(pixels, colors, 8);

    //uint32_t mrSplat_colors[] = { 0x000000, 0x00FFFF, 0xFF9900 };
    //Image_Base *image = new Image_IndexedColor(pixels, mrSplat_colors, 3);

    //Image_Base *image = new Image_Grayscale(pixels);

    //image->export_code(std::string("../Shared/Images/").append(imageName).append(".h"), imageName);
    //return 0;

    //la_pandora.initialize();
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