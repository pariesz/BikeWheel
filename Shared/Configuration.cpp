#include "Configuration.h"

namespace Configuration {
    void writeString(int address, const char* data) {
        int size = strlen(data);

        for (int i = 0; i < size; i++) {
            EEPROM.write(address + i, data[i]);
        }

        EEPROM.write(address + size, '\0'); // Add termination null character
    }


    void readString(int address, char* buffer) {
        int i = 0;

        while (true) {
            buffer[i] = EEPROM.read(address + i);

            // Read until null character
            if (buffer[i++] == '\0') break;
        }
    }
}