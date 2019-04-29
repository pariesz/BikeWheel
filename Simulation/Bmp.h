#pragma once
#include <fstream>


// can only read bitmaps for the following format:
// - 24 colors with pixels
// - 'Bottom - Top' (default) row direction
// - 200px minimum on the smallest dimension
// conversion tool: https://online-converting.com/image/convert2bmp/ 
class Bmp {

public:
    int width, height;
    
    unsigned char* data = nullptr;

    Bmp(const std::string filename) {
        FILE *fp;
        errno_t err;
        if ((err = fopen_s(&fp, filename.c_str(), "rb")) != 0) {
            throw std::exception("File opening failed: " + err);
        }

        unsigned char info[54];
        fread(info, sizeof(unsigned char), 54, fp); // read the 54-byte header

        // extract image height and width from header
        width = *(int*)&info[18];
        height = *(int*)&info[22];

        int size = 3 * width * height;
        
        data = new unsigned char[size]; // allocate 3 bytes per pixel
        
        fread(data, sizeof(unsigned char), size, fp); // read the rest of the data at once
        
        fclose(fp);
    }

    ~Bmp() {
        delete [] data;
    }
};

