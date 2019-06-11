/*
 * mpi_cmu.h
 *
 *  Created on: Oct 5, 2018
 *      Author: access
 */

#ifndef MPI_CMU_H_
#define MPI_CMU_H_

#include <stdint.h>

int mpi_cmuInit(void* host_object, int (*host_cmu_interface_global_fn)()); 
int mpi_cmuConfigReg(void* host_object, int (*host_cmu_interface_single_reg_fn)(), uint32_t config_register); 
int mpi_cmuQueryReg(void* host_object, int (*host_cmu_interface_single_reg_fn)(), uint32_t config_register); 

#endif /* MPI_CMU_H_ */
