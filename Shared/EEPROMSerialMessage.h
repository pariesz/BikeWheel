#pragma once
#include "Mocks/Arduino_Mock.h"
#include "Mocks/EEPROM_Mock.h"
#include "Mocks/Serial_Mock.h"
#include "Logging.h"

class EEPROMSerialMessage {
private:
    bool write;
    uint16_t address;
    uint8_t length;
    uint8_t position;

public:
    EEPROMSerialMessage(bool write);
    bool consume(char ch);
    void print(Stream* stream);
};

