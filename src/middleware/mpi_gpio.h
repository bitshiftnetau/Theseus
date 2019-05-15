/*
 * mpi_gpio.h
 *
 *  Created on: Oct 11, 2018
 *      Author: access
 */

#ifndef MPI_GPIO_H_
#define MPI_GPIO_H_

int mpi_gpioInit(void* host_object, uint32_t read_write_clear, int (*host_gpio_interface_global_fn)()); 
int mpi_gpioConfigReg(void* host_object, uint32_t read_write_clear, int (*host_gpio_interface_single_reg_fn)()); 

void gpio_SetHigh(void(*pa_high[])(), const int* pol_alpha);
void gpio_SetLow(void(*pa_low[])(), const int* pol_alpha);

#endif /* MPI_GPIO_H_ */
