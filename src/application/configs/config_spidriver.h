#ifndef CONFIG_SPIDRIVER_H_
#define CONFIG_SPIDRIVER_H_

#include <stddef.h>

#include "mpi_port.h"
#include "spidriver.h"

extern SPIDriver sd_status;
extern MPI_ext_dev sd_intf;

typedef struct {
    char tx[8];
    char rx[8];
}SD_DATA;

typedef struct {
    const char port[8];
}SD_CONF;

#endif