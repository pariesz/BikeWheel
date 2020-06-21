#pragma once
#include "Program.h"

class PortalSettings {
public:
    uint8_t  lineFrameSkip = 3;
    uint16_t lineMinWidth = 0x1FFF;
    uint16_t lineMaxWidth = 0x2FFF;
    uint16_t lineColorChangeRate = 765;
    uint8_t  lineRotationRate = 100;
};

class PortalLine {
    private:
        uint32_t color = 0;
        uint16_t start_angle = 0;
        uint16_t end_angle = 0;

    public:
        PortalLine() { }
        PortalLine(uint16_t hue, uint16_t width)
            : color(Adafruit_DotStar::ColorHSV(hue))
            , start_angle(random(0, 0xFFFF))
            , end_angle(start_angle + width) {
        }

        bool show(uint16_t angle) {
            if (end_angle < start_angle) {
                // overflow
                if (angle > start_angle || angle < end_angle) {
                    return true;
                }
            } else {
                if (angle > start_angle && angle < end_angle) {
                    return true;
                }
            }
            return false;
        }

        inline uint32_t get_color() {
            return color;
        }
};

class Portal : public Program {
    private:
        PortalLine lines[LEDS_PER_STRIP];
        uint8_t index = 0;
        uint16_t color_offset = random(0, 0xFFFF);
        uint16_t angle_offset = 0;
        uint32_t ms_prev = millis();
        PortalSettings settings;
        uint16_t frame = 0;

    public:

        void update(int32_t rotation_rate) override {
            angle_offset += settings.lineRotationRate;

            // create new stars
            if (frame % settings.lineFrameSkip == 0) {
                if (++index == LEDS_PER_STRIP) {
                    index = 0;
                }
                lines[index] = PortalLine(color_offset += settings.lineColorChangeRate, random(settings.lineMinWidth, settings.lineMaxWidth));
            }

            frame++;
        }

        void render(uint16_t zero_angle) {
            zero_angle += angle_offset;

            Leds::clear();

            // update leds
            for (uint8_t i = 0, y = 0; i < LEDS_COUNT; i++, y++) {
                if (y == LEDS_PER_STRIP) y = 0;

                int8_t i_star = y - index;

                if (i_star < 0) {
                    i_star = LEDS_PER_STRIP + i_star;
                }

                PortalLine line = lines[i_star];

                if (line.show(zero_angle + Leds::get_angle(i))) {
                    Leds::set_color(i, line.get_color());
                }
            }
        }
};