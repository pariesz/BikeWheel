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

// When used as analog pins, the Arduino software uses a separate set of zero-based numbers, 
// so pin 0 (used with pinMode, digitalWrite, analogWrite, and digitalRead) is different than analog pin 0.
#define BATTERY_PIN 0

#define BLUETOOTH Serial1

#include <shared.h>

// 31 frames a second
inline uint16_t get_frame_count() {
    return (millis() >> 5) & 0xFFFF;
}
uint16_t frame_count = get_frame_count();

Mpu mpu;

MainProgram program;

void setup(void) {

#if LOGGING == 1
    Serial.begin(9600);
    while (!Serial);
    log_val("Serial", F("Connected"));
#endif

    BLUETOOTH.begin(9600);

    //pinMode(BATTERY_PIN, INPUT);

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
        read_serial();
        frame_count = get_frame_count();
        program.update(mpu.get_rotation_rate());
    }

    program.render(mpu.get_angle());
    
    Leds::leds.show();
}


uint8_t command = 0;
SerialMessage* message = new SerialMessage(&BLUETOOTH);

void read_serial() {
    while (BLUETOOTH.available()) {
        uint8_t ch = BLUETOOTH.read(); // only read whats available so its non-blocking

        if (command == 0) {
            free(message);
            message = new SerialMessage(&BLUETOOTH);

            command = ch;
            BLUETOOTH.write(command); // echo the command back

            log_val("cmd", ch);

            switch (command) {
                case CMD_SET_EEPROM:
                    message = new EEPROMSetSerialMessage(&BLUETOOTH, &program);
                    continue;

                case CMD_GET_EEPROM:
                    message = new EEPROMGetSerialMessage(&BLUETOOTH);
                    continue;

                case CMD_BATTERY:
                    log_val("battery", analogRead(BATTERY_PIN));
                    BLUETOOTH.println(analogRead(BATTERY_PIN));
                    break;

                case CMD_ANGLE:
                    log_val("angle", mpu.get_angle());
                    BLUETOOTH.println(mpu.get_angle());
                    break;

                case CMD_ROTATION_RATE:
                    log_val("rotation rate", mpu.get_rotation_rate());
                    BLUETOOTH.println(mpu.get_rotation_rate());
                    break;

                case CMD_SET_MOVING_PROGRAM:
                    message = new SetMovingProgramSerialMessage(&BLUETOOTH, &program);
                    continue;

                case CMD_GET_MOVING_PROGRAM:
                    log_val("moving program", program.getMovingProgram());
                    BLUETOOTH.println(program.getMovingProgram());
                    break;

                case CMD_SET_STATIONARY_PROGRAM:
                    message = new SetStationaryProgramSerialMessage(&BLUETOOTH, &program);
                    continue;

                case CMD_GET_STATIONARY_PROGRAM:
                    log_val("stationary program", program.getStationaryProgram());
                    BLUETOOTH.println(program.getStationaryProgram());
                    break;

                default:
                    log_val("command err", ch);
                    BLUETOOTH.println("err");
                    break;
            }
        } else if (!message->consume(ch)) {
            continue;
        }

        // command has been executed, clear it
        command = 0;
    }
}