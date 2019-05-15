/*
 * efm32zg_gpio_IO_HAL.h
 *
 *  Created on: Dec 5, 2018
 *      Author: access
 */

#ifndef EFM32ZG_GPIO_IO_HAL_H_
#define EFM32ZG_GPIO_IO_HAL_H_

#include <stdint.h>

#define GPIO_READ_WRITE_CLEAR 3
#define GPIO_READ_WRITE 2

int(*const *const gpio_I_O_TGL[GPIO_READ_WRITE_CLEAR])();
void(*const gpio_IO_host_slave_transfer[GPIO_READ_WRITE])(); 

#endif /* EFM32ZG_GPIO_IO_HAL_H_ */
