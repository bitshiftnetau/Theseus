/* # SpongeCake, an embedded software design philosophy for bare-metal systems
 * Copyright (C) 2018 Aidan Millar-Powell
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include "mpi_usart.h"
#include "mpi_types.h"
#include "mpi_port.h"  

/********************************** SOLUTION TO PROBLEM ***************************************************
 *
 *  use void pointers instead of typdef'd pointers, do this all the way through the pipes until you 
 *  reach the HAL layers, then cast the pointer to the struct type and use it as you need. 
 *
 *  This will require a certain amount of access to HAL layer structs. 
 *
 *  Perhaps we should have a middleware layers struct with a void pointer to a HAL typedef'd struct instance???
 *
 */

/*
 * Example usage:
 *
 * mpi_usartGlobalConf(usart_GlobalInit, XXX_host, USART_WRITE);
 *
 * where usart_GlobalInit is a HAL interface function, XXX_host is a MPI_host struct instance (which should 
 * be declare in your config-specific file, and USART_WRITE is telling sending the declared define which 
 * tells it to write to the registers.
 *
 * See the included efm32zg222f32 HAL for examples on how to use this middleware with ease
 *
 */

#define GLOBAL 0
#define SINGLE 1

/* USART peripheral configuration */
int mpi_usartInit(void* host_object, int(*host_usart_interface_global_fn)()){
  return host_usart_interface_global_fn(host_object); 
}
int mpi_usartConfigReg(void* host_object, int(*host_usart_interface_single_reg_fn)(), uint32_t config_register){
  return host_usart_interface_single_reg_fn(host_object, config_register); 
}
int mpi_usartQueryReg(void* host_object, int(*host_usart_interface_single_reg_fn)(), uint32_t config_register){
  return host_usart_interface_single_reg_fn(host_object, config_register); 
}

/*
 * We always read from an external device layer, rather than directly from the host usart
 */
int mpi_usartData(void* host_object, int(*host_usart_interface_fn)(), void* ext_dev_object, int(*ext_dev_interface_fn)(), uint32_t read_write){
	return ext_dev_interface_fn(host_object, host_usart_interface_fn, ext_dev_object, read_write);
}




