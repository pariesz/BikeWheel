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

// settings
bool on = 0;
uint8_t program_index = 0;
Program* program = new Color(COLOR_BLACK);
Mpu mpu;

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

Program* start_program(void) {
    log_val("program", program_index);

    switch (program_index) {
        case 0: return new Spiral;
        case 1: return new LaPandora;
        case 2: return new MasaCritica;
        case 3: return new Fist;
        case 4: return new ExplodingText(37, "- BCN - Critical Mass - Masa Critica");
        case 5: return new NyanCat;
        case 6: return new Poo;
        case 7: return new Velocity;
        case 8: return new Hamster;
        case 9: return new Portal;
        case 10: return new Rays;
        case 11: return new ShootingStars;
    }

    // loop back around
    program_index = mpu.get_rotation_rate() < 0 ? 11 : 0;
    return start_program();
}

void loop(void) {
    mpu.update();

    int32_t rotation_rate = mpu.get_rotation_rate();

    if (on) {
        if (abs(rotation_rate) < 60000) {
            // too slow
            delete program;
            program = new Color(COLOR_BLACK);
            on = false;
        }
    } else {
        if (abs(rotation_rate) > 80000) {
            if (rotation_rate < 0) {
                --program_index;
            } else {
                ++program_index;
            }

            log_val("program", program_index);

            delete program;
            program = start_program();
            on = true;
        }
    }

    program->render(mpu.get_angle(), rotation_rate);
    Leds::leds.show();
}
