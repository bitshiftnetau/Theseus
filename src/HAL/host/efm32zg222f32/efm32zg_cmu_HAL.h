#ifndef _EFM32ZG_CMU_HAL_H_
#define _EFM32ZG_CMU_HAL_H_

#include <stdbool.h>
#include <stdint.h>

#define CMU_HFRCO_FREQ_4MHZ		4000000
#define CMU_HFRCO_FREQ_7MHZ		7000000
#define CMU_HFRCO_FREQ_14MHZ	14000000
#define CMU_HFRCO_FREQ_21MHZ	21000000
#define CMU_HFRCO_FREQ_24MHZ	24000000

#define PERIPH_REGISTER_TABLE_MEMBERS 32

int (*const *const cmu_config_table[PERIPH_REGISTER_TABLE_MEMBERS])();

/*
 * Index defines for cmu_config_table are in the efm32zg_types_HAL.h file
 */


#endif
