#pragma once

uint8_t eeprom_read_byte(const uint8_t* addr);

void eeprom_write_byte(uint8_t* addr, uint8_t value);