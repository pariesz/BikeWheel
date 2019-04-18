#include "./Programs.h"
//#include "./Gyro.h"
//#include "./Mpu2.h"
#include "./HallSensor.h"
#include "./Pixels.h"
#include "./Timers.h"
#include "./Vector.h"
#include "./Debug.h"

void setup(void) {

#ifdef DEBUG
    Serial.begin(9600);
    while (!Serial);

    Serial.println(F("Connected"));
#endif

    Pixels::Strip strips[] = {
        Pixels::Strip(
            -32, 48,
            -51, 282
        ),
        Pixels::Strip(
            32, 48,
            51, 282
        ),
        Pixels::Strip(
            58, 4,
            270, -97
        ),
        Pixels::Strip(
            25, -52,
            219, -185
        )
    };

    Pixels::init(strips);

    //Vector3<int16_t> gyro_offset = Vector3<int16_t>(-2426, 1993, 5225);
    //Vector3<int16_t> acc_offset = Vector3<int16_t>(149, 60, 59);
    //Gyro::init(gyro_offset, acc_offset);
    //Mpu2::init(gyro_offset, acc_offset);

    HallSensor::init(0);
	
    Timers::begin();
}

void loop(void) {
    HallSensor::update();
    
    if (HallSensor::interval_micros > 1000000L || HallSensor::interval_micros == 0) {
        // No sensor information yet, or the wheel is moving too slow (less than 1rps)
        Programs::set_color(0x000000);
    } else {
        Programs::set_half_color(0x001100, HallSensor::angle);
    }

    Pixels::leds.show();

#ifdef DEBUG
    fps_counter();
#endif
}

#ifdef DEBUG
void fps_counter() {
    static unsigned int fps = 0;
    static unsigned long fps_millis = millis();

    if (millis() - fps_millis > 1000) {
        Serial.print(fps);
        Serial.println(F("fps"));

        fps_millis = millis();
        fps = 0;
    }

    fps++;
}
#endif
