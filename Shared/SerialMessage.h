#pragma once
#include "Mocks/Arduino_Mock.h"
#include "Mocks/EEPROM_Mock.h"
#include "Mocks/Serial_Mock.h"
#include "Logging.h"
#include "Configuration.h"
#include "Programs/MainProgram.h"

class SerialMessage {
protected:
    Stream* bluetooth;

public:
    SerialMessage(Stream* bluetooth)
        : bluetooth(bluetooth) {
    }

    virtual bool consume(char ch) {
        log_val("message err", (int)ch);
        bluetooth->println("err");
        return true;
    };
};

class SetMovingProgramSerialMessage : public SerialMessage {
private:
    MainProgram* program;

public:
    SetMovingProgramSerialMessage(Stream* bluetooth, MainProgram* program)
        : SerialMessage(bluetooth)
        , program(program) {
    }

    bool consume(char ch) override {
        log_val("set moving program", (int)ch);
        program->setMovingProgram(ch);
        bluetooth->println(program->getMovingProgram());
        return true;
    }
};

class SetStationaryProgramSerialMessage : public SerialMessage {
private:
    MainProgram* program;

public:
    SetStationaryProgramSerialMessage(Stream* bluetooth, MainProgram* program)
        : SerialMessage(bluetooth)
        , program(program) {
    }

    bool consume(char ch) override {
        log_val("set stationary program", (int)ch);
        program->setStationaryProgram(ch);
        bluetooth->println(program->getStationaryProgram());
        return true;
    }
};

class EEPROMSerialMessage : public SerialMessage {
protected:
    uint16_t address = 0;
    uint8_t length = 0;
    uint8_t position = 0;

    EEPROMSerialMessage(Stream* bluetooth) 
        : SerialMessage(bluetooth) {
    }

    void print() {
        // Host byte order (little-edian)
        bluetooth->write((uint8_t)(address & 0xFF));
        bluetooth->write((uint8_t)(address >> 8));

        bluetooth->write(length);

        log("data: 0x");
        for (uint16_t i = address; i < address + length; i++) {
            // Host byte order (little-edian)
            log_hex(EEPROM.read(i));
            bluetooth->write(EEPROM.read(i));
        }
        log_ln("");
    }
};

class EEPROMGetSerialMessage : public EEPROMSerialMessage {
public:
    EEPROMGetSerialMessage(Stream* bluetooth)
        : EEPROMSerialMessage(bluetooth) {
    }

    bool consume(char ch) override {
        switch (++position) {
        case 1:
            address = ch;
            return false;

        case 2:
            address |= ((uint16_t)ch << 8); // little-edian
            log_val("address", address);
            return false;

        case 3:
            length = ch;
            log_val("length", length);
            EEPROMSerialMessage::print();
            return true;

        default:
            return SerialMessage::consume(ch);
        }
    }
};

class EEPROMSetSerialMessage : public EEPROMSerialMessage {
private:
    Program* program;

public:
    EEPROMSetSerialMessage(Stream* bluetooth, Program* program)
        : EEPROMSerialMessage(bluetooth)
        , program(program) {
    }

    bool consume(char ch) override {
        switch (++position) {
        case 1:
            address = ch;
            return false;

        case 2:
            address |= ((uint16_t)ch << 8); // little-edian
            log_val("address", address);
            return false;

        case 3:
            length = ch;
            log_val("length", length);
            return false;

        default: // >= 4  data must be sent in host byte order (little-edian)
            if (position - 3 < length) {
                EEPROM.write(address + position - 4, ch);
                return false;
            }

            if (position - 3 == length) {
                EEPROM.write(address + position - 4, ch);
                EEPROMSerialMessage::print();
                program->configure();
                return true;
            }
            
            return SerialMessage::consume(ch);
        }
    }
};

