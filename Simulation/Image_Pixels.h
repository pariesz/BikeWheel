#pragma once

#include <vector>
#include "Pixels.h"
#include "Bmp.h"

using namespace std;

class Image_Pixels {
public:
    uint8_t min_radius;
    vector<vector<vector<int>*>*>* arcs = new vector<vector<vector<int>*>*>;

public:
    const int get_resolution(const int row) {
        // base the resolution of the arcs circumferance
        uint8_t pos = min_radius + (((float)row / PIXELS_PER_STRIP) * (255 - min_radius));
        return  pos * 2 * M_PI;
    }

    Image_Pixels(const Bmp &bmp, const uint8_t min_radius) : min_radius(min_radius) {
        int max_dist = min(bmp.width, bmp.height) >> 1;
        int min_dist = max_dist * (min_radius / 255.0f);
        int x_offset = (bmp.width >> 1) - max_dist;
        int y_offset = (bmp.height >> 1) - max_dist;
        int strip_lenth = max_dist - min_dist;

        // initialize vectors
        for (int i = 0; i < PIXELS_PER_STRIP; i++) {
            auto rowVec = new vector<vector<int>*>;
            arcs->push_back(rowVec);

            int res = get_resolution(i);
            for (int j = 0; j < res; j++) {
                rowVec->push_back(new vector<int>);
            }
        }

        // Read all the pixels into arcs
        for (int y = y_offset; y < (bmp.height - y_offset); y++) {
            for (int x = x_offset; x < (bmp.width - x_offset); x++) {

                // Pixels are read from top left corner, so move index to +-x,y space
                int cx = (x - max_dist) - x_offset;
                int cy = (max_dist - y) - y_offset;

                uint16_t dist = sqrtf(sq(cx) + sq(cy));

                if (dist > max_dist || dist < min_dist) {
                    continue;
                }

                unsigned int row = round(((float)(dist - min_dist) / strip_lenth) * (PIXELS_PER_STRIP - 1));

                float radians = atan2(cx, cy);
                float angle = (radians / M_PI) / 2;
                if (angle < 0) {
                    angle = 1 - abs(angle);
                }

                unsigned int resolution = get_resolution(row);
                unsigned int arc = angle * (resolution - 1);

                // BMP pixels are arranged left->right , bottom->top
                int i = 3 * ((((bmp.height - 1) - y) * bmp.width) + x);

                // windows stores the color values as (B, G, R) triples
                unsigned char r = bmp.data[i + 2];
                unsigned char g = bmp.data[i + 1];
                unsigned char b = bmp.data[i];

                unsigned int color = (r << 16) + (g << 8) + b;

                arcs->at(row)->at(arc)->push_back(color);
            }
        }
    }

    ~Image_Pixels() {
        for (int i = 0; i < PIXELS_PER_STRIP; i++) {
            int res = get_resolution(i);

            auto row = arcs->at(i);

            for (int j = 0; j < res; j++) {
                row->at(j)->clear();
            }
            row->clear();
        }

        arcs->clear();
    }
};