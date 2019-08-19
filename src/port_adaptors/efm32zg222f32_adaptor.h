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

int cmu_Init(void* host_ptr);
int cmu_ConfigReg(void* host_ptr, uint32_t config_register);
int cmu_QueryReg(void* host_ptr, uint32_t config_register);

/**********************
 *      USART
 **********************/

int usart_Init(void* host_ptr);
int usart_ConfigReg(void* host_ptr, uint32_t config_register);
int usart_QueryReg(void* host_ptr, uint32_t config_register);

int usart_Data(void* host_ptr, uint32_t RW, void* ext_dev_array, uint32_t array_len);

/*********************
 *      GPIO 
 *********************/

int gpio_Init(void* host_ptr);
int gpio_ConfigReg(void* host_ptr, uint32_t config_register);
int gpio_QueryReg(void* host_ptr, uint32_t config_register);

int gpio_Data(void* host_ptr, uint32_t RW, uint32_t port, uint16_t pin);

/*********************
 *      TIMER 
 *********************/

#ifndef TIMER_CMD_START
#define TIMER_CMD_START EFM32ZG_TIMER_CMD_START
#endif

#ifndef TIMER_CMD_STOP
#define TIMER_CMD_STOP EFM32ZG_TIMER_CMD_STOP
#endif


int timer_Init(void* host_ptr);
int timer_ConfigReg(void* host_ptr, uint32_t config_register);
int timer_QueryReg(void* host_ptr, uint32_t config_register);


#endif /* EFM32ZG_GLOBAL_HAL_H_ */
