#define SIMULATION 1
#define LOGGING 1

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include <shared.h>
#include "Graphics.h"
#include "OutputData.h"
#include "MockData.h"
#include "Bmp.h"
#include "Image_6BitColor.h"
#include "Image_IndexedColor.h"
#include "Image_Grayscale.h"
#include "Leds_Export.h"

bool on = true;

//OutputData data_source("output.csv");
MockData data_source(0);

int16_t mpu_offsets[] = { 0, 0, 0, 0, 0, 0 };
Mpu mpu;

Image_Base *image = nullptr;
Rays program;

void loop() {
    // Simulate sensor data
    DataLine dl;
    if (!data_source.try_get_next(dl)) {
        // reset sensors and graphics
        Graphics::clear();
        mpu = Mpu();
        mpu.setup(mpu_offsets);
    }

    MPU6050::setMotion6(dl.acc_x, dl.acc_y, dl.acc_z, dl.gyro_x, dl.gyro_y, dl.gyro_z);
    digitalWrite(HALL_PIN, dl.hall);

    // Run program
    mpu.update();
    program.render(mpu.get_angle(), mpu.get_rotation_rate());

    // Update graphics vertices buffer
    for (int i = 0; i < LEDS_COUNT; i++) {
        int addr = i * 5;
        int vert = i * 3;
        double radians = ((Leds::get_angle(i) + mpu.get_angle()) / (float)0xFFFF) * TWO_PI;

        // cos and sin are reversed as angle is 0 on y-axis
        Graphics::vertices[addr + 0] = Leds::get_distance(i) * (float)sin(radians) / (float)255; // x
        Graphics::vertices[addr + 1] = Leds::get_distance(i) * (float)cos(radians) / (float)255; // y

        Graphics::vertices[addr + 2] = Adafruit_DotStar::vertices[vert + 0] / (float)255; // r
        Graphics::vertices[addr + 3] = Adafruit_DotStar::vertices[vert + 1] / (float)255; // g
        Graphics::vertices[addr + 4] = Adafruit_DotStar::vertices[vert + 2] / (float)255; // b
    }
}

int main() {
    // LED EXPORT
    //float led_positions[4][NUM_PIXEL_STRIPS] = {
    //    // x0,  y0,   x1,   y1
    //    {  59,   9,  262,  140 },
    //    {   9, -59,  140, -262 },
    //    { -59,  -9, -262, -140 },
    //    {  -9,  59, -140,  262 }
    //};
    //Leds_Export::export_code("../BikeWheel/Leds.cpp", led_positions);

    // IMAGES
    //std::string imageName({name});
    //BMP bmp("../Images/" + imageName + ".bmp");
    //Image_Pixels pixels(bmp, Leds::min_dist);
    //image = new Image_IndexedColor(pixels, {colors}, 3);
    //image = new Image_Grayscale(pixels);
    //image = new Image_6BitColor(pixels);

    // IMAGE EXPORT
    //image->export_code(std::string("../Shared/Images/").append(imageName).append(".h"), imageName);
    //return 0;

    mpu.setup(mpu_offsets);

    if (!Graphics::init()) {
        return -1;
    }
    do {
        loop();
    } while (Graphics::render());

    Graphics::terminate();
    return 0;
}