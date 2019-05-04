
#ifdef SIMULATION
#include "SensorData.h"
#include "Arduino_Mock.h"
#endif
#include "HallSensor.h"
#include "Logging.h"

#define HALL_PIN 3

HallSensor::HallSensor(uint16_t offset)
        : offset(offset)
        , angle(offset)
        , rotations(0)
        , rotation_rate(0)
        , value(HIGH)
        , rotation_us(micros())
        , frame_us(micros()) {
}

void HallSensor::setup() {
#ifndef SIMULATION
    pinMode(HALL_PIN, INPUT); // input from the OH137
#endif
}

void HallSensor::loop(bool reverse) {
#ifdef SIMULATION
    int read = SensorData::get().hall;
#else
    int read = digitalRead(HALL_PIN); // read OH137 Value
#endif

    uint32_t us = micros();
    uint32_t us_diff = us - rotation_us;

    // if we are recording 10 rotations a second (us_diff > 100000)
    // with a 299in wheel circumferance of ~2300mm we would be going
    // ~80kmh so we can assume a bad read.
    if (value == LOW && read == HIGH && us_diff > 100000) {
        frame_us = rotation_us = us;
        rotation_rate = ((uint16_t)-1) / (us_diff / 1000000.0f);

        if (reverse) {
            rotation_rate = -rotation_rate;
        }

        angle = offset;
        value = read;
        rotations++;

        return;
    }

    value = read;

    if (us_diff > 1000000) {
        // if we are going less than 1 rotation a second (<8kmh) 
        // it is too slow for any sort of accuracy so reset the count
        rotations = 0;
        return;
    }

    
    angle += (rotation_rate * (int64_t)(us - frame_us)) / 1000000;
    
    frame_us = us;
}