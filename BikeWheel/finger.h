#pragma once
#include <avr/pgmspace.h>
#include "Image.h"
namespace finger_data {
	const uint16_t arcs[] PROGMEM {
		  0x0000, 0x1A65, 0x1C06, 0x1CC2, 0x2596, 0x2665, 0x2736, 0x2804, 0x2B33, 0x2F30, 0x3003, 0x3260, 0x34C3, 0x3804, 0x3990, 0xE005, 0xE0C2, 0xEB34, 0xEC00
		, 0x0000, 0x1523, 0x15E4, 0x1695, 0x1816, 0x18C2, 0x1D26, 0x1DE5, 0x1EA4, 0x2183, 0x23B0, 0xDFE6, 0xE0A2, 0xEA15, 0xEAD3, 0xEB90
		, 0x0000, 0x11C4, 0x1265, 0x13B6, 0x1462, 0x1905, 0x19A4, 0x1AF3, 0x1C40, 0xDF14, 0xDFC2, 0xE995, 0xEA40
		, 0x0000, 0x0EF3, 0x0F95, 0x10C6, 0x1162, 0x1625, 0x16C4, 0x1763, 0x1890, 0xDE64, 0xDF06, 0xDFA2, 0xEA64, 0xEB00
		, 0x0000, 0x0D64, 0x0DF5, 0x0E86, 0x0F12, 0x14A6, 0x1533, 0x15C0, 0xDD54, 0xDDE6, 0xDE72, 0xE5B6, 0xE644, 0xE6D6, 0xE762, 0xEAC6, 0xEB50
		, 0x0000, 0x0BD5, 0x0C66, 0x0CE2, 0x14A6, 0x1525, 0x15A4, 0x16B0, 0x6AD3, 0x6B54, 0x6F73, 0x7000, 0xDBD4, 0xDC65, 0xDCE6, 0xDD62, 0xE396, 0xE424, 0xE523, 0xE5A0, 0xE734, 0xE7B6, 0xE842, 0xEBD5, 0xEC60
		, 0x0000, 0x0A85, 0x0B06, 0x0B82, 0x0E64, 0x1045, 0x1142, 0x1776, 0x18E5, 0x1AD4, 0x1C43, 0x1D30, 0x6A64, 0x6AE2, 0x7026, 0x70A4, 0x7123, 0x7190, 0xDA24, 0xDA95, 0xDB96, 0xDC02, 0xE156, 0xE1C5, 0xE244, 0xE330, 0xE803, 0xE886, 0xE8F2, 0xEC56, 0xECD3, 0xED40
		, 0x0000, 0x0904, 0x0985, 0x09F2, 0x0CA5, 0x0D23, 0x0D90, 0x11A3, 0x1294, 0x1465, 0x15B2, 0x1DE6, 0x1FB5, 0x2184, 0x2430, 0x6AE4, 0x6B65, 0x6BD6, 0x6C42, 0x7145, 0x71B4, 0x7220, 0x7BB3, 0x7C25, 0x7C92, 0x7ED6, 0x7F55, 0x7FC4, 0x8030, 0xD7A4, 0xD895, 0xD976, 0xD9F2, 0xDF65, 0xDFD4, 0xE0B3, 0xE1A0, 0xE8E3, 0xE955, 0xE9C2, 0xECF6, 0xED64, 0xEDE0
		, 0x0000, 0x0814, 0x0876, 0x08E2, 0x0B76, 0x0BE4, 0x0C40, 0x1613, 0x1754, 0x1975, 0x1B92, 0x24E6, 0x26A5, 0x28C4, 0x2A03, 0x2A74, 0x2AE3, 0x2B40, 0x6CA4, 0x6D15, 0x6D86, 0x6DF2, 0x72A4, 0x7300, 0x7BF2, 0x7FC5, 0x8030, 0xB393, 0xB406, 0xB463, 0xB4D0, 0xD444, 0xD585, 0xD666, 0xD732, 0xDCC5, 0xDD94, 0xDE73, 0xDF40, 0xE9E5, 0xEA52, 0xEDB5, 0xEE20
		, 0x0000, 0x0796, 0x0802, 0x0AC4, 0x0B33, 0x0B90, 0x1CC3, 0x1E64, 0x1EC3, 0x1F34, 0x2265, 0x2402, 0x2466, 0x24C2, 0x2C66, 0x2E65, 0x3204, 0x32C3, 0x3330, 0x3404, 0x3460, 0x6E64, 0x6EC5, 0x6F36, 0x6F92, 0x7335, 0x7390, 0x7C06, 0x7C62, 0x7F34, 0x7F90, 0xB203, 0xB264, 0xB2C5, 0xB332, 0xB463, 0xB4C0, 0xCE63, 0xCEC4, 0xD135, 0xD2C6, 0xD392, 0xD995, 0xDAC4, 0xDB93, 0xDC60, 0xEA64, 0xEAC2, 0xEE64, 0xEEC0
		, 0x0000, 0x0673, 0x06D5, 0x0732, 0x09E6, 0x0A43, 0x0AA0, 0x25B3, 0x2794, 0x2B05, 0x2C32, 0x3676, 0x3985, 0x3B04, 0x3B63, 0x3ED0, 0x6553, 0x65B4, 0x6733, 0x6800, 0x6F94, 0x7065, 0x70C2, 0x73C5, 0x7433, 0x7490, 0x7C36, 0x7C92, 0x7ED0, 0xB0C3, 0xB124, 0xB182, 0xB3C6, 0xB430, 0xBCF4, 0xC2A5, 0xCAA6, 0xCDB2, 0xD496, 0xD4F5, 0xD614, 0xD803, 0xD920, 0xEB04, 0xEB62, 0xEED5, 0xEF30
		, 0x0000, 0x05C3, 0x0625, 0x0672, 0x0905, 0x0963, 0x09B0, 0x2E33, 0x3064, 0x33A5, 0x3456, 0x34B2, 0x35C5, 0x3622, 0x40A6, 0x40F5, 0x4324, 0x4663, 0x4890, 0x64B5, 0x6516, 0x6572, 0x67F6, 0x6855, 0x68B4, 0x6963, 0x69C0, 0x70A3, 0x7104, 0x7165, 0x71B6, 0x7212, 0x7445, 0x74A4, 0x74F0, 0x7C35, 0x7C92, 0x7E63, 0x7EB0, 0xAF13, 0xAF74, 0xB032, 0xB375, 0xB3D4, 0xB7C6, 0xB932, 0xC866, 0xC8C5, 0xC916, 0xC975, 0xCD14, 0xD0B3, 0xD104, 0xD163, 0xD3F0, 0xEB64, 0xEBC2, 0xEF06, 0xEF64, 0xEFC0
		, 0x0000, 0x0575, 0x05D2, 0x0894, 0x08E0, 0x37D3, 0x3830, 0x3883, 0x3A95, 0x3AF3, 0x3BF4, 0x3EB5, 0x3FB4, 0x4012, 0x4956, 0x4A05, 0x4B04, 0x4D73, 0x4ED0, 0x65C3, 0x6624, 0x66C5, 0x6776, 0x6822, 0x6A35, 0x6A94, 0x6AE3, 0x6B90, 0x7214, 0x72C6, 0x7322, 0x74D6, 0x7533, 0x7580, 0x7C66, 0x7CB2, 0x7DC6, 0x7E10, 0xAD13, 0xADC4, 0xAE15, 0xAE62, 0xB076, 0xB125, 0xB2E4, 0xB3E5, 0xB9B6, 0xBA62, 0xBEE5, 0xBF34, 0xC043, 0xC4B0, 0xC503, 0xC5B0, 0xEBC3, 0xEC15, 0xEC72, 0xEF86, 0xEFE4, 0xF030
		, 0x0000, 0x04E5, 0x0542, 0x07E4, 0x0833, 0x0880, 0x41B3, 0x4264, 0x4505, 0x47F6, 0x4992, 0x4F86, 0x4FD5, 0x5124, 0x5323, 0x5420, 0x6884, 0x6925, 0x69D6, 0x6A22, 0x6BC5, 0x6C14, 0x6C73, 0x6CC0, 0x7354, 0x73A5, 0x7406, 0x7452, 0x7556, 0x75A3, 0x75F0, 0x7C86, 0x7CE2, 0x7D84, 0x7DD0, 0xAB33, 0xAB84, 0xAC86, 0xAD85, 0xAED4, 0xAF73, 0xAFD0, 0xBA53, 0xBAA6, 0xBAF2, 0xBDF5, 0xBE44, 0xBE90, 0xEC43, 0xEC96, 0xECF2, 0xEFE6, 0xF034, 0xF080
		, 0x0000, 0x0464, 0x04B2, 0x0783, 0x07D0, 0x4A53, 0x4AF4, 0x4C85, 0x4E16, 0x4F52, 0x54B6, 0x5505, 0x55F4, 0x57D3, 0x58C0, 0x6AA4, 0x6B45, 0x6BE6, 0x6C32, 0x6D24, 0x6DC3, 0x6E10, 0x7414, 0x74B6, 0x7502, 0x75F4, 0x7640, 0x7C84, 0x7CD6, 0x7D25, 0x7D70, 0xAA53, 0xAAA4, 0xAB90, 0xB963, 0xB9B5, 0xBA06, 0xBA52, 0xBD26, 0xBD73, 0xBDC0, 0xECD6, 0xED22, 0xF056, 0xF0A4, 0xF0F0
		, 0x0000, 0x03E3, 0x0436, 0x0472, 0x06E5, 0x0730, 0x5003, 0x5054, 0x5225, 0x5356, 0x5482, 0x59A5, 0x5A84, 0x5C53, 0x5D80, 0x6C84, 0x6D15, 0x6DB6, 0x6E54, 0x6EE3, 0x6F30, 0x74E3, 0x7534, 0x7585, 0x75C6, 0x7615, 0x7660, 0xB7C3, 0xB854, 0xB8F6, 0xB942, 0xBB56, 0xBBF4, 0xBC43, 0xBC80, 0xED14, 0xED66, 0xEDB2, 0xF0B6, 0xF104, 0xF140
		, 0x0000, 0x03C6, 0x0402, 0x0654, 0x06A3, 0x06F0, 0x5553, 0x5594, 0x56C5, 0x5836, 0x5912, 0x5E05, 0x5EE4, 0x5F25, 0x5F74, 0x6093, 0x6170, 0x6E74, 0x6F53, 0x6FA0, 0xB3A3, 0xB4C4, 0xB685, 0xB712, 0xB926, 0xB9F5, 0xBA94, 0xBAD0, 0xED74, 0xEDC2, 0xF134, 0xF180
		, 0x0000, 0x0355, 0x0392, 0x0613, 0x0660, 0x5994, 0x5B45, 0x5C56, 0x5D32, 0x61E6, 0x6225, 0x6304, 0x6423, 0x64F0, 0xAB23, 0xADA4, 0xB065, 0xB182, 0xB1C5, 0xB212, 0xB686, 0xB755, 0xB7E3, 0xB870, 0xEDB3, 0xEDF2, 0xF146, 0xF194, 0xF1D0
		, 0x0000, 0x0332, 0x0595, 0x05D0, 0x5D83, 0x5DC4, 0x5F15, 0x6026, 0x60F2, 0x6575, 0x66D4, 0x6823, 0x68F0, 0xA413, 0xA5F4, 0xA855, 0xA8E6, 0xA925, 0xA9B2, 0xB276, 0xB385, 0xB4E4, 0xB5A3, 0xB5F0, 0xEE24, 0xEE62, 0xF196, 0xF1E3, 0xF220
		, 0x0000, 0x0293, 0x02D6, 0x0312, 0x0525, 0x0563, 0x05A0, 0x6184, 0x6295, 0x63D6, 0x64E2, 0x6986, 0x69C5, 0x6AD4, 0x6C63, 0x6DE0, 0x9E73, 0xA004, 0xA185, 0xA292, 0xA2D5, 0xA312, 0xA946, 0xACA5, 0xACE6, 0xAD25, 0xAF74, 0xB140, 0xEE73, 0xEEB2, 0xF214, 0xF250
		, 0x0000, 0x0275, 0x02B2, 0x04F3, 0x0530, 0x6523, 0x6564, 0x66E5, 0x6866, 0x69A2, 0x6E96, 0x6F15, 0x7054, 0x7393, 0x7680, 0x98D3, 0x9A54, 0x9C55, 0x9D92, 0xA106, 0xA245, 0xA444, 0xA5C3, 0xA604, 0xA680, 0xA6C4, 0xA740, 0xA783, 0xA7C0, 0xEED4, 0xEF12, 0xF255, 0xF290
		, 0x0000, 0x0224, 0x0262, 0x0485, 0x04C0, 0x6A64, 0x6C95, 0x6EB6, 0x7252, 0x7296, 0x72D2, 0x77D6, 0x7812, 0x7856, 0x7895, 0x78C6, 0x7905, 0x7C24, 0x7CE5, 0x7D14, 0x8313, 0x8394, 0x83D3, 0x8414, 0x8453, 0x8630, 0x9363, 0x9554, 0x9705, 0x97B6, 0x97F2, 0x9D06, 0x9DF5, 0x9F24, 0x9FE3, 0xA010, 0xEF34, 0xEF76, 0xEFB2, 0xF295, 0xF2D0
		, 0x0000, 0x01D4, 0x0212, 0x0435, 0x0460, 0x7404, 0x74B5, 0x7526, 0x75A2, 0x7956, 0x7995, 0x7C96, 0x7CD5, 0x7D56, 0x7F22, 0x7FA6, 0x7FE2, 0x8795, 0x8A24, 0x9065, 0x91D6, 0x9202, 0x9246, 0x9282, 0x99F6, 0x9AA5, 0x9B94, 0x9C43, 0x9C80, 0xEF73, 0xEFB4, 0xEFE2, 0xF2B6, 0xF2F0
		, 0x0000, 0x01C6, 0x0202, 0x0403, 0x0440, 0x75C4, 0x7635, 0x76E6, 0x7712, 0x79C5, 0x7A44, 0x7AB3, 0x7B20, 0x8133, 0x81E4, 0x8545, 0x8584, 0x85F5, 0x91E4, 0x9215, 0x9254, 0x9295, 0x9306, 0x93B2, 0x9786, 0x97F5, 0x98E4, 0x9983, 0x99C0, 0xF003, 0xF035, 0xF072, 0xF325, 0xF363, 0xF390
		, 0x0000, 0x0186, 0x01B2, 0x03B4, 0x03E0, 0x7774, 0x7825, 0x78C6, 0x7932, 0x7B36, 0x7B65, 0x7C14, 0x7C83, 0x7D60, 0x9023, 0x90C4, 0x91E5, 0x9252, 0x94E6, 0x9595, 0x9634, 0x9710, 0xF084, 0xF0B5, 0xF0F2, 0xF356, 0xF395, 0xF3C3, 0xF400
		, 0x0000, 0x0104, 0x0146, 0x0172, 0x0326, 0x0364, 0x0390, 0x7963, 0x79A4, 0x7A45, 0x7AE6, 0x7B82, 0x7DA6, 0x7DE5, 0x7E44, 0x7F53, 0x7FC4, 0x8003, 0x80A0, 0x8BE3, 0x8D94, 0x8ED5, 0x8F46, 0x8F72, 0x9246, 0x9315, 0x93F4, 0x9490, 0xF0E3, 0xF124, 0xF156, 0xF192, 0xF3E6, 0xF414, 0xF450
		, 0x0000, 0x0093, 0x00D5, 0x0102, 0x02E6, 0x0313, 0x0340, 0x7C14, 0x7D15, 0x7E26, 0x7EF2, 0x8176, 0x81D5, 0x8A46, 0x8AB2, 0x8AE6, 0x8B12, 0x8E36, 0x8F65, 0x90A4, 0x91B0, 0xF194, 0xF1C5, 0xF202, 0xF475, 0xF4A4, 0xF4E0
		, 0x0000, 0x0034, 0x0066, 0x0092, 0x0266, 0x0293, 0x02C0, 0x7FB3, 0x8014, 0x82E5, 0x8344, 0x83E5, 0x89B4, 0x89E5, 0x8A14, 0x8D10, 0x8D73, 0x8DB0, 0xF203, 0xF234, 0xF265, 0xF292, 0xF505, 0xF534, 0xF563, 0xF590
		, 0x0002, 0x01C5, 0x01F4, 0x0223, 0x0250, 0xF2B3, 0xF2E4, 0xF325, 0xF352, 0xF5A5, 0xF604, 0xF640, 0xFF03, 0xFF35, 0xFF96
		, 0x0002, 0x0126, 0x0154, 0x0183, 0x01B0, 0xF343, 0xF3A4, 0xF3D5, 0xF402, 0xF656, 0xF685, 0xF6E4, 0xF740, 0xFDE4, 0xFE45, 0xFEA6, 0xFED2
		, 0x0002, 0x0056, 0x0084, 0x00E3, 0x0110, 0xF433, 0xF464, 0xF4B5, 0xF512, 0xF786, 0xF7B5, 0xF844, 0xF953, 0xF9B0, 0xFA43, 0xFA70, 0xFB04, 0xFCA5, 0xFD36, 0xFD92
		, 0x0003, 0x0020, 0xF523, 0xF584, 0xF5E5, 0xF646, 0xF672, 0xFF15, 0xFF44
		, 0x0000, 0xF683, 0xF704, 0xF7B5, 0xF876, 0xF8C2, 0xFD05, 0xFDB4, 0xFE63, 0xFEC0
		, 0x0000, 0xF923, 0xF950, 0xF973, 0xFC30
		, 0x0000
		, 0x0000
	}; // 2080 bytes

	const uint16_t row_ends[] PROGMEM {
		0x0012, 0x0022, 0x002F, 0x003D, 0x004E, 0x0067, 0x0087, 0x00B2, 0x00DD, 0x010F, 0x013E, 0x017A, 0x01B6, 0x01EC, 0x021A, 0x0243, 0x0263, 0x0280, 0x029D, 0x02BD, 0x02DE, 0x0307, 0x0329, 0x034C, 0x0369, 0x038C, 0x03A7, 0x03C1, 0x03D0, 0x03E1, 0x03F5, 0x03FE, 0x0408, 0x040D, 0x040E, 0x040F
	}; // 72 bytes
	const uint32_t colors[] PROGMEM {
		0x00000000, 0x00FF0000, 0x00FFFFFF, 0x00333333, 0x00666666, 0x00999999, 0x00CCCCCC, 0x00330000, 0x00660000, 0x00990000, 0x00CC0000, 0x00FF3333, 0x00FF6666, 0x00FF9999, 0x00FFCCCC
	}; // 60 bytes
}

class finger : public Image {
protected:
	inline uint16_t get_arc(uint16_t i) override {
		return pgm_read_word(&finger_data::arcs[i]);
	}

	inline uint16_t get_row_end(uint8_t row_index) override {
		return pgm_read_word(&finger_data::row_ends[row_index]);
	}

protected:
	const uint32_t angle_mask = 0xFFF0;
	const uint32_t color_mask = 0x000F;

	inline uint16_t get_angle(uint16_t arc) override {
		return arc & angle_mask;
	}

	inline uint32_t get_color(uint16_t arc) override {
		return pgm_read_dword(&finger_data::colors[arc & color_mask]);
	}
};
