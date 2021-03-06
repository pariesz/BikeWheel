#pragma once
#include "../Image.h"

namespace NyanCat1Data {
	const uint16_t arcs[] PROGMEM {
		  0x000B, 0x68C1, 0x719B
		, 0x000B, 0x0801, 0x0E9B, 0xB13C, 0xB94D, 0xC4EB
		, 0x000B, 0x07E1, 0x11CB, 0x30BC, 0x354D, 0x3FDC, 0x4E5B, 0xA9CC, 0xAD1D, 0xC4CB
		, 0x000B, 0x0731, 0x102B, 0x28CC, 0x2CFD, 0x50EC, 0x565B, 0x70BC, 0x8EBB, 0xA44C, 0xA74D, 0xBB00, 0xC2DD, 0xC4AC, 0xCDAB
		, 0x000B, 0x24EC, 0x269D, 0x3366, 0x33FD, 0x57CC, 0x5A8B, 0x60BC, 0x626B, 0x6A3C, 0x6EAD, 0x7F70, 0x800D, 0x90CC, 0x953B, 0xA3CC, 0xA60D, 0xAEF0, 0xB361, 0xC31D, 0xD07C, 0xD46B, 0xEB51, 0xEF3B
		, 0x000B, 0x218C, 0x231D, 0x2D66, 0x2F74, 0x3215, 0x352D, 0x3A51, 0x45AD, 0x4BD7, 0x4EF8, 0x529D, 0x5BDC, 0x600D, 0x631C, 0x64AB, 0x65AC, 0x68CD, 0x7841, 0x852D, 0x96BC, 0x99CB, 0xA6BD, 0xA940, 0xABD1, 0xC290, 0xC9CD, 0xD63C, 0xD8CB, 0xE841, 0xF08B
		, 0x000B, 0x1EAC, 0x201D, 0x28B6, 0x2A24, 0x32D5, 0x362D, 0x3A71, 0x458D, 0x4AC7, 0x5089, 0x54DA, 0x57BD, 0x78C1, 0x84CD, 0x9A5C, 0x9D3B, 0xA37C, 0xA4ED, 0xAA21, 0xAFFB, 0xB341, 0xCD20, 0xD1FD, 0xD92B, 0xE971, 0xF0AB
		, 0x000B, 0x1D7D, 0x24B6, 0x2604, 0x33A5, 0x36DD, 0x3AE1, 0x455D, 0x4A47, 0x4FB9, 0x594A, 0x5B1D, 0x6250, 0x6491, 0x66D0, 0x683D, 0x7880, 0x796D, 0x9DAC, 0x9FFB, 0xA40C, 0xA56D, 0xABBB, 0xB451, 0xD400, 0xD56D, 0xD7AB
		, 0x000C, 0x087B, 0x1A5C, 0x1B9D, 0x2113, 0x22D2, 0x24E4, 0x3435, 0x373D, 0x3B61, 0x44CD, 0x4977, 0x4E89, 0x5D6D, 0x5FF0, 0x61A1, 0x6870, 0x69BD, 0xA07C, 0xA22B, 0xA44C, 0xA5FD, 0xA881, 0xAC5B, 0xB4D1, 0xD4BD, 0xD9CB, 0xDD91, 0xE09B, 0xF71C
		, 0x000D, 0x0C0C, 0x0F9B, 0x153C, 0x179B, 0x18CC, 0x199D, 0x1EC3, 0x2002, 0x26C4, 0x3403, 0x3464, 0x34C6, 0x373D, 0x3B91, 0x4060, 0x4538, 0x46CD, 0x48C7, 0x4D99, 0x5B9A, 0x5CCC, 0x5D3D, 0x5F30, 0x60C1, 0x68C0, 0x6A6D, 0xA2CC, 0xA33D, 0xA860, 0xA991, 0xAD9B, 0xB600, 0xB93D, 0xBA60, 0xBAC9, 0xBB31, 0xBD39, 0xBEC1, 0xD39D, 0xD80C, 0xD93B, 0xDB91, 0xE2CB, 0xF00C, 0xF40D
		, 0x000D, 0x118C, 0x136D, 0x1CF3, 0x1E12, 0x2864, 0x336D, 0x3BC1, 0x406D, 0x44F7, 0x4CF9, 0x5C3D, 0x6120, 0x62A1, 0x6550, 0x679D, 0xA790, 0xA981, 0xAEDB, 0xB241, 0xB61D, 0xBB09, 0xBF31, 0xCDB0, 0xD061, 0xD180, 0xD24D, 0xD67C, 0xD79B, 0xDCF1, 0xE18B, 0xEB6C, 0xEE1D
		, 0x000D, 0x18E3, 0x1C22, 0x2984, 0x345D, 0x3850, 0x390D, 0x3960, 0x3B91, 0x40AD, 0x44F7, 0x4C29, 0x598B, 0x5D2C, 0x5E3D, 0x62E0, 0x64BD, 0xA721, 0xB6BD, 0xBAAA, 0xBF01, 0xC970, 0xC9D1, 0xCDCD, 0xD10C, 0xD3FD, 0xD61B, 0xE7CC, 0xE9FD
		, 0x000D, 0x1A03, 0x1BC2, 0x2A74, 0x3103, 0x336D, 0x35C1, 0x406D, 0x4487, 0x4BB9, 0x581B, 0x5EEC, 0x604D, 0xA790, 0xA891, 0xB1D0, 0xB3E1, 0xB70D, 0xBF31, 0xC92D, 0xCBE0, 0xCCEC, 0xCE4D, 0xD10B, 0xD4DC, 0xD52B, 0xE54C, 0xE6FD
		, 0x000D, 0x1C93, 0x1E32, 0x2BB4, 0x319D, 0x3631, 0x3C20, 0x3FCD, 0x4010, 0x406D, 0x4457, 0x4B49, 0x56CB, 0x619D, 0xA450, 0xA4FD, 0xA8E0, 0xA9E1, 0xAD80, 0xAFDD, 0xB4B1, 0xB75D, 0xB9A0, 0xBA0D, 0xBAA0, 0xBEE1, 0xC4D0, 0xC8CD, 0xCD1B, 0xD051, 0xD2FB, 0xE2CC, 0xE46D
		, 0x000D, 0x1EB3, 0x2002, 0x2CD4, 0x328D, 0x36E1, 0x3C8D, 0x40F7, 0x4AA9, 0x55AB, 0x5FAC, 0x60FD, 0xA371, 0xA550, 0xA64D, 0xAA00, 0xAAF1, 0xAE1D, 0xB230, 0xB411, 0xC4BD, 0xC91B, 0xCA0C, 0xCC3B, 0xCF01, 0xD46B, 0xE0FC, 0xE23D
		, 0x000D, 0x20A3, 0x2192, 0x2D94, 0x32FD, 0x3770, 0x3C4D, 0x40B7, 0x4A59, 0x548B, 0x5E2C, 0x5F0D, 0xA2C0, 0xA3F1, 0xA6A0, 0xA79D, 0xABC1, 0xAF1D, 0xB2A1, 0xC4AD, 0xC88B, 0xCFB1, 0xD35B, 0xDF0C, 0xE03D
		, 0x000D, 0x2223, 0x2302, 0x2E44, 0x337D, 0x3583, 0x373D, 0x3D55, 0x40C7, 0x49C9, 0x539B, 0x5C9C, 0x5DBD, 0xA440, 0xA521, 0xA7C0, 0xA8AD, 0xACB1, 0xAF9D, 0xB351, 0xC46D, 0xC82B, 0xDD9C, 0xDEBD
		, 0x000D, 0x2452, 0x2F24, 0x37BD, 0x3D45, 0x4097, 0x4979, 0x52EB, 0x5B8C, 0x5C5D, 0xA590, 0xA661, 0xA92D, 0xAD51, 0xB06D, 0xB3B1, 0xC45D, 0xC7FB, 0xDC3C, 0xDD03, 0xDD5D
		, 0x000D, 0x24C3, 0x2582, 0x2FA4, 0x37F6, 0x3874, 0x38B5, 0x40B7, 0x48F9, 0x520B, 0x5A4C, 0x5B1D, 0xA670, 0xA85D, 0xAE31, 0xB0ED, 0xB3D0, 0xB701, 0xC40D, 0xC78B, 0xDAFC, 0xDBCD
		, 0x000D, 0x25E3, 0x26B2, 0x3044, 0x3905, 0x4087, 0x48C9, 0x514B, 0x590C, 0x59CD, 0xAEF1, 0xB18D, 0xB731, 0xB9CD, 0xBCA1, 0xC3DD, 0xC73C, 0xC98B, 0xD9CC, 0xDA9D
		, 0x000D, 0x2782, 0x30F4, 0x35A5, 0x3B67, 0x4359, 0x47D7, 0x4859, 0x50CB, 0x58BD, 0xAF71, 0xB1FD, 0xB531, 0xB9AD, 0xBCE1, 0xC3DD, 0xCB4C, 0xCE0B, 0xD97D
		, 0x000D, 0x2882, 0x3124, 0x3475, 0x3BA7, 0x4319, 0x4ACB, 0x4C70, 0x4E69, 0x500B, 0x574C, 0x57FD, 0xAFF1, 0xB29D, 0xB531, 0xBA0D, 0xBCE1, 0xC390, 0xC63D, 0xCF1C, 0xD14B, 0xD59C, 0xD60B, 0xD7FC, 0xD8BD
		, 0x000D, 0x28C3, 0x2972, 0x2E54, 0x34E5, 0x3BD7, 0x4319, 0x4A8B, 0x511C, 0x51FB, 0x56ED, 0xACD0, 0xAD8D, 0xB091, 0xB2ED, 0xB5B1, 0xC63D, 0xD25C, 0xD3FB, 0xD4AC, 0xD55D, 0xD70C, 0xD7BD
		, 0x000D, 0x2A12, 0x2D74, 0x3525, 0x3BE7, 0x42D9, 0x4A1B, 0x50DD, 0x52DC, 0x54AB, 0x558C, 0x563D, 0xABC1, 0xAE4D, 0xB131, 0xB37D, 0xB5E1, 0xBA60, 0xBC3D, 0xBD29, 0xBFD1, 0xC62D
		, 0x000D, 0x2813, 0x2932, 0x2E04, 0x35A5, 0x3BF7, 0x42F9, 0x49BB, 0x503D, 0xAC71, 0xAEED, 0xB171, 0xB3AD, 0xB610, 0xB79D, 0xB8B1, 0xBAAD, 0xBD49, 0xBFE1, 0xC7FD
		, 0x000D, 0x26A3, 0x2742, 0x2EB4, 0x35E5, 0x3C17, 0x42A9, 0x497B, 0x4FDD, 0xAD01, 0xAF5D, 0xB211, 0xB43D, 0xB8E1, 0xBACD, 0xBD2A, 0xBFE1, 0xC7BD
		, 0x000D, 0x2742, 0x2F24, 0x3615, 0x3C47, 0x42A9, 0x494B, 0x4F3D, 0xADE0, 0xAF5D, 0xB261, 0xB47D, 0xB5B0, 0xB7F1, 0xBADD, 0xC001, 0xC790, 0xC94D
		, 0x000D, 0x2793, 0x2822, 0x2F94, 0x3655, 0x3C57, 0x4289, 0x48FB, 0x4EFD, 0xB2D1, 0xBB0D, 0xBC70, 0xBFD1, 0xC93D
		, 0x000D, 0x2853, 0x28F2, 0x3024, 0x36C5, 0x3C77, 0x4279, 0x48BB, 0x4E9D, 0xB321, 0xB480, 0xB551, 0xB7AB, 0xBAF1, 0xC90D
		, 0x000D, 0x2982, 0x3084, 0x36F5, 0x3C77, 0x4259, 0x487B, 0x4E2D, 0xB5A1, 0xB7CB, 0xBB21, 0xC0DD, 0xC280, 0xC741, 0xC8DD
		, 0x000D, 0x29A3, 0x2A32, 0x30E4, 0x3725, 0x3CA7, 0x4269, 0x484B, 0x4DAD, 0xB5D0, 0xB6CD, 0xB81B, 0xBB31, 0xC0BD
		, 0x000D, 0x2AC2, 0x3164, 0x3765, 0x3CC7, 0x4269, 0x47FB, 0x4D6D, 0xB83B, 0xBB40, 0xC0AD
		, 0x000D, 0x2AD3, 0x2B62, 0x31B4, 0x3785, 0x3CC7, 0x4239, 0x47DB, 0x4CFD
		, 0x000D, 0x2BD2, 0x3204, 0x37D5, 0x3CF7, 0x4249, 0x47BB, 0x4CBD
		, 0x000D, 0x2BF3, 0x2C72, 0x3274, 0x3805, 0x3CE7, 0x4219, 0x477B, 0x4C5D
		, 0x000D, 0x2CA2, 0x3294, 0x3825, 0x3D07, 0x4229, 0x475B, 0x4C1D
	}; // 1460 bytes

	const uint16_t row_ends[] PROGMEM {		
		0x0002, 0x0008, 0x0012, 0x0021, 0x0039, 0x0058, 0x0073, 0x008E, 
		0x00AC, 0x00DA, 0x00FB, 0x0118, 0x0134, 0x0155, 0x0171, 0x018A, 
		0x01A2, 0x01B7, 0x01CD, 0x01E1, 0x01F4, 0x020D, 0x0224, 0x023A, 
		0x024E, 0x0260, 0x0272, 0x0280, 0x028F, 0x029E, 0x02AC, 0x02B7, 
		0x02C0, 0x02C8, 0x02D1, 0x02D9
	}; // 72 bytes

	const uint32_t colors[] PROGMEM {		
		0x00888888, 0x00FFFFFF, 0x00FF0000, 0x00880000, 0x00FF8800, 0x00FFFF00, 
		0x00888800, 0x0000FF00, 0x00008800, 0x0000FFFF, 0x00008888, 0x00FF00FF, 
		0x00880088, 0x00000000
	}; // 56 bytes
}

class NyanCat1 : public Image {
public:
	NyanCat1() {
		Image::Initialise();
	}
protected:
	inline uint16_t get_arc(uint16_t i) override {
		return pgm_read_word(&NyanCat1Data::arcs[i]);
	}

	inline uint16_t get_row_end(uint8_t row_index) override {
		return pgm_read_word(&NyanCat1Data::row_ends[row_index]);
	}

protected:
	const uint16_t angle_mask = 0xFFF0;
	const uint16_t color_mask = 0x000F;

	inline uint16_t get_angle(uint16_t arc) override {
		return arc & angle_mask;
	}

	inline uint32_t get_color(uint16_t arc) override {
		return pgm_read_dword(&(NyanCat1Data::colors[arc & color_mask]));
	}
};
