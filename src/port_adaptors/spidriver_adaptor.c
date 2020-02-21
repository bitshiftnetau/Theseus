#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include "mpi_port.h"
#include "spidriver.h"

#include "spidriver_adaptor.h"

void(* read_write_readwrite[READ_WRITE_RW])() = 
{&spi_read, &spi_write, &spi_writeread};

/*
// UNUSED
//void spi_seta(SPIDriver *sd, char v);
//void spi_setb(SPIDriver *sd, char v);
//int spi_commands(SPIDriver *sd, int argc, char *argv[]);

//sd_Init
void spi_connect(SPIDriver *sd, const char* portname);

//sd_RegDump
void spi_getstatus(SPIDriver *sd);

//sd_Data
void spi_sel(SPIDriver *sd);
void spi_unsel(SPIDriver *sd);
(read_write_readwrite jump table)
void spi_write(SPIDriver *sd, const char bytes[], size_t nn);
void spi_read(SPIDriver *sd, char bytes[], size_t nn);
void spi_writeread(SPIDriver *sd, char bytes[], size_t nn);

*/

int sd_RegDump(void* host_object, int(*host_usart)(), void* ext_dev_object){
 
  MPI_host* host_ptr = (MPI_host*)host_object;
  MPI_ext_dev* dw_slave_ptr = (MPI_ext_dev*)ext_dev_object;
  SPIDriver* sd_config = (SPIDriver*)dw_slave_ptr->MPI_conf[SD_CONFIG_INDEX];  

  //spi_getstatus
 
  return 0;
}

int sd_QueryReg(void* host_object, int(*host_usart)(), void* ext_dev_object){
 
  MPI_host* host_ptr = (MPI_host*)host_object;
  MPI_ext_dev* dw_slave_ptr = (MPI_ext_dev*)ext_dev_object;
  SPIDriver* sd_config = (SPIDriver*)dw_slave_ptr->MPI_conf[SD_CONFIG_INDEX];  

  //spi_getstatus
 
  return 0;
}
int sd_ConfigReg(void* host_object, int(*host_usart)(), void* ext_dev_object){
 
  MPI_host* host_ptr = (MPI_host*)host_object;
  MPI_ext_dev* dw_slave_ptr = (MPI_ext_dev*)ext_dev_object;
  SPIDriver* sd_config = (SPIDriver*)dw_slave_ptr->MPI_conf[SD_CONFIG_INDEX];  

  //spi_getstatus
 
  return 0;
}


int sd_Init(void* host_object, int(*host_usart)(), void* ext_dev_object){

  MPI_host* host_ptr = (MPI_host*)host_object;
  MPI_ext_dev* dw_slave_ptr = (MPI_ext_dev*)ext_dev_object;
  SPIDriver* sd_config = (SPIDriver*)dw_slave_ptr->MPI_conf[SD_CONFIG_INDEX];  

  //spi_connect

  //spi_commands

  return 0;

}

int sd_Data(void* host_object, int(*host_usart)(), void* ext_dev_object, uint32_t read_write){

  MPI_host* host_ptr = (MPI_host*)host_object;
  MPI_ext_dev* dw_slave_ptr = (MPI_ext_dev*)ext_dev_object;
  SPIDriver* sd_config = (SPIDriver*)dw_slave_ptr->MPI_conf[SD_CONFIG_INDEX];  

  //spi_sel

  //read_write_readwrite

  //spi_unsel

  return 0;

}

