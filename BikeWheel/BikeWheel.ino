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
#include <shared.h>

// settings
uint8_t program_index = 0;
Program* program = new Color(Colors::black);
WheelSensors sensors;

void setup(void) {

#if LOGGING == 1
    Serial.begin(9600);
    while (!Serial);
    log_ln("Connected");
#endif

    sensors.setup();
    Leds::setup();
}

Program* get_next_program(void) {
    if (sensors.rotation_rate < 0) {
        --program_index;
    } else {
        ++program_index;
    }

    switch (program_index) {
        case 1:  return new Spiral;
        case 2:  return new LaPandora;
        case 3:  return new MasaCritica;
        case 4:  return new Kaleidoscope;
        case 5:  return new Radioactive;
        case 6:  return new Fist;
        case 7:  return new RainbowText(37, "- BCN - Critical Mass - Masa Critica");
        case 8:  return new NyanCat;
        case 9:  return new Poo;
        case 10: return new Velocity;
        case 11: return new Hamster;
    }

    // loop back around
    program_index = sensors.rotation_rate < 0 ? 11 : 1;
    return get_next_program();
}

void loop(void) {
    sensors.update();

    if (program_index) {
        if (abs(sensors.rotation_rate) < 60000) {
            // too slow
            delete program;
            program_index = 0;
            program = new Color(Colors::black);
        }
    } else {
        if (abs(sensors.rotation_rate) > 80000) {
            delete program;
            program = get_next_program();
        }
    }

    program->render(sensors.angle, sensors.rotation_rate);
    Leds::leds.show();
}
