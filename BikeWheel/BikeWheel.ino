/*
   Persistence of vision is a theory which attempts to explain
   how the human eye/brain can be "fooled" into seeing continuous
   motion when presented with a sequence of discrete still images
   (film or video frames) at a rate of 10 frames per second (fps)
   or greater.

   We have 4 stips so the wheel must turn 10/4 = 2.5 times a second.
   The is a rate of change og about 163 angle/ms.

   To stop flicker at the threashold we add a buffer zone.
   Turn on at ~360 deg/ms and off at ~450 deg/s.
*/

#define LOGGING 0
#include <shared.h>

Mpu mpu;
MainProgram program;

void setup(void) {
#if LOGGING == 1
    Serial.begin(9600);
    while (!Serial);
    log_ln("Connected");
#endif

    // Get offsets calibrated using ../MPU6050 Calibration/MPU6050Calibration.ino
    // acc x, acc y, acc z, gyro x, gyro y, gyro z
    int16_t mpu_offsets[] = { -1288, 979, 1242, 39, -17, 164 };
    mpu.setup(mpu_offsets);
    Leds::setup();
}

void loop(void) {
    mpu.update();
    program.render(mpu.get_angle(), mpu.get_rotation_rate());
    Leds::leds.show();
}
