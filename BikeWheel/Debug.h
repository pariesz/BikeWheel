//#pragma once

//#define DEBUG

#ifdef DEBUG 
#define LOG(message) Serial.print(F(message))
#define LOG_LN(message) Serial.println(F(message))
#else
#define LOG(message)
#define LOG_LN(message)
#endif