#pragma once
#ifdef SIMULATION
#include "Arduino_Mock.h"
#else
#include <avr/pgmspace.h>
#endif

#include "../Image.h"

namespace rocket_data {
	const uint16_t arcs[] PROGMEM {
		  0x0000
		, 0x0000, 0x1469, 0x2818
		, 0x0000, 0x1071, 0x2D68
		, 0x0000, 0x0E61, 0x3088
		, 0x0000, 0x0D69, 0x3248
		, 0x0000, 0x0D69, 0x3318
		, 0x0000, 0x02E3, 0x0ED9, 0x32D0
		, 0x0001, 0x05E3, 0x11A9, 0x30E8, 0xFA91
		, 0x0001, 0x087B, 0x1381, 0x24E8, 0x28C1, 0x2A70, 0x2AE1, 0x2B48, 0xF639
		, 0x0001, 0x039B, 0x0A01, 0x1463, 0x1799, 0x2400, 0xF333, 0xF8C9
		, 0x0003, 0x0AA9, 0x1493, 0x1CF1, 0x25B0, 0xF063, 0xFC31, 0xFE1B
		, 0x0003, 0x0B31, 0x1493, 0x1D39, 0x2C08, 0xEE4B, 0xF921, 0xFF43
		, 0x0001, 0x0103, 0x0B49, 0x143B, 0x1C71, 0x2FA0, 0xECCB, 0xF661
		, 0x0001, 0x01A3, 0x0B29, 0x13B3, 0x1B99, 0x3298, 0xEB49, 0xF383, 0xF4D1
		, 0x0001, 0x0233, 0x0AF9, 0x0BEB, 0x11E1, 0x3500, 0xEA59, 0xF233, 0xF641
		, 0x0001, 0x0263, 0x03E1, 0x0A33, 0x1079, 0x13C8, 0x1411, 0x28C2, 0x2D41, 0x36D8, 0xE931, 0xF0B3, 0xF799
		, 0x0001, 0x004B, 0x0201, 0x08F3, 0x0C20, 0x1489, 0x2300, 0x2349, 0x270A, 0x3049, 0x3868, 0xE841, 0xEF3B, 0xF879
		, 0x0003, 0x01A9, 0x06A8, 0x14C9, 0x22A8, 0x240A, 0x32C1, 0x39F0, 0xE791, 0xEDFB, 0xF911, 0xFC63
		, 0x0003, 0x0089, 0x02A8, 0x1549, 0x2258, 0x258A, 0x3541, 0x3DC8, 0xE6F1, 0xECD3, 0xF911, 0xF99B
		, 0x0000, 0x15E9, 0x2250, 0x26F2, 0x35E8, 0x36F1, 0x3FB8, 0xE671, 0xEEF3, 0xF6B1, 0xF9CB, 0xFEF0
		, 0x0000, 0x1659, 0x2288, 0x28C2, 0x36A8, 0x3869, 0x40D8, 0xE5E1, 0xF053, 0xF451, 0xF98B, 0xFC40
		, 0x0000, 0x1701, 0x2280, 0x2AEA, 0x3758, 0x3891, 0x41A8, 0xE5A1, 0xF123, 0xF291, 0xF980
		, 0x0000, 0x1781, 0x22B0, 0x2D32, 0x37E0, 0x38D1, 0x4220, 0xE531, 0xF720
		, 0x0000, 0x1851, 0x2318, 0x2FF2, 0x3848, 0x3931, 0x4268, 0xE4C1, 0xF4F0
		, 0x0000, 0x1911, 0x2350, 0x325A, 0x38B0, 0x39C9, 0x42B8, 0xE481, 0xF2E8
		, 0x0000, 0x19A9, 0x23D8, 0x346A, 0x3950, 0x3A59, 0x42A0, 0xE461, 0xF0E8
		, 0x0000, 0x1A51, 0x24D0, 0x3652, 0x3998, 0x3B09, 0x4278, 0xE431, 0xEF50
		, 0x0000, 0x1AF9, 0x25F8, 0x37C2, 0x3A20, 0x3BC1, 0x41F0, 0xE401, 0xED98
		, 0x0000, 0x1BE1, 0x26C8, 0x3952, 0x3A78, 0x3CD1, 0x40B8, 0xE3E9, 0xEBE8
		, 0x0000, 0x1CD1, 0x2710, 0x3A32, 0x3A60, 0x3A9A, 0x3AF8, 0xE3B9, 0xEA30
		, 0x0000, 0x1E39, 0x2718, 0xE3C1, 0xE890
		, 0x0000, 0x1FC1, 0x2668, 0xE3A9, 0xE6E8
		, 0x0000, 0x2241, 0x2510, 0xE3B1, 0xE548
		, 0x0000
		, 0x0000
		, 0x0000
	}; // 520 bytes

	const uint16_t row_ends[] PROGMEM {		
		0x0000, 0x0003, 0x0006, 0x0009, 0x000C, 0x000F, 0x0013, 0x0018, 
		0x0021, 0x0029, 0x0031, 0x0039, 0x0041, 0x004A, 0x0053, 0x0060, 
		0x006E, 0x007A, 0x0086, 0x0092, 0x009E, 0x00A9, 0x00B2, 0x00BB, 
		0x00C4, 0x00CD, 0x00D6, 0x00DF, 0x00E8, 0x00F1, 0x00F6, 0x00FB, 
		0x0100, 0x0101, 0x0102, 0x0103
	}; // 72 bytes

	const uint32_t colors[] PROGMEM {		
		0x00000000, 0x00FF0000, 0x000000FF, 0x00FFFFFF
	}; // 16 bytes
}

class rocket : public Image {
protected:
	inline uint16_t get_arc(uint16_t i) override {
		return pgm_read_word(&rocket_data::arcs[i]);
	}

	inline uint16_t get_row_end(uint8_t row_index) override {
		return pgm_read_word(&rocket_data::row_ends[row_index]);
	}

protected:
	const uint16_t angle_mask = 0xFFF8;
	const uint16_t color_mask = 0x0007;

	inline uint16_t get_angle(uint16_t arc) override {
		return arc & angle_mask;
	}

	inline uint32_t get_color(uint16_t arc) override {
		return pgm_read_dword(&(rocket_data::colors[arc & color_mask]));
	}

public:
    rocket() {
        Image::Initialise();
    }
};
