#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
    #include <I2Cdev.h>
    #include <MPU6050.h>
    #include <Wire.h>
#else
    #include "Arduino_Mock.h"
    #include "MPU6050_Mock.h"
#endif

#include "Logging.h"
#include "WheelSensors.h"


#define MPU_RADIUS 25 // distance in mm, required to calculate and offset centrifugal acceleration

// Expected orientation of MPU6050
//      +z
//       ^
// -x <-- --> +x
#define REVERSE_X 1
#define REVERSE_Z 0
#define diff_abs(a,b) (((a)>(b)) ? ((a)-(b)) : ((b)-(a)))

WheelSensors::WheelSensors()
    : angle(0)
    , rotation_rate(0)
    , mpu(MPU6050(MPU6050_DEFAULT_ADDRESS)) {
}

uint16_t WheelSensors::get_angle() {
    return angle;
}

int32_t WheelSensors::get_rotation_rate() {
    return rotation_rate;
}

void WheelSensors::setup() {
#ifndef SIMULATION
    /* Switch to 400KHz I2C */
    TWBR = ((F_CPU / 400000L) - 16) / 2;

    mpu.initialize();

#if LOGGING == 1
    Serial.println(mpu.testConnection() ? F("MPU connected") : F("MPU failed"));
#endif

    mpu.setI2CBypassEnabled(1);
    mpu.setFullScaleGyroRange(MPU6050_GYRO_FS_2000);
    mpu.setFullScaleAccelRange(MPU6050_ACCEL_FS_8);
    mpu.setFIFOEnabled(0);
    mpu.setDMPEnabled(0);
    mpu.setIntEnabled(0);

    // Offsets calibrated using MPU6050Calibration.ino
    mpu.setXAccelOffset(-1288);
    mpu.setYAccelOffset(979);
    mpu.setZAccelOffset(1242);

    mpu.setXGyroOffset(39);
    mpu.setYGyroOffset(-17);
    mpu.setZGyroOffset(164);

    delay(100); // Wait for sensor to stabilize
#endif

    int16_t acc[3];

    mpu.getAcceleration(&acc[0], &acc[1], &acc[2]);
    
#if REVERSE_Z == 1    
    acc[2] = -acc[2];
#endif
#if REVERSE_X == 1
    acc[0] = -acc[0];
#endif
    
    angle = get_acc_angle(acc);
}

void WheelSensors::update() {
    // get time interval
    uint32_t us = micros();
    static uint32_t us_prev = us;

    uint32_t us_diff = us - us_prev;
    us_prev = us;

    // read sensor data
    int16_t acc[3], gyro[3];
    mpu.getMotion6(&acc[0], &acc[1], &acc[2], &gyro[0], &gyro[1], &gyro[2]);

    // validate data
    if (acc[0] == 0 && acc[2] == 0) {
        log_ln("MPU6050 ZERO");
        angle = get_rotation_rate_angle(us_diff);
        return;
    }

/*
#ifndef SIMULATION
    // CALIBRATION TESTING
    Serial.print("acc(");
    Serial.print(acc[0]);
    Serial.print("\t, ");
    Serial.print(acc[1]);
    Serial.print("\t, ");
    Serial.print(acc[2]);
    Serial.print("\t, ");
    Serial.print(gyro[1]);
    Serial.println(")");
    delay(100);
    return;
#endif
*/

#if REVERSE_Z == 1    
    acc[2] = -acc[2];
#endif

#if REVERSE_X == 1
    acc[0] = -acc[0];
    gyro[1] = -gyro[1];
#endif

    // gyro is signed int16 at a scale of +-2000deg/s : +-32768
    // so to convert: gyro_y * (2000 / 360) * 2
    rotation_rate = gyro[1] * 11.1111111f;

    uint16_t rotation_rate_angle = get_rotation_rate_angle(us_diff); 
    
    uint16_t acc_angle = get_acc_angle(acc);

    //angle = rotation_rate_angle;
    //angle = acc_angle;
    //return;

    // Validation: MPU6050 sometimes sticks on a value
    // or gives wild values at higher speeds
    static uint16_t prev_acc_angle = acc_angle;

    if (prev_acc_angle == acc_angle) {
        angle = rotation_rate_angle;
        return;
    }

    prev_acc_angle = acc_angle;

    // overflow check.  gyro and acc are 180 degress out 
    if (diff_abs(rotation_rate_angle, acc_angle) > 0xF000) {
        angle = rotation_rate_angle;
        return;
    }

    // combination filter: 95% gyro + 5% acc
    angle = (rotation_rate_angle * 0.95f) + (acc_angle * 0.05f);
}

inline uint16_t WheelSensors::get_rotation_rate_angle(uint32_t time_diff) {
    return angle + ((rotation_rate * (int64_t)time_diff) / 1000000);
}

inline uint16_t WheelSensors::get_acc_angle(int16_t* acc) {
    // Centrifugal Acceleration: a = v^2 / r 
    // rs = rotations per second 
    //    = rotation_rate / 0xFFFF
    //  v = circumference (2PI * MPU_RADIUS) * rot
    //  a = (2PI * MPU_RADIUS * rs)^2 / MPU_RADIUS
    //    = MPU_RADIUS * (2PI * rs)^2

    // Acceleromter full-range (±0x8000) is set to ±8g
    // a(mpu) = (a * 0x8000) / (9.8ms2 * 1000mm * 8g) = a * 0.417959
    
    // acts on the z-axis in the positive direction
    // so we subtract to correct
    float x = TWO_PI * abs(rotation_rate) / (float)0xFFFF;
    
    int16_t centrifugal_acceleration = (MPU_RADIUS * sq(x) * 0.417959);

    // Possible overflow, but we shouldn't be approaching those accelerations
    // offset 90 degrees so 0 is up
    return 0x4000 + ((atan2(acc[2] - centrifugal_acceleration, acc[0]) * (32768 / (float)PI)));
}