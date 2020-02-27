#include <stddef.h>

#include "mpi_port.h"
#include "mpi_types.h"

#include "spidriver_adaptor.h"
#include "config_spidriver.h"
#include "spidriver.h"

/****
 FOUND IN SPIDRIVER.H FILE PLACED HERE FOR REFERENCE

typedef struct {
  int connected;          // Set to 1 when connected
  HANDLE port;
  char      model[16],
            serial[9];    // Serial number of USB device
  uint64_t  uptime;       // time since boot (seconds)
  float     voltage_v,    // USB voltage (Volts)
            current_ma,   // device current (mA)
            temp_celsius; // temperature (C)
  unsigned int a, b, cs;  // state of three output lines
  unsigned int
            ccitt_crc,    // Hardware CCITT CRC
            e_ccitt_crc;  // Host CCITT CRC, should match
} SPIDriver;


******/

SPIDriver sd_status;

SD_CONF sd_conf = {
    .port = {"ttyUSB0"}
};

SD_DATA sd_data = {
    .rxtx = {'0'},
};

/*
MPI_ext_dev sd_intf = {
    
    .model = {"spidriver"},
    .revision = {1.0},
    ._interface = {
        ._dev_init = &sd_Init,
        ._dev_reg_dump = &sd_RegDump,
        ._dev_data = &sd_Data
    },
    .MPI_status[0] = &sd_status,
    .MPI_conf[0] = &sd_conf,
    .MPI_data[0] = &sd_data 
};*/

/*
typedef struct MPI_HOST{

  char model[16];
  char revision[8];
  //int_callback mmap;
  int_callback interrupt_handlers;
  MPI_core_mcuconf _core_mcuconf;
  MPI_core_periphconf _core_periphconf;
  MPI_periph_periphconf _periph_periphconf;
  void* MPI_data[12]; // middleware layer data struct as defined as standard

}MPI_host;
*/

MPI_host sd_host = {
    
    .model = {"spidriver"},
    .revision = {1.0},
    ._periph_periphconf = {
        ._usart_init = &sd_Init,
        ._usart_query_reg = &sd_RegDump,
        ._usart_data = &sd_Data
    },
    .MPI_status[0] = &sd_status,
    .MPI_conf[0] = &sd_conf,
    .MPI_data[0] = &sd_data
};