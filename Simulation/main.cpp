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
#include "Timers.h"


bool off = true; // clear all pixels

int16_t velocity = 0; // angle / ms

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

void update_velocity() {
    static uint16_t prev_angle = Mpu::angle;
    static uint32_t prev_time = Timers::micros();

    uint32_t time = Timers::micros();
    uint16_t time_diff = prev_time - time;
    if (time_diff < (1 << 15)) {
        return;
    }

    prev_time = time;

    if ((prev_angle < 10000 && Mpu::angle > 50000) || (prev_angle > 50000 && Mpu::angle < 10000)) {
        // overflow check
        prev_angle = Mpu::angle;
        return;
    }

    velocity = ((int32_t)prev_angle - Mpu::angle) << 10 / time_diff;

    //std::cout << time_diff << "\t" << prev_angle << "\t" << Mpu::angle << "\t" << velocity << std::endl;

    prev_angle = Mpu::angle;
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

        update_velocity();

        HallSensor::update();

        //uint16_t angle = HallSensor::angle;
        uint16_t angle = Mpu::angle;
        uint16_t velocity_abs = abs(velocity);

        if (velocity_abs < 5) {
            off = true;
        }
        else if (velocity_abs > 15) {
            off = false;
        }

        if (off) {
            Programs::set_color(0x000000);
        }
        else {
            //Programs::set_half_color(0x00FF00, angle);
            //Programs::spiral(angle);
            Programs::rainbow(angle);
            //Programs::text(Mpu::angle, 15, "MASSA CRITICA");
        }

        updateVertices(angle);

        //Sleep(100);

    } while (Graphics::render(sizeof(vertices), (void*)vertices));

    Graphics::terminate();
    return 0;
}