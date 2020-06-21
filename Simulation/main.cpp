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
#include "Image_Colors.h"
#include "Image_6BitColor.h"
#include "Image_IndexedColor.h"
#include "Image_Grayscale.h"
#include "Leds_Export.h"
#include "Timer.h"
#include "Programs/Rainbow.h"
#include "Programs/Spiral.h"
#include "Programs/PulseProgram.h"
#include "Programs/TimerProgram.h"
#include "Programs/MainProgram.h"
#include "Programs/ExplodingText.h"

//OutputData data_source("output.csv");
MockData data_source;
Mpu mpu;
Image_Base *image = nullptr;
MainProgram program;
uint16_t frame_count;

inline uint16_t get_frame_count() {
    return (millis() >> 5) & 0xFFFF; // 32 frames sec
}

void setup() {
    int16_t mpu_offsets[] = { 0, 0, 0, 0, 0, 0 };
    mpu.setup(mpu_offsets);
    Leds::setup(144, 11, 13, DOTSTAR_BGR);

    EEPROM.put(EEPROM_BRIGHTNESS, (uint8_t)20);
    EEPROM.put(EEPROM_TIMER_FRAMES, (uint16_t)60);
    EEPROM.put(EEPROM_WHEEL_CIRCUMFERENCE, (uint16_t)2288);
    EEPROM.put(EEPROM_STATIONARY_RATE, (uint32_t)60000);
    EEPROM.put(EEPROM_MOVING_RATE, (uint32_t)80000);
    Configuration::writeString(EEPROM_EXPLODING_TEXT, " - BCN - Critical Mass - Massa Critica");

    program.configure();
    program.setStationaryProgram(PROGRAM_TIMER);
}

// Simulate the Arduino loop() and setup() functions
void loop() {
    mpu.update();

    if (frame_count != get_frame_count()) {
        frame_count = get_frame_count();
        program.update(mpu.get_rotation_rate());
    }

    program.render(mpu.get_angle());

    Leds::leds.show();
}

void update_sensors() {
    DataLine dl;

    if (!data_source.try_get_next(dl)) {
        // Reset
        Graphics::clear();
        mpu = Mpu();
        setup();
    }

    MPU6050::setMotion6(dl.acc_x, dl.acc_y, dl.acc_z, dl.gyro_x, dl.gyro_y, dl.gyro_z);

    digitalWrite(HALL_PIN, dl.hall);
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
    //std::string imageName("Rocket");
    //BMP bmp("../Images/" + imageName + ".bmp");
    //Image_Pixels pixels(bmp, Leds::min_dist);
    //image = new Image_IndexedColor(pixels, Image_Colors::rocket);
    //image = new Image_Grayscale(pixels);
    //image = new Image_6BitColor(pixels);

    // IMAGE EXPORT
    //image->export_code(std::string("../Shared/Images/").append(imageName).append(".h"), imageName);
    //return 0;

    if (!Graphics::init()) {
        return -1;
    }

    update_sensors();

    // Arduino setup function
    setup();

    do {
        // Simulate sensor data
        update_sensors();

        // Arduino loop function
        Timer::start();
        loop();
        Timer::end();

        // Update graphics
        Graphics::updateVertices(mpu.get_angle());
    } while (Graphics::render());

    Graphics::terminate();
    return 0;
}