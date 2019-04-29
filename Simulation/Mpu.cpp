#include <math.h>
#include <chrono>
#include "MPU6050.h"
#include "Arduino.h"

#define REVERSE
#define DIFF_ABS(a,b) (((a)>(b)) ? ((a)-(b)) : ((b)-(a)))
#define BITWISE_ROUND(val, push) ((val) + (1 << ((push) - 1))) >> (push)

namespace Mpu {
    using namespace std;

    uint16_t angle = 0;
    int32_t rotation_rate = 0;

    static MPU6050 mpu = MPU6050(MPU6050_DEFAULT_ADDRESS);

    inline uint16_t get_gyro_angle(uint32_t time_diff) {
        // << 20 (/ 1048576) to convert micros to seconds
        int16_t gyro_dist = BITWISE_ROUND(rotation_rate * (int32_t)time_diff, 19);

        // update angle from gyro reading
        return angle + gyro_dist;
    }

    inline uint16_t get_acc_angle(int16_t* acc) {
#ifdef REVERSE
        return (atan2(acc[2], ~acc[0]) * (32768.0f / M_PI));
#else
        return (atan2(acc[2], acc[0]) * (32768.0f / M_PI));
#endif
    }

    uint32_t micros() {
        using namespace std::chrono;
        static auto start = high_resolution_clock::now();
        auto time = high_resolution_clock::now();
        auto elapsed = time - start;
        return (uint32_t)duration_cast<microseconds>(elapsed).count();
    }

    void update() {
        static uint32_t prev_time = micros();
        static uint16_t prev_acc_angle = 0;
        static uint8_t update_accum = 10;

        // get time interval
        uint32_t time = micros();
        uint32_t time_diff = time - prev_time;
        prev_time = time;

        if (++update_accum < 10) {
            angle = get_gyro_angle(time_diff);
            return;
        }

        // read sensor data
        int16_t acc[3], gyro[3];
        mpu.getMotion6(&acc[0], &acc[1], &acc[2], &gyro[0], &gyro[1], &gyro[2]);

        if (acc[0] == 0 && acc[2] == 0) {
            // bad read
            LOG_LN("BAD ACC READ: 0");
            angle = get_gyro_angle(time_diff);
            return;
        }

        // gyro signed int32 at a scale of +-2000deg/s
        // so to convert gyro_y * (2000 / 360)
#ifdef REVERSE
        rotation_rate = -gyro[1];
#else
        rotation_rate = gyro[1];
#endif
        rotation_rate *= 5.5555f;

        uint16_t gyro_angle = get_gyro_angle(time_diff);
        uint16_t acc_angle = get_acc_angle(acc);

        if (prev_acc_angle == acc_angle) {
            //LOG("BAD ACC READ: "); LOG_LN(acc_angle);
            angle = gyro_angle;
            return;
        }

        //LOG(acc_angle - prev_acc_angle);
        //LOG("\t,")
        //LOG_LN(BITWISE_ROUND((int32_t)rotation_rate * (int32_t)time_diff, 19))

        prev_acc_angle = acc_angle;

        if (DIFF_ABS(gyro_angle, acc_angle) > (1 << 15)) {
            // overflow check.  there must be a better way to do this
            //LOG_LN("OVERFLOW");
            angle = gyro_angle;
            return;
        }

        // combination filter
        angle = (0.8 * gyro_angle) + (0.2 * acc_angle);
        update_accum = 0;

        //cout << gyro_angle << ", " << acc_angle << ": " << angle << endl;
    }

    void init() {
        mpu.setZAccelOffset(-8000);

        int16_t acc[3];
        mpu.getAcceleration(&acc[0], &acc[1], &acc[2]);
        angle = get_acc_angle(acc);
    }
}