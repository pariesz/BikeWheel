#pragma once
#include <chrono>
#include <iostream>

namespace Timer {
    using namespace std::chrono;

    std::chrono::nanoseconds ns;

    uint32_t frame_start = millis();
    uint16_t frame_count = 0;
    float frame_time = 0;


    std::chrono::nanoseconds nanos() {
        auto now = high_resolution_clock::now();
        return now.time_since_epoch();
    }

    inline void start() {
        if (millis() - frame_start > 1000) {
            frame_count = 0;
            frame_start = millis();
            std::cout << (frame_time / 1000000) << " ms" << std::endl;
        }

        ns = nanos();
    }

    inline void end() {
        float cf = 1 / (float)++frame_count;
        frame_time = frame_time * (1 - cf) + ((nanos() - ns) * cf).count();
    }

}