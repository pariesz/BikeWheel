#include "Programs.h"
#include "WheelSensors.h"
#include "Leds.h"
#include "Logging.h"
#include "./Images/rocket.h"

bool on = 0;
uint8_t prog = 0;
rocket rocket_image;
WheelSensors sensors;

void setup(void) {

#if LOGGING == 1
    Serial.begin(9600);
    while (!Serial);
    Serial.println(F("Connected"));
#endif

    sensors.setup();

    Leds::leds.setBrightness(20);
    Leds::leds.begin();
    Leds::leds.show();
}

void loop(void) {
    sensors.loop();

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
    if (on) {
        switch(prog) {
            case 0:
                Programs::spiral(sensors.angle); break;
            case 1: 
                Programs::rainbow_text(sensors.angle, 37, "- BCN - Critical Mass - Masa Critica"); break;
            case 2:
                Programs::masa_critica(sensors.angle); break;
            case 3:
                Programs::flower(sensors.angle); break;
            case 4:
                Programs::umbrella(sensors.angle); break;
            case 5:
                Programs::radioactive(sensors.angle); break;
            case 6:
                rocket_image.render(sensors.angle, sensors.rotation_rate); break;
            default:
                prog = sensors.rotation_rate < 0 ? 6 : 0; break;
        }
        
        if (abs(sensors.rotation_rate) < 60000) {
            on = 0;
        }
    } else {
        Programs::set_color(0x000000);

        if (abs(sensors.rotation_rate) > 80000) {
            on = 1;

            if (sensors.rotation_rate < 0) {
                prog--;
            } else {
                prog++;
            }
        }
    }

    Leds::leds.show();
}
