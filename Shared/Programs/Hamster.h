#pragma once
#include "../Images/HamsterRun1.h"
#include "../Images/HamsterRun2.h"
#include "../Images/HamsterRoll1.h"
#include "../Images/HamsterRoll2.h"
#include "../Program.h"

class Hamster : public Program {

private:
    Image* frame1 = new HamsterRun1;
    Image* frame2 = new HamsterRun2;
    uint8_t index = -1;

private:
    void update_index(uint16_t new_index) {
        index = (uint8_t)new_index;

        delete frame1;
        delete frame2;

        switch (index) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
                frame1 = new HamsterRun1;
                frame2 = new HamsterRun2;
                break;

            default:
                frame1 = new HamsterRoll1;
                frame2 = new HamsterRoll2;
                break;
        }
    }

public:
    void render(uint16_t zero_angle, int32_t rotation_rate) {
        // Images are in reverse.
        // hamster should be running against bike!
        rotation_rate = -rotation_rate;

        uint32_t ms = millis();

        uint32_t rate = abs(rotation_rate);

        //rate <<= 1; // DEBUGING
        
        if (rate >> 14 != index) {
            update_index(rate >> 14);
        }

        bool frame = 0;

        switch (index) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4: 
            case 5: // <12kmh
                frame = ms & (1 << 10);
                break;

            case 6: { // 12-14kmh
                    uint16_t loop = ms & 0x7FF;

                    if (loop & 0x400) {
                        loop ^= 0x7FF;
                    }

                    zero_angle += (loop << 3) - 0x1000;
                    frame = ms & (1 << 9);
                }
                break;

            case 7: { // 14-16kmh
                    uint16_t loop = ms & 0x7FF;

                    if (loop & 0x400) {
                        loop ^= 0x7FF;
                    }

                    zero_angle += (loop << 4) - 0x2000;

                    frame = ms & (1 << 8);
                }
                break;
            
            case 8:
            case 9: // 16-20kmh
                zero_angle += ms << 5;
                frame = ms & (1 << 9);
                break;
            
            default: // >20kmh
                zero_angle += ms << 6;
                frame = ms & (1 << 8);
                break;
        }

        if (frame) {
            frame1->render(zero_angle, rotation_rate);
        } else {
            frame2->render(zero_angle, rotation_rate);
        }
    }

    ~Hamster() {
        delete frame1;
        delete frame2;
    }
};