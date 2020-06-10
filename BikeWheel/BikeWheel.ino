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

// 31 frames a second
inline uint16_t get_frame_count() {
    return (millis() >> 5) & 0xFFFF;
}

Mpu mpu;
MainProgram program;
uint16_t frame_count = get_frame_count();
char command = 0;
EEPROMSerialMessage message = EEPROMSerialMessage(false);

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

    Leds::setup(144, 11, 13, DOTSTAR_BGR);
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
        char ch = stream->read(); // only read whats available so its non-blocking

        if (command == 0) {
            command = ch;
            stream->print(command); // echo the command back

            log_val("cmd", ch);

            switch (command) {
                case CMD_BATTERY:
                    stream->println(analogRead(BATTERY_PIN));
                    break;

                case CMD_ANGLE:
                    stream->println(mpu.get_angle());
                    break;

                case CMD_ROTATION_RATE:
                    stream->println(mpu.get_rotation_rate());
                    break;

                case CMD_GET_MOVING_PROGRAM:
                    stream->println(program.getMovingProgram());
                    break;

                case CMD_GET_STATIONARY_PROGRAM:
                    stream->println(program.getStationaryProgram());
                    break;

                case CMD_SET_EEPROM:
                    message = EEPROMSerialMessage(true);
                    continue;

                case CMD_GET_EEPROM:
                    message = EEPROMSerialMessage(false);
                    continue;

                default:
                    continue; // wait for more input
            }
        } else {
            switch (command) {
                case CMD_SET_EEPROM:
                    if (!message.consume(ch)) continue;
                    message.print(stream);
                    program.configure();
                    break;

                case CMD_GET_EEPROM:
                    if (!message.consume(ch)) continue;
                    message.print(stream);
                    break;

                case CMD_SET_MOVING_PROGRAM:
                    log_val("program",  ch);
                    program.setMovingProgram(ch);
                    stream->println(program.getMovingProgram());
                    break;

                case CMD_SET_STATIONARY_PROGRAM:
                    log_val("program", ch);
                    program.setStationaryProgram(ch);
                    stream->println(program.getStationaryProgram());
                    break;

                default:
                    log_ln("err");
                    stream->println("err");
                    break;
            }
        }

        // command has been executed, clear it
        command = 0;
    }
}