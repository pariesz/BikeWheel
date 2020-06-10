#pragma once
#include "EEPROM_Mock.h"

#if !defined(ARDUINO)
#include <ios>
#include <iostream>
#include <fstream>
#include "avr_functions_Mock.h"

#define EEPROM_FILENAME "eeprom.bin"
#define EEPROM_LENGTH 4096 // Teensy3.6 https://www.pjrc.com/teensy/td_libs_EEPROM.html (E2END + 1)

char eeprom[EEPROM_LENGTH];
bool eeprom_read = false;

uint8_t eeprom_read_byte(const uint8_t* addr) {
    std::ifstream stream;

    if (!eeprom_read) {
        stream.open(EEPROM_FILENAME, std::ios::in | std::ios::binary);
        
        if (stream.fail()) {
            return 0;
        }

        stream.read(eeprom, EEPROM_LENGTH);
        stream.close();
        eeprom_read = true;
    }

    return eeprom[(int)addr];
}

void eeprom_write_byte(uint8_t* addr, uint8_t value) {
    eeprom[(int)addr] = value;

    std::ofstream stream;
    stream.open(EEPROM_FILENAME, std::ios::out | std::ios::binary);
    stream.write(eeprom, EEPROM_LENGTH);
    stream.close();
}
#endif