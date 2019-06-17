/*
 * mpi_radio.h
 *
 *  Created on: Dec 3, 2018
 *      Author: access
 */

#ifndef MPI_RADIO_H_
#define MPI_RADIO_H_

#include <stdint.h>

int mpi_extdevInit(void* host_object, int(*host_comm_interface_fn)(), void* ext_dev_object, int(*ext_dev_interface_fn)());

int mpi_extdevConfigReg(void* host_object, int(*host_comm_interface_fn)(), void* ext_dev_object, int(*ext_dev_interface_fn)(), void* register_enum);

int mpi_extdevQueryReg(void* host_object, int(*host_comm_interface_fn)(), void* ext_dev_object, int(*ext_dev_interface_fn)(), void* register_enum);

int mpi_extdevData(void* host_object, int(*host_comm_interface_fn)(), void* ext_dev_object, int(*ext_dev_interface_fn)(), uint32_t read_write);


#endif /* MPI_RADIO_H_ */
