#ifndef I2S_H_
#define I2S_H_

// #include "common/tusb_common.h"

#include "hardware/pio.h"
#include <stdint.h>

struct I2sPIO {
  PIO pio;
  uint sm;
  uint offset;
};

struct I2sPIO* get_pio();

void i2s_configure_pio(struct I2sPIO *i2s_pio, uint32_t start_pin,
                       uint32_t bit_depth, uint32_t sample_rate);

void i2s_set_sampling_rate(struct I2sPIO *i2s_pio, uint32_t sample_rate);

void i2s_put_8bits(struct I2sPIO *i2s_pio, uint8_t sample);

void i2s_put_16bits(struct I2sPIO *i2s_pio, uint16_t sample);

void i2s_put_24bits(struct I2sPIO *i2s_pio, int32_t sample);

void i2s_put_32bits(struct I2sPIO *i2s_pio, int32_t sample);

#endif
