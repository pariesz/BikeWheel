#include "Programs.h"
#include "WheelSensors.h"
#include "Leds.h"
#include "Logging.h"
#include "./Images/LaPandora.h"
#include "./Images/fist.h"


WheelSensors sensors;

// settings
bool on = 0;
uint8_t prog = 0;

// images
LaPandora* la_pandora = nullptr;
fist* fist_img = nullptr;

void setup(void) {

#if LOGGING == 1
    Serial.begin(9600);
    while (!Serial);
    Serial.println(F("Connected"));
#endif

    sensors.setup();
    Leds::setup();
}

void stop(void) {
    on = 0;

    switch (prog) {
        case 1:
            delete la_pandora;
            break;
        case 6:
            delete fist_img;
            break;
    }
}

void start(void) {
    on = 1;

    switch (prog) {
        case 1:
            la_pandora = new LaPandora();
            la_pandora->initialize();
            break;
        case 6:
            fist_img = new fist();
            fist_img->Initialize();
            break;
    }
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
                la_pandora->render(sensors.angle, sensors.rotation_rate); break;
            case 2:
                Programs::masa_critica(sensors.angle); break;
            case 3:
                Programs::flower(sensors.angle); break;
            case 4:
                Programs::umbrella(sensors.angle); break;
            case 5:
                Programs::radioactive(sensors.angle); break;
            case 6:
                fist_img->render(sensors.angle, sensors.rotation_rate); break;
            case 7:
                Programs::rainbow_text(sensors.angle, 37, "- BCN - Critical Mass - Masa Critica"); break;
            default:
                prog = sensors.rotation_rate < 0 ? 7 : 0; 
                start(); 
                break;
        }
        
        if (abs(sensors.rotation_rate) < 60000) {
            stop();
        }
    } else {
        Programs::set_color(0x000000);

        if (abs(sensors.rotation_rate) > 80000) {
            if (sensors.rotation_rate < 0) {
                prog--;
            } else {
                prog++;
            }

            start();
        }
    }

    Leds::leds.show();
}
