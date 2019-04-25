#pragma once
#include <I2Cdev.h>
#include <MPU6050.h>
#include <Wire.h>

#define DIFF_ABS(a,b) ((a)>(b)) ? ((a)-(b)) : ((b)-(a))

namespace Mpu {
    uint16_t angle = 0;
    
    static MPU6050 mpu = MPU6050(MPU6050_DEFAULT_ADDRESS);

    void update() {
        // get time interval
        static uint32_t prev_time = micros();
        
        uint32_t time = micros();
        
        uint32_t time_diff = time - prev_time;

        prev_time = time;

        // read sensor data
        int16_t acc[3], gyro[3];
        mpu.getMotion6(&acc[0], &acc[1], &acc[2], &gyro[0], &gyro[1], &gyro[2]);

        if (acc[0] == 0 && acc[2] == 0) {
            // bad read
            Serial.println("BAD READ");
            return;
        }
/*
        // CALIBRATION TESTING
        Serial.print("acc(");
        Serial.print(acc[0]);
        Serial.print("\t, ");
        Serial.print(acc[1]);
        Serial.print("\t, ");
        Serial.print(acc[2]);
        Serial.println(")");
        delay(100);
        return;
*/
        // gyro is at a scale of +-2000deg/s
        // << 15 (* 32768) then >> 10 (/ 2048) = << 5
        int32_t gyro_force = (int32_t)gyro[1] << 4;

        // << 20 (/ 1048576) to convert micros to seconds
        int32_t gyro_dist = (gyro_force * (int32_t)time_diff) >> 20;

        // update angle from gyro reading (subtract?)
        uint16_t gyro_angle = angle - gyro_dist;

        uint16_t acc_angle = atan2(acc[0], acc[2]) * 32768.0f / M_PI;

        if (DIFF_ABS(gyro_angle, acc_angle) > (1 << 15)) {
            // overflow check
            // there must be a better way to do this
#ifdef DEBUG
            Serial.print("OVERFLOW:  gyro: ");
            Serial.print(gyro_angle);
            Serial.print("\tacc: ");
            Serial.println(acc_angle);
#endif
            angle = gyro_angle;

        } else {
            // combination filter
            angle = (0.8 * gyro_angle) + (0.2 * acc_angle);
        }

        /*
        Serial.print("gyro: ");
        Serial.print(gyro_angle);
        Serial.print("\t acc: ");
        Serial.print(acc_angle);
        Serial.print("\t angle: ");
        Serial.println(angle);
        */
    }

    void init() {
        mpu.initialize();
        mpu.setI2CMasterModeEnabled(0);
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

        int16_t acc[3];
        mpu.getAcceleration(&acc[0], &acc[1], &acc[2]);
        angle = atan2(acc[0], acc[2]) * 32768.0f / M_PI;
    }
}
