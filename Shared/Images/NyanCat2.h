#pragma once
#include "../Image.h"

namespace NyanCat2Data {
	const uint16_t arcs[] PROGMEM {
		  0x000B, 0x30CD, 0x4E6C, 0x519B, 0x759C, 0x899B, 0xC401, 0xD0CB, 0xE001, 0xE40B
		, 0x000B, 0x276C, 0x2A4D, 0x53DC, 0x584B, 0x5F8C, 0x627B, 0x6BFC, 0x733D, 0x8C0C, 0x935B, 0xBB7D, 0xBFDC, 0xC4E0, 0xCF2B, 0xDCF1, 0xE67B
		, 0x000B, 0x223C, 0x243D, 0x3540, 0x3A91, 0x3FD0, 0x432D, 0x4A58, 0x4C5D, 0x598C, 0x5E1D, 0x635C, 0x69FD, 0x956C, 0x99FB, 0xBB8D, 0xD09C, 0xD53B, 0xDC71, 0xE7AB
		, 0x0001, 0x009B, 0x0431, 0x04CB, 0x1E9C, 0x205D, 0x29F6, 0x2F5D, 0x3681, 0x432D, 0x4A57, 0x4DF9, 0x505A, 0x548D, 0x7AE0, 0x7B8D, 0x9B4C, 0x9E4B, 0xB5AC, 0xBA7D, 0xBF40, 0xC67D, 0xD7DC, 0xDA3B, 0xE031, 0xE33B
		, 0x0001, 0x07DB, 0x1D1D, 0x2696, 0x2834, 0x29E5, 0x30AD, 0x3751, 0x431D, 0x49C7, 0x4C99, 0x56AA, 0x596D, 0x6FC0, 0x75F1, 0x7C1D, 0x9EBC, 0xA0FB, 0xB5AD, 0xBCE1, 0xCA50, 0xD07D, 0xDB1B
		, 0x0001, 0x07BB, 0x1ADD, 0x2394, 0x2B55, 0x321D, 0x37B1, 0x431D, 0x48C7, 0x4BD9, 0x5ADA, 0x5C6D, 0x6EF1, 0x7C6D, 0xA39B, 0xB63D, 0xBCEB, 0xC5A1, 0xD290, 0xD63D, 0xD94B
		, 0x000B, 0x18ED, 0x2094, 0x2D15, 0x32DD, 0x3D51, 0x42AD, 0x4868, 0x4B4A, 0x4D29, 0x5A9A, 0x5C0D, 0x5FE0, 0x60DD, 0x7021, 0x7290, 0x7B3D, 0xA46C, 0xA5DB, 0xB1DD, 0xB811, 0xBCEB, 0xC5F1, 0xD64D, 0xD9AC, 0xDB9B
		, 0x000B, 0x171D, 0x1CF6, 0x1E54, 0x2E35, 0x37BD, 0x3D21, 0x429D, 0x4D79, 0x58CA, 0x5A2D, 0x5CE0, 0x5F21, 0x61D0, 0x633D, 0xA64C, 0xA7AB, 0xB28D, 0xB861, 0xBCFB, 0xC581, 0xD56D, 0xDD1C, 0xDEEB, 0xEB91, 0xEC1B
		, 0x000B, 0x153D, 0x1B92, 0x1E94, 0x2F85, 0x380D, 0x3D81, 0x42A0, 0x489D, 0x4C69, 0x570A, 0x584D, 0x5B40, 0x5C81, 0x6430, 0x657D, 0xA81C, 0xA96B, 0xAEEC, 0xB24D, 0xB400, 0xB6F1, 0xBD5B, 0xC4F1, 0xD660, 0xD8FD, 0xDFBC, 0xE10B, 0xE761, 0xED5B
		, 0x000B, 0x140D, 0x1A02, 0x20C4, 0x3065, 0x386D, 0x3D91, 0x4A0D, 0x4D9A, 0x5009, 0x566D, 0x5A60, 0x5B91, 0x6330, 0x659D, 0x9F30, 0xA0CD, 0xA99C, 0xAACB, 0xAF9D, 0xB4C1, 0xC530, 0xC861, 0xDA00, 0xDC0D, 0xE20C, 0xE33B, 0xE791, 0xEE6B
		, 0x000B, 0x130D, 0x1862, 0x22A4, 0x3125, 0x38CD, 0x3DB0, 0x4241, 0x498D, 0x4F99, 0x55BC, 0x580D, 0x5C30, 0x5E11, 0x60C0, 0x62AD, 0x9BC0, 0x9CF1, 0xA120, 0xA2AD, 0xABCB, 0xB06D, 0xB551, 0xC49D, 0xC8C9, 0xCCF1, 0xDCF0, 0xDE7D, 0xE3CC, 0xE4FB, 0xE921, 0xEB6B
		, 0x000C, 0x0A1B, 0x0DBD, 0x103C, 0x11BD, 0x1603, 0x1712, 0x24D4, 0x31D5, 0x3D0D, 0x4261, 0x48ED, 0x4F19, 0x547B, 0x592C, 0x5AAD, 0x5E90, 0x606D, 0x9B40, 0x9D61, 0xA330, 0xA4AD, 0xACFB, 0xB14D, 0xB5F1, 0xBEA0, 0xC0C1, 0xC46D, 0xC869, 0xCCB1, 0xDF80, 0xE0FD, 0xE2CC, 0xE48B, 0xF58C
		, 0x000D, 0x1592, 0x2604, 0x32B5, 0x3D08, 0x3FB7, 0x4018, 0x411D, 0x43D0, 0x484D, 0x4E29, 0x534B, 0x5B8C, 0x5D3D, 0x9DF0, 0x9F51, 0xA4D0, 0xA5DD, 0xAE1B, 0xB23D, 0xB651, 0xB9BD, 0xC0F1, 0xC40D, 0xC9DA, 0xCC41, 0xDFC0, 0xE12D, 0xE33B, 0xEFEC, 0xF2FD
		, 0x000D, 0x1653, 0x1852, 0x2764, 0x3345, 0x3D17, 0x416D, 0x484A, 0x4B9D, 0x4D39, 0x527B, 0x5C5C, 0x5DAD, 0x9FB0, 0xA151, 0xA3A0, 0xA54D, 0xAEDB, 0xB2CD, 0xB6B1, 0xBA0D, 0xBD90, 0xC131, 0xC3D0, 0xC5DD, 0xCBB1, 0xDDD0, 0xDECD, 0xE3BB, 0xEBFC, 0xEE4D
		, 0x000D, 0x1913, 0x1AA2, 0x28C4, 0x33C5, 0x3D27, 0x4148, 0x450D, 0x4829, 0x519B, 0x5AFC, 0x5C3D, 0xA190, 0xA2DD, 0xAFAB, 0xB37D, 0xB731, 0xBA5D, 0xBE11, 0xC8C0, 0xCB41, 0xD4B0, 0xD5A1, 0xD870, 0xD96D, 0xDA50, 0xDBE1, 0xDC30, 0xDD7D, 0xE14C, 0xE28B, 0xE8CC, 0xEAAD
		, 0x000D, 0x1B93, 0x1D12, 0x29A4, 0x3475, 0x3D27, 0x46B9, 0x50AB, 0x59AC, 0x5ADD, 0xB08B, 0xB3DD, 0xB7C1, 0xBA7D, 0xBE01, 0xD000, 0xD261, 0xD3A0, 0xD48D, 0xD6E0, 0xD82D, 0xDB2C, 0xDD8D, 0xDF5C, 0xE08B, 0xE5EC, 0xE7BD
		, 0x000D, 0x1D83, 0x1EA2, 0x2AC4, 0x34E5, 0x3D57, 0x4649, 0x4FDB, 0x588C, 0x596D, 0xB10B, 0xB48D, 0xB7F1, 0xBADD, 0xBE01, 0xCFBD, 0xD370, 0xD3BD, 0xD78B, 0xD8AC, 0xDAFB, 0xDE2C, 0xDF0B, 0xE3FC, 0xE56D
		, 0x000D, 0x1F53, 0x2072, 0x2B84, 0x3545, 0x3D97, 0x4629, 0x4F5B, 0x575C, 0x583D, 0xA8E0, 0xAA41, 0xAAD0, 0xABAD, 0xB1CB, 0xB4DD, 0xB821, 0xBAFD, 0xBE41, 0xCF2D, 0xD351, 0xD500, 0xD6AB, 0xE20C, 0xE32D
		, 0x000D, 0x20C3, 0x21D2, 0x2C74, 0x35C5, 0x3D87, 0x4609, 0x4E9B, 0x571D, 0xA7D1, 0xAC5D, 0xB23B, 0xB52D, 0xB891, 0xBB4D, 0xC121, 0xCE7D, 0xD271, 0xD5AB, 0xE09C, 0xE1AD
		, 0x000D, 0x2213, 0x2312, 0x2D24, 0x3AD5, 0x4257, 0x4A19, 0x4E3B, 0x563D, 0xA8C1, 0xAC60, 0xAD2D, 0xB29B, 0xB5AD, 0xB8C1, 0xBB5D, 0xBE30, 0xC101, 0xC310, 0xC631, 0xCDED, 0xD1CB, 0xD421, 0xD4EB, 0xDF3C, 0xE00D
		, 0x000D, 0x2383, 0x2442, 0x2DF4, 0x2F32, 0x32B4, 0x3AE5, 0x4217, 0x4A19, 0x4DC0, 0x4F8B, 0x54CC, 0x557D, 0xA900, 0xA9C1, 0xADBD, 0xB33B, 0xB5ED, 0xB921, 0xBB6D, 0xBE61, 0xC31D, 0xC611, 0xCD8D, 0xD10B, 0xDDBC, 0xDE7D
		, 0x000D, 0x24A3, 0x2562, 0x3304, 0x3B35, 0x4227, 0x49D9, 0x517B, 0x549D, 0xAA61, 0xACD0, 0xAE0D, 0xB38C, 0xB3CD, 0xB941, 0xBBAD, 0xBE51, 0xC2ED, 0xC5F1, 0xCCFD, 0xD08B, 0xDC8C, 0xDD3D
		, 0x000D, 0x25B3, 0x2662, 0x3374, 0x3B25, 0x4227, 0x4969, 0x511B, 0x541C, 0x557D, 0xAAB0, 0xABED, 0xB961, 0xBBBD, 0xBE41, 0xCC8D, 0xD00B, 0xDB6C, 0xDC2D
		, 0x000D, 0x2683, 0x2722, 0x28F3, 0x2A1D, 0x2BE2, 0x3404, 0x3B75, 0x41F7, 0x4929, 0x509B, 0x563C, 0x572D, 0xB9C1, 0xBC0D, 0xBE71, 0xC2C0, 0xC571, 0xCC70, 0xCE3D, 0xCF5C, 0xD07B, 0xDA6C, 0xDB1D
		, 0x000D, 0x2773, 0x281D, 0x2C03, 0x2CB2, 0x3454, 0x3B85, 0x41D7, 0x48D9, 0x500B, 0x569C, 0x573D, 0xBA01, 0xBBFD, 0xC0C1, 0xC2BD, 0xC559, 0xC7B1, 0xCE8D, 0xD11C, 0xD23B, 0xD96C, 0xDA0D
		, 0x000D, 0x2D32, 0x34A4, 0x3BA5, 0x41C7, 0x4899, 0x4F9B, 0x55CC, 0x566D, 0xBA21, 0xBC1D, 0xC0B1, 0xC2AD, 0xC539, 0xC7B1, 0xCE1D, 0xD33C, 0xD47B, 0xD66C, 0xD70D, 0xD73C, 0xD84B, 0xD8BC, 0xD92D
		, 0x000D, 0x2DA2, 0x3514, 0x3BE5, 0x41D7, 0x4839, 0x4F0B, 0x559D, 0xBA31, 0xC2AD, 0xC66A, 0xC791, 0xCE90, 0xCF6D, 0xD53C, 0xD63D
		, 0x000D, 0x2E22, 0x3554, 0x3BF5, 0x41B7, 0x4829, 0x4EBB, 0x54ED, 0xBA71, 0xC2AD, 0xC7A1, 0xCF7D
		, 0x000D, 0x2EC2, 0x3594, 0x3C05, 0x41B7, 0x47F9, 0x4E2B, 0x53DC, 0x546D, 0xBCB1, 0xBEEB, 0xC231, 0xC580, 0xC741, 0xCED0, 0xCFDD
		, 0x000D, 0x2F32, 0x35D4, 0x3C15, 0x4197, 0x47A9, 0x4DBB, 0x533C, 0x53DD, 0xBCD1, 0xBDD0, 0xBEFB, 0xC221, 0xD06D
		, 0x000D, 0x2FC2, 0x3634, 0x3C45, 0x41A7, 0x4769, 0x4D7B, 0x532D, 0xBF1B, 0xC231, 0xC7B0, 0xC9C1, 0xD00D
		, 0x000D, 0x3022, 0x3674, 0x3C45, 0x41A7, 0x4749, 0x4D0B, 0x52AD, 0xBF0B, 0xC271, 0xC7BD, 0xCB50, 0xCD11, 0xCFAD
		, 0x000D, 0x3072, 0x36A4, 0x3C75, 0x4187, 0x4729, 0x4CCB, 0x523D, 0xC5D0, 0xC76D, 0xCE40, 0xCF2D
		, 0x000D, 0x30F2, 0x36F4, 0x3C75, 0x4197, 0x46E9, 0x4C5B, 0x51AD
		, 0x000D, 0x3152, 0x3734, 0x3C85, 0x4167, 0x46C9, 0x4C2B, 0x513D
		, 0x000D, 0x3162, 0x3724, 0x3C95, 0x4177, 0x4689, 0x4BCB, 0x50DD
	}; // 1550 bytes

	const uint16_t row_ends[] PROGMEM {		
		0x0009, 0x001A, 0x002E, 0x0048, 0x005F, 0x0074, 0x008E, 0x00A8, 
		0x00C6, 0x00E3, 0x0103, 0x0126, 0x0145, 0x0164, 0x0185, 0x01A0, 
		0x01B9, 0x01D2, 0x01E7, 0x0201, 0x021C, 0x0233, 0x0246, 0x025E, 
		0x0275, 0x028D, 0x029D, 0x02A9, 0x02B9, 0x02C7, 0x02D4, 0x02E2, 
		0x02EE, 0x02F6, 0x02FE, 0x0306
	}; // 72 bytes
}

class NyanCat2 : public Image {
public:
	NyanCat2() {
		Image::Initialise();
	}
protected:
	inline uint16_t get_arc(uint16_t i) override {
		return pgm_read_word(&NyanCat2Data::arcs[i]);
	}

	inline uint16_t get_row_end(uint8_t row_index) override {
		return pgm_read_word(&NyanCat2Data::row_ends[row_index]);
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
