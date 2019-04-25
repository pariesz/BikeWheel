#include "./Programs.h"
#include "./Mpu.h"
#include "./Pixels.h"
#include "./Timers.h"
#include "./Debug.h"

//#define HALL
#ifdef HALL
#include "./HallSensor.h"
#endif

void setup(void) {

#ifdef DEBUG
    Serial.begin(9600);
    while (!Serial);

    Serial.println(F("Connected"));
#endif

    Pixels::Strip strips[] = {
        Pixels::Strip(
           59,   9,
          262, 140
        ),
        Pixels::Strip(
            9,  -59,
          140, -262
        ),
        Pixels::Strip(
            -59,  -9,
           -262,-140
        ),
        Pixels::Strip(
             -9,  59,
           -140, 262
        )
    };

    Pixels::init(strips);

    Mpu::init();

#ifdef HALL
    HallSensor::init(0);
#endif
}

bool off = true; // clear all pixels

int16_t velocity = 0; // angle / ms

void loop(void) {
#ifdef HALL
    HallSensor::update();
#endif

    Mpu::update();

    update_velocity();

    /*
       Persistence of vision is a theory which attempts to explain 
       how the human eye/brain can be "fooled" into seeing continuous 
       motion when presented with a sequence of discrete still images 
       (film or video frames) at a rate of 10 frames per second (fps) 
       or greater.

       We have 4 stips so the wheel must 2 10/4 = 2.5 times a second.
       The is a rate of change og about 26 angle/ms.

       To stop flicker at the threashold we add a buffer zone.
       Turn on at 20 ang/ms and off at 30 ang/ms. 
    */

    uint16_t velocity_abs = abs(velocity);

    if (velocity_abs < 5) {
        off = true;
    } else if (velocity_abs > 15) {
        off = false;
    }

    if (off) {
        Programs::set_color(0x000000);
    } else {
        Programs::text(Mpu::angle, 14, "MASSA CRITICA ");
    }


    Pixels::leds.show();
}

void update_velocity() {
    static uint16_t prev_angle = Mpu::angle;
    static uint32_t prev_time = micros();

    uint32_t time = micros();
    uint16_t time_diff = prev_time - time;
    if (time_diff < (1 << 15)) {
        return;
    }

    prev_time = time;

    if (DIFF_ABS(prev_angle, Mpu::angle) > (1 << 15)) {
        // overflow check
        prev_angle = Mpu::angle;
        return;
    }

    velocity = (((int32_t)Mpu::angle - prev_angle) << 10) / time_diff;
    prev_angle = Mpu::angle;

    Serial.println(velocity);
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
