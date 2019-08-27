
#include "mpi_port.h"
#include "rpi2_adaptor.h"
#include "spi.h"

RPI_spi_conf rpi_spi_conf = {
  .bit_order = BCM2835_SPI_BIT_ORDER_MSBFIRST,
  .spi_mode = BCM2835_SPI_MODE2,
  .spi_clkdiv = BCM2835_SPI_CLOCK_DIVIDER_64,
  .spi_cs = BCM2835_SPI_CS_NONE,
  .pin = pin21
};

MPI_host rpi_spi = {

  ._periph_periphconf = {
    ._usart_init = &spi_Init,
    ._usart_data = &spi_Data
  },
  .MPI_data[1] = &rpi_spi_conf
};

