#pragma once

class DataLine {
public:
    unsigned short us;
    bool hall;
    short acc_x;
    short acc_y;
    short acc_z;
    short gyro_x;
    short gyro_y;
    short gyro_z;
};

namespace SensorData {
    void init();
    bool update();
    DataLine get();
};