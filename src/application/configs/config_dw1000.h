#ifndef CONFIG_DW1000_H_
#define CONFIG_DW1000_H_

#include "mpi_port.h"
#include "mpi_types.h"

#include "dw1000_types.h"
#include "dw1000_tofCalcs.h"

extern DW_config dw_config;
extern DW_data dw_data;
extern DW_network_dev dw_dev;  

extern DW_nodelist dw_list; 
extern MPI_ext_dev dw1000;

#endif 
