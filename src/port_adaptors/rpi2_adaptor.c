#include <stdio.h>
#include <stdlib.h>

#include <bcm2835.h>

#include "mpi_port.h"
#include "rpi2_adaptor.h"
#include "spi.h"
#include "gpio.h"

int spi_Init(void* host_ptr)
{
   
  MPI_host* rpi_spi = (MPI_host*)host_ptr;
  RPI_spi_conf* rpi_spi_conf = rpi_spi->MPI_data[RPI_SPI_CONF_INDEX];

  // If you call this, it will not actually access the GPIO
  // Use for testing
  // bcm2835_set_debug(1);

  if (!bcm2835_init()){
      printf("bcm2835_init failed. Are you running as root??\n");
      return 1;
  }
  
  if (!bcm2835_spi_begin()){
      printf("bcm2835_spi_begin failed. Are you running as root??\n");
      return 1;
  }

  bcm2835_spi_setBitOrder(rpi_spi_conf->bit_order);      // The default

	//Set SPI data mode
	//	BCM2835_SPI_MODE0 = 0,  // CPOL = 0, CPHA = 0
	//	BCM2835_SPI_MODE1 = 1,  // CPOL = 0, CPHA = 1
	//	BCM2835_SPI_MODE2 = 2,  // CPOL = 1, CPHA = 0
	//	BCM2835_SPI_MODE3 = 3,  // CPOL = 1, CPHA = 1
  //(SPI_MODE_# | SPI_CS_HIGH)=Chip Select active high, (SPI_MODE_# | SPI_NO_CS)=1 device per bus no Chip Select
  //
  bcm2835_spi_setDataMode(rpi_spi_conf->spi_mode); // The default is mode0

	//Set SPI clock speed
  //
	//	BCM2835_SPI_CLOCK_DIVIDER_65536 = 0,       ///< 65536 = 262.144us = 3.814697260kHz (total H+L clock period)
	//	BCM2835_SPI_CLOCK_DIVIDER_32768 = 32768,   ///< 32768 = 131.072us = 7.629394531kHz
	//	BCM2835_SPI_CLOCK_DIVIDER_16384 = 16384,   ///< 16384 = 65.536us = 15.25878906kHz
	//	BCM2835_SPI_CLOCK_DIVIDER_8192  = 8192,    ///< 8192 = 32.768us = 30/51757813kHz
	//	BCM2835_SPI_CLOCK_DIVIDER_4096  = 4096,    ///< 4096 = 16.384us = 61.03515625kHz
	//	BCM2835_SPI_CLOCK_DIVIDER_2048  = 2048,    ///< 2048 = 8.192us = 122.0703125kHz
	//	BCM2835_SPI_CLOCK_DIVIDER_1024  = 1024,    ///< 1024 = 4.096us = 244.140625kHz
	//	BCM2835_SPI_CLOCK_DIVIDER_512   = 512,     ///< 512 = 2.048us = 488.28125kHz
	//	BCM2835_SPI_CLOCK_DIVIDER_256   = 256,     ///< 256 = 1.024us = 976.5625MHz
	//	BCM2835_SPI_CLOCK_DIVIDER_128   = 128,     ///< 128 = 512ns = = 1.953125MHz
	//	BCM2835_SPI_CLOCK_DIVIDER_64    = 64,      ///< 64 = 256ns = 3.90625MHz
	//	BCM2835_SPI_CLOCK_DIVIDER_32    = 32,      ///< 32 = 128ns = 7.8125MHz
	//	BCM2835_SPI_CLOCK_DIVIDER_16    = 16,      ///< 16 = 64ns = 15.625MHz
	//	BCM2835_SPI_CLOCK_DIVIDER_8     = 8,       ///< 8 = 32ns = 31.25MHz
	//	BCM2835_SPI_CLOCK_DIVIDER_4     = 4,       ///< 4 = 16ns = 62.5MHz
	//	BCM2835_SPI_CLOCK_DIVIDER_2     = 2,       ///< 2 = 8ns = 125MHz, fastest you can get
	//	BCM2835_SPI_CLOCK_DIVIDER_1     = 1,       ///< 1 = 262.144us = 3.814697260kHz, same as 0/65536
  //
  bcm2835_spi_setClockDivider(rpi_spi_conf->spi_clkdiv); 
  //bcm2835_spi_chipSelect(BCM2835_SPI_CS0); // The default is CS0
  bcm2835_spi_chipSelect(rpi_spi_conf->spi_cs);
 
 	//Set CS pins polarity to low
	//bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, 0);
	//bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS1, 0);
  //
  //bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, 1);  // the default
  
  // Set the pin to be an output
  bcm2835_gpio_fsel(rpi_spi_conf->pin, BCM2835_GPIO_FSEL_OUTP);

	// Turn it on
	bcm2835_gpio_write(rpi_spi_conf->pin, HIGH);

  return EXIT_SUCCESS;
}

int spi_Data(void* host_ptr, uint32_t RW, void* ext_dev_array, uint32_t array_len){

  MPI_host* rpi = (MPI_host*)host_ptr;
  RPI_spi_conf* rpi_spi_conf = rpi->MPI_data[RPI_SPI_CONF_INDEX];
  
  char* array = (char*)ext_dev_array;

  int(* spi_rxtx)() = spi_rxtx_array[spi_conf->duplex][RW];
  int len = array_len;
  int ret;

  bcm2835_gpio_write(rpi_spi_conf->pin, LOW);
  for(int i = 0; i < len; i++){
    ret = spi_rxtx(array[0]); //transmit byte at index 0 and replace with returned byte
  }
  bcm2835_gpio_write(rpi_spi_conf->pin, HIGH);

  return ret;  
}

int spi_Off(){

  printf("Closing spi... ");

  bcm2835_spi_end();
  bcm2835_close();

  return 0;
}

//FILL THESE OUT
int gpio_Init(void* host_ptr);
int gpio_Data(void* host_ptr, uint32_t read_write_tgl, uint32_t port, uint32_t pin);

//FILL THESE OUT
int timer_Init(void* host_ptr);
int timer_Delay(uint32_t delay_ms);