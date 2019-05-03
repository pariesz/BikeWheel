#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <list>
#include "SensorData.h"
#include "Arduino_Mock.h"

using namespace std;
using namespace std::chrono;

void split_line(string& line, string delim, list<string>& values) {
    size_t pos = 0;

    while ((pos = line.find(delim)) != string::npos) {
        values.push_back(line.substr(0, pos));
        line = line.substr(pos + 1);
    }

    if (!line.empty()) {
        values.push_back(line);
    }
}

namespace SensorData {
    static list<DataLine>::const_iterator iter;
    static list<DataLine> lines;

    static time_point<steady_clock> start;

    static uint16_t angle = 0;
    static uint32_t gyro_y = 4000;


    void load_csv() {
        ifstream file("output.csv"); // declare file stream: http://www.cplusplus.com/reference/iostream/ifstream/

       // skip header
        string line;
        getline(file, line);

        while (file.good()) {
            getline(file, line); // read a string until next new line: http://www.cplusplus.com/reference/string/getline/

            // if (value.find('\n') != string::npos) {

            list<string> cols;
            split_line(line, ",", cols);

            if (cols.size() != 8) {
                break;
            }

            auto dl = new DataLine;

            dl->us = stoi(cols.front());  cols.pop_front();
            dl->hall = cols.front() != "0"; cols.pop_front();
            dl->acc_x = stoi(cols.front());  cols.pop_front();
            dl->acc_y = stoi(cols.front());  cols.pop_front();
            dl->acc_z = stoi(cols.front());  cols.pop_front();
            dl->gyro_x = stoi(cols.front());  cols.pop_front();
            dl->gyro_y = stoi(cols.front());  cols.pop_front();
            dl->gyro_z = stoi(cols.front());

            lines.push_back(*dl);
        }
    }

    void init() {
#ifdef SENSOR_DATA
        load_csv();
        start = high_resolution_clock::now();
        iter = lines.begin();
#endif
        update();
    }

    bool update() {
#ifdef SENSOR_DATA
        // .end() points one past the end of the sequence
        if (iter == lines.end()) {
            cout << "RESET" << endl;
            start = high_resolution_clock::now();
            iter = lines.begin();
            return false;
        }

        auto elapsed = high_resolution_clock::now() - start;
        auto ms = duration_cast<microseconds>(elapsed).count();

        if (ms > iter->us) {
            start = high_resolution_clock::now();
            iter = next(iter);
        }
#else
        angle += 100;
#endif
        return true;
    }

    DataLine get() {
#ifdef SENSOR_DATA
        if (iter == lines.end()) {
            return DataLine();
        }
        return *iter;
#else
        auto dl = new DataLine;

        float radians = (angle / (float)65535) * 2 * PI;

        dl->us     = 6000;
        dl->hall   = angle < 500 ? LOW : HIGH;
        dl->acc_x  = cos(radians) * ((1 << 15) - 1);
        dl->acc_y  = 0;
        dl->acc_z  = sin(radians) * ((1 << 15) - 1);
        dl->gyro_x = 0;
        dl->gyro_y = gyro_y;
        dl->gyro_z = 0;

        return *dl;
#endif
    }
}
