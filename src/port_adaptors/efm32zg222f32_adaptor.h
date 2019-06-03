/*
 * efm32zg_global_HAL.h
 *
 *  Created on: Dec 5, 2018
 *      Author: access
 */

#ifndef EFM32ZG_GLOBAL_HAL_H_
#define EFM32ZG_GLOBAL_HAL_H_

#include "efm32zg_gpio_HAL.h"
#include "efm32zg_gpio_IO_HAL.h"
#include "efm32zg_usart_HAL.h"



/********************
 *      CMU 
 ********************/

int cmu_Init(void* host_ptr, uint32_t RWC);
int cmu_ConfigReg(void* host_ptr, uint32_t RWC);

/**********************
 *      USART
 **********************/

int usart_Init(void* host_ptr, uint32_t RWC);
int usart_ConfigReg(void* host_ptr, uint32_t RWC);
int usart_IO(void* host_ptr, uint32_t RW, void* ext_dev_array, uint32_t array_len);

/*********************
 *      GPIO 
 *********************/

int gpio_Init(void* host_ptr, uint32_t RWC);
int gpio_ConfigReg(void* host_ptr, uint32_t RWC);
int gpio_RW(void* host_ptr, uint32_t RW);
int gpio_IO(void* host_ptr, uint32_t RW, void* ext_dev_array, uint32_t array_len);
int gpio_Tgl(void* host_ptr, uint32_t RW);

/*********************
 *      TIMER 
 *********************/

int timer_Init(void* host_ptr, uint32_t RWC);
int timer_ConfigReg(void* host_ptr, uint32_t RWC);

#endif /* EFM32ZG_GLOBAL_HAL_H_ */
