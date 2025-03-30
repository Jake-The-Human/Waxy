#ifndef DEVICE_CONFIG_H_
#define DEVICE_CONFIG_H_

#include "common/tusb_common.h"

#include <stdint.h>

#define MANUFACTURER "Texas Instruments"
#define DAC_CHIP "PCM5102"
#define CHANNEL_CONFIGS (const int32_t[]){2}
#define BITS_PER_SAMPLE (const int32_t[]){16, 24, 32}
// #define SAMPLING_RATES (const int32_t[]){8000, 11025, 16000,  22050, 41000,  48000,  88200,  96000, 176400, 192000, 352800, 384000}
#define SAMPLING_RATES (const int32_t[]){8000, 11025, 16000,  22050, 41000,  48000,  88200,  96000}
#define N_CHANNEL_CONFIGS TU_ARRAY_SIZE(CHANNEL_CONFIGS)
#define N_BITS_PER_SAMPLE TU_ARRAY_SIZE(BITS_PER_SAMPLE)
#define N_SAMPLE_RATES TU_ARRAY_SIZE(SAMPLING_RATES)

#define MAX_CHANNEL_CONFIGS CHANNEL_CONFIGS[N_CHANNEL_CONFIGS - 1]
#define MAX_BIT_PER_SAMPLE BITS_PER_SAMPLE[N_BITS_PER_SAMPLE - 1]
#define MAX_SAMPLE_RATES SAMPLING_RATES[N_SAMPLING_RATES - 1]
#define MIN_CHANNEL_CONFIGS CHANNEL_CONFIGS[0]
#define MIN_BIT_PER_SAMPLE BITS_PER_SAMPLE[0]
#define MIN_SAMPLING_RATE SAMPLING_RATES[0]

static struct DacConfig {
  int32_t channels;
  int32_t bits_per_sample;
  int32_t sampling_rate;
} DAC_CONFIG = {.channels = 2, .bits_per_sample = 16, .sampling_rate = 41000};

#endif
