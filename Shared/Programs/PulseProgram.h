#pragma once
#include "Program.h"

class Pulse {
public:
    uint8_t position = 0xFF;
    uint16_t hue = 0;
};

class PulseProgram : public Program {

private:
    uint8_t frame = 0;
    uint8_t spawn_frame = 0;
    uint16_t spawn_strip = 0;
    uint16_t hue = random(0, 0xFFFF);
    Pulse pulses[LEDS_STRIPS_COUNT];

public:
    void update(uint16_t frame_count, int32_t rotation_rate) override {
        // Progress the existing pulses
        for (uint8_t i = 0; i < LEDS_STRIPS_COUNT; i++) {
            Pulse* pulse = &pulses[i];

            if (pulse->position >= (LEDS_PER_STRIP << 1)) {
                if (i == spawn_strip && frame >= spawn_frame) {
                    pulse->position = 0;
                    pulse->hue = hue += 6000;
                    spawn_strip = random(0, LEDS_STRIPS_COUNT - 1);
                    spawn_frame = random(0, 30);
                    frame = 0;
                }
            } else {
                pulse->position++;
                pulse->hue += 100;
            }
        }

        frame++;
    }

    void render(uint16_t zero_angle) override {
        Leds::clear();

        for (uint8_t strip = 0; strip < LEDS_STRIPS_COUNT; strip++) {
            Pulse pulse = pulses[strip];

            // The pulse has a length on 1 LED strip so we have to double the length
            // to render by bitshifting 1 as the head could be off the wheel
            int16_t startIndex = (int16_t)pulse.position - (LEDS_PER_STRIP << 1);

            // If the index is past the end of the strip we don't need to do anything
            if (startIndex > LEDS_PER_STRIP) {
                continue;
            }

            // Set the index to the bounds of the strip
            startIndex = max(startIndex, 0) + (strip * LEDS_PER_STRIP);

            // We only have to render until the head of the pulse or the bounds of the strip
            uint8_t pulseHead = (strip * LEDS_PER_STRIP) + pulse.position;
            uint8_t stripEnd = ((strip + 1) * LEDS_PER_STRIP) - 1;
            uint8_t endIndex = min(stripEnd, pulseHead);

            for (uint8_t i = startIndex; i <= endIndex; i++) {

                // bitshit 3 to scale LEDS_PER_STRIP (36) to uint8 (256)
                uint16_t brightnessOffset = ((pulse.position - (i - startIndex)) << 3);
                
                // The bitshit 3 (36 * 8) is slightly larger at 288 so we still need this check
                if (brightnessOffset >= 0xFF) {
                    Leds::set_color(i, COLOR_BLACK);
                    continue;
                }

                uint32_t color = Adafruit_DotStar::ColorHSV(pulse.hue, 0xFF, Adafruit_DotStar::gamma8(0xFF - brightnessOffset));

                Leds::set_color(i, color);
            }
        }
    }
};