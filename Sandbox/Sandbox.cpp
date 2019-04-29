
#include <iostream>

using namespace std;

void print_result(uint32_t time, int16_t gyro) {
    //int16_t result = ((gyro * 32767 / 2000) * ((float)time / 1000000));
    //int16_t result = ((gyro << 4) * ((float)time / 1000000));
    cout << ((int32_t)gyro << 5) << endl;

    int32_t result = (int32_t)(((int32_t)gyro << 4) * time) >> 20;
    //cout << result << endl;
}

void Bitwise_Round(uint32_t val, uint8_t push) {
    auto result = (val + (1 << push - 1)) >> push;
    cout << val << " = " << result << endl;
}

int main()
{
    //print_result(60000, -1);
    //print_result(60000,  0);
    //print_result(60000, 32767);
    //print_result(6000, 4000);
    //print_result(6000, -4000);

    //Bitwise_Round(62, 2);
    //Bitwise_Round(63, 2);
    //Bitwise_Round(64, 2);
    //Bitwise_Round(65, 2);
    //Bitwise_Round(66, 2);
    //Bitwise_Round(67, 2);
    //Bitwise_Round(68, 2);

    uint8_t i = 0xFF;
    uint8_t ii[] = { i, i, 0, 0 };
    uint32_t int32 = *(uint32_t*)ii;

    cout << int32 << endl;

    return 1;
}