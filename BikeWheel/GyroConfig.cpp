#include "./GyroConfig.h"

/* Local static variables moved here so they can be saved / restored
 * to/from eeprom as a block
 */
#define EEPROM_VER 1
#define EEPROM_MAGIC (0x00abcdef + EEPROM_VER)

GyroConfig::GyroConfig()
    : magic(EEPROM_MAGIC)
    , prog(0)
    , gyro_multiplier(1 << 14)
    , cf_samples(0)
    , cf_acc{ 50.0f * 65536 * 16, -150.0f * 65536 * 16 } {
}

void GyroConfig::load(void) {
#if USE_EEPROM == true
    eeprom_read_block(&config, NULL, sizeof(config));
#endif
    if (magic != EEPROM_MAGIC) {
        /* No saved config found, reset the config */
        magic = EEPROM_MAGIC;
        prog = 0;
        gyro_multiplier = 1 << 14;
        cf_acc[0] = 50.0f * 65536 * 16;
        cf_acc[1] = -150.0f * 65536 * 16;
        cf_samples = 0;
    }
}

void GyroConfig::save(void) const {
#if USE_EEPROM == true
    if (!(abs(config.gyro_mult - prev_config.gyro_mult) < 40)) {
        return;
    }

    eeprom_write_block(&config, NULL, sizeof(config));

    prev_config = config;
#endif
}
