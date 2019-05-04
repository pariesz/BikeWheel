#pragma once

#define LOGGING 0

#if LOGGING == 1

#ifdef SIMULATION
#define LOG(str) std::cout << (str)
#define LOG_LN(str) std::cout << (str) << std::endl
#define LOG_VAL(name, val) std::cout << (name) << ": " << (val) << std::endl
#define LOG_RGB(val) std::cout << "R:" << (((val) & 0xFF0000) >> 16) << ", G:" << (((val) & 0x00FF00) >> 8) << ", B:" << ((val) & 0x0000FF) << std::endl

#else
#define LOG(message) Serial.print(F(message))
#define LOG_LN(message) Serial.println(F(message))
#define LOG_VAL(name, val) Serial.print(F(name)); Serial.print(F(": ")); Serial.println(val)
#define LOG_RGB(val) Serial.print(  "R:"); Serial.print(  (val & 0xFF0000) >> 16);\
                     Serial.print(", G:"); Serial.print(  (val & 0x00FF00) >> 8);\
                     Serial.print(", B:"); Serial.println((val & 0x0000FF))
#endif

#define LOG_FPS log_fps()
namespace Logging {
    inline void log_fps();
    void test_segments(uint16_t zero_angle, bool hallVal);
}

#else
#define LOG(message)
#define LOG_LN(message)
#define LOG_VAL(name, val)
#define LOG_RGB(val)
#define LOG_FPS
#endif