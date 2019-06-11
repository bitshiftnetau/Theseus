#ifndef MPI_TIMER_H_
#define MPI_TIMER_H_

#include "mpi_types.h"
#include "mpi_port.h"

int mpi_timerInit(void* host_object, int (*host_timer_interface_global_fn)());
int mpi_timerConfigReg(void* host_object, int (*host_timer_interface_single_reg_fn)(), uint32_t config_register);
int mpi_timerQueryReg(void* host_object, int (*host_timer_interface_single_reg_fn)(), uint32_t config_register);
int mpi_timerDelay(void* host_object,  int (*host_timer_interface_delay_fn)(), uint32_t delay_ms);

#endif
