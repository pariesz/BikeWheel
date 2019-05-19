#pragma once
#ifdef SIMULATION
#include "Arduino_Mock.h"
#else
#include <avr/pgmspace.h>
#endif

#include "../Image.h"

namespace Poo_data {
	const uint16_t arcs[] PROGMEM {
		  0x0004, 0x3260, 0x3F34, 0xA0C5, 0xA730, 0xB264
		, 0x0004, 0x2181, 0x30D4, 0x3191, 0x3250, 0x3D44, 0xA2A5, 0xA930, 0xB2B4, 0xCC31, 0xD152, 0xDAC1, 0xDFE4, 0xEE75, 0xFA24
		, 0x0005, 0x0544, 0x1CF1, 0x1EE2, 0x35F0, 0x3B34, 0x71D1, 0x8D74, 0xA485, 0xAA70, 0xB3A4, 0xC8B1, 0xCAB2, 0xE1B1, 0xE3B5, 0xEF84, 0xF035, 0xF0D4, 0xF965, 0xFA14, 0xFAB5
		, 0x0003, 0x01C4, 0x0695, 0x0994, 0x1B92, 0x2651, 0x2BC2, 0x3A24, 0x68E1, 0x6E52, 0x8FE1, 0x9072, 0x9111, 0x95E4, 0xA6A5, 0xAC10, 0xB474, 0xC7A2, 0xD131, 0xD604, 0xD901, 0xDC02, 0xE634, 0xE933, 0xECD0, 0xFD03
		, 0x0000, 0x0743, 0x0984, 0x0BB5, 0x0CD4, 0x19B2, 0x23C3, 0x2570, 0x2DD3, 0x2F81, 0x31B2, 0x3994, 0x62E1, 0x6642, 0x9801, 0x9B64, 0xA7A5, 0xAD40, 0xB514, 0xC5D2, 0xD070, 0xDDE1, 0xDF92, 0xE6D0
		, 0x0000, 0x0BD3, 0x0D64, 0x1942, 0x2180, 0x3312, 0x3A54, 0x5F71, 0x6182, 0x7B51, 0x84A2, 0x9CE1, 0x9F74, 0xA945, 0xAE70, 0xB5A4, 0xC5A2, 0xCDE0, 0xE102, 0xE733, 0xED64, 0xF843, 0xFE70
		, 0x0004, 0x0077, 0x00F3, 0x0450, 0x0ED3, 0x10C4, 0x18E2, 0x2010, 0x33C2, 0x3A74, 0x5D01, 0x5E72, 0x6FB1, 0x77D0, 0x7E13, 0x80F7, 0x8453, 0x84C7, 0x8543, 0x8730, 0x88A3, 0x8A11, 0x9042, 0xA091, 0xA284, 0xAA25, 0xAF70, 0xB624, 0xC582, 0xCD20, 0xE152, 0xE784
		, 0x0004, 0x0563, 0x07B0, 0x1133, 0x1294, 0x18E2, 0x1FB0, 0x21F1, 0x23C0, 0x33A2, 0x39F4, 0x5CE2, 0x6991, 0x6E10, 0x78F7, 0x7BB6, 0x88D7, 0x8C70, 0x92C1, 0x9662, 0xA311, 0xA474, 0xAAD5, 0xB040, 0xB694, 0xC602, 0xCD40, 0xDBC1, 0xE040, 0xE0B1, 0xE132, 0xE714
		, 0x0004, 0x0873, 0x0A90, 0x12A3, 0x13F4, 0x19E2, 0x1FD1, 0x2042, 0x2551, 0x2700, 0x3352, 0x3954, 0x5DD1, 0x6870, 0x7607, 0x7746, 0x8D57, 0x8F10, 0x97F1, 0x9AF2, 0xA4B4, 0xABF5, 0xB100, 0xB764, 0xC712, 0xCE50, 0xD951, 0xDAA2, 0xE684
		, 0x0004, 0x0B33, 0x0C60, 0x1534, 0x1A01, 0x1B32, 0x2790, 0x3262, 0x3864, 0x6A03, 0x7390, 0x74C7, 0x7536, 0x9060, 0x94C3, 0x9530, 0x9593, 0x9C01, 0xA264, 0xAC65, 0xB190, 0xB794, 0xC862, 0xCE61, 0xD000, 0xD992, 0xE594
		, 0x0004, 0x0D53, 0x0E70, 0x1614, 0x1B61, 0x1C92, 0x2730, 0x2E71, 0x30C2, 0x36D4, 0x63C7, 0x64F3, 0x79E4, 0x8006, 0x8304, 0x83C6, 0x8864, 0x88C6, 0x8924, 0xAD55, 0xB240, 0xB804, 0xC9E2, 0xD0C1, 0xD360, 0xDAA2, 0xE301, 0xE494
		, 0x0004, 0x0EC3, 0x0FE0, 0x1714, 0x1CE1, 0x1E52, 0x25E1, 0x2D22, 0x33F1, 0x3514, 0x5D23, 0x6170, 0x7C93, 0x80E4, 0xADA5, 0xB2B0, 0xB884, 0xC975, 0xCC52, 0xD501, 0xD902, 0xE141, 0xE2C4
		, 0x0004, 0x10C0, 0x17A4, 0x1F21, 0x2132, 0x3151, 0x3263, 0x3364, 0x5813, 0x5B20, 0x8233, 0x85F4, 0xAE15, 0xB330, 0xB8B4, 0xC7C5, 0xCEA1, 0xCFA2, 0xDE61, 0xE074
		, 0x0004, 0x1113, 0x1210, 0x1854, 0x22D1, 0x2762, 0x27C1, 0x2812, 0x2A11, 0x2A62, 0x2B01, 0x2EA3, 0x3040, 0x3344, 0x53C3, 0x56C0, 0x6533, 0x6A24, 0x6A73, 0x6AC4, 0x6B23, 0x6B74, 0x6C13, 0x6C74, 0x70B3, 0x7104, 0x7203, 0x7740, 0x86B3, 0x89B4, 0xAE85, 0xB3C0, 0xB904, 0xC585, 0xCE04, 0xD003, 0xD2A1, 0xDC84
		, 0x0004, 0x1233, 0x1320, 0x1914, 0x2913, 0x2AF0, 0x3324, 0x5053, 0x52D0, 0x5D73, 0x5FA4, 0x63C5, 0x7914, 0x7D23, 0x7EB0, 0x8AA3, 0x8CD4, 0xAEB5, 0xB410, 0xB914, 0xC3C5, 0xCC34, 0xCD23, 0xCDC0, 0xD6E3, 0xD7D4, 0xF005, 0xFB94
		, 0x0004, 0x13C0, 0x19C3, 0x1C74, 0x2523, 0x2790, 0x3384, 0x4DA3, 0x4F70, 0x5903, 0x5C04, 0x5D85, 0x5DD4, 0x6E05, 0x7FB4, 0x82B3, 0x8430, 0x8D73, 0x8F44, 0xAF15, 0xB470, 0xB984, 0xC1A5, 0xCA04, 0xCBD0, 0xD8B5, 0xDB24, 0xEAB5, 0xF5C4, 0xF9B3, 0xFA44, 0xFA93, 0xFCB4, 0xFD93, 0xFF67
		, 0x0000, 0x0047, 0x0094, 0x13A0, 0x3453, 0x3534, 0x4B73, 0x4D30, 0x55E3, 0x5834, 0x7495, 0x7DD4, 0x84C0, 0x8FC3, 0x9184, 0xAF45, 0xB510, 0xB9F4, 0xBF75, 0xC794, 0xC990, 0xD984, 0xDAA5, 0xE074, 0xE4C5, 0xF0A4, 0xF2F3, 0xF4B0
		, 0x0004, 0x1360, 0x35C3, 0x3734, 0x49C3, 0x4AE0, 0x52A3, 0x54D4, 0x75E3, 0x77D4, 0x7A03, 0x7B20, 0x9223, 0x9384, 0xAF45, 0xB560, 0xBA64, 0xBC55, 0xC3D4, 0xC603, 0xC720, 0xDAD3, 0xDC34, 0xDDE5, 0xDE24, 0xDE75, 0xEC04, 0xEDF3, 0xEE34, 0xEE83, 0xEFE0, 0xFE53
		, 0x0004, 0x1260, 0x3833, 0x3984, 0x46D3, 0x48F0, 0x4FE3, 0x51C4, 0x7173, 0x7460, 0x93D3, 0x9574, 0xAF85, 0xB5A0, 0xBB44, 0xBC53, 0xBCD4, 0xC0D3, 0xC2B0, 0xDF33, 0xE2F4, 0xE483, 0xE4D4, 0xE663, 0xE6B4, 0xE6F3, 0xEA60, 0xF2F3, 0xF6F4
		, 0x0004, 0x1083, 0x1140, 0x3C23, 0x4560, 0x45A3, 0x45E0, 0x4D63, 0x4EF4, 0x6E33, 0x7080, 0x95E3, 0x96F4, 0xAF75, 0xB5A0, 0xF083, 0xF214
		, 0x0004, 0x0EA3, 0x0FE0, 0x4B43, 0x4CC4, 0x6B53, 0x6D50, 0x9753, 0x9894, 0xAF35, 0xB5E0, 0xF114
		, 0x0004, 0x0CB3, 0x0DE0, 0x4AC4, 0x6933, 0x6AE0, 0x98E3, 0x99E4, 0xAF35, 0xB5B0, 0xF194
		, 0x0004, 0x0AF3, 0x0C10, 0x4B04, 0x66F3, 0x6850, 0x9A33, 0x9AE4, 0xAF25, 0xB570, 0xF203, 0xF2B4
		, 0x0004, 0x0903, 0x0A50, 0x4B64, 0x64D3, 0x6630, 0x9B23, 0x9C04, 0xAEF5, 0xB530, 0xF2F3, 0xF394, 0xF445, 0xF4B4
		, 0x0004, 0x07A3, 0x0880, 0x4C14, 0x62F3, 0x6440, 0x9C53, 0x9D34, 0xAE75, 0xB480, 0xF433, 0xF4E4, 0xF585, 0xF704
		, 0x0004, 0x05F3, 0x0700, 0x4CA4, 0x6133, 0x6240, 0x9D83, 0x9E24, 0xAE45, 0xB3C0, 0xF634, 0xF6D5, 0xF8C4
		, 0x0004, 0x0453, 0x0550, 0x4D64, 0x5F73, 0x60B0, 0x9EA3, 0x9F74, 0xADA5, 0xB300, 0xF795, 0xF964
		, 0x0004, 0x0293, 0x0390, 0x4E24, 0x5D83, 0x5EE0, 0x9FA3, 0xA074, 0xAD45, 0xB144, 0xB1D0, 0xF864
		, 0x0004, 0x00C3, 0x01F0, 0x4E63, 0x4EF4, 0x5B73, 0x5D00, 0xA0D3, 0xA204, 0xAC55, 0xAFD4, 0xB0A0, 0xF804
		, 0x0003, 0x0030, 0x4F43, 0x5034, 0x5923, 0x5AD0, 0xA283, 0xA3D4, 0xAB95, 0xADE4, 0xAF00, 0xF7D4, 0xFE73
		, 0x0000, 0x50C3, 0x52A4, 0x5507, 0x5534, 0x5567, 0x55C3, 0x5820, 0xA453, 0xA717, 0xA803, 0xA837, 0xA893, 0xAAC4, 0xACA0, 0xF784, 0xFBF3, 0xFD90
		, 0x0000, 0xF783, 0xFB20
		, 0x0000
		, 0x0000
		, 0x0000
		, 0x0000
	}; // 1328 bytes

	const uint16_t row_ends[] PROGMEM {		
		0x0005, 0x0014, 0x0029, 0x0043, 0x005B, 0x0072, 0x0092, 0x00B2, 
		0x00CF, 0x00EA, 0x0106, 0x011D, 0x0131, 0x0157, 0x0173, 0x0196, 
		0x01B2, 0x01D2, 0x01EF, 0x0200, 0x020C, 0x0217, 0x0223, 0x0231, 
		0x023F, 0x024C, 0x0258, 0x0264, 0x0271, 0x027E, 0x0290, 0x0293, 
		0x0294, 0x0295, 0x0296, 0x0297
	}; // 72 bytes

	const uint32_t colors[] PROGMEM {		
		0x00000000, 0x00999999, 0x00FFFFFF, 0x003B1800, 0x00803300, 0x00FF7F2A, 
		0x00FF0000, 0x00660000
	}; // 32 bytes
}

class Poo : public Image {
protected:
	inline uint16_t get_arc(uint16_t i) override {
		return pgm_read_word(&Poo_data::arcs[i]);
	}

	inline uint16_t get_row_end(uint8_t row_index) override {
		return pgm_read_word(&Poo_data::row_ends[row_index]);
	}

protected:
	const uint16_t angle_mask = 0xFFF0;
	const uint16_t color_mask = 0x000F;

	inline uint16_t get_angle(uint16_t arc) override {
		return arc & angle_mask;
	}

	inline uint32_t get_color(uint16_t arc) override {
		return pgm_read_dword(&(Poo_data::colors[arc & color_mask]));
	}

public:
    Poo() {
        Image::Initialise();
    }
};
