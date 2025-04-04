#ifndef I2S_H_
#define I2S_H_

// #include "common/tusb_common.h"
#include "i2s_pio.h"

#include <stdint.h>

struct I2sPIO {
  PIO pio;
  uint32_t sm;
  uint32_t offset;
};

void i2s_configure_pio(struct I2sPIO *i2s_pio, uint32_t start_pin, uint32_t bit_depth,
                       uint32_t sample_rate) {
  PIO *pio_ptr = &i2s_pio->pio;
  uint32_t *sm_ptr = &i2s_pio->sm;
  uint32_t *offset_ptr = &i2s_pio->offset;
  
  bool success = pio_claim_free_sm_and_add_program_for_gpio_range(
      &i2s_pio_program, pio_ptr, sm_ptr, offset_ptr, start_pin, 3, false);
  hard_assert(success);

  // Load and configure PIO program
  pio_sm_config c = i2s_pio_program_get_default_config(*offset_ptr);

  // Configure side-set, wrap, etc.
  sm_config_set_sideset(&c, 2, false, false);
  pio_sm_init(*pio_ptr, *sm_ptr, *offset_ptr, &c);

  // Send instruction to set X dynamically
  pio_sm_exec(*pio_ptr, *sm_ptr, pio_encode_set(pio_x, bit_depth - 1));
  pio_sm_exec(*pio_ptr, *sm_ptr, pio_encode_set(pio_y, bit_depth - 1));

  // Enable PIO state machine
  pio_sm_set_enabled(*pio_ptr, *sm_ptr, true);

  // Set the PIO clock divider
  // Example: Set the PIO clock to 1 MHz (clk_sys = 125 MHz)
  float divider = (float)clock_get_hz(clk_sys) /
                  (float)sample_rate; // calculate the divider
  pio_sm_set_clkdiv(*pio_ptr, *sm_ptr, divider);
}

void i2s_put_8bits(struct I2sPIO *i2s_pio, uint8_t sample) {
  for (int i = 8 - 1; i >= 0; --i) {
    pio_sm_put_blocking(i2s_pio->pio, i2s_pio->sm, (sample >> i) & 0x01);
  }
}

void i2s_put_16bits(struct I2sPIO *i2s_pio, uint16_t sample) {
  for (int i = 16 - 1; i >= 0; --i) {
    pio_sm_put_blocking(i2s_pio->pio, i2s_pio->sm, (sample >> i) & 0x01);
  }
}

void i2s_put_24bits(struct I2sPIO *i2s_pio, int32_t sample) {
  for (int i = 24 - 1; i >= 0; --i) {
    pio_sm_put_blocking(i2s_pio->pio, i2s_pio->sm, (sample >> i) & 0x01);
  }
}

void i2s_put_32bits(struct I2sPIO *i2s_pio, int32_t sample) {
  for (int i = 32 - 1; i >= 0; --i) {
    pio_sm_put_blocking(i2s_pio->pio, i2s_pio->sm, (sample >> i) & 0x01);
  }
}

#endif
