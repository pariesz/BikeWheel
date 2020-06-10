#pragma once
#include "Mocks/Arduino_Mock.h"

#if defined LOGGING && LOGGING == 1

const char hexChars[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

    #define log(message) Serial.print(F(message))
    
    #define log_ln(message) Serial.println(F(message))

    #define log_val(name, val) Serial.print(F(name));\
                               Serial.print(F(": "));\
                               Serial.println(val)

    #define log_rgb(val) Serial.print(  "R:"); Serial.print(  (val & 0xFF0000) >> 16);\
                         Serial.print(", G:"); Serial.print(  (val & 0x00FF00) >> 8);\
                         Serial.print(", B:"); Serial.println((val & 0x0000FF))

    #define log_hex(b) Serial.print(hexChars[b >> 4]);\
                       Serial.print(hexChars(b & 0x0F))

    inline void log_fps() {
        static unsigned int fps = 0;
        static unsigned long fps_millis = millis();

        if (millis() - fps_millis > 1000) {
            log_val("fps", fps);
            fps_millis = millis();
            fps = 0;
        }

        fps++;
    }
#else
    #define log(message)
    #define log_ln(message)
    #define log_val(name, val)
    #define log_rgb(val)
    #define log_fps()
    #define log_hex(b)
#endif