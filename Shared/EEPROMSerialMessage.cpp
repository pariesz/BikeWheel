#include "EEPROMSerialMessage.h"

EEPROMSerialMessage::EEPROMSerialMessage(bool write)
    : write(write)
    , address(0) 
    , length(0)
    , position(0) {
}

bool EEPROMSerialMessage::consume(char ch) {
    switch (++position) {
        case 1:
            address = (uint16_t)ch << 8;
            return false;

        case 2:
            address |= ch;
            log_val("address", address);
            return false;

        case 3:
            length = ch;
            log_val("length", length);
            return !write;

        default:
            EEPROM.write(address + position - 4, ch);
            return position - 3 >= length;
    }
}

void EEPROMSerialMessage::print(Stream* stream) {
    log("data: 0x");

    for (uint16_t i = address; i < address + length; i++) {
        log_hex(EEPROM.read(i));
        stream->write(EEPROM.read(i));
    }

    log_ln("");
}
