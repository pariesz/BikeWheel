#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
#include "EEPROM.h"
#else
#include "Arduino_Mock.h"
#include "avr_functions_Mock.h"

struct EERef {

    #define E2END 0xFFF

    EERef(const int index)
        : index(index) {}

    //Access/read members.
    uint8_t operator*() const { return eeprom_read_byte((uint8_t*)index); }
    operator const uint8_t() const { return **this; }

    //Assignment/write members.
    EERef& operator=(const EERef& ref) { return *this = *ref; }
    EERef& operator=(uint8_t in) { return eeprom_write_byte((uint8_t*)index, in), * this; }
    EERef& operator +=(uint8_t in) { return *this = **this + in; }
    EERef& operator -=(uint8_t in) { return *this = **this - in; }
    EERef& operator *=(uint8_t in) { return *this = **this * in; }
    EERef& operator /=(uint8_t in) { return *this = **this / in; }
    EERef& operator ^=(uint8_t in) { return *this = **this ^ in; }
    EERef& operator %=(uint8_t in) { return *this = **this % in; }
    EERef& operator &=(uint8_t in) { return *this = **this & in; }
    EERef& operator |=(uint8_t in) { return *this = **this | in; }
    EERef& operator <<=(uint8_t in) { return *this = **this << in; }
    EERef& operator >>=(uint8_t in) { return *this = **this >> in; }

    EERef& update(uint8_t in) { return  in != *this ? *this = in : *this; }

    /** Prefix increment/decrement **/
    EERef& operator++() { return *this += 1; }
    EERef& operator--() { return *this -= 1; }

    /** Postfix increment/decrement **/
    uint8_t operator++ (int) {
        uint8_t ret = **this;
        return ++(*this), ret;
    }

    uint8_t operator-- (int) {
        uint8_t ret = **this;
        return --(*this), ret;
    }

    int index; //Index of current EEPROM cell.
};

struct EEPtr {

    EEPtr(const int index)
        : index(index) {}

    operator const int() const { return index; }
    EEPtr& operator=(int in) { return index = in, *this; }

    //Iterator functionality.
    bool operator!=(const EEPtr& ptr) { return index != ptr.index; }
    EERef operator*() { return index; }

    /** Prefix & Postfix increment/decrement **/
    EEPtr& operator++() { return ++index, * this; }
    EEPtr& operator--() { return --index, * this; }
    EEPtr operator++ (int) { return index++; }
    EEPtr operator-- (int) { return index--; }

    int index; //Index of current EEPROM cell.
};

struct EEPROMClass {
    //Basic user access methods.
    EERef operator[](const int idx) { return idx; }
    uint8_t read(int idx) { return EERef(idx); }
    void write(int idx, uint8_t val) { (EERef(idx)) = val; }
    void update(int idx, uint8_t val) { EERef(idx).update(val); }

    //STL and C++11 iteration capability.
    EEPtr begin() { return 0x00; }
    EEPtr end() { return length(); } //Standards requires this to be the item after the last valid entry. The returned pointer is invalid.
    uint16_t length() { return E2END + 1; }

    //Functionality to 'get' and 'put' objects to and from EEPROM.
    template< typename T > T& get(int idx, T& t) {
        EEPtr e = idx;
        uint8_t* ptr = (uint8_t*)&t;
        for (int count = sizeof(T); count; --count, ++e)  *ptr++ = *e;
        return t;
    }

    template< typename T > const T& put(int idx, const T& t) {
        const uint8_t* ptr = (const uint8_t*)&t;
        EEPtr e = idx;
        for (int count = sizeof(T); count; --count, ++e)  (*e).update(*ptr++);
        return t;
    }
};

static EEPROMClass EEPROM;
#endif