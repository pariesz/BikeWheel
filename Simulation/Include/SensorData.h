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

class SensorData {
    virtual bool try_get_next(DataLine &dl) = 0;
};