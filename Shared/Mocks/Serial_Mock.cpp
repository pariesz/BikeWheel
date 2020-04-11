#include "Serial_Mock.h"
#include <iostream>
#include <iomanip>

using namespace std;

void Print::print(const char val[]) {
    cout << val;
}
void Print::print(char val) {
    cout << val;
}
void Print::print(unsigned char val, int format) {
    cout << val;
}
void Print::print(int val, int format) {
    cout << val;
}
void Print::print(unsigned int val, int format) {
    cout << val;
}
void Print::print(long val, int format) {
    cout << val;
}
void Print::print(unsigned long val, int format) {
    cout << val;
}
void Print::print(double val, int precision) {
    cout << setprecision(precision) << val;
}
void Print::println(const char val[]) {
    cout << val << endl;
}
void Print::println(char val) {
    cout << val << endl;
}
void Print::println(unsigned char val, int format) {
    cout << val << endl;
}
void Print::println(int val, int format) {
    cout << val << endl;
}
void Print::println(unsigned int val, int format) {
    cout << val << endl;
}
void Print::println(long val, int format) {
    cout << val << endl;
}
void Print::println(unsigned long val, int format) {
    cout << val << endl;
}
void Print::println(double val, int precision) {
    cout << setprecision(precision) << val << endl;
}
void Print::println(void) {
    cout << endl;
}

Print Serial;
