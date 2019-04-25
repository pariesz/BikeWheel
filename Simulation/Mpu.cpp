#include <math.h>
#include <chrono>
#include "MPU6050.h"
#include "Mpu.h"
#include "Arduino.h"

using namespace std;

namespace Mpu {
    uint16_t angle = 0;

    static MPU6050 mpu = MPU6050(MPU6050_DEFAULT_ADDRESS);

    uint16_t get_acc_angle() {
        int16_t acc[3];

        mpu.getAcceleration(&acc[0], &acc[1], &acc[2]);

        return atan2(acc[0], acc[2] - 8000) * 32768.0f / M_PI;
    }

    uint32_t get_elapsed() {
        using namespace std::chrono;
        static auto time_prev = high_resolution_clock::now();
        auto time = high_resolution_clock::now();
        auto elapsed = time - time_prev;
        time_prev = time;
        return (uint32_t)duration_cast<microseconds>(elapsed).count();
    }

    void init() {
        angle = get_acc_angle();
    }

    void update() {
        auto time_diff = get_elapsed();

        // read sensor data
        int16_t gyro[3];
        mpu.getRotation(&gyro[0], &gyro[1], &gyro[2]);

        // gyro is at a scale of 2000deg/s
        // << 15 (* 32768) then >> 10 (/ 2048) = << 5
        int32_t gyro_force = (int32_t)gyro[1] << 4;

        // convert micros to seconds (<< 20: / 1048576)
        int32_t gyro_dist = (gyro_force * (int32_t)time_diff) >> 20;

        uint16_t gyro_angle = angle - gyro_dist;

        uint16_t acc_angle = get_acc_angle();

        if (abs(gyro_angle - acc_angle) > (1 << 15)) {
            // overload detected
            cout << "OVERLOAD" << endl;
            angle = gyro_angle;
        } else {
            // combination filter
            angle = (0.8 * gyro_angle) + (0.2 * acc_angle);
        }

        //cout << gyro_angle << ", " << acc_angle << ": " << angle << endl;
    }
}