#include "Mocks/Arduino_Mock.h"
#include "HallSensor.h"
#include "Logging.h"

HallSensor::HallSensor()
    : us_rotation(micros())
    , value(HIGH)
    , angle(HALL_OFFSET)
    , rotation_rate(0) {
}

void HallSensor::setup() {
#if defined(ARDUINO) && ARDUINO >= 100
    pinMode(HALL_PIN, INPUT); // input from the OH137
#endif
}

void HallSensor::loop(bool reverse, uint32_t us, uint32_t us_diff) {
    int read = digitalRead(HALL_PIN); // read OH137 Value

    uint32_t us_rotation_diff = us - us_rotation;

    // if we are recording 10 rotations a second (us_diff > 100000)
    // with a 299in wheel circumferance of ~2300mm we would be going
    // ~80kmh so we can assume a bad read.
    if (value == LOW && read == HIGH && us_rotation_diff > 100000) {
        rotation_rate = (0xFFFF / (float)us_rotation_diff) * 1000000;

        if (reverse) {
            rotation_rate = -rotation_rate;
        }

        us_rotation = us;
        angle = HALL_OFFSET;
        value = read;
        return;
    }

    value = read;

//    if (us_rotation_diff > 1000000) {
//        // if we are going less than 1 rotation a second (<8kmh) 
//        // it is too slow for any sort of accuracy so reset the count
//        rotation_rate = 0;
//        return;
//    }

    
    angle += (rotation_rate * (int64_t)(us_diff)) / 1000000;
}