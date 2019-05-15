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

int mpi_usartInit(void* host_object, uint32_t read_write_clear, int (*host_usart_interface_global_fn)());
int mpi_usartConfigReg(void* host_object, uint32_t read_write_clear, int (*host_usart_interface_single_reg_fn)());

int mpi_usartWrite(void* host_object, int(*host_usart_interface_spi_fn)(), void* ext_dev_object, int (*ext_dev_interface_fn)());
int mpi_usartRead(void* host_object, int(*host_usart_interface_spi_fn)(), void* ext_dev_object, int (*ext_dev_interface_fn)());


#endif /* MPI_SPI_H_ */
