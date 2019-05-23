#include "Logging.h"

#if LOGGING == 1
void log_fps() {
    static unsigned int fps = 0;
    static unsigned long fps_millis = millis();

    if (millis() - fps_millis > 1000) {
        log_val("fps", fps);
        fps_millis = millis();
        fps = 0;
    }

    fps++;
}
#endif