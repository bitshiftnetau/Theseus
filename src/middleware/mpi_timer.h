#ifndef MPI_TIMER_H_
#define MPI_TIMER_H_

#include "mpi_types.h"
#include "mpi_port.h"

int mpi_timerInit(void* host_object, uint32_t read_write_clear, int (*host_timer_interface_global_fn)());
int mpi_timerConfigReg(void* host_object, uint32_t read_write_clear, int (*host_timer_interface_single_reg_fn)());

#endif
