#pragma once
#include "../Images/HamsterRun1.h"
#include "../Images/HamsterRun2.h"
#include "../Images/HamsterRoll1.h"
#include "../Images/HamsterRoll2.h"
#include "../Program.h"

class Hamster : public Program {

private:
    uint8_t speed = 0;
    uint16_t angle_offset = 0;

    Image* frame1 = new HamsterRun1;
    Image* frame2 = new HamsterRun2;
    Image* frame = nullptr;

private:
    void update_frames() {
        delete frame1;
        delete frame2;

        if (speed <= 7) {
            frame1 = new HamsterRun1;
            frame2 = new HamsterRun2;
        } else {
            frame1 = new HamsterRoll1;
            frame2 = new HamsterRoll2;
        }
    }

public:
    void update(uint16_t frame_count, int32_t rotation_rate) override {
        uint32_t ms = millis();

        uint32_t rate = abs(rotation_rate);

        //rate <<= 1; // DEBUGING

        if (rate >> 14 != speed) {
            speed = rate >> 14;
            update_frames();
        }

        bool frame_select = 0;

        switch (speed) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5: // <12kmh
                angle_offset = 0;
                frame_select = ms & (1 << 10);
                break;

            case 6: { // 12-14kmh
                uint16_t loop = ms & 0x7FF;

                if (loop & 0x400) {
                    loop ^= 0x7FF;
                }

                angle_offset = (loop << 3) - 0x1000;
                frame_select = ms & (1 << 9);
            }
                    break;

            case 7: { // 14-16kmh
                uint16_t loop = ms & 0x7FF;

                if (loop & 0x400) {
                    loop ^= 0x7FF;
                }

                angle_offset = (loop << 4) - 0x2000;

                frame_select = ms & (1 << 8);
            }
                    break;

            case 8:
            case 9: // 16-20kmh
                angle_offset = ms << 5;
                frame_select = ms & (1 << 9);
                break;

            default: // >20kmh
                angle_offset = ms << 6;
                frame_select = ms & (1 << 8);
                break;
        }

        frame = frame_select ? frame1 : frame2;
        frame->update(frame_count, ~rotation_rate);
    }

    inline void render(uint16_t zero_angle) {
        frame->render(zero_angle + angle_offset);
    }

    virtual ~Hamster() {
        delete frame1;
        delete frame2;
    }
};