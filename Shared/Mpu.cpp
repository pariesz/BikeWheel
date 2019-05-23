#if defined(ARDUINO) && ARDUINO >= 100
    #include <I2Cdev.h>
    #include <Wire.h>
#endif

#include "Logging.h"
#include "Mpu.h"

// Expected orientation of MPU6050
//      +z
//       ^
// -x <-- --> +x
#define MPU_X_INDEX 0
#define MPU_Y_INDEX 1
#define MPU_Z_INDEX 2
#define MPU_X_REVERSE 1
#define MPU_Z_REVERSE 0

// MPU sensors distance from wheel center in in mm
// required to calculate and offset centrifugal acceleration
#define MPU_Z_POSITION 25 

// Gyro and Accelerometer data are combined with
// a combination filter at this weight
#define MPU_COMBINE_ACC 0.05f

#define diff_abs(a,b) (((a)>(b)) ? ((a)-(b)) : ((b)-(a)))

Mpu::Mpu()
    : angle(0)
    , rotation_rate(0)
    , mpu(MPU6050(MPU6050_DEFAULT_ADDRESS)) {
}

uint16_t Mpu::get_angle() {
    return angle;
}

int32_t Mpu::get_rotation_rate() {
    return rotation_rate;
}

void Mpu::setup(int16_t offsets[6]) {
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

    mpu.setXAccelOffset(offsets[0]);
    mpu.setYAccelOffset(offsets[1]);
    mpu.setZAccelOffset(offsets[2]);

    mpu.setXGyroOffset(offsets[3]);
    mpu.setYGyroOffset(offsets[4]);
    mpu.setZGyroOffset(offsets[5]);

    delay(100); // Wait for sensor to stabilize
#endif

    int16_t acc[3];

    mpu.getAcceleration(
        &acc[MPU_X_INDEX],
        &acc[MPU_Y_INDEX],
        &acc[MPU_Z_INDEX]);
    
#if MPU_Z_REVERSE == 1    
    acc[2] = -acc[2];
#endif

#if MPU_X_REVERSE == 1
    acc[0] = -acc[0];
#endif
    
    angle = get_acc_angle(acc);
}

void Mpu::update() {
    // get time interval
    uint32_t us = micros();
    static uint32_t us_prev = us;

    uint32_t us_diff = us - us_prev;
    us_prev = us;

    // read sensor data
    int16_t acc[3], gyro[3];
    
    mpu.getMotion6(
        &acc[MPU_X_INDEX],
        &acc[MPU_Y_INDEX],
        &acc[MPU_Z_INDEX],
        &gyro[MPU_X_INDEX],
        &gyro[MPU_Y_INDEX],
        &gyro[MPU_Z_INDEX]);

    // validate data
    if (acc[0] == 0 && acc[2] == 0) {
        log_ln("MPU6050 Error: 0 read");
        angle = get_rotation_rate_angle(us_diff);
        return;
    }

/*
#ifndef SIMULATION
    // CALIBRATION
    Serial.print("acc(");
    Serial.print(acc[MPU_X_INDEX]);
    Serial.print("\t, ");
    Serial.print(acc[MPU_Y_INDEX]);
    Serial.print("\t, ");
    Serial.print(acc[MPU_Z_INDEX]);
    Serial.println(")");
    delay(100);
    return;
#endif
*/

#if MPU_Z_REVERSE == 1    
    acc[2] = -acc[2];
#endif

#if MPU_X_REVERSE == 1
    acc[0] = -acc[0];
    gyro[1] = -gyro[1];
#endif

    // gyro is signed int16 at a scale of +-2000deg/s : +-32768
    // so to convert: gyro_y * (2000 / 360) * 2
    rotation_rate = gyro[1] * 11.1111111f;

    uint16_t rotation_rate_angle = get_rotation_rate_angle(us_diff); 
    
    uint16_t acc_angle = get_acc_angle(acc);

    // DEBUGGING
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

    // overflow check.  gyro and acc are > 180 degress out 
    if (diff_abs(rotation_rate_angle, acc_angle) > 0x8000) {
        angle = rotation_rate_angle;
        return;
    }

    // combination filter: 95% gyro + 5% acc
    angle = (rotation_rate_angle * (1 - MPU_COMBINE_ACC)) + (acc_angle * MPU_COMBINE_ACC);
}

inline uint16_t Mpu::get_rotation_rate_angle(uint32_t time_diff) {
    return angle + ((rotation_rate * (int64_t)time_diff) / 1000000);
}

inline uint16_t Mpu::get_acc_angle(int16_t* acc) {
    // Centrifugal Acceleration
    // rs = rotations per second 
    //    = abs(rotation_rate) / 0xFFFF
    //  r = MPU_Z_POSITION
    //  v = circumference * rs
    //    = 2π * r * rs
    //  a = v² / r
    //    = (2π * r * rs)² / r
    //    = sq(TWO_PI * abs(rotation_rate) / 0xFFFF) * MPU_Z_POSITION

    // Acceleromter full-range (±0x8000) is set to ±8g
    // a(mpu) = (a * 0x8000) / (9.8ms2 * 1000mm * 8g) = a * 0.417959
    
    // acts on the z-axis in the positive direction
    // so we subtract to correct
    float x = TWO_PI * abs(rotation_rate) / (float)0xFFFF;
    
    int16_t centrifugal_acceleration = (MPU_Z_POSITION * sq(x) * 0.417959);

    // Possible overflow, but we shouldn't be approaching those accelerations
    // offset 90 degrees so 0 is up
    return 0x4000 + ((atan2(acc[2] - centrifugal_acceleration, acc[0]) * (0x8000 / (float)PI)));
}