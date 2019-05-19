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

// upside down
WheelSensors sensors;

// settings
bool on = 0;
uint8_t prog = 0;

// images
fist* fist_img = nullptr;
Hamster* hamster = nullptr;
LaPandora* la_pandora = nullptr;
NyanCat* nyan_cat = nullptr;
Poo* poo = nullptr;

void setup(void) {

#if LOGGING == 1
    Serial.begin(9600);
    while (!Serial);
    log_ln("Connected");
#endif

    sensors.setup();
    Leds::setup();
}

void stop(void) {
    on = 0;

    delete la_pandora;
    la_pandora = nullptr;

    delete fist_img;
    fist_img = nullptr;

    delete hamster;
    hamster = nullptr;

    delete nyan_cat;
    nyan_cat = nullptr;

    delete poo;
    poo = nullptr;
}

void start(void) {
    on = 1;

    switch (prog) {
        case 1: la_pandora = new LaPandora; break;
        case 5: fist_img = new fist; break;
        case 7: hamster = new Hamster; break;
        case 8: nyan_cat = new NyanCat; break;
        case 9: poo = new Poo; break;
    }
}

void loop(void) {
    sensors.loop();

//    Logging::test_segments(sensors.angle, sensors.hall_sensor.value);
//    Leds::leds.show();
//    return;

    if (on) {
        switch(prog) {
            case 0:
                Programs::spiral(sensors.angle); break;
            case 1:
                la_pandora->render(sensors.angle, sensors.rotation_rate); break;
            case 2:
                Programs::masa_critica(sensors.angle); break;
            case 3:
                Programs::kaleidoscope(sensors.angle); break;
            case 4:
                Programs::radioactive(sensors.angle); break;
            case 5:
                fist_img->render(sensors.angle, sensors.rotation_rate); break;
            case 6:
                Programs::rainbow_text(sensors.angle, 37, "- BCN - Critical Mass - Masa Critica"); break;
            case 7:
                hamster->render(sensors.angle, sensors.rotation_rate); break;
            case 8:
                nyan_cat->render(sensors.angle, sensors.rotation_rate); break;
            case 9:
                poo->render(sensors.angle, sensors.rotation_rate); break;
            case 10:
                Programs::velocity(sensors.angle, sensors.rotation_rate); break;
            default:
                prog = sensors.rotation_rate < 0 ? 10 : 0; 
                start(); 
                break;
        }
        
        if (abs(sensors.rotation_rate) < 60000) {
            stop();
        }
    } else {
        Programs::set_color(Colors::black);

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
