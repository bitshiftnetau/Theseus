#ifndef _EFM32ZG_CMU_HAL_H_
#define _EFM32ZG_CMU_HAL_H_

#include <stdbool.h>
#include <stdint.h>


#define CMU_HFRCO_FREQ_4MHZ		4000000
#define CMU_HFRCO_FREQ_7MHZ		7000000
#define CMU_HFRCO_FREQ_14MHZ	14000000
#define CMU_HFRCO_FREQ_21MHZ	21000000

#define CMU_HFXO_FREQ_24MHZ	24000000

#define CMU_1MHZ_TUNE_ADDR ((unsigned long*)0x0FE081DC)
#define CMU_7MHZ_TUNE_ADDR ((unsigned long*)0x0FE081DD)
#define CMU_11MHZ_TUNE_ADDR ((unsigned long*)0x0FE081DE)
#define CMU_14MHZ_TUNE_ADDR ((unsigned long*)0x0FE081DF)
#define CMU_21MHZ_TUNE_ADDR ((unsigned long*)0x0FE081E0)

#ifdef DEFAULT_HFRCO_1MHZ
  #define CMU_DEFAULT_BOOT_TUNE CMU_1MHZ_TUNE_ADDR
#endif
#ifdef DEFAULT_HFRCO_7MHZ
  #define CMU_DEFAULT_BOOT_TUNE CMU_7MHZ_TUNE_ADDR
#endif
#ifdef DEFAULT_HFRCO_11MHZ
  #define CMU_DEFAULT_BOOT_TUNE CMU_11MHZ_TUNE_ADDR
#endif
#ifdef DEFAULT_HFRCO_14MHZ
  #define CMU_DEFAULT_BOOT_TUNE CMU_14MHZ_TUNE_ADDR
#endif
#ifdef DEFAULT_HFRCO_21MHZ
  #define CMU_DEFAULT_BOOT_TUNE CMU_21MHZ_TUNE_ADDR
#endif

#define PERIPH_REGISTER_TABLE_MEMBERS 32

int (*const *const cmu_config_table[PERIPH_REGISTER_TABLE_MEMBERS])();

/*
 * Index defines for cmu_config_table are in the efm32zg_types_HAL.h file
 */


#endif
