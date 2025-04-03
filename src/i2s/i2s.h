#ifndef I2S_H_
#define I2S_H_

#include "i2s_pio.h"

#include <stdint.h>

 static PIO pio;
 static uint32_t sm;

void i2s_configure_pio(uint32_t bit_depth, uint32_t sample_rate) {
    // Load and configure PIO program
    uint32_t offset = pio_add_program(pio, &i2s_pio_program);
    pio_sm_config c = i2s_pio_program_get_default_config(offset);
    
    // Configure side-set, wrap, etc.
    sm_config_set_sideset(&c, 2, false, false);
    pio_sm_init(pio, sm, offset, &c);

    // Send instruction to set X dynamically
    pio_sm_exec(pio, sm, pio_encode_set(pio_x, bit_depth - 1));
    pio_sm_exec(pio, sm, pio_encode_set(pio_y, bit_depth - 1));

    // Enable PIO state machine
    pio_sm_set_enabled(pio, sm, true);

    // Set the PIO clock divider
    // Example: Set the PIO clock to 1 MHz (clk_sys = 125 MHz)
    float divider = (float)clock_get_hz(clk_sys) / (float)sample_rate; //calculate the divider
    pio_sm_set_clkdiv(pio, sm, divider);
}

void i2s_put_8(uint8_t sample) {
    for (int i = 8 - 1; i >= 0; --i) {
        pio_sm_put_blocking(pio, sm, (sample >> i) & 0x01);
    }
}

void i2s_put_16(uint16_t sample) {
    for (int i = 16 - 1; i >= 0; --i) {
        pio_sm_put_blocking(pio, sm, (sample >> i) & 0x01);
    }
}

void i2s_put_24(int32_t sample) {
    for (int i = 24 - 1; i >= 0; --i) {
        pio_sm_put_blocking(pio, sm, (sample >> i) & 0x01);
    }
}


void i2s_put_32(int32_t sample) {
    for (int i = 32 - 1; i >= 0; --i) {
        pio_sm_put_blocking(pio, sm, (sample >> i) & 0x01);
    }
}

#endif
