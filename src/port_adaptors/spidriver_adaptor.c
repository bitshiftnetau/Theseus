#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>

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

//read_write_readwrite jump table
void spi_write(SPIDriver *sd, const char bytes[], size_t nn);
void spi_read(SPIDriver *sd, char bytes[], size_t nn);
void spi_writeread(SPIDriver *sd, char bytes[], size_t nn);

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

*/

int sd_RegDump(void* host_object){

  MPI_host* spidriver_ptr = (MPI_host*)host_object;
  SPIDriver* sd_status = (SPIDriver*)spidriver_ptr->MPI_status[SD_STATUS_INDEX];

  //spi_getstatus
  spi_getstatus(sd_status);

  printf("model: %s\n", sd_status->model);
  printf("serial: %s\n", sd_status->serial);
  printf("uptime: %d\n", sd_status->uptime);
  printf("output a: %d\n", sd_status->a);
  printf("output b: %d\n", sd_status->b);
  printf("output cs: %d\n", sd_status->cs);
  bool crc = (sd_status->ccitt_crc & sd_status->e_ccitt_crc) ? true: false;
  printf("%s", (crc ? "CRC CHECK: TRUE" : "CRC CHECK: FALSE"));
 
  return 0;
}


int sd_Init(void* host_object){

  MPI_host* spidriver_ptr = (MPI_host*)host_object;
  SD_CONF* sd_conf = (SD_CONF*)spidriver_ptr->MPI_conf[SD_CONFIG_INDEX];  
  SPIDriver* sd_status = (SPIDriver*)spidriver_ptr->MPI_status[SD_STATUS_INDEX];

  //spi_connect
  spi_connect(sd_status, "/dev/ttyUSB0");

  if(sd_status->connected){
    printf("spi connected\n");
  } else {
    printf("spi NOT connected\n");
    return EXIT_SUCCESS;
  }



  sleep(1);
  spi_getstatus(sd_status);

  printf("model: %s\n", sd_status->model);
  printf("serial: %s\n", sd_status->serial);
  printf("uptime: %d\n", sd_status->uptime);
  printf("output a: %d\n", sd_status->a);
  printf("output b: %d\n", sd_status->b);
  printf("output cs: %d\n", sd_status->cs);
  bool crc = (sd_status->ccitt_crc & sd_status->e_ccitt_crc) ? true: false;
  printf("%s", (crc ? "CRC CHECK: TRUE" : "CRC CHECK: FALSE"));
 
  return 0;

}

int sd_Data(void* host_ptr, uint32_t RW, void* ext_dev_array, uint32_t array_len){

  MPI_host* spidriver_ptr = (MPI_host*)host_ptr;
  SD_DATA* sd_data = (SD_DATA*)spidriver_ptr->MPI_data[SD_DATA_INDEX];  
  SPIDriver* sd_status = (SPIDriver*)spidriver_ptr->MPI_status[SD_STATUS_INDEX];

  // spi_sel
  spi_sel(sd_status);

  // store read_write_readwrite
  void(*rw)() = read_write_readwrite[SD_READ_WRITE];

  // call rw
  rw(sd_status, (char*)ext_dev_array, array_len);
  
  //spi_unsel
  spi_unsel(sd_status);

  return 0;

}

