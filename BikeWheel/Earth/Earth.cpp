/*
 * Rotating globe attempt
 *
 * Lots of tabularised trig here, all of it only valid for the current
 * set of LED positions.  Any change and all of this data needs to be
 * regenerated.
 */

#if 0
#include <avr/pgmspace.h>
#include "./Leds.h"

extern const uint8_t a_d_to_lon_data[];
extern const uint8_t a_d_to_y_data[];
extern const uint8_t y_lon_to_land[];

static inline uint8_t a_d_to_lon(uint16_t angle, uint8_t dist) opts;
static inline uint8_t a_d_to_lon(uint16_t angle, uint8_t dist) {
	uint8_t a = angle >> 7;
	uint8_t ret;

	if (!a)
		return 0;
	if (a > 128)
		a = ~a;
	else
		a -= 1;
	ret = pgm_read_byte(&a_d_to_lon_data[a | ((uint16_t) dist << 7)]);

	return (angle >> 15) ? -ret : ret;
}

static inline uint8_t a_d_to_y(uint16_t angle, uint8_t dist) {
	uint8_t a = angle >> 7;
	uint8_t ret;

	if (a == 128)
		return 32;
	if (a > 128)
		a = -a;
	ret = pgm_read_byte(&a_d_to_y_data[a | ((uint16_t) dist << 7)]);

	return 32 + ((((angle >> 14) ^ (angle >> 15)) & 1) ? ret : -ret);
}

static void prog_globe_set_leds(uint16_t zero_angle, RGB_t *rgb) {
	uint8_t secsby64 = Timers::now() >> 18;

	for (uint8_t i = 0, d = 0; i < led_cnt; i ++, d ++) {
		uint16_t angle = zero_angle - led_angle[i];

		if (d == 15)
			d = 0;

		uint8_t lon = -secsby64 - a_d_to_lon(angle, d);
		uint8_t y = a_d_to_y(angle, d);

		uint16_t addr = ((uint16_t) y << 8) | lon;
		bool land = (pgm_read_byte(&y_lon_to_land[addr >> 3]) >>
				(addr & 7)) & 1;

		if (land) {
			if (y > 8) {
				/* Green land */
				rgb[i].r = LED_ON / 3;
				rgb[i].g = LED_ON;
				rgb[i].b = LED_ON / 5;
			} else {
				/* Antarctica */
				rgb[i].r = LED_ON;
				rgb[i].g = LED_ON;
				rgb[i].b = LED_ON;
			}
		} else {
			/* Dark blue ocean */
			rgb[i].r = 0;
			rgb[i].g = 0;
			rgb[i].b = LED_ON / 5;
		}
	}
}
#endif