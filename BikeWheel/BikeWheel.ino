#include "./Programs.h"
#include "./Mpu.h"
#include "./Pixels.h"
#include "./Timers.h"
#include "./Debug.h"
#include "./rocket.h"

//#define HALL
#ifdef HALL
#include "./HallSensor.h"
#endif

rocket image;

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

void loop(void) {
#ifdef HALL
    HallSensor::update();
#endif

    Mpu::update();

    /*
       Persistence of vision is a theory which attempts to explain 
       how the human eye/brain can be "fooled" into seeing continuous 
       motion when presented with a sequence of discrete still images 
       (film or video frames) at a rate of 10 frames per second (fps) 
       or greater.

       We have 4 stips so the wheel must 2 10/4 = 2.5 times a second.
       The is a rate of change og about 26 angle/ms.

       To stop flicker at the threashold we add a buffer zone.
       Turn on at 60 ang/ms and off at 30 ang/ms. 
    */

    uint32_t rotation_rate_abs = abs(Mpu::rotation_rate);

#ifdef DEBUG
    off = false;
#else
    if (rotation_rate_abs < 30000) {
        off = true;
    } else if (rotation_rate_abs > 60000) {
        off = false;
    }
#endif

    if (off) {
        Programs::set_color(0x000000);
    } else {
        //Programs::text(Mpu::angle, 13, "MASA CRITICA ");
        //Programs::color_segments(Mpu::angle);
        image.render(Mpu::angle, Mpu::rotation_rate);
    }

    Pixels::leds.show();
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
