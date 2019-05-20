#pragma once
#ifdef SIMULATION
#include "Arduino_Mock.h"
#else
#include <avr/pgmspace.h>
#endif

#include "../Image.h"

namespace HamsterRoll1Data {
	const uint16_t arcs[] PROGMEM {
		  0x0000, 0xE331, 0xF4C8
		, 0x0002, 0x02E8, 0xDCF9, 0xFAE2
		, 0x0002, 0x0738, 0xDA79, 0xFA12
		, 0x0002, 0x0730, 0xD869, 0xE468, 0xED69, 0xFBCA
		, 0x0004, 0x011A, 0x01AC, 0x0358, 0xD6A1, 0xE408, 0xED89, 0xF9DB, 0xFD34
		, 0x0003, 0x0318, 0xD529, 0xE5A8, 0xEB59, 0xF94B
		, 0x0003, 0x02E0, 0xD08A, 0xD369, 0xF853
		, 0x0003, 0x015A, 0x01C8, 0xCDB2, 0xD239, 0xF6F3, 0xF9AA, 0xFF1B
		, 0x0002, 0x00D8, 0xCBC2, 0xD149, 0xF563, 0xF858, 0xFEBA
		, 0x0000, 0xCB32, 0xD331, 0xF39B, 0xF798
		, 0x0000, 0xCB6A, 0xD5B1, 0xF123, 0xF804, 0xFB08
		, 0x0000, 0xCC02, 0xD789, 0xEBC3, 0xF922, 0xFA38
		, 0x0000, 0xCB3A, 0xD789, 0xEA6B, 0xF6BA, 0xF7C0
		, 0x0000, 0xCAC2, 0xD5E9, 0xE953, 0xF3D2, 0xF4D0, 0xF722, 0xFA10
		, 0x0000, 0xCB4A, 0xD411, 0xE8CB, 0xF280, 0xF692, 0xFAF8
		, 0x0000, 0xD1D1, 0xE853, 0xF0B2, 0xFA48
		, 0x0000, 0x0252, 0x04A4, 0x04EA, 0x0534, 0x06F2, 0x1110, 0x115A, 0x11A0, 0xD249, 0xE76B, 0xEFCA, 0xF9E8
		, 0x0004, 0x0163, 0x0732, 0x1630, 0xD281, 0xE5A3, 0xEF12, 0xF190, 0xF4E2, 0xF910, 0xFC1A, 0xFDC4
		, 0x0003, 0x07FC, 0x08CA, 0x17F8, 0xD2F9, 0xE44B, 0xEEF0, 0xF37A, 0xF844, 0xFB33
		, 0x0003, 0x098C, 0x0A92, 0x0B58, 0x152A, 0x1778, 0xD399, 0xE31B, 0xEEB2, 0xEF78, 0xF10A, 0xF148, 0xF18A, 0xF6F4, 0xF7BB
		, 0x0001, 0x04FB, 0x0B28, 0xD441, 0xE22B, 0xF2D4, 0xF58B, 0xFD01
		, 0x0001, 0x0583, 0x0B40, 0xD511, 0xE18B, 0xE971, 0xF123, 0xFA01
		, 0x0001, 0x060B, 0x0AF2, 0x0C18, 0xD611, 0xE103, 0xE801, 0xF27B, 0xF901
		, 0x0001, 0x06C3, 0x0ACA, 0x0D48, 0xD701, 0xE20C, 0xE2F3, 0xE56C, 0xE5AB, 0xE5E4, 0xE689, 0xF2B3, 0xF891
		, 0x0001, 0x076B, 0x0A72, 0x0DF0, 0xD7E1, 0xF20B, 0xF821
		, 0x0001, 0x0843, 0x09FA, 0x0E68, 0xD8B9, 0xF0B3, 0xF7E9
		, 0x0001, 0x0940, 0x0B52, 0x0ED0, 0xD981, 0xEEEB, 0xF791
		, 0x0001, 0x07F8, 0x0BFA, 0x0EF8, 0xDA69, 0xED33, 0xF731
		, 0x0001, 0x06A0, 0x0CAA, 0x0F30, 0xDB89, 0xE8CB, 0xE9F4, 0xEA2B, 0xF6D1
		, 0x0001, 0x0548, 0x0CB2, 0x0F58, 0xDC89, 0xE87B, 0xF5C1
		, 0x0001, 0x0408, 0x0C5A, 0x0F48, 0xDD81, 0xE8C3, 0xF401
		, 0x0001, 0x02B0, 0x0C12, 0x0E98, 0xDE99, 0xE9A4, 0xEA8B, 0xF219
		, 0x0001, 0x0160, 0xDFD9, 0xEB9B, 0xF029
		, 0x0000, 0xE1B1, 0xFF78
		, 0x0000, 0xE3F9, 0xFD20
		, 0x0000, 0xE6C9, 0xFB68
	}; // 512 bytes

	const uint16_t row_ends[] PROGMEM {		
		0x0002, 0x0006, 0x000A, 0x0010, 0x0019, 0x001F, 0x0024, 0x002C, 
		0x0033, 0x0038, 0x003E, 0x0044, 0x004A, 0x0052, 0x0059, 0x005E, 
		0x006B, 0x0077, 0x0081, 0x0090, 0x0098, 0x00A0, 0x00A9, 0x00B6, 
		0x00BD, 0x00C4, 0x00CB, 0x00D2, 0x00DB, 0x00E2, 0x00E9, 0x00F1, 
		0x00F6, 0x00F9, 0x00FC, 0x00FF
	}; // 72 bytes

	const uint32_t colors[] PROGMEM {		
		0x00000000, 0x00FFCC00, 0x00FF5555, 0x00FFFFFF, 0xCCCCCCCC
	}; // 20 bytes
}

class HamsterRoll1 : public Image {
protected:
	inline uint16_t get_arc(uint16_t i) override {
		return pgm_read_word(&HamsterRoll1Data::arcs[i]);
	}

	inline uint16_t get_row_end(uint8_t row_index) override {
		return pgm_read_word(&HamsterRoll1Data::row_ends[row_index]);
	}

protected:
	const uint16_t angle_mask = 0xFFF8;
	const uint16_t color_mask = 0x0007;

	inline uint16_t get_angle(uint16_t arc) override {
		return arc & angle_mask;
	}

	inline uint32_t get_color(uint16_t arc) override {
		return pgm_read_dword(&(HamsterRoll1Data::colors[arc & color_mask]));
	}

public:
    HamsterRoll1() {
        Image::Initialise();
    }
};