#pragma once
#include <chrono>
#include "Arduino_Mock.h"

uint32_t millis() {
    using namespace std::chrono;
    auto now = high_resolution_clock::now();
    auto ns = now.time_since_epoch();
    auto ms = duration_cast<milliseconds>(ns);
    return ms.count();
}

uint32_t micros() {
    using namespace std::chrono;
    auto now = high_resolution_clock::now();
    auto ns = now.time_since_epoch();
    auto us = duration_cast<microseconds>(ns);
    return us.count();
}