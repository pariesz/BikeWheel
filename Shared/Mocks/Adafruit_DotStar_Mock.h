#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
    #include <Adafruit_DotStar.h>
#else
#include "Arduino_Mock.h"

#define DOTSTAR_BGR 0

class Adafruit_DotStar {
    public:
        static uint8_t* vertices;
        
        Adafruit_DotStar(uint16_t num_pixels, uint8_t mode);
        
        void setPixelColor(uint16_t index, uint32_t color);
        void setPixelColor(uint16_t index, uint8_t r, uint8_t g, uint8_t b);
        void setBrightness(uint8_t);
        void begin();
        void show();
        void show(uint16_t angle);

        ~Adafruit_DotStar();
};
#endif

