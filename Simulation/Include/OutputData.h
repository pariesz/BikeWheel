#pragma once
#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <list>
#include "SensorData.h"
#include "Logging.h"

class OutputData : public SensorData {
private:
    std::list<DataLine>::const_iterator iter;
    std::list<DataLine> lines;
    std::chrono::time_point<std::chrono::steady_clock> start;

    void split_line(std::string& line, std::string delim, std::list<std::string>& values) {
        size_t pos = 0;

        while ((pos = line.find(delim)) != std::string::npos) {
            values.push_back(line.substr(0, pos));
            line = line.substr(pos + 1);
        }

        if (!line.empty()) {
            values.push_back(line);
        }
    }

public:
    OutputData(const std::string &filename) {
        std::ifstream file(filename); // declare file stream: http://www.cplusplus.com/reference/iostream/ifstream/

        // skip header
        std::string line;
        getline(file, line);

        while (file.good()) {
            getline(file, line); // read a string until next new line: http://www.cplusplus.com/reference/string/getline/

            // if (value.find('\n') != string::npos) {

            std::list<std::string> cols;
            split_line(line, ",", cols);

            if (cols.size() != 8) {
                break;
            }

            auto dl = new DataLine;

            dl->us = stoi(cols.front());  cols.pop_front();
            dl->hall = cols.front() != "0"; cols.pop_front();
            dl->acc_x = stoi(cols.front());  cols.pop_front();
            dl->acc_y = stoi(cols.front());  cols.pop_front();
            dl->acc_z = stoi(cols.front()) - 8000;  cols.pop_front();
            dl->gyro_x = stoi(cols.front());  cols.pop_front();
            dl->gyro_y = stoi(cols.front()); cols.pop_front();
            dl->gyro_z = stoi(cols.front());

            lines.push_back(*dl);
        }

        start = std::chrono::high_resolution_clock::now();
        iter = lines.begin();
    }

    bool try_get_next(DataLine &dl) override {
        auto elapsed = std::chrono::high_resolution_clock::now() - start;

        auto ms = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

        if (ms > iter->us) {
            start = std::chrono::high_resolution_clock::now();
            iter = next(iter);
        }

        // .end() points one past the end of the sequence
        if (iter == lines.end()) {
            log("RESET");
            iter = lines.begin();
            dl = *iter;
            return false;
        }

        dl = *iter;
        return true;
    }
};