#include "arduino.h"
#include "HallSensor.h"
#include "./Debug.h"
#define HALL_PIN 3
#define LED_PIN 13 

namespace HallSensor {
    uint16_t angle = 0;
    long interval_micros = 0;

    static uint16_t angle_offset = 0;
    static int hallVal = HIGH; // This is where we record the OH137 Input
    
    static unsigned long time_micros = 0;

    void init(uint16_t offet) {
        pinMode(HALL_PIN, INPUT); // input from the OH137
        angle_offset = offet;
        time_micros = micros();
    }

    void update(void) {
        int val = digitalRead(HALL_PIN); // read OH137 Value

        if (hallVal == LOW && val == HIGH) {  // means magnetic field detected
            interval_micros = micros() - time_micros;
            time_micros = micros();
            angle = 0;

#ifdef DEBUG
            Serial.print(F("interval: "));
            Serial.println(interval_micros);
#endif

            hallVal = HIGH;
            digitalWrite(LED_PIN, HIGH);
            return;
        }

        if (hallVal == HIGH && val == LOW) {
            hallVal = val;
            digitalWrite(LED_PIN, LOW);
        }

        auto time_diff = micros() - time_micros;

        if (time_diff > interval_micros) {
            // Slowing down
            interval_micros = time_diff;
            angle = 65535;
            return;
        }

        angle = (
            (
                time_diff / (float)interval_micros // divide the difference to get a factor reperesenting the rotation
            ) * 65535 // scale the angle factor by uint16
        ) + angle_offset; // offset the rotation relative to the y axis
    }
}
