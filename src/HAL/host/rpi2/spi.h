#ifndef RPI2_SPI_H
#define RPI2_SPI_H

#include <bcm2835.h>

#define READ  0
#define WRITE 1

#define HALF_DUPLEX   0
#define FULL_DUPLEX   1

#define RPI_SPI_DATA_INDEX 0
#define RPI_SPI_CONF_INDEX 1

#define READ_WRITE       2
#define READ_WRITE_CLEAR 3


typedef struct {

  int duplex;  
  int bit_order;
  int spi_mode;
  int spi_clkdiv;
  int spi_cs;
  PIN_ENUM pin;

} RPI_spi_conf;

int spi_RxTx(char* data_byte);
extern int(* spi_rxtx_array[])();

#endif
