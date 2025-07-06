#include "i2s.h"

#include "i2s.pio.h"

#include "hardware/clocks.h"
#include "tusb.h"

static struct I2sPIO g_i2s_pio = {};

struct I2sPIO* get_pio() { return &g_i2s_pio; }

void i2s_configure_pio(struct I2sPIO *i2s_pio, uint32_t start_pin,
                       uint32_t bit_depth, uint32_t sample_rate) {
  PIO *pio_ptr = &i2s_pio->pio;
  uint *sm_ptr = &i2s_pio->sm;
  uint *offset_ptr = &i2s_pio->offset;

  bool success = pio_claim_free_sm_and_add_program_for_gpio_range(
      &i2s_pio_out_program, pio_ptr, sm_ptr, offset_ptr, start_pin, 3, true);
  TU_LOG1("pio_claim_free_sm_and_add_program_for_gpio_range %d!\n", success);
  hard_assert(success);

  i2s_set_sampling_rate(i2s_pio, sample_rate);

  // Load and configure PIO program
  pio_i2s_out_program_init(*pio_ptr, *sm_ptr, *offset_ptr, 9, 10, bit_depth);
}

void i2s_set_sampling_rate(struct I2sPIO *i2s_pio, uint32_t sample_rate) {
  (void)i2s_pio;
  (void)sample_rate;
  PIO *pio_ptr = &i2s_pio->pio;
  uint *sm_ptr = &i2s_pio->sm;
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
  pio_sm_put_blocking(i2s_pio->pio, i2s_pio->sm,(uint32_t)sample);
}