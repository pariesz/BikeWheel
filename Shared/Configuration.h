#pragma once
#include "Mocks/Arduino_Mock.h"
#include "Mocks/EEPROM_Mock.h"

#define EEPROM_WHEEL_CIRCUMFERENCE 0 // int16
#define EEPROM_MOVING_RATE 2 // int32
#define EEPROM_STATIONARY_RATE 6 // int32
#define EEPROM_BRIGHTNESS 10 // int8
#define EEPROM_EXPLODING_TEXT 11 // 39 byte string (with NUL terminator)
#define EEPROM_TIMER_FRAMES 50 // int16

#define CMD_SET_EEPROM 1
#define CMD_GET_EEPROM 2
#define CMD_BATTERY 3
#define CMD_ANGLE 4
#define CMD_ROTATION_RATE 5
#define CMD_SET_MOVING_PROGRAM 6
#define CMD_GET_MOVING_PROGRAM 7
#define CMD_SET_STATIONARY_PROGRAM 8
#define CMD_GET_STATIONARY_PROGRAM 9

namespace Configuration {
    void writeString(int address, const char* data);
    void readString(int address, char* buffer);
}