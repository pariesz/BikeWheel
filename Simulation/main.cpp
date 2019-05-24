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

//OutputData data_source("output.csv");
MockData data_source;
Mpu mpu;
Image_Base *image = nullptr;
Portal program;

// Simulate the Arduino loop() and setup() functions
void loop() {
    mpu.update();
    program.render(mpu.get_angle(), mpu.get_rotation_rate());
    Leds::leds.show();
}

void setup() {
    int16_t mpu_offsets[] = { 0, 0, 0, 0, 0, 0 };
    mpu.setup(mpu_offsets);
    Leds::setup();
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
    //image = new Image_IndexedColor(pixels, Image_Colors::{colors}, 3);
    //image = new Image_Grayscale(pixels);
    //image = new Image_6BitColor(pixels);

    // IMAGE EXPORT
    //image->export_code(std::string("../Shared/Images/").append(imageName).append(".h"), imageName);
    //return 0;

    if (!Graphics::init()) {
        return -1;
    }

    // Arduino setup function
    setup();

    do {
        // Simulate sensor data
        DataLine dl;

        if (!data_source.try_get_next(dl)) {
            // Reset
            Graphics::clear();
            mpu = Mpu();
            setup();
        }

        MPU6050::setMotion6(dl.acc_x, dl.acc_y, dl.acc_z, dl.gyro_x, dl.gyro_y, dl.gyro_z);
        digitalWrite(HALL_PIN, dl.hall);

        // Arduino loop function
        loop();

        // Update graphics
        Graphics::updateVertices(mpu.get_angle());
    } while (Graphics::render());

    Graphics::terminate();
    return 0;
}