#pragma once
#ifdef SIMULATION#include "Arduino_Mock.h"
#else
#include <avr/pgmspace.h>
#endif

#include "../Image.h"

namespace space_data {
	const uint16_t arcs[] PROGMEM {
		  0x0000
		, 0x0000
		, 0x0000
		, 0x0000, 0x9415, 0x9480
		, 0x0000
		, 0x0000
		, 0x0000
		, 0x0000
		, 0x0000, 0x702A, 0x7155, 0x71C0
		, 0x0000, 0x1855, 0x1980, 0x7015, 0x70C0, 0xD4EA, 0xD6C0
		, 0x0000, 0x186A, 0x19C0, 0x5BD5, 0x5D6A, 0x5F3F, 0x6183, 0x6788, 0x68C4, 0x6A40, 0xD555, 0xD640
		, 0x0022, 0x0451, 0x06C0, 0x5ABF, 0x6003, 0x654C, 0x6B08, 0x6D00, 0xBABF, 0xBC00, 0xFB51, 0xFE22
		, 0x0022, 0x07D1, 0x0940, 0x35EA, 0x37C0, 0x587F, 0x5E03, 0x634C, 0x6E80, 0xF911, 0xFA22
		, 0x0022, 0x0A80, 0x573F, 0x5B2B, 0x5C83, 0x61CC, 0x6F80, 0xF7D1, 0xF8E2
		, 0x0011, 0x0152, 0x0362, 0x0B40, 0x55EB, 0x5997, 0x5A83, 0x6346, 0x650C, 0x7080, 0xF301, 0xF511
		, 0x0011, 0x06D2, 0x07E2, 0x0BC0, 0x5543, 0x5702, 0x5783, 0x57C2, 0x5806, 0x5903, 0x644C, 0x7100, 0xC7D4, 0xC9A8, 0xCD94, 0xCF00, 0xEF01, 0xF011
		, 0x0022, 0x0312, 0x0411, 0x09D2, 0x0AA2, 0x0C00, 0x558C, 0x5B83, 0x628C, 0x7140, 0x8BBF, 0x8CC0, 0xC554, 0xC628, 0xC73C, 0xD068, 0xD114, 0xD180, 0xED51, 0xF280, 0xF662
		, 0x0022, 0x0751, 0x0CC0, 0x54CC, 0x5A83, 0x610C, 0x7140, 0x8C15, 0x8C40, 0xC4FC, 0xD300, 0xECD1, 0xF100, 0xF662
		, 0x0022, 0x0A51, 0x0E80, 0x54CC, 0x5A03, 0x6206, 0x6483, 0x688C, 0x7140, 0xC3BC, 0xD400, 0xF6A2
		, 0x0022, 0x0B00, 0x0C51, 0x1040, 0x550C, 0x5983, 0x69C6, 0x6AC2, 0x6B06, 0x6C8C, 0x7140, 0xC2FC, 0xD480, 0xF722
		, 0x0022, 0x0A80, 0x0D91, 0x1180, 0x554C, 0x5943, 0x63C6, 0x64C3, 0x6D4C, 0x7100, 0xC2BC, 0xD500, 0xF7E2
		, 0x0022, 0x09C0, 0x0E51, 0x1240, 0x4B10, 0x4C00, 0x560C, 0x5903, 0x5EC6, 0x6083, 0x60C6, 0x630C, 0x6643, 0x6E0C, 0x7080, 0xC27C, 0xD500, 0xF851, 0xF922
		, 0x0022, 0x07D1, 0x0880, 0x0E51, 0x1300, 0x4910, 0x49E4, 0x4C00, 0x568C, 0x5983, 0x5E4C, 0x6703, 0x7000, 0xC2BC, 0xD4C0, 0xE62A, 0xE740, 0xF951, 0xFA22
		, 0x0022, 0x05D1, 0x06C0, 0x1181, 0x1200, 0x4864, 0x4B80, 0x578C, 0x5A83, 0x5ECC, 0x6509, 0x6606, 0x66C3, 0x6F00, 0xC2FC, 0xD4C0, 0xE655, 0xE700, 0xFB51, 0xFC62
		, 0x0011, 0x03C0, 0x47A4, 0x4B80, 0x588C, 0x5BC3, 0x5F8C, 0x6309, 0x6385, 0x6406, 0x6443, 0x6A57, 0x6CC3, 0x6D42, 0x6DC1, 0x6E00, 0x99AA, 0x9A3F, 0x9A95, 0x9AC0, 0xB715, 0xB7C0, 0xC33C, 0xD440, 0xFE11
		, 0x0000, 0x21D5, 0x226A, 0x2300, 0x38EA, 0x39C0, 0x4764, 0x4BC0, 0x5948, 0x5A0C, 0x5CC3, 0x600C, 0x61C9, 0x6246, 0x62C3, 0x6917, 0x69AB, 0x69FF, 0x6D00, 0x9995, 0x9A00, 0xB6EA, 0xB7C0, 0xC3FC, 0xD3C0
		, 0x0000, 0x2215, 0x2300, 0x3915, 0x3980, 0x4764, 0x4C40, 0x5A44, 0x5AC8, 0x5B4C, 0x5CC3, 0x6089, 0x6183, 0x6597, 0x676B, 0x683F, 0x6AEA, 0x6B55, 0x6BC0, 0xC4BC, 0xD294, 0xD300
		, 0x0000, 0x47A4, 0x4D00, 0x5C82, 0x5D83, 0x6117, 0x62AB, 0x63FF, 0x68AA, 0x6995, 0x6A00, 0xA915, 0xA940, 0xC514, 0xC63C, 0xD154, 0xD200, 0xD895, 0xD900
		, 0x003F, 0x00AA, 0x00C0, 0x47D0, 0x4864, 0x4DD0, 0x4E40, 0x5E81, 0x602A, 0x6695, 0x6780, 0x8255, 0x8300, 0xA92A, 0xAA00, 0xC6D4, 0xC83C, 0xCEE8, 0xCF94, 0xD080, 0xD915, 0xD940, 0xFFBF
		, 0x0000, 0x4890, 0x4924, 0x4F90, 0x5100, 0x826A, 0x8340, 0xC994, 0xCD80
		, 0x0000, 0x4990, 0x4AA4, 0x5090, 0x5140
		, 0x0000, 0x4B50, 0x4F80
		, 0x0000
		, 0x0000
		, 0x0000
		, 0x0000
	}; // 724 bytes

	const uint16_t row_ends[] PROGMEM {		
		0x0000, 0x0001, 0x0002, 0x0005, 0x0006, 0x0007, 0x0008, 0x0009, 
		0x000D, 0x0014, 0x0020, 0x002C, 0x0037, 0x0040, 0x004C, 0x005E, 
		0x0073, 0x0081, 0x008D, 0x009B, 0x00A8, 0x00BB, 0x00CE, 0x00E2, 
		0x00FB, 0x0114, 0x012A, 0x013D, 0x0154, 0x015D, 0x0162, 0x0165, 
		0x0166, 0x0167, 0x0168, 0x0169
	}; // 72 bytes
}

class space : public Image {
protected:
	inline uint16_t get_arc(uint16_t i) override {
		return pgm_read_word(&space_data::arcs[i]);
	}

	inline uint16_t get_row_end(uint8_t row_index) override {
		return pgm_read_word(&space_data::row_ends[row_index]);
	}

protected:
	inline uint16_t get_angle(uint16_t arc) override {
		return arc & 0xFFC0;
	}

	inline uint32_t get_color(uint16_t arc) override {
		return ((arc & 0x0030) << 18) + ((arc & 0x000C) << 12) + ((arc & 0x0003) << 6);
	}
};
