// spi.c
//
// Example program for bcm2835 library
// Shows how to interface with SPI to transfer a byte to and from an SPI device
//
// After installing bcm2835, you can build this
// with something like:
// gcc -o spi spi.c -l bcm2835
// sudo ./spi
//
// Or you can test it before installing with:
// gcc -o spi -I ../../src ../../src/bcm2835.c spi.c
// sudo ./spi
//
// Author: Mike McCauley
// Copyright (C) 2012 Mike McCauley
// $Id: RF22.h,v 1.21 2012/05/30 01:51:25 mikem Exp $

#include <stdlib.h>
#include <stdio.h>
#include <bcm2835.h>

#include "mpi_port.h"

typedef enum {

  pin1 = PIN_1;
  pin2 = PIN_2;
  pin3 = PIN_3;
  pin4 = PIN_4;
  pin5 = PIN_5;
  pin6 = PIN_6;
  pin7 = PIN_7;
  pin8 = PIN_8;
  pin9 = PIN_9;
  pin10 = PIN_10;
  pin11 = PIN_11;
  pin12 = PIN_12;
  pin13 = PIN_13;
  pin14 = PIN_14;
  pin15 = PIN_15;
  pin16 = PIN_16;
  pin17 = PIN_17;
  pin18 = PIN_18;
  pin19 = PIN_19;
  pin20 = PIN_20;
  pin21 = PIN_21;
  pin22 = PIN_22;
  pin23 = PIN_23;
  pin24 = PIN_24;
  pin25 = PIN_25;
  pin26 = PIN_26;
  pin27 = PIN_27;
  pin28 = PIN_28;
  pin29 = PIN_29;
  pin30 = PIN_30;

} PIN_ENUM;


typedef struct {

  int bit_order;
  int spi_mode;
  int spi_clkdiv;
  int spi_cs;
  PIN_ENUM pin;

} RPI_data;


RPI_data rpi_data = {
  bit_order = ;
  spi_mode = ;
  spi_clkdiv = ;
  spi_cs = ;
  pin = pin21;
}


MPI_host raspbi = {

  ._interface = {
    ._dev_init = raspbi_Init
    ._dev_reg_dump = NULL
    ._dev_data = raspbi_ReadWrite
    ._dev_config_reg = NULL
    ._dev_query_reg = NULL
    ._dev_wakeup = NULL
    ._dev_sleep = NULL
    ._dev_mode_level = NULL
    ._dev_reset = NULL
    ._dev_off = NULL 
  },
  MPI_data[0] = &rpi_data;
}


#define PIN_21 RPI_V2_GPIO_P1_21




int raspbi_Init()
{
    
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

  bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      // The default

	//Set SPI data mode
	//	BCM2835_SPI_MODE0 = 0,  // CPOL = 0, CPHA = 0
	//	BCM2835_SPI_MODE1 = 1,  // CPOL = 0, CPHA = 1
	//	BCM2835_SPI_MODE2 = 2,  // CPOL = 1, CPHA = 0
	//	BCM2835_SPI_MODE3 = 3,  // CPOL = 1, CPHA = 1
  //(SPI_MODE_# | SPI_CS_HIGH)=Chip Select active high, (SPI_MODE_# | SPI_NO_CS)=1 device per bus no Chip Select
  //
  bcm2835_spi_setDataMode(BCM2835_SPI_MODE2); // The default is mode0

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
  bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_64); 
  //bcm2835_spi_chipSelect(BCM2835_SPI_CS0); // The default is CS0
  bcm2835_spi_chipSelect(BCM2835_SPI_CS_NONE);
 
 	//Set CS pins polarity to low
	//bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, 0);
	//bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS1, 0);
  //
  //bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, 1);  // the default

  printf("Transferring 10 bytes... ");
  //Transfer n many bytes
	char data_buffer[10];
	int Count;
	for (Count = 0; Count < 10; Count++){
    data_buffer[Count] = 0x80 + Count;
  }

  
  // Set the pin to be an output
  bcm2835_gpio_fsel(PIN_21, BCM2835_GPIO_FSEL_OUTP);

	// Turn it on
	bcm2835_gpio_write(PIN_21, HIGH);


 
  return EXIT_SUCCESS;
}


int raspbi_Write(char* data_buffer, int size){

  // turn it off
  bcm2835_gpio_write(PIN_21, LOW);
  bcm2835_spi_transfern(&data_buffer[0], size);			//data_buffer used for tx and rx
  bcm2835_gpio_write(PIN_21, HIGH);

}


int raspbi_ReadWrite(char* data_byte){

  // OR Send a byte to the slave and simultaneously read a byte back from the slave
  
  bcm2835_gpio_write(PIN_21, LOW);
  data_byte = bcm2835_spi_transfer(data_byte);
  bcm2835_gpio_write(PIN_21, HIGH);
  
  //check data if doing loopback test
  //if (send_data != read_data){
  //    printf("Do you have the loopback from MOSI to MISO connected?\n");
  //}

}


int raspbi_Read(){



}

int raspbi_Off(){

  printf("Closing spi... ");

  bcm2835_spi_end();
  bcm2835_close();

  return 0;
}
