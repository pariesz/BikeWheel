#include "MockData.h"

int16_t MockData::gyro_y = 100;

inline int16_t MPU6050_ACCEL_FS_8(float radians) {
    return radians * 0xFFF; // 1g
}

bool MockData::try_get_next(DataLine &dl) {
    static int us_prev = micros();
    int us = micros();
    int diff = us - us_prev;
    us_prev = us;

    angle += gyro_y
        * ((float)diff / 1000000) // us to seconds
        * (2000 / 360.0f)         // MPU ±2000 scale to 1 rotation
        * 2;                      // signed 16bit to unsigned 16bit

    // rotate -90 degrees
    float radians = (angle / (float)0xFFFF) * TWO_PI;

    dl.us = 6000;
    dl.hall = angle < 500 ? LOW : HIGH;
    dl.acc_x = MPU6050_ACCEL_FS_8(sin(radians)); // MPU_X_REVERSE = 1
    dl.acc_y = 0;
    dl.acc_z =  MPU6050_ACCEL_FS_8(cos(radians));
    dl.gyro_x = 0;
    dl.gyro_y = -gyro_y;  // MPU_X_REVERSE = 1
    dl.gyro_z = 0;

    return true;
}