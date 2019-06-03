/*
 * mpi_gpio.h
 *
 *  Created on: Oct 11, 2018
 *      Author: access
 */

#ifndef MPI_GPIO_H_
#define MPI_GPIO_H_

#include <stdint.h>

int mpi_gpioInit(void* host_object, uint32_t read_write_clear, int (*host_gpio_interface_global_fn)()); 
int mpi_gpioConfigReg(void* host_object, uint32_t read_write_clear, int (*host_gpio_interface_single_reg_fn)()); 

int mpi_gpioRead(void* host_object, int(*host_gpio_interface_spi_fn)(), void* ext_dev_object, int(*ext_dev_interface_fn)());

int mpi_gpioWrite(void* host_object, int(*host_gpio_interface_spi_fn)(), void* ext_dev_object, int(*ext_dev_interface_fn)());

int mpi_gpioToggle(void* host_object, int(*host_gpio_interface_spi_fn)(), void* ext_dev_object, int(*ext_dev_interface_fn)());


#endif /* MPI_GPIO_H_ */
