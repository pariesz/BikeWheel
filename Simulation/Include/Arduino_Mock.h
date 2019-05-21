#pragma once
#include <math.h>
#include <iostream>

inline char pgm_read_byte(const char *ptr) {
    return *ptr;
}
inline uint8_t pgm_read_byte(const uint8_t *ptr) {
    return *ptr;
}
inline uint16_t pgm_read_word(const uint16_t *ptr) {
    return *ptr;
}
inline uint32_t pgm_read_dword(const uint32_t *ptr) {
    return *ptr;
}

uint32_t millis();

uint32_t micros();

uint32_t random(uint32_t lower, uint32_t upper);

char *dtostrf(double val, int width, unsigned int prec, char *sout);

#define __attribute__(...)

#define PROGMEM
#define F(str) str
//#define F_CPU 16000000L

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
//#define abs(x) ((x)>0?(x):-(x))
//#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
//#define round(x)     ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
//#define radians(deg) ((deg)*DEG_TO_RAD)
//#define degrees(rad) ((rad)*RAD_TO_DEG)
#define sq(x) ((x)*(x))

//#define clockCyclesPerMicrosecond() ( F_CPU / 1000000L )
//#define clockCyclesToMicroseconds(a) ( (a) / clockCyclesPerMicrosecond() )
//#define microsecondsToClockCycles(a) ( (a) * clockCyclesPerMicrosecond() )

//#define lowByte(w) ((uint8_t) ((w) & 0xff))
//#define highByte(w) ((uint8_t) ((w) >> 8))

//#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
//#define bitSet(value, bit) ((value) |= (1UL << (bit)))
//#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
//#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

//#define interrupts()
//#define noInterrupts()

#define HIGH 0x1
#define LOW  0x0

//#define INPUT 0x0
//#define OUTPUT 0x1
//#define INPUT_PULLUP 0x2

#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105
#define EULER 2.718281828459045235360287471352

//#define SERIAL  0x0
//#define DISPLAY 0x1
//
//#define LSBFIRST 0
//#define MSBFIRST 1
//
//#define CHANGE 1
//#define FALLING 2
//#define RISING 3
//
//#define NOT_ON_TIMER 0
//#define TIMER0A 1
//#define TIMER0B 2
//#define TIMER1A 3
//#define TIMER1B 4
//#define TIMER1C 5
//#define TIMER2  6
//#define TIMER2A 7
//#define TIMER2B 8

#define TIMER3A 9
#define TIMER3B 10
#define TIMER3C 11
#define TIMER4A 12
#define TIMER4B 13
#define TIMER4C 14
#define TIMER4D 15
#define TIMER5A 16
#define TIMER5B 17
#define TIMER5C 18