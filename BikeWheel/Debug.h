#pragma once

#define DEBUG

#ifdef DEBUG 
#define LOG(message) Serial.println(F(message))
#else
#define LOG(message)
#endif