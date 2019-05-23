#pragma once
#pragma warning(disable:4996)
#include "Arduino_Mock.h"

#if !defined(ARDUINO)
#include <chrono>
#include <string.h>
#include <stdlib.h>

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

uint32_t random(uint32_t lower, uint32_t upper) {
    int range = (upper - lower + 1);
    int rand = (std::rand() % range);
    if (range > RAND_MAX) rand *= range / RAND_MAX;
    return rand + lower;
}

char *dtostrf(double val, int width, unsigned int prec, char *sout) {
    char fmt[20];
    sprintf_s(fmt, "%%%d.%df", width, prec);
    sprintf(sout, fmt, val);
    return sout;
}

static uint8_t digitalPins[12];

void digitalWrite(uint8_t index, uint8_t value) {
    digitalPins[index] = value;
}

uint8_t digitalRead(uint8_t index) {
    return digitalPins[index];
}
#endif