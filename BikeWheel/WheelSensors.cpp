#pragma once

#ifdef SIMULATION
#include <math.h>
#include "Arduino_Mock.h"
#include "MPU6050_Mock.h"
#else
#include <I2Cdev.h>
#include <MPU6050.h>
#include <Wire.h>
#endif

#include "Helpers.h"
#include "Logging.h"
#include "WheelSensors.h"

#define REVERSE
#define diff_abs(a,b) (((a)>(b)) ? ((a)-(b)) : ((b)-(a)))

WheelSensors::WheelSensors()
    : angle(0)
    , rotation_rate(0)
    , mpu(MPU6050(MPU6050_DEFAULT_ADDRESS)) {
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
    angle = get_acc_angle(acc);
}

void WheelSensors::loop() {
    static uint32_t prev_time = micros();
    static uint16_t prev_acc_angle = 0;

    // get time interval
    uint32_t time = micros();
    uint32_t time_diff = time - prev_time;
    prev_time = time;

    // read sensor data
    int16_t acc[3], gyro[3];
    mpu.getMotion6(&acc[0], &acc[1], &acc[2], &gyro[0], &gyro[1], &gyro[2]);

    // validate data
    if (acc[0] == 0 && acc[2] == 0) {
        LOG_LN("BAD ACC READ: 0");
        angle = get_gyro_angle(time_diff);
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

#ifdef REVERSE
    rotation_rate = -gyro[1];
#else
    rotation_rate = gyro[1];
#endif

    // gyro is signed int16 at a scale of +-2000deg/s : +-32768
    // so to convert: gyro_y * (2000 / 360) * 2
    rotation_rate *= 11.1111111f;

    uint16_t gyro_angle = get_gyro_angle(time_diff);
    uint16_t acc_angle = get_acc_angle(acc);    

    // MPU6050 sometimes sticks on a value
    if (prev_acc_angle == acc_angle) {
#ifdef DEBUG
        Serial.print(F("BAD ACC READ: "));
        Serial.println(acc_angle);
#endif
        angle = gyro_angle;
        return;
    }
    prev_acc_angle = acc_angle;

    // overflow check.  gyro and acc are 180 degress out 
    if (diff_abs(gyro_angle, acc_angle) > 0xF000) {
        angle = gyro_angle;
        return;
    }

    // combination filter: 95% gyro + 5% acc
    angle = (gyro_angle * 0.95f) + (acc_angle * 0.05f);
}

inline uint16_t WheelSensors::get_gyro_angle(uint32_t time_diff) {
    // >> 20 (/ 1048576) to convert micros to seconds
    // update angle from gyro reading (subtract?)
    return angle += (rotation_rate * (int64_t)time_diff) / 1000000;
}

inline uint16_t WheelSensors::get_acc_angle(int16_t* acc) {
#ifdef REVERSE
    // offset 90 degrees
    return (1 << 14) + ((atan2(acc[2], ~acc[0]) * (32768.0f / PI)));
#else
    return (atan2(acc[2], acc[0]) * (32768.0f / M_PI));
#endif
}