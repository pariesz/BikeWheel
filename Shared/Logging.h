#pragma once
#include "Mocks/Arduino_Mock.h"

#ifndef LOGGING
    #define LOGGING 0
#endif

#if LOGGING == 1
    #ifdef SIMULATION
        #define log(str) std::cout << (str)
        #define log_ln(str) std::cout << (str) << std::endl
        #define log_val(name, val) std::cout << (name) << ": " << (val) << std::endl
        #define log_rgb(val) std::cout << "R:" << (((val) & 0xFF0000) >> 16) << ", G:" << (((val) & 0x00FF00) >> 8) << ", B:" << ((val) & 0x0000FF) << std::endl

    #else
        #define log(message) Serial.print(F(message))
        #define log_ln(message) Serial.println(F(message))
        #define log_val(name, val) Serial.print(F(name)); Serial.print(F(": ")); Serial.println(val)
        #define log_rgb(val) Serial.print(  "R:"); Serial.print(  (val & 0xFF0000) >> 16);\
                             Serial.print(", G:"); Serial.print(  (val & 0x00FF00) >> 8);\
                             Serial.print(", B:"); Serial.println((val & 0x0000FF))
    #endif

    void log_fps();
#else
    #define log(message)
    #define log_ln(message)
    #define log_val(name, val)
    #define log_rgb(val)
    #define log_fps()
#endif