#pragma once
#include "../Program.h"
#include "../Logging.h"
#include "Programs.h"
#include "Transition.h"

class TimerProgram : public Program {

private:
    enum class TransitionState { Complete, Out, In };
    TransitionState transitionState = TransitionState::Complete;
    uint16_t frame = 0;
    uint16_t delayFrames;
    bool moving;
    uint8_t program;
    Program* programPtr;

public:
    TimerProgram(bool moving)
        : moving(moving)
        , program((moving ? random(2, PROGRAM_MOVING_COUNT) : random(2, PROGRAM_STATIONARY_COUNT)) - 1) {
        transitionIn();
        configure();
    }

    void configure() override {
        programPtr->configure();
        EEPROM.get(EEPROM_TIMER_FRAMES, delayFrames);
        log_val("TimerProgram delayFrames", delayFrames);
    }

    void update(int32_t rotation_rate) override {
        switch (transitionState) {
            case TransitionState::Complete:
                if (++frame > delayFrames) {
                    log_ln("TimerProgram Out");

                    if (moving) {
                        if (++program >= PROGRAM_MOVING_COUNT) {
                            program = 2;
                        }
                    }
                    else {
                        if (++program >= PROGRAM_STATIONARY_COUNT) {
                            program = 2;
                        }
                    }

                    programPtr = new Transition(programPtr, false);
                    transitionState = TransitionState::Out;
                    frame = 0;
                }
                break;

            case TransitionState::Out: {
                Transition* transitionOut = (Transition*)programPtr;
                if (transitionOut->finished()) {
                    transitionIn();
                    delete transitionOut->get_program();
                    delete transitionOut;
                }
                break;
            }

            case TransitionState::In: {
                Transition* transitionIn = (Transition*)programPtr;
                if (transitionIn->finished()) {
                    log_ln("TimerProgram Complete");
                    programPtr = transitionIn->get_program();
                    transitionState = TransitionState::Complete;
                    delete transitionIn;
                }
                break;
            }
        }

        programPtr->update(rotation_rate);
    }

    void transitionIn() {
        if (Programs::use_in_transition(program, moving)) {
            programPtr = new Transition(Programs::get_program(program, moving), true);
            transitionState = TransitionState::In;
            log_ln("TimerProgram In");
        }
        else {
            programPtr = Programs::get_program(program, moving);
            transitionState = TransitionState::Complete;
            log_ln("TimerProgram Complete");
        }
    }

    void render(uint16_t zero_angle) override {
        programPtr->render(zero_angle);
    }

    ~TimerProgram() {
        switch (transitionState) {
            case TransitionState::Out:
            case TransitionState::In:
                delete ((Transition*)programPtr)->get_program();
            default:
                break;
        }

        delete programPtr;
    }
};