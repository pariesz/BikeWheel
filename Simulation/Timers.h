#pragma once
#include <chrono>
#include "arduino.h"

class Timers {
    Timers(void) = delete;
public:
    static uint32_t now(void) {
        using namespace std::chrono;
        auto now = high_resolution_clock::now();
        auto ns = now.time_since_epoch();
        auto ms = duration_cast<microseconds>(ns);
        return ms.count();
    }

    static uint32_t millis(void) {
        using namespace std::chrono;
        auto now = high_resolution_clock::now();
        auto ns = now.time_since_epoch();
        auto ms = duration_cast<milliseconds>(ns);
        return ms.count();
    }

    static uint32_t micros(void) {
        using namespace std::chrono;
        auto now = high_resolution_clock::now();
        auto ns = now.time_since_epoch();
        auto us = duration_cast<microseconds>(ns);
        return us.count();
    }
};
