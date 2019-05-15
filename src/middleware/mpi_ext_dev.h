/*
 * mpi_radio.h
 *
 *  Created on: Dec 3, 2018
 *      Author: access
 */

#ifndef MPI_RADIO_H_
#define MPI_RADIO_H_

int mpi_extdevInit(void* host_object, int(*host_comm_interface_fn)(), void* ext_dev_object, int(*ext_dev_interface_fn)());
int mpi_extdevConfigReg(void* host_object, int(*host_comm_interface_fn)(), void* ext_dev_object, int(*ext_dev_interface_fn)());
int mpi_extdevStop(void* host_object, int(*host_comm_interface_fn)(), void* ext_dev_object, int(*ext_dev_interface_fn)());
int mpi_extdev_IO(void* host_object, int(*host_comm_interface_fn)(), void* ext_dev_object, int(*ext_dev_interface_fn)(), int(*mpi_host_comm_IO_fn)());

#endif /* MPI_RADIO_H_ */
