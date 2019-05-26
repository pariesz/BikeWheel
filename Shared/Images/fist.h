#pragma once
#include "../Image.h"

namespace FistData {
	const uint16_t arcs[] PROGMEM {
		  0x0000, 0x1F31, 0x28CC, 0x3665, 0x8E64, 0x9C01, 0xBB30, 0xC999, 0xF264
		, 0x0000, 0x25ED, 0x2990, 0x35F9, 0x8EF0, 0x9C15, 0xB9F8, 0xCAC1, 0xF224
		, 0x0000, 0x0349, 0x1A50, 0x354D, 0x901C, 0x9B4D, 0xB844, 0xCD51, 0xF184
		, 0x0000, 0x0099, 0x205C, 0x34C1, 0x907C, 0x9AAD, 0xB6D8, 0xBE0D, 0xC5D8, 0xCF71, 0xF068
		, 0x0001, 0x2334, 0x3519, 0x9034, 0x9A45, 0xB5A8, 0xBCED, 0xC938, 0xD10D, 0xF058
		, 0x0001, 0x2420, 0x3529, 0x9084, 0x99CD, 0xB4A4, 0xBA51, 0xCB58, 0xD295, 0xEF78, 0xFEF5
		, 0x0001, 0x24E8, 0x3535, 0x904C, 0x9969, 0xB3C4, 0xB985, 0xCDA8, 0xD3E5, 0xEF38, 0xF5ED, 0xF7D8, 0xFE8D
		, 0x0001, 0x24B0, 0x2B7D, 0x3004, 0x3575, 0x9014, 0x983D, 0xB2F8, 0xB951, 0xCF10, 0xD4F5, 0xEEC8, 0xF521, 0xF84C, 0xFEA5
		, 0x0000, 0x0519, 0x2480, 0x2999, 0x3284, 0x35E9, 0x810C, 0x8AD1, 0x8F10, 0x978D, 0xB328, 0xBC11, 0xD0E0, 0xD5F9, 0xEE94, 0xF41D, 0xF8C8
		, 0x0000, 0x0A01, 0x2464, 0x2799, 0x3398, 0x3601, 0x8064, 0x9665, 0xB600, 0xBD31, 0xBD98, 0xBE01, 0xD200, 0xD6CD, 0xEE64, 0xF399, 0xFC00
		, 0x0001, 0x030C, 0x0D55, 0x2490, 0x2679, 0x34F0, 0x35B5, 0x8124, 0x95B5, 0xB8C0, 0xC001, 0xD30C, 0xD79D, 0xEE18, 0xF30D
		, 0x0001, 0x0794, 0x103D, 0x819C, 0x94C1, 0xBAAC, 0xC189, 0xD3F0, 0xD849, 0xEDF0, 0xF245
		, 0x0001, 0x0838, 0x1281, 0x5CDC, 0x5D8D, 0x5E3C, 0x60FD, 0x6150, 0x6259, 0x62B0, 0x6309, 0x8238, 0x8865, 0x8F40, 0x9305, 0xBD80, 0xC355, 0xD4D0, 0xD8ED, 0xED7C, 0xF1F1
		, 0x0001, 0x06E4, 0x0D79, 0x0DCC, 0x14B5, 0x5324, 0x682D, 0x82C8, 0x8861, 0xBF40, 0xC485, 0xD598, 0xD9E1, 0xED44, 0xF189
		, 0x0001, 0x05A4, 0x0B49, 0x10A0, 0x1645, 0x4E6C, 0x6919, 0x8370, 0x8879, 0xC0A0, 0xC5A5, 0xD694, 0xDAA9, 0xED2C, 0xF141
		, 0x0001, 0x047C, 0x09E5, 0x1294, 0x17AD, 0x4AF0, 0x6A1D, 0x83E4, 0x8865, 0xC1A4, 0xC6BD, 0xD6EC, 0xDB6D, 0xECD0, 0xF0B5
		, 0x0001, 0x03C0, 0x08AD, 0x143C, 0x1929, 0x4850, 0x6ABD, 0x8478, 0x8889, 0xC2AC, 0xC7E1, 0xD780, 0xDC21, 0xEC54, 0xF0A9
		, 0x0001, 0x02C4, 0x0735, 0x15E8, 0x1A59, 0x4628, 0x6B9D, 0x84D8, 0x8875, 0x99A4, 0xC8CD, 0xD780, 0xDD55, 0xE5EC, 0xF269
		, 0x0001, 0x01DC, 0x0621, 0x1770, 0x1B71, 0x43EC, 0x6C25, 0x8530, 0x8865, 0x985C, 0xC9A9, 0xD560, 0xF7BD
		, 0x0001, 0x0148, 0x0529, 0x18C4, 0x1CA5, 0x2CA4, 0x36F5, 0x3778, 0x398D, 0x4210, 0x6CE5, 0x8568, 0x8885, 0x97BC, 0xCA95, 0xD1CC, 0xFDED
		, 0x0000, 0x0439, 0x19D8, 0x1DD1, 0x2644, 0x3DA1, 0x405C, 0x6D59, 0x85F4, 0x8871, 0x96DC
		, 0x0000, 0x0545, 0x1834, 0x201D, 0x2244, 0x6DC9, 0x8638, 0x8861, 0x9648
		, 0x0000, 0x07AD, 0x1620, 0x6E2D, 0x8664, 0x8881, 0x9588
		, 0x0000, 0x0A21, 0x1440, 0x6EC5, 0x86A4, 0x8871, 0x950C
		, 0x0000, 0x0BFD, 0x1288, 0x6F35, 0x86F8, 0x8881, 0x9444
		, 0x0000, 0x0DCD, 0x1130, 0x6FA5, 0x8734, 0x887D, 0x93BC
		, 0x0000, 0x6FF1, 0x879C, 0x886D, 0x9358
		, 0x0000, 0x704D, 0x92E0
		, 0x0000, 0x70B1, 0x926C
		, 0x0000, 0x7105, 0x9200
		, 0x0000, 0x713D, 0x9184
		, 0x0000, 0x7179, 0x9138
		, 0x0000, 0x71D9, 0x90C4
		, 0x0000, 0x7209, 0x9084
		, 0x0000, 0x723D, 0x9018
		, 0x0000, 0x7269, 0x8FE0
	}; // 706 bytes

	const uint16_t row_ends[] PROGMEM {		
		0x0008, 0x0011, 0x001A, 0x0025, 0x002F, 0x003A, 0x0047, 0x0056, 
		0x0067, 0x0078, 0x0087, 0x0092, 0x00A7, 0x00B6, 0x00C5, 0x00D4, 
		0x00E3, 0x00F2, 0x00FF, 0x0110, 0x011B, 0x0124, 0x012B, 0x0132, 
		0x0139, 0x0140, 0x0145, 0x0148, 0x014B, 0x014E, 0x0151, 0x0154, 
		0x0157, 0x015A, 0x015D, 0x0160
	}; // 72 bytes
}

class Fist : public Image {

private:
    uint8_t hue;
    uint32_t color;
    uint32_t ms_prev = millis();

public:
	Fist()
        : hue(random(0, 0xFF))
        , color(Colors::HslToRgb(hue, 0xFF, 0xFF)) {
        Image::Initialise();
	}

    void render(uint16_t zero_angle, int32_t rotation_rate) override {
        if (millis() - ms_prev > 200) {
            ms_prev = millis();
            color = Colors::HslToRgb(++hue, 0xFF, 0xFF);
        }

        Image::render(zero_angle, rotation_rate);
    };
protected:
	inline uint16_t get_arc(uint16_t i) override {
		return pgm_read_word(&FistData::arcs[i]);
	}

	inline uint16_t get_row_end(uint8_t row_index) override {
		return pgm_read_word(&FistData::row_ends[row_index]);
	}

protected:
	const uint16_t angle_mask = 0xFFFC;
	const uint16_t color_mask = 0x0003;

	inline uint16_t get_angle(uint16_t arc) override {
		return arc & angle_mask;
	}

    inline uint32_t get_color(uint16_t arc) override {
        switch (arc & color_mask) {
            case 0: return 0;
            default: return color;
        }
    }
};
