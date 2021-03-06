#pragma once
#include "../Program.h"
#include "../Configuration.h"

class ExplodingText : public Program {

private:
    uint16_t angle_offset = 0;
    uint8_t y_top = 0;
    uint16_t hue = random(0, 0xFFFF);
    char label[38];
    uint8_t label_length;
    uint8_t brightness = 0;
    uint32_t color = 0;
    uint16_t frame = 0;

public:
    ExplodingText() {
        configure();
    }

    void configure() override {
        Configuration::readString(EEPROM_EXPLODING_TEXT, label);
        label_length = strlen(label);
    }

    void update(int32_t rotation_rate) override {
        if (frame++ % 4 == 0) {
            angle_offset -= 500;

            if (++y_top > LEDS_PER_STRIP + FONT_HEIGHT) {
                y_top = 0;
                brightness = 0;
                hue = random(0, 0xFFFF);
            }
        }

        if (brightness < 0xFA) {
            brightness += 0x4;
        }

        color = Adafruit_DotStar::ColorHSV(hue, 255, brightness);
    }

    void render(uint16_t zero_angle) {
        zero_angle += angle_offset;

        Leds::clear();

        const int8_t y_bottom = y_top - (FONT_HEIGHT - 1);

        for (int i = 0, y = 0; i < LEDS_COUNT; i++, y++) {
            if (y == LEDS_PER_STRIP) {
                y = 0;
            }
            if (y < y_bottom || y > y_top) {
                continue;
            }

            uint16_t angle = zero_angle + Leds::get_angle(i);

            uint16_t x = ((uint32_t)angle * (label_length << FONT_WIDTH_SHIFT)) >> 16;

            uint8_t ch_x = x & (FONT_WIDTH - 1);
            uint8_t ch_y = (FONT_HEIGHT - 1) - (y - y_bottom);
            uint8_t ch_num = x >> FONT_WIDTH_SHIFT;

            // repeat the word
            if (ch_num >= label_length) {
                ch_num %= label_length;
            }

            char ch = label[ch_num];

            if (((pgm_read_byte(&(fontdata_8x8[(uint16_t)ch * FONT_HEIGHT + ch_y])) >> ((FONT_WIDTH - 1) - ch_x)) & 1)) {
                Leds::set_color(i, color);
            }
        }
    }
};