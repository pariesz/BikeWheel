#pragma once

class DataLine {
public:
    unsigned short ms;
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
    void update();
    DataLine get();
};

