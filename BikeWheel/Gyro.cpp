#include <I2Cdev.h>
#include <MPU6050.h>
#include <Wire.h>
#include "./Timers.h"
#include "./Gyro.h"
#include "./GyroConfig.h"
#include "./Vector.h"

#define ROUDED_RIGHT_BITSHIFT(x, bits) (((x) + (1 << ((bits) - 1))) >> (bits))
#define OPTIMIZE __attribute__((optimize("O3")))

#if ORIENTATION == 1 // X
#define GET_ACCELARTION(mpu, acc) mpu.getAcceleration(&(acc.x), &(acc.y), &(acc.z))
#define GET_MOTION_6(mpu, acc, gyro) mpu.getMotion6(&(acc.x), &(acc.y), &(acc.z), &(gyro.x), &(gyro.y), &(gyro.z))
#define GET_ROTATION(mpu) mpu.getRotationX()

#elif ORIENTATION == 2 // Y
#define GET_ACCELARTION(mpu, acc) mpu.getAcceleration(&(acc.x), &(acc.z), &(acc.y))
#define GET_MOTION_6(mpu, acc, gyro) mpu.getMotion6(&(acc.x), &(acc.z), &(acc.y), &(gyro.x), &(gyro.z), &(gyro.y))
#define GET_ROTATION(mpu) mpu.getRotationY() 

#elif AXEL_ORIENTATION == 3 // Z
#define GET_ACCELARTION(mpu, acc) mpu.getAcceleration(&(acc.z), &(acc.y), &(acc.x))
#define GET_MOTION_6(mpu, acc, gyro) mpu.getMotion6(&(acc.z), &(acc.y), &(acc.x), &(gyro.z), &(gyro.y), &(gyro.x))
#define GET_ROTATION(mpu) mpu.getRotationZ() 
#endif

namespace Gyro {
    uint16_t angle = 0;

    static Vector3<int16_t> acc;

    static constexpr auto c_mult_bits = 4;
    static constexpr auto c_calib_shift = 7;

    static MPU6050 mpu = MPU6050(MPU6050_DEFAULT_ADDRESS);
    static GyroConfig config = GyroConfig();

    static int16_t gyro_reading;
    static Vector3<int32_t> gyro_offset;

    static uint16_t angle_accum = 0;
    static uint8_t update_accum = 0;

    static Vector3<int16_t> acc_reading;
    static Vector3<int16_t> cf_acc_int;

    void acc_update(void) OPTIMIZE;
    void acc_update(void) {
        GET_ACCELARTION(mpu, acc_reading);

        acc = acc_reading;

        /*
         * If cf calibration is based on reasonably many samples, use it for
         * acc reading correction in gyro drift correction.
         */
        if (config.cf_samples > 128) {
            int factor = ((uint32_t)gyro_reading * gyro_reading) >> 20;

            acc.x = cf_acc_int.x * factor;
            acc.y = cf_acc_int.y * factor;
        }
    }
    void correct_gyro(bool correct, unsigned int acc_angle) OPTIMIZE;
    void correct_gyro(bool correct, unsigned int acc_angle) {
        static uint16_t acc_prev_angle = 0;
        static uint16_t gyro_prev_angle = 0;

        /*
         * Quite literally what is described in comment above.
         * Use floats so we don't have to worry about ranges.
         * Since this is only done every now and then, the
         * overhead should be fine.
         * TODO: increase the sample weight with rotation rate?
         */
        config.cf_acc[0] += (acc_reading.x / (float)sq(gyro_reading) - config.cf_acc[0]) / 100;
        config.cf_acc[1] += (acc_reading.y / (float)sq(gyro_reading) - config.cf_acc[1]) / 100;

        if (config.cf_samples < 255) {
            config.cf_samples += 1;
        }

        cf_acc_int.x = config.cf_acc[0] * 65536 * 16;
        cf_acc_int.y = config.cf_acc[1] * 65536 * 16;

        /*
         * TODO: add phase shift between the cf calibration
         * and acc-based gyro drift correction.
         */

         /*
          * Update gyro rate multiplier, use 1/32 weight (the
          * 14-bit shift is reduced by 5 bits).
          * TODO: decrease weight with rotation rate?
          * TODO: rounding?
          */
        int16_t gyro_velocity = gyro_prev_angle - angle;
        int16_t acc_velocity = acc_prev_angle - acc_angle;

        gyro_prev_angle = angle;
        acc_prev_angle = acc_angle;

        if (correct && !(((uint16_t)acc_velocity ^ gyro_velocity) & 0x8000) && angle_accum < DEGS_TO_ANGLE(150.0f)) {
            config.gyro_multiplier += (((int32_t)abs(acc_velocity) - abs(gyro_velocity)) << (14 - 7)) / angle_accum;
        }

        if (config.gyro_multiplier < 0x2000) {
            config.gyro_multiplier = 0x2000;
        }
        if (config.gyro_multiplier > 0xc000) {
            config.gyro_multiplier = 0xc000;
        }

        angle_accum = 0;
    }

    /*
     * Centrifugal force estimation.  We sum (acceleration vector /
     * rotation rate ^ 2) over time -- at least a few full turns at a
     * high enough rotation rate, to find the direction of the force
     * and the relation to rotation rate.  This way, knowing the rotation
     * rate at any later point, we can calculate the centrifugal force
     * vector and subtract it from accelerometer readings in order to
     * better approximate the gravity vector.
     *
     * The MPU6050 gyro has a max range of 2000deg/s and this is a slightly
     * faster than we expect a bicycle wheel to be able to turn, so we
     * assume a practical range of our centrifugal force calculations to be
     * 90deg/s - 2000deg/s.  We set a lower limit too because the force is
     * proportional to the square of rotation rate and below a given value
     * the force should be negligible.
     */

    void correct_acc(void) OPTIMIZE;
    void correct_acc(void) {
        acc_update();

        uint32_t len = sq(acc.x) + sq(acc.y);

        uint8_t correct = len > 0x1000000 / 2
                    && len < 0x1000000 * 2;

        uint16_t acc_angle = atan2(acc.x, acc.y) * (-32768.0f / M_PI);

        int16_t angle_error = acc_angle - angle;

        /* Correct the current angle */
        if (correct) {
            angle += (angle_error + 4) >> 3; 
#if REVERSE == true
            gyro_offset.z += (-(int32_t)angle_error << 2) / update_accum;
#else
            gyro_offset.z += ((int32_t)angle_error << 2) / update_accum;
#endif
        }

#if 0
        uint16_t tdiff = (now - time_prev) / 1000;
        Serial.print((uint32_t)1000 * iter_accum / tdiff);
        Serial.write("fps\r\n");
#endif
        if (angle_accum > DEGS_TO_ANGLE(30.0f) && abs(gyro_reading) > DEGS_PER_S_TO_RATE(70.0f)) {
            correct_gyro(correct, acc_angle);
        }
    }

    long ms = 0;
    void update(void) {
        static uint32_t time_correct = 0;
        static uint32_t time_prev = 0;

        uint32_t time_now = MICROS();
        uint32_t time_diff = time_now - time_prev;

        time_prev = time_now;

        // Update gyro values and timestamps, used for gyro integration 
        int32_t gyro_reading_mult = ((int32_t)GET_ROTATION(mpu) << c_mult_bits)
            - ROUDED_RIGHT_BITSHIFT(gyro_offset.z, c_calib_shift - c_mult_bits);

#if REVERSE == true
        gyro_reading_mult = -gyro_reading_mult;
#endif

        // divide by 16 and round the result
        gyro_reading = ROUDED_RIGHT_BITSHIFT(gyro_reading_mult, c_mult_bits);

        int angle_step = ((int32_t)gyro_reading_mult * (int16_t)time_diff)
            // degs     lsb/deg   us/sec     lsb/360deg rounding
            / (int32_t)(360.0f * 16.4f * 1000000.0f / 65536.0f + 0.499f);

        // TODO: use optimised avr multiplier */
        angle_step = ROUDED_RIGHT_BITSHIFT((int32_t)angle_step * config.gyro_multiplier, 14 + c_mult_bits);

        angle += angle_step;

        angle_accum += abs(angle_step);

        update_accum += 1;

        if (update_accum > 100 || time_now - time_correct > 150000) {
            correct_acc();
            time_correct = time_now;
            update_accum = 0;
        }

        if (millis() - ms > 500) {
            Serial.print("acc { x:");
            Serial.print(acc.x);
            Serial.print(", y:");
            Serial.print(acc.y);
            Serial.print(", z:");
            Serial.print(acc.z);
            Serial.print(" } gyro:");
            Serial.print(GET_ROTATION(mpu));
            Serial.print(", angle_step:");
            Serial.print(angle_step);
            Serial.print(", angle_accum:");
            Serial.print(angle_accum);
            Serial.print(", gyro_reading_mult:");
            Serial.print(gyro_reading_mult);
            Serial.print(", angle:");
            Serial.println(angle);
            ms = millis();
        }
    }

    static void zero(void) {
        Vector3<int16_t> acc_reading, gyro_reading;

        gyro_offset = Vector3<int32_t>();

        for (int i = 0; i < (1 << c_calib_shift); i++) {
            GET_MOTION_6(mpu, acc_reading, gyro_reading);
            gyro_offset.x += gyro_reading.x;
            gyro_offset.y += gyro_reading.y;
            gyro_offset.z += gyro_reading.z;
            delay(1);
        }
    };

    void init(void) {
        /* Switch to 400KHz I2C */
        TWBR = ((F_CPU / 400000L) - 16) / 2;

        mpu.initialize();
#ifdef DEBUG        
        Serial.print(mpu.testConnection() ? F("successful") : F("failed"));
#endif
        mpu.setI2CMasterModeEnabled(0);
        mpu.setI2CBypassEnabled(1);
        mpu.setFullScaleGyroRange(MPU6050_GYRO_FS_2000);
        mpu.setFullScaleAccelRange(MPU6050_ACCEL_FS_8);

        // Offsets calibrated using MPU6050Calibration.ino
        mpu.setXAccelOffset(-2426);
        mpu.setYAccelOffset(1993);
        mpu.setZAccelOffset(5225);

        mpu.setXGyroOffset(149);
        mpu.setYGyroOffset(60);
        mpu.setZGyroOffset(59);

        config.load();

        zero();

        /* Accelerometer-based rough initial angle */
        acc_update();
        angle = atan2(acc.x, acc.y) * (-32768.0f / M_PI);
    }
}


