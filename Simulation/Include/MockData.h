#pragma once
#include "Mocks/Arduino_Mock.h"
#include "SensorData.h"

class MockData : public SensorData {
public:
    static int16_t gyro_y;
private:
    uint16_t angle = 0;
public:
    bool try_get_next(DataLine &dl) override;
};