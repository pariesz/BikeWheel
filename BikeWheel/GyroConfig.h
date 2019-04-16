#pragma once
#include "arduino.h"

/*
 * Don't actually use this by default, seem to kill cheap arduino
 * clones left and right...
 */
#define USE_EEPROM false

class GyroConfig {
    public:
        uint32_t magic;
        uint8_t prog;
        uint16_t gyro_multiplier;
        uint8_t cf_samples;
        float cf_acc[2];

    public:
        GyroConfig();
        void load(void);
        void save(void) const;
};

