#pragma once
#include <avr/pgmspace.h>
#include "Image.h"
namespace rocket_data {
	const uint16_t arcs[] PROGMEM {
		  0x0000
		, 0x0000, 0x1468, 0x15E9, 0x1A4A, 0x20D9, 0x2538, 0x2760
		, 0x0000, 0x1078, 0x1119, 0x11CA, 0x1311, 0x28CA, 0x2A19, 0x2B68, 0x2D60
		, 0x0000, 0x0E69, 0x0EFA, 0x0F91, 0x2D9A, 0x2E29, 0x2F58, 0x2FF0
		, 0x0000, 0x0D67, 0x0DF1, 0x301A, 0x30A9, 0x3138, 0x31B0
		, 0x0000, 0x0D61, 0x318A, 0x3218, 0x3290
		, 0x0000, 0x0263, 0x02E4, 0x06B5, 0x0D6C, 0x0EDB, 0x0F51, 0x31D8, 0x3250
		, 0x000A, 0x015B, 0x02BC, 0x056D, 0x05EE, 0x0652, 0x0F6E, 0x104D, 0x113C, 0x1211, 0x2F9A, 0x3009, 0x3078, 0x30E7, 0x3160, 0xFA98, 0xFBE9, 0xFEAA
		, 0x0001, 0x06CB, 0x073C, 0x0872, 0x124E, 0x12AD, 0x131C, 0x1381, 0x248A, 0x24E8, 0x25C9, 0x27E1, 0x2A7A, 0x2AE9, 0x2B4A, 0x2BB9, 0x2C28, 0x2DD7, 0x2F10, 0xF638, 0xF719, 0xF85A, 0xF9A1
		, 0x0001, 0x039C, 0x040B, 0x046C, 0x066D, 0x08CE, 0x0932, 0x099E, 0x0A0C, 0x0A6B, 0x0ACC, 0x0B3B, 0x10CC, 0x1391, 0x140B, 0x146C, 0x14CD, 0x153C, 0x180B, 0x1861, 0x2398, 0x2407, 0x2460, 0xF334, 0xF405, 0xF4C6, 0xF59C, 0xF991
		, 0x000D, 0x018E, 0x02A2, 0x09EE, 0x0A4D, 0x0AAB, 0x0B01, 0x143C, 0x1492, 0x18CE, 0x1A4D, 0x1BCC, 0x1CF1, 0x230A, 0x2369, 0x2498, 0x2550, 0x25B7, 0x2610, 0x2677, 0x26D0, 0xF0C4, 0xF185, 0xF246, 0xF2A2, 0xFAAE, 0xFB6D, 0xFC9C, 0xFDBB, 0xFE1C, 0xFF3D
		, 0x0002, 0x0ADD, 0x0B31, 0x143B, 0x1492, 0x1CE1, 0x27BA, 0x2929, 0x2AF8, 0x2C00, 0xEEA4, 0xEF65, 0xEFC6, 0xF072, 0xF98D, 0xFA3C, 0xFBAB, 0xFCC1, 0xFDDB, 0xFE8C, 0xFEED
		, 0x0001, 0x005B, 0x00AC, 0x0102, 0x0AFE, 0x0B41, 0x143E, 0x1482, 0x1C7B, 0x1CC1, 0x2CEA, 0x2DE9, 0x2E98, 0x2FF0, 0xED24, 0xED75, 0xEDD6, 0xEE82, 0xF66E, 0xF6BD, 0xF76C, 0xF81B, 0xF921
		, 0x0001, 0x015B, 0x01AD, 0x01F2, 0x0B21, 0x136C, 0x13BE, 0x1402, 0x1B9C, 0x1BEB, 0x1C41, 0x304A, 0x30F9, 0x3198, 0x31F7, 0x3248, 0x3290, 0xEBF8, 0xEC49, 0xEC9A, 0xECFC, 0xED4B, 0xEEE1, 0xEF3B, 0xF031, 0xF08B, 0xF2DC, 0xF3DD, 0xF47E, 0xF4DC, 0xF5DB, 0xF621
		, 0x0001, 0x01EB, 0x023E, 0x0282, 0x0AAE, 0x0AFB, 0x0B41, 0x0B9C, 0x10FD, 0x119C, 0x11ED, 0x123C, 0x1281, 0x12DB, 0x132C, 0x16ED, 0x1AAC, 0x1AFB, 0x1B41, 0x32DA, 0x3379, 0x3418, 0x3460, 0xEAA8, 0xEAF9, 0xEB4A, 0xEB91, 0xF28C, 0xF32D, 0xF3CE, 0xF412, 0xF50E, 0xF5AD, 0xF64C, 0xF69B, 0xF6E1
		, 0x0001, 0x0262, 0x03EE, 0x043D, 0x056C, 0x077B, 0x0991, 0x0A3D, 0x0A7E, 0x0AC2, 0x102E, 0x107D, 0x10CC, 0x11AB, 0x11F1, 0x137A, 0x13C9, 0x1411, 0x2829, 0x2877, 0x28C0, 0x2957, 0x2A98, 0x2C19, 0x2CFA, 0x2D41, 0x350A, 0x35A9, 0x3648, 0x36D0, 0xE988, 0xE9D9, 0xEA1A, 0xEA61, 0xF0BC, 0xF14D, 0xF1EE, 0xF232, 0xF70E, 0xF74D, 0xF7EC, 0xF831
		, 0x000C, 0x012D, 0x020C, 0x025B, 0x0321, 0x094C, 0x098E, 0x09D2, 0x0C25, 0x0D44, 0x0D95, 0x0DE4, 0x0F98, 0x0FE7, 0x1230, 0x1439, 0x1481, 0x22B9, 0x234A, 0x2399, 0x23D1, 0x247A, 0x24B1, 0x25E9, 0x262A, 0x2679, 0x26C8, 0x27A7, 0x27E0, 0x2DB7, 0x2E98, 0x2FB9, 0x3001, 0x36FA, 0x3789, 0x37D8, 0x3867, 0x38B0, 0xE898, 0xE8D9, 0xE92A, 0xE961, 0xEF3B, 0xEF8C, 0xEFCD, 0xF01E, 0xF062, 0xF83E, 0xF87D, 0xF8CC, 0xF901
		, 0x0002, 0x01AD, 0x01FB, 0x0231, 0x06EA, 0x0739, 0x0808, 0x0894, 0x09B3, 0x0B10, 0x1488, 0x14C1, 0x2260, 0x30D7, 0x3158, 0x3239, 0x327A, 0x32C1, 0x389A, 0x38D9, 0x3928, 0x39B0, 0x3B58, 0x3BA7, 0x3C20, 0xE7D8, 0xE829, 0xE86A, 0xE8B1, 0xEDFC, 0xEE8D, 0xEECE, 0xEF52, 0xF91E, 0xF95C, 0xF991, 0xFC6C, 0xFCFD, 0xFE0E, 0xFEE2
		, 0x0002, 0x00CE, 0x011C, 0x015B, 0x0191, 0x02E9, 0x03B8, 0x0507, 0x0620, 0x14C7, 0x1509, 0x154A, 0x1591, 0x2219, 0x2250, 0x3327, 0x33A8, 0x347A, 0x34B1, 0x350A, 0x3541, 0x3A1A, 0x3A51, 0x3C79, 0x3CB1, 0x3D09, 0x3D48, 0x3E17, 0x3E50, 0xE738, 0xE779, 0xE7CA, 0xE801, 0xED1C, 0xED5D, 0xEDEE, 0xEE22, 0xF91E, 0xF95D, 0xF99B, 0xF9DC, 0xFA2D, 0xFAFE, 0xFBB2
		, 0x0005, 0x0049, 0x0088, 0x0187, 0x0250, 0x1568, 0x15A9, 0x15E1, 0x2219, 0x2250, 0x3527, 0x35E8, 0x363A, 0x3679, 0x36BA, 0x36F1, 0x3EF8, 0x3F77, 0x3FB0, 0xE6B8, 0xE6F9, 0xE731, 0xED2B, 0xEDEC, 0xEEFD, 0xEF7E, 0xEFB2, 0xF6FD, 0xF77C, 0xF84B, 0xF901, 0xF9CC, 0xFA12, 0xFF3D, 0xFF76
		, 0x0000, 0x15D8, 0x1619, 0x1651, 0x2209, 0x2240, 0x3727, 0x37A8, 0x3829, 0x3861, 0x4018, 0x4097, 0x40D0, 0xE628, 0xE669, 0xE6A1, 0xEF9B, 0xF01C, 0xF09D, 0xF0D2, 0xF49D, 0xF51C, 0xF5CB, 0xF681, 0xF9CD, 0xFA02, 0xFC46, 0xFC85, 0xFCC4, 0xFE03, 0xFF00
		, 0x0000, 0x1647, 0x1688, 0x16C9, 0x1701, 0x2247, 0x2280, 0x3818, 0x3851, 0x40F9, 0x4137, 0x4170, 0xE5D8, 0xE611, 0xF0EB, 0xF12C, 0xF16D, 0xF192, 0xF29E, 0xF2DD, 0xF30C, 0xF3CB, 0xF441, 0xF94C, 0xF986, 0xF9C5, 0xFA34, 0xFB33, 0xFBA7, 0xFBE0
		, 0x0000, 0x1707, 0x1749, 0x1781, 0x223A, 0x2277, 0x22B0, 0x3827, 0x385A, 0x3891, 0x41B8, 0x41E0, 0xE578, 0xE5AA, 0xE5E1, 0xF18B, 0xF241, 0xF72A, 0xF769, 0xF7D8, 0xF8C7, 0xF970
		, 0x0000, 0x17A7, 0x17D8, 0x1819, 0x1851, 0x227A, 0x22A8, 0x22E0, 0x3887, 0x38B9, 0x38F1, 0x41F7, 0x4230, 0xE539, 0xE561, 0xF539, 0xF5A8, 0xF657, 0xF6F0
		, 0x0000, 0x1837, 0x1868, 0x18A9, 0x18DA, 0x1911, 0x22E9, 0x2318, 0x2350, 0x38E7, 0x3928, 0x3959, 0x3991, 0x4219, 0x4240, 0xE4F9, 0xE521, 0xF329, 0xF398, 0xF437, 0xF4E0
		, 0x0000, 0x1907, 0x1948, 0x197A, 0x19A1, 0x233A, 0x2379, 0x23A8, 0x23D0, 0x3987, 0x39B8, 0x39FA, 0x3A21, 0x420A, 0x4237, 0x4270, 0xE498, 0xE4D1, 0xF0EA, 0xF159, 0xF198, 0xF237, 0xF2D0
		, 0x0000, 0x19B7, 0x19E8, 0x1A29, 0x1A51, 0x23CA, 0x2409, 0x2468, 0x24D7, 0x2500, 0x3A37, 0x3A78, 0x3AA9, 0x3AD1, 0x41AA, 0x41D8, 0x4240, 0xE468, 0xE4AA, 0xE4D1, 0xEF5A, 0xEF89, 0xEFB8, 0xF097, 0xF0F0
		, 0x0000, 0x1A67, 0x1A98, 0x1AC9, 0x1AF1, 0x252A, 0x2559, 0x25C8, 0x25F0, 0x3AF7, 0x3B59, 0x3B8A, 0x3BC1, 0x40FA, 0x4129, 0x4188, 0x41B0, 0xE46A, 0xE491, 0xED9A, 0xEDD9, 0xEE38, 0xEED7, 0xEF30
		, 0x0000, 0x1B17, 0x1B48, 0x1B79, 0x1BE1, 0x260A, 0x2639, 0x2668, 0x2690, 0x3C77, 0x3CD8, 0x3F87, 0x3FF9, 0x4028, 0x40B0, 0xE45A, 0xE481, 0xEBE9, 0xEC48, 0xED17, 0xED70
		, 0x0000, 0x1BE7, 0x1C18, 0x1C79, 0x1CD1, 0x26A9, 0x26D0, 0xE419, 0xE451, 0xEA3A, 0xEA69, 0xEAC8, 0xEB57, 0xEBB0
		, 0x0000, 0x1CF7, 0x1D28, 0x1DB9, 0x1E11, 0x26BA, 0x26E0, 0xE421, 0xE8C9, 0xE928, 0xE9A7, 0xEA00
		, 0x0000, 0x1E47, 0x1EA8, 0x1F69, 0x1FE1, 0x2639, 0x2668, 0x2697, 0x26C0, 0xE40A, 0xE431, 0xE6E9, 0xE778, 0xE807, 0xE880
		, 0x0000, 0x2027, 0x20D8, 0x21B9, 0x21E1, 0x248A, 0x24B1, 0x24E9, 0x2518, 0x25C7, 0x25F0, 0xE3E7, 0xE411, 0xE519, 0xE5A8, 0xE657, 0xE6B0
		, 0x0000, 0x22C7, 0x2420, 0xE3E7, 0xE4C0
		, 0x0000
		, 0x0000
	}; // 1502 bytes

	const uint16_t row_ends[] PROGMEM {
		0x0000, 0x0007, 0x0010, 0x0018, 0x001F, 0x0024, 0x002D, 0x003F, 0x0056, 0x0072, 0x0091, 0x00A6, 0x00BD, 0x00DD, 0x0101, 0x012B, 0x015E, 0x0186, 0x01B2, 0x01D5, 0x01F4, 0x0212, 0x0228, 0x023B, 0x0250, 0x0267, 0x0280, 0x0298, 0x02AD, 0x02BB, 0x02C7, 0x02D6, 0x02E7, 0x02EC, 0x02ED, 0x02EE
	}; // 72 bytes
	const uint32_t colors[] PROGMEM {
		0x00000000, 0x00FF0000, 0x00FFFFFF, 0x00333333, 0x00666666, 0x00999999, 0x00CCCCCC, 0x00330000, 0x00660000, 0x00990000, 0x00CC0000, 0x00FF3333, 0x00FF6666, 0x00FF9999, 0x00FFCCCC
	}; // 60 bytes
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
	const uint32_t angle_mask = 0xFFF0;
	const uint32_t color_mask = 0x000F;

	inline uint16_t get_angle(uint16_t arc) override {
		return arc & angle_mask;
	}

	inline uint32_t get_color(uint16_t arc) override {
		return pgm_read_dword(&rocket_data::colors[arc & color_mask]);
	}
};
