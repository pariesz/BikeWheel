/*
 * 16-bit timer 1 used for Sensorino timekeeping as well as arbitrary
 * timeouts.
 *
 * Licensed under AGPLv3.
 */
#pragma once
#include <stdint.h>

#if F_CPU == 16000000
#define MICROS() (Timers::now() >> 4)
#elif F_CPU == 8000000
#define MICROS() (Timers::now() >> 3)
#else
#define MICROS() (Timers::now() / (F_CPU / 1000000))
#endif

#define SET_OBJ_TIMEOUT(method, timeout) setTimeout(new Callback<typeof(*this)>(this, &method), timeout)

class GenCallback {
public:
	virtual void call(void) = 0;
};

class Timers {
	Timers(void) = delete;
public:
	static void begin(void);
	static uint32_t now(void);
	static uint32_t millis(void);
	static void delay(uint16_t msecs);
	static void setTimeout(void (*callback)(void), uint32_t timeout);
	static void setTimeout(GenCallback *callback, uint32_t timeout);
};

template <typename T>
class Callback : public GenCallback {
	T *obj;
	void (T::*method)(void);

public:
	Callback(T *nobj, void (T::*nmethod)(void)) 
        : obj(nobj)
        , method(nmethod) {}

	void call(void) { 
        (obj->*method)();
    }
};
