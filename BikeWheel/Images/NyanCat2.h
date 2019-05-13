#pragma once
#ifdef SIMULATION
#include "Arduino_Mock.h"
#else
#include <avr/pgmspace.h>
#endif

#include "../Image.h"

namespace NyanCat2_data {
	const uint16_t arcs[] PROGMEM {
		  0x0033, 0x0BFF, 0x19B3, 0x3262, 0x34D1, 0x3700, 0x4591, 0x47E2, 0x4BF3, 0x7722, 0x7F11, 0x7FE2, 0x87F3
		, 0x0033, 0x0D37, 0x12FF, 0x1833, 0x30C0, 0x4ED1, 0x51A2, 0x54B3, 0x6CA2, 0x7051, 0x7480, 0x8A91, 0x8EE2, 0x92B3
		, 0x0033, 0x3200, 0x5633, 0x66A2, 0x6891, 0x6A80, 0x7C55, 0x8800, 0x9491, 0x96A2, 0x98B3
		, 0x0033, 0x2CD1, 0x3080, 0x34EA, 0x4755, 0x4DC0, 0x53F3, 0x6391, 0x6540, 0x7CAA, 0x8C40, 0x9A11, 0x9BE2, 0x9D33, 0xA4E2, 0xA633, 0xB0E2, 0xB511, 0xB800, 0xCA11, 0xCE22, 0xD033, 0xF437, 0xF5F3
		, 0x0033, 0x2791, 0x29C0, 0x352A, 0x46FB, 0x482A, 0x5100, 0x5591, 0x5722, 0x57F3, 0x6080, 0x7C95, 0x876A, 0x8B00, 0x9FE2, 0xA280, 0xA833, 0xA9E2, 0xAB91, 0xAD40, 0xD291, 0xD633, 0xEE3B, 0xF0FF, 0xF733
		, 0x0033, 0x2391, 0x2500, 0x2F55, 0x34AA, 0x45B3, 0x4C77, 0x4FC0, 0x5733, 0x5DC0, 0x9ED5, 0x9FC0, 0xB9EA, 0xBC55, 0xBD6A, 0xC480, 0xCAD4, 0xCD40, 0xD791, 0xDA73, 0xEF7F, 0xF733
		, 0x0033, 0x0BFB, 0x0F77, 0x1173, 0x2091, 0x2200, 0x2A15, 0x2CAA, 0x45B3, 0x4F2A, 0x5155, 0x5340, 0x5562, 0x5733, 0x5B80, 0x9DAA, 0xA195, 0xA2C0, 0xAC85, 0xAF4F, 0xB440, 0xBA2A, 0xC400, 0xCA7C, 0xCEB8, 0xD340, 0xDB91, 0xDD73, 0xF0BF, 0xF23B, 0xF477, 0xF773
		, 0x0033, 0x0B7F, 0x12B3, 0x2100, 0x2695, 0x27EA, 0x4573, 0x4DEA, 0x5340, 0x5851, 0x5940, 0x9B6A, 0xA4C0, 0xA805, 0xAACF, 0xB500, 0xBA2A, 0xC400, 0xC9BC, 0xD234, 0xD780, 0xE073
		, 0x0033, 0x0BFF, 0x1173, 0x21C0, 0x24EA, 0x3C7F, 0x4015, 0x44F3, 0x4D6A, 0x52C0, 0x9AD5, 0x9D2A, 0xA580, 0xA88F, 0xB580, 0xBAEA, 0xC380, 0xC8FC, 0xD174, 0xDB40, 0xE111, 0xE262, 0xE2B3
		, 0x0033, 0x0E77, 0x1073, 0x1AFB, 0x1BF7, 0x1CF3, 0x20C0, 0x266A, 0x3BBF, 0x4040, 0x44EA, 0x49F7, 0x4C6A, 0x5500, 0x9DD5, 0x9F2A, 0xA1D5, 0xA300, 0xA9CF, 0xB640, 0xB8C4, 0xB9C0, 0xBF2A, 0xC380, 0xC990, 0xCAD4, 0xCCFC, 0xCFF4, 0xDD80, 0xE473
		, 0x0033, 0x19BF, 0x1F33, 0x2240, 0x27EA, 0x3BFF, 0x4040, 0x44AA, 0x5480, 0xA055, 0xA0C0, 0xA6D1, 0xA7F3, 0xAB0F, 0xB70C, 0xBA40, 0xBF2A, 0xC340, 0xCCBC, 0xCF34, 0xDB20, 0xDE10, 0xDF80, 0xE673
		, 0x0000, 0x0551, 0x09A2, 0x0BB3, 0x18FF, 0x1F33, 0x2400, 0x2855, 0x2980, 0x2D2A, 0x3B80, 0x442A, 0x47D5, 0x4BEA, 0x5340, 0x5795, 0x5800, 0xA5B3, 0xAC0F, 0xB7CC, 0xBA80, 0xBF2A, 0xC515, 0xC940, 0xCC7C, 0xCEB4, 0xD9A0, 0xE010, 0xE180, 0xE773, 0xEB62, 0xEC33, 0xF422, 0xF5D1, 0xFA00
		, 0x0000, 0x0D91, 0x0FE2, 0x10F3, 0x19B7, 0x1C7B, 0x1CF7, 0x1D73, 0x26A2, 0x27F3, 0x29C0, 0x2D95, 0x2E80, 0x31AA, 0x3BC0, 0x442A, 0x4740, 0x4E6A, 0x5280, 0x572A, 0x5955, 0x5A40, 0xA333, 0xAD0F, 0xB84C, 0xBAC0, 0xBF2A, 0xC980, 0xCEB4, 0xD820, 0xE210, 0xE380, 0xE911, 0xEA40, 0xED33, 0xEEE2, 0xEFD1, 0xF1C0
		, 0x0000, 0x1251, 0x1422, 0x1533, 0x2937, 0x2B22, 0x2C73, 0x2E40, 0x3255, 0x3340, 0x362A, 0x4980, 0x4DEA, 0x5140, 0x55EA, 0x5A00, 0xA233, 0xAE0F, 0xB88C, 0xBAC4, 0xBBC8, 0xBE40, 0xC3AA, 0xC900, 0xCE74, 0xD6E0, 0xE410, 0xE500
		, 0x0000, 0x15D1, 0x17F3, 0x26FB, 0x27FF, 0x2BF3, 0x2E91, 0x2FA2, 0x3173, 0x3211, 0x3280, 0x36EA, 0x4940, 0x4D6A, 0x5080, 0x54AA, 0x57D5, 0x58C0, 0xA3F3, 0xAF0F, 0xB8CC, 0xBE40, 0xC355, 0xC4AA, 0xC8C0, 0xCDF4, 0xD5A0, 0xE3C0
		, 0x0000, 0x1891, 0x1A73, 0x27FF, 0x2C73, 0x32C0, 0x372A, 0x4900, 0x4CAA, 0x5000, 0x53EA, 0x5780, 0xA533, 0xAF8F, 0xB94C, 0xC200, 0xCD34, 0xD4E0, 0xE180
		, 0x0000, 0x1AD1, 0x1C73, 0x29F7, 0x2AF3, 0x3340, 0x37AA, 0x4880, 0x4C6A, 0x4F40, 0x5455, 0x5640, 0xA673, 0xB04F, 0xB94C, 0xC240, 0xC878, 0xC9A8, 0xCCB4, 0xD3A0, 0xDFC0
		, 0x0000, 0x1CD1, 0x1DA2, 0x1DF3, 0x3400, 0x37AA, 0x4555, 0x4840, 0x4BAA, 0x4E40, 0xA7B3, 0xB0CF, 0xB9CC, 0xC228, 0xC364, 0xC3A8, 0xC3E4, 0xC428, 0xC464, 0xC5D4, 0xC83C, 0xCB34, 0xD320, 0xDE40
		, 0x0000, 0x1E91, 0x1F62, 0x1FB3, 0x3440, 0x382A, 0x3F95, 0x42EA, 0x4540, 0x4B6A, 0x4E00, 0xA8B3, 0xB18F, 0xB9CC, 0xC23C, 0xCA74, 0xD220, 0xDD00
		, 0x0000, 0x2173, 0x3351, 0x3480, 0x38AA, 0x3F80, 0x42EA, 0x4780, 0x4AEA, 0x4D40, 0xA9B3, 0xB20F, 0xBA4C, 0xC21C, 0xC47C, 0xCA34, 0xD1A0, 0xDBC0
		, 0x0000, 0x22B3, 0x2EE2, 0x2F91, 0x30C0, 0x38AA, 0x3F80, 0x42EA, 0x4780, 0x4AAA, 0x4D00, 0xAA33, 0xB28F, 0xB45B, 0xB50F, 0xBCCC, 0xC4BC, 0xC9F8, 0xCC34, 0xD120, 0xDA80
		, 0x0000, 0x23B3, 0x2CD1, 0x2E00, 0x3615, 0x382A, 0x4740, 0x4A2A, 0x4C40, 0x4FAA, 0x5095, 0x5180, 0xAB33, 0xB58F, 0xBCCC, 0xC47C, 0xCBF4, 0xD060, 0xD980, 0xF26A, 0xF440
		, 0x0000, 0x24F3, 0x26E2, 0x2733, 0x2A51, 0x2B40, 0x36AA, 0x3D3F, 0x3F95, 0x426A, 0x4700, 0x49EA, 0x4C00, 0x4EEA, 0x5180, 0x6F15, 0x702A, 0x70BF, 0x70D5, 0x7100, 0xABF3, 0xAD62, 0xAE73, 0xB5CF, 0xBD0C, 0xC43C, 0xCBB4, 0xD1E0, 0xD880, 0xF27F, 0xF2EA, 0xF440
		, 0x0000, 0x24D1, 0x2500, 0x2811, 0x28C0, 0x366A, 0x3D3F, 0x3F80, 0x426A, 0x4440, 0x4555, 0x46C0, 0x496A, 0x4B80, 0x4E6A, 0x5100, 0x6FBF, 0x706A, 0x7140, 0xAC11, 0xAC00, 0xAEF3, 0xB60F, 0xBD0C, 0xC43C, 0xCB34, 0xD1A0, 0xD7C0, 0xF6EA, 0xF880
		, 0x0000, 0x34EA, 0x3F80, 0x426A, 0x4440, 0x492A, 0x4B00, 0x4E6A, 0x5040, 0xA095, 0xA100, 0xAFB3, 0xB68F, 0xBD4C, 0xC43C, 0xCAF4, 0xD120, 0xD740, 0xF095, 0xF1C0, 0xF6EA, 0xF880
		, 0x0000, 0x356A, 0x3D00, 0x422A, 0x4515, 0x4840, 0x4895, 0x48EA, 0x4AC0, 0x4F95, 0x4FC0, 0x9955, 0x9A00, 0x9F55, 0xA03F, 0xA180, 0xB033, 0xB6CF, 0xBD4C, 0xC3FC, 0xCAB4, 0xD0A0, 0xD7D0, 0xD880, 0xF07F, 0xF240
		, 0x0000, 0x3355, 0x346A, 0x3D00, 0x426A, 0x4A80, 0x986A, 0x98FF, 0x9AD5, 0x9B80, 0x9E15, 0x9EFF, 0xA140, 0xB0B3, 0xB70F, 0xBD4C, 0xC3BC, 0xCA34, 0xD020, 0xD7C0, 0xF095, 0xF180, 0xF415, 0xF4EA, 0xF5C0
		, 0x0000, 0x33EA, 0x4233, 0x44F7, 0x45AA, 0x47D5, 0x49AA, 0x4A15, 0x4A40, 0x9955, 0x99EA, 0x9A7F, 0x9C55, 0x9CC0, 0x9D55, 0x9DFF, 0x9F6A, 0x9FD5, 0xA000, 0xB133, 0xB74F, 0xBD4C, 0xC3BC, 0xC9F4, 0xCFA0, 0xD700, 0xF47F, 0xF600
		, 0x0000, 0x346A, 0x4233, 0x45AA, 0x4780, 0x9AD5, 0x9B6A, 0x9BFF, 0x9C6A, 0x9CD5, 0x9CC0, 0x9D55, 0x9DAA, 0x9E3F, 0x9EAA, 0x9E95, 0x9F00, 0xB173, 0xB78F, 0xBD8C, 0xC3BC, 0xC9B4, 0xCF60, 0xD640
		, 0x0000, 0x34AA, 0x3615, 0x362A, 0x3655, 0x3680, 0x3C6A, 0x4233, 0x4595, 0x4780, 0x9B55, 0x9BFF, 0x9C6A, 0x9C95, 0x9D00, 0x9D95, 0x9DEA, 0x9DFF, 0x9F40, 0xB1F3, 0xB78F, 0xBD8C, 0xC3BC, 0xC934, 0xCEA0, 0xD580
		, 0x0000, 0x3C6A, 0x4222, 0x42B3, 0x4540, 0x9B3F, 0x9CC0, 0x9D95, 0x9E2A, 0x9E3F, 0x9FD5, 0xA040, 0xB233, 0xB80F, 0xBD8C, 0xC37C, 0xC934, 0xCE60, 0xD500
		, 0x0000, 0x9A3F, 0x9BAA, 0x9C00, 0x9F7F, 0xA0D5, 0xA140, 0xB2B3, 0xB80F, 0xBDCC, 0xC33C, 0xC8F4, 0xCE20, 0xD480
		, 0x0000, 0x99BF, 0x9B40, 0x9F95, 0xA02A, 0xA07F, 0xA0EA, 0xA155, 0xA140, 0xB2F3, 0xB84F, 0xBDCC, 0xC33C, 0xC8B4, 0xCDA0, 0xD400
		, 0x0000, 0x9995, 0x9A2A, 0x9A55, 0x9A80, 0xB373, 0xB88F, 0xBDCC, 0xC33C, 0xC874, 0xCD60, 0xD340
		, 0x0000, 0xB373, 0xB88F, 0xBDCC, 0xC33C, 0xC834, 0xCCE0, 0xD300
		, 0x0000, 0xB3B3, 0xB8CF, 0xBC8C, 0xC1FC, 0xC834, 0xCCE0, 0xD2C0
	}; // 1602 bytes

	const uint16_t row_ends[] PROGMEM {		
		0x000C, 0x001A, 0x0025, 0x003D, 0x0056, 0x006C, 0x008C, 0x00A2, 
		0x00B9, 0x00D7, 0x00EF, 0x0112, 0x0138, 0x0154, 0x0170, 0x0183, 
		0x0198, 0x01B0, 0x01C2, 0x01D4, 0x01E9, 0x01FE, 0x021E, 0x023C, 
		0x0252, 0x026C, 0x0285, 0x02A1, 0x02B9, 0x02D3, 0x02E6, 0x02F4, 
		0x0304, 0x0310, 0x0318, 0x0320
	}; // 72 bytes
}

class NyanCat2 : public Image {
protected:
	inline uint16_t get_arc(uint16_t i) override {
		return pgm_read_word(&NyanCat2_data::arcs[i]);
	}

	inline uint16_t get_row_end(uint8_t row_index) override {
		return pgm_read_word(&NyanCat2_data::row_ends[row_index]);
	}

protected:
	inline uint16_t get_angle(uint16_t arc) override {
		return arc & 0xFFC0;
	}

	inline uint32_t get_color(uint16_t arc) override {
		return ((uint32_t)(arc & 0x0030) << 18) + ((uint32_t)(arc & 0x000C) << 12) + ((arc & 0x0003) << 6);
	}
};
