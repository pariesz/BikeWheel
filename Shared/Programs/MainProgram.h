#pragma once

#include "../Program.h"
#include "../Logging.h"
#include "../Programs.h"
#include "../Shared.h"

#include "Transition.h"


class MainProgram : public Program {

private:
    enum class TransitionState { Complete, Out, In };

    bool moving = false;

    TransitionState transitionState = TransitionState::Complete;

    uint32_t movingRotationRate;
    uint8_t movingProgram = PROGRAM_TIMER;

    uint32_t stationaryRotationRate;
    uint8_t stationaryProgram = PROGRAM_OFF;

    Program* programPtr;

    inline Program* createProgram() {
        return Programs::get_program(moving ? movingProgram : stationaryProgram, moving);
    }

public:
    MainProgram() {
        programPtr = createProgram();
        configure();
    }

    inline void setMovingProgram(uint8_t index) {
        movingProgram = index;
        if (moving) transitionState = TransitionState::Out;
    }

    inline void setStationaryProgram(uint8_t index) {
        stationaryProgram = index;
        if (!moving) transitionState = TransitionState::Out;
    }

    inline uint8_t getMovingProgram() {
        return movingProgram;
    }

    inline uint8_t getStationaryProgram() {
        return stationaryProgram;
    }

    void configure() override {
        programPtr->configure();
        EEPROM.get(EEPROM_STATIONARY_RATE, stationaryRotationRate);
        EEPROM.get(EEPROM_MOVING_RATE, movingRotationRate);
        Leds::set_brightness(EEPROM.read(EEPROM_BRIGHTNESS));
    }

    void update(uint16_t frame_count, int32_t rotation_rate) override {
        switch (transitionState) {
            case TransitionState::Complete:
                if ((moving && abs(rotation_rate) < stationaryRotationRate) || (!moving && abs(rotation_rate) > movingRotationRate)) {
                    programPtr = new Transition(programPtr, false);
                    transitionState = TransitionState::Out;
                    log_ln("MainProgram Out");
                    moving = !moving;
                }
                break;

            case TransitionState::Out: {
                Transition* transitionOut = (Transition*)programPtr;
                if (transitionOut->finished()) {
                    if (Programs::use_in_transition(moving ? movingProgram : stationaryProgram, moving)) {
                        programPtr = new Transition(createProgram(), true);
                        transitionState = TransitionState::In;
                        log_ln("MainProgram In");
                    }
                    else {
                        programPtr = createProgram();
                        transitionState = TransitionState::Complete;
                        log_ln("MainProgram Complete");
                    }
                    delete transitionOut->get_program();
                    delete transitionOut;
                }
                break;
            }

            case TransitionState::In: {
                Transition* transitionIn = (Transition*)programPtr;
                if (transitionIn->finished()) {
                    programPtr = transitionIn->get_program();
                    transitionState = TransitionState::Complete;
                    log_ln("MainProgram Complete");
                    delete transitionIn;
                }
                break;
            }
        }

        programPtr->update(frame_count, rotation_rate);
    };

    inline void render(uint16_t zero_angle) {
        programPtr->render(zero_angle);
    }
};