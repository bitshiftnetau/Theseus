/*
 * mpi_cmu.h
 *
 *  Created on: Oct 5, 2018
 *      Author: access
 */

#ifndef MPI_CMU_H_
#define MPI_CMU_H_

int mpi_cmuInit(void* host_object, uint32_t read_write_clear, int (*host_cmu_interface_global_fn)()); 
int mpi_cmuConfigReg(void* host_object, uint32_t read_write_clear, int (*host_cmu_interface_single_reg_fn)()); 

#endif /* MPI_CMU_H_ */
