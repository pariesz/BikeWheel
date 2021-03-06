#pragma once
#include "../Image.h"

namespace HamsterRun1Data {
	const uint16_t arcs[] PROGMEM {
		  0x0000
		, 0x0000
		, 0x0000
		, 0x0000
		, 0x0000, 0x78B9, 0x8F10
		, 0x0000, 0x7189, 0x9630
		, 0x0000, 0x6DC9, 0x8994, 0x8BFB, 0x8DE4, 0x8F51, 0x9C48
		, 0x0000, 0x6BD1, 0x8703, 0x9171, 0xA560
		, 0x0000, 0x6A89, 0x8693, 0x9131, 0xAE10
		, 0x0000, 0x6931, 0x86CB, 0x9261, 0xB398
		, 0x0000, 0x6861, 0x867B, 0x9491, 0xB738, 0xBAAA, 0xBC90, 0xBD52, 0xC120
		, 0x0000, 0x67A1, 0x8653, 0x96E9, 0xB822, 0xC1E0
		, 0x0000, 0x66C9, 0x85FB, 0x97D1, 0xB75A, 0xC1A0
		, 0x0000, 0x6631, 0x856B, 0x97D1, 0xB70A, 0xC090
		, 0x0000, 0x65A1, 0x8553, 0x9464, 0x9551, 0xB6E2, 0xC230
		, 0x0000, 0x6551, 0x851B, 0x91A9, 0xB72A, 0xC288
		, 0x0000, 0x64F1, 0x84C3, 0x9131, 0x9FF3, 0xA4E1, 0xBA4A, 0xBBB9, 0xBEA2, 0xC218
		, 0x0000, 0x6461, 0x8493, 0x9109, 0x9F33, 0xA6F1, 0xBED2, 0xC150
		, 0x0000, 0x6429, 0x8463, 0x90E9, 0x9F0B, 0xA859, 0xBEBA, 0xC050
		, 0x0000, 0x6421, 0x8463, 0x90C1, 0x9F3B, 0xA989, 0xBF38
		, 0x0000, 0x63E9, 0x84BB, 0x9121, 0x9FD3, 0xAA81, 0xBE60
		, 0x0000, 0x6431, 0x84CB, 0x91B9, 0xA0D3, 0xABA1, 0xBE88
		, 0x0000, 0x64D9, 0x700C, 0x70BB, 0x77B9, 0x844B, 0x9331, 0xA1E3, 0xAD14, 0xAD4B, 0xAD89, 0xBE88
		, 0x0000, 0x68B4, 0x695B, 0x7924, 0x79C9, 0x83F3, 0x9584, 0x9629, 0xA1E3, 0xAFD9, 0xBEB0
		, 0x0000, 0x6872, 0x69FB, 0x7B69, 0x822B, 0x892C, 0x90CB, 0x9444, 0x95CA, 0x9604, 0x963A, 0x9754, 0x978A, 0x97C4, 0x98A1, 0x98DC, 0x9949, 0xA15B, 0xB111, 0xB8E8, 0xB991, 0xBEC8
		, 0x0000, 0x6802, 0x6A5B, 0x726C, 0x73E2, 0x75CC, 0x76AB, 0x7894, 0x7BC3, 0x8474, 0x865A, 0x8810, 0x91D2, 0x9943, 0x9CDC, 0x9D4B, 0x9D84, 0x9F33, 0xB139, 0xB8A8, 0xBB39, 0xBE98
		, 0x0000, 0x6782, 0x6B33, 0x6EB4, 0x70FA, 0x7230, 0x76F4, 0x7792, 0x7CEB, 0x813C, 0x82AA, 0x83B0, 0x94CA, 0x99EC, 0x9A22, 0x9A54, 0x9E0B, 0x9E44, 0x9E73, 0xA404, 0xA433, 0xA46C, 0xA6E2, 0xAB34, 0xAC3B, 0xB129, 0xB8C8, 0xBB79, 0xBE58
		, 0x0000, 0x66BA, 0x6B80, 0x6BEA, 0x6DE8, 0x761A, 0x7D1C, 0x7F82, 0x8078, 0x957A, 0x9978, 0x9F7A, 0xA7A8, 0xAC42, 0xAD14, 0xADAB, 0xB141, 0xB970, 0xBAA1, 0xBDA0
		, 0x0000, 0x662A, 0x6A40, 0x752A, 0x7AA0, 0x95EA, 0x9970, 0xA042, 0xA648, 0xAE1C, 0xAEB3, 0xB1D1, 0xBCE8
		, 0x0000, 0x60E2, 0x6908, 0x743A, 0x7898, 0x95FA, 0x9968, 0xA15A, 0xA618, 0xAF9B, 0xB274, 0xB361, 0xBC48
		, 0x0000, 0x5FEA, 0x67D0, 0x73A2, 0x7750, 0x95C2, 0x9910, 0xA27A, 0xA6B8, 0xB083, 0xB228, 0xB3D4, 0xB491, 0xBBF0
		, 0x0000, 0x5FFA, 0x6560, 0x731A, 0x76B0, 0x958A, 0x98F8, 0xA3CA, 0xA960, 0xB12C, 0xB1E3, 0xB23C, 0xB26A, 0xB2C8, 0xB4C3, 0xB8EA, 0xBAE1, 0xBBA0
		, 0x0000, 0x60A2, 0x6150, 0x6182, 0x61B0, 0x7342, 0x76C0, 0x955A, 0x98A8, 0xA52A, 0xAD38, 0xB254, 0xB330, 0xB553, 0xB822, 0xBB48
		, 0x0000, 0x73EA, 0x77B0, 0x9552, 0x9860, 0xA74A, 0xAD18, 0xB454, 0xB68B, 0xB70C, 0xB73B, 0xB764, 0xB7EA, 0xBAF8
		, 0x0000, 0x74C2, 0x78C8, 0x954A, 0x9828, 0xB88A, 0xBA60
		, 0x0000, 0x75B2, 0x78F0, 0x9542, 0x97E0
	}; // 670 bytes

	const uint16_t row_ends[] PROGMEM {		
		0x0000, 0x0001, 0x0002, 0x0003, 0x0006, 0x0009, 0x0010, 0x0015, 
		0x001A, 0x001F, 0x0028, 0x002E, 0x0034, 0x003A, 0x0041, 0x0047, 
		0x0051, 0x0059, 0x0061, 0x0068, 0x006F, 0x0076, 0x0082, 0x008D, 
		0x00A3, 0x00B9, 0x00D6, 0x00EA, 0x00F7, 0x0104, 0x0112, 0x0124, 
		0x0134, 0x0142, 0x0149, 0x014E
	}; // 72 bytes

	const uint32_t colors[] PROGMEM {		
		0x00000000, 0x00FFCC00, 0x00FF5555, 0x00FFFFFF, 0xCCCCCCCC
	}; // 20 bytes
}

class HamsterRun1 : public Image {
protected:
	inline uint16_t get_arc(uint16_t i) override {
		return pgm_read_word(&HamsterRun1Data::arcs[i]);
	}

	inline uint16_t get_row_end(uint8_t row_index) override {
		return pgm_read_word(&HamsterRun1Data::row_ends[row_index]);
	}

protected:
	const uint16_t angle_mask = 0xFFF8;
	const uint16_t color_mask = 0x0007;

	inline uint16_t get_angle(uint16_t arc) override {
		return arc & angle_mask;
	}

	inline uint32_t get_color(uint16_t arc) override {
		return pgm_read_dword(&(HamsterRun1Data::colors[arc & color_mask]));
	}

public:
    HamsterRun1() {
        Image::Initialise();
    }
};
