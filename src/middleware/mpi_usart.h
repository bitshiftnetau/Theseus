/*
 * mpi_spi.h
 *
 *  Created on: Oct 4, 2018
 *      Author: access
 */

#ifndef MPI_SPI_H_
#define MPI_SPI_H_

#include "mpi_types.h"
#include "mpi_port.h"

/******************************************************************************
 * @brief sends data using whatever USART is chosen
 * @param txBuffer points to data to transmit
 * @param bytesToSend bytes will be sent
 * @param device selects CS pin for required device
 *****************************************************************************/

int mpi_usartInit(void* host_object, int (*host_usart_interface_global_fn)());
int mpi_usartConfigReg(void* host_object, int (*host_usart_interface_single_reg_fn)(), uint32_t config_register);
int mpi_usartQueryReg(void* host_object, int (*host_usart_interface_single_reg_fn)(), uint32_t config_register);
int mpi_usartData(void* host_object, int(*host_usart_interface_fn)(), void* ext_dev_object, int(*ext_dev_interface_fn)(), uint32_t read_write);

#endif /* MPI_SPI_H_ */
