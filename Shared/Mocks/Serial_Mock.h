#pragma once

#if not defined(ARDUINO)
#include <windows.h>
#include <iostream>

#define DEC 10
#define HEX 16
#define OCT 8

class String {
public:
    std::string value;

    String() : value("") {}
    String(char* data) { value = std::string(data); }
    String(std::string value) : value(value) { }

    char operator[](int index) {
        return value[index];
    }

    unsigned char startsWith(const String& prefix) {
        return value.rfind(prefix.value, 0) == 0;
    };
    
    String substring(unsigned int beginIndex, unsigned int endIndex) {
        return String(value.substr(beginIndex, endIndex - beginIndex));
    };

    int length() {
        return value.length();
    }
};

class Print {
public:
    size_t write(uint8_t b);

    //void print(const __FlashStringHelper *);
    void print(const String& s) { print(s.value.c_str()); }
    void print(const char[]);
    void print(char);
    void print(unsigned char, int = DEC);
    void print(int, int = DEC);
    void print(unsigned int, int = DEC);
    void print(long, int = DEC);
    void print(unsigned long, int = DEC);
    void print(double, int = 2);
    //void print(const Printable&);

    //void println(const __FlashStringHelper *);
    void println(const String &s) { println(s.value.c_str()); }
    void println(const char[]);
    void println(char);
    void println(unsigned char, int = DEC);
    void println(int, int = DEC);
    void println(unsigned int, int = DEC);
    void println(long, int = DEC);
    void println(unsigned long, int = DEC);
    void println(double, int = 2);
    //void println(const Printable&);
    void println(void);
};

class Stream : public Print {
public:
    int available(void);
    String readString(std::size_t max = 120);
};

extern Print Serial; 
extern Stream Serial1;
#endif

