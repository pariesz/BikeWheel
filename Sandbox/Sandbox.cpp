
#include <iostream>

using namespace std;

void print_result(uint32_t time, int16_t gyro) {
    //int16_t result = ((gyro * 32767 / 2000) * ((float)time / 1000000));
    //int16_t result = ((gyro << 4) * ((float)time / 1000000));
    int32_t result = (int32_t)(((int32_t)gyro << 4) * time) >> 20;
    cout << result << endl;
}

int main()
{
    /*
    print_result(60000, -1);
    print_result(60000,  0);
    print_result(60000,  1);
    print_result(6000, 4000);
    print_result(6000, -4000);
    */
    cout << (1 << 10) << endl;
    return 1;
}