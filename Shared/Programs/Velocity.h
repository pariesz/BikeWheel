#pragma once
#include "../Program.h"
#include "../Configuration.h"

#define VELOCITY_NUMBER_LEN 2 // ##
#define VELOCITY_DECIMAL_LEN 6 // .# KMH

class Velocity : public Program {
private:
    char number[6]; // ##.# + one extra for NUL
    char decimal[7] = ".0 KMH";
    uint32_t color = 0;
    float factor;

public:
    Velocity() {
        configure();
    }

    void configure() {
        uint16_t wheelCircumference;

        EEPROM.get(EEPROM_WHEEL_CIRCUMFERENCE, wheelCircumference);

        // use a default to ensure we dont divide by 0
        if (wheelCircumference == 0) {
            wheelCircumference = 2288;
        }

        // c (wheel circumference) for 29in rim + 2.1in tire = 2288mm
        // v = rotation_rate * c
        // v(kmh) = (rotation_rate / 0xFFFF) * 2288mm * 60sec * 60min / (1000mm * 1000m)
        factor = ((float)0xFFFF * 1000 * 1000) / ((uint32_t)wheelCircumference * 60 * 60);
    }

    void update(int32_t rotation_rate) override {
        float v = abs(rotation_rate) / factor;

        // ##.# (4 char width, 1 decimal precision)
        dtostrf(v, 4, 1, number);

        // Move the decimal digit
        decimal[1] = number[3];

        color = Adafruit_DotStar::ColorHSV(v * 5120, 255, 255);
    }

    void render(uint16_t zero_angle) {
        // rotate image
        zero_angle += 0x800;

        Leds::clear();

        for (int i = 0, y = LEDS_PER_STRIP - 1; i < LEDS_COUNT; i++, y--) {
            if (y < 0) {
                y = LEDS_PER_STRIP - 1;
            }
            if (y > (FONT_HEIGHT << 1) - 1) {
                continue;
            }

            uint16_t angle = zero_angle + Leds::get_angle(i);

            // clear after the fisrt 135deg
            if (angle > 0x6000) {
                continue;
            }

            if (angle < 0x2000) {
                // render number in first 45deg (2ch per 45deg)
                uint16_t x = ((uint32_t)angle * (VELOCITY_NUMBER_LEN << FONT_WIDTH_SHIFT)) >> 13;
                uint8_t ch_x = x & (FONT_WIDTH - 1);
                uint8_t ch_num = x >> FONT_WIDTH_SHIFT;
                char ch = number[ch_num];

                if (((pgm_read_byte(&(fontdata_8x8[(uint16_t)ch * FONT_HEIGHT + (y >> 1)])) >> ((FONT_WIDTH - 1) - ch_x)) & 1)) {
                    Leds::set_color(i, color);
                }

                
            } else if (y >= FONT_HEIGHT) {
                // render decimal from 45deg to 135deg (8ch per 90deg)
                // offset 8px down

                uint16_t x = (((uint32_t)angle - 0x2000) * (VELOCITY_DECIMAL_LEN << FONT_WIDTH_SHIFT)) >> 14;
                uint8_t ch_x = x & (FONT_WIDTH - 1);
                uint8_t ch_num = x >> FONT_WIDTH_SHIFT;
                char ch = decimal[ch_num];

                if (((pgm_read_byte(&(fontdata_8x8[(uint16_t)ch * FONT_HEIGHT + y - FONT_HEIGHT])) >> ((FONT_WIDTH - 1) - ch_x)) & 1)) {
                    Leds::set_color(i, ch_num < 2 ? color : COLOR_WHITE);
                }
            }
        }
    }
};