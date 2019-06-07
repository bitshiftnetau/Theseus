/*
 * efm32zg_timer_HAL.h
 *
 *  Created on: Jan 16, 2019
 *      Author: access
 */

#ifndef EFM32ZG_TIMER_HAL_H_
#define EFM32ZG_TIMER_HAL_H_

#include <stdint.h>

#include "efm32zg222f32.h"
#include "efm32zg_types_HAL.h"

#define TIMER_READ_WRITE_CLEAR 3
#define TIMER_CHANNEL_0 0
#define TIMER_CHANNEL_1 0
#define TIMER_CHANNEL_2 0

int (*const *const timer_config_table[PERIPH_REGISTER_TABLE_MEMBERS])();

int(* timer_cc1_ccvp_table[1])();
int(* timer_cc2_ccvp_table[1])();
int(* timer_cc0_ccvp_table[1])();
int(* timer_cmd_table[1])();
int(* timer_status_table[1])();


#endif
