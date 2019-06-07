/*
 * efm32zg_gpio_HAL.h
 *
 *  Created on: Oct 5, 2018
 *      Author: access
 */


#ifndef EFM32ZG_GPIO_HAL_H_
#define EFM32ZG_GPIO_HAL_H_

#include <stdint.h>
#include "efm32zg_types_HAL.h"

#define GPIO_PERIPH_REGISTERS 			32

#define GPIO_INTERNAL_INT_CTRL_FNS 		5
#define GPIO_INTERNAL_INT_ENABLE_FLAG 	2

#define GPIO_EXTERNAL_INT_PIN_FNS 		2
#define GPIO_EXTERNAL_INT_HIGH_LOW 		2

#define GPIO_HIGH_LOW					2
#define SINGLE_FN_ARRAY					1

#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3
#define PORTE 4
#define PORTF 5

#define GPIO_P_PIN_NUMBER_0  (1UL << 0)
#define GPIO_P_PIN_NUMBER_1  (1UL << 1)
#define GPIO_P_PIN_NUMBER_2  (1UL << 2)
#define GPIO_P_PIN_NUMBER_3  (1UL << 3)
#define GPIO_P_PIN_NUMBER_4  (1UL << 4)
#define GPIO_P_PIN_NUMBER_5  (1UL << 5)
#define GPIO_P_PIN_NUMBER_6  (1UL << 6)
#define GPIO_P_PIN_NUMBER_7  (1UL << 7)

#define GPIO_P_PIN_NUMBER_8  (1UL << 8)
#define GPIO_P_PIN_NUMBER_9  (1UL << 9)
#define GPIO_P_PIN_NUMBER_10 (1UL << 10)
#define GPIO_P_PIN_NUMBER_11 (1UL << 11)
#define GPIO_P_PIN_NUMBER_12 (1UL << 12)
#define GPIO_P_PIN_NUMBER_13 (1UL << 13)
#define GPIO_P_PIN_NUMBER_14 (1UL << 14)
#define GPIO_P_PIN_NUMBER_15 (1UL << 15)

int(*const *const gpio_config_table[PERIPH_REGISTER_TABLE_MEMBERS])();

int(*const gpio_em4clr_all[1])();
int(*const gpio_em4cause[1])();


#endif /* EFM32ZG_GPIO_HAL_H_ */
