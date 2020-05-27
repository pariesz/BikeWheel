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
#define LOGGING 1
#define BATTERY_PIN 14
#define BLUETOOTH Serial1
#include <shared.h>

inline uint16_t get_frame_count() {
    return (millis() >> 5) & 0xFFFF;
}

Mpu mpu;
MainProgramSettings settings;
MainProgram program = MainProgram(&settings);
uint16_t frame_count = get_frame_count();

void setup(void) {

#if LOGGING == 1
    Serial.begin(9600);
    while (!Serial);
    log_ln("Connected");
#endif

    pinMode(BATTERY_PIN, INPUT);

    // Get offsets calibrated using ../MPU6050 Calibration/MPU6050Calibration.ino
    int16_t mpu_offsets[] = { 
        -1288, 979, 1242, // accl x, y, z
           39, -17,  164  // gyro x, y, z
    };

    mpu.setup(mpu_offsets);

    Leds::setup();
}

void loop(void) {
    mpu.update();
    
    if (frame_count != get_frame_count()) {
        read_serial(&BLUETOOTH);
        frame_count = get_frame_count();
        program.update(frame_count, mpu.get_rotation_rate());
    }

    program.render(mpu.get_angle());
    
    Leds::leds.show();
}

void read_serial(Stream* stream) {
    while (stream->available()) {
        String str = stream->readString();

        Serial.print(str.substring(0, 3));
        Serial.print(":");

        bool write = str.length() > 3;

        if (str.startsWith("PRO")) {
            if (write) {
                settings.program = str.substring(4).toInt();
                program = MainProgram(&settings);
            }
            stream->println(settings.program);
        }
        else if (str.startsWith("BAT")) {
            stream->println(analogRead(BATTERY_PIN));
        }
        else if (str.startsWith("ROT")) {
            stream->println(mpu.get_rotation_rate());
        }
        else if (str.startsWith("ANG")) {
            stream->println(mpu.get_angle());
        }
        //else if (str.startsWith("TXT")) {
        //    if (write) settings.explodingText = str.substring(4);
        //    stream->println(settings.explodingText);
        //}
        else if (str.startsWith("BRI")) {
            if (write) Leds::set_brightness(str.substring(4).toInt());
            stream->println(Leds::get_brightness());
        }
        else if (str.startsWith("ONR")) {
            if (write) settings.onRotationRate = str.substring(4).toInt();
            stream->println(settings.onRotationRate);
        }
        else if (str.startsWith("OFR")) {
            if (write) settings.offRotationRate = str.substring(4).toInt();
            stream->println(settings.offRotationRate);
        }
        else {
            stream->println("unrecognised command");
        }
    }
}
