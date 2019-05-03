#include "Programs.h"
#include "Wheel_Sensors.h"
#include "Leds.h"
#include "Logging.h"
#include "./Images/rocket.h"

//#define LOGGING

bool on = 0; // clear all pixels
uint8_t prog = 0;
rocket image;

void setup(void) {

#ifdef LOGGING
    Serial.begin(9600);
    while (!Serial);

    Serial.println(F("Connected"));
#endif

    Leds::leds.setBrightness(20);
    Leds::leds.begin();
    Leds::leds.show();

    Wheel_Sensors::init();
}

void loop(void) {
    Wheel_Sensors::update();

    /*
       Persistence of vision is a theory which attempts to explain 
       how the human eye/brain can be "fooled" into seeing continuous 
       motion when presented with a sequence of discrete still images 
       (film or video frames) at a rate of 10 frames per second (fps) 
       or greater.

       We have 4 stips so the wheel must 2 10/4 = 2.5 times a second.
       The is a rate of change og about 26 angle/ms.

       To stop flicker at the threashold we add a buffer zone.
       Turn on at 270 deg/ms and off at 180 deg/s. 
    */

    uint32_t rotation_rate_abs = abs(Wheel_Sensors::rotation_rate);

#ifdef DEBUG
    on = 0;  
#endif
    if (on) {
        switch(prog) {
            case 0:
                Programs::spiral(Wheel_Sensors::angle); break;
            case 1:
                image.render(Wheel_Sensors::angle, Wheel_Sensors::rotation_rate); break;
            case 2: 
                Programs::rainbow_text(Wheel_Sensors::angle, 37, "- BCN - Critical Mass - Masa Critica"); break;
            case 3:
                Programs::masa_critica(Wheel_Sensors::angle); break;
            case 4:
                Programs::flower(Wheel_Sensors::angle); break;
            case 5:
                Programs::umbrella(Wheel_Sensors::angle); break;
            case 6:
                Programs::radioactive(Wheel_Sensors::angle); break;
            default:
                prog = 0; break;
        }
        
        if (rotation_rate_abs < 30000) {
            on = 0;
        }
    } else {
        Programs::set_color(0x000000);

        if (rotation_rate_abs > 40000) {
            on = 1;

            if (Wheel_Sensors::rotation_rate < 0) {
                prog--;
            } else {
                prog++;
            }
        }
    }

    Leds::leds.show();
}
