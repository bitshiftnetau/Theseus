 /* # SpongeCake, an embedded software design philosophy for bare-metal systems
 * Copyright (C) 2018 Aidan Millar-Powell
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 *
 */
 
#include <stdint.h>

#include "mpi_port.h"
#include "dw1000_types.h"
#include "dw1000_regs.h"
#include "dw1000_buildMAC.h"
#include "dw1000_commRxTx.h"

/***********************************************************
 *                       Comm fns
 **********************************************************/

/* 
 * Consider how we are going to write the messages in the 
 * following format:
 *
 * Build the message 
 *
 *  <bit #0> <bit #1> <bitfield 3:7>
 *  <bit #0> <bit #1> <bitfield 3:7>
 *  <bit #0> <bitfield 2:7>
 *
 * The length of the frame will determine how many times
 * we iterate the above writing procedure. Each time we 
 * iterate the writing procedure, we should also iterate
 * through the message out array and write to the device
 *
 * The reverse is true for receiving data, although we still 
 * have to write to the device to request data. 
 *
 */



uint32_t dw_Tx(void* host_object, int(*host_usart)(), void* ext_dev_object, uint8_t* buffer_out, uint32_t buffer_len){

  MPI_ext_dev* ext_dev_ptr = (MPI_ext_dev*)ext_dev_object;
  DW_config* dw_config = (DW_config*)ext_dev_ptr->MPI_conf[DW_CONFIG_INDEX];
  DW_nodelist* dw_nodelist = (DW_nodelist*)ext_dev_ptr->MPI_data[NODE_LIST_INDEX];
  

  /*************************************************************************/
  //  de-assert CS line here
  /*************************************************************************/

/*
 * INSERT CONDITIONAL TO CHECK IF AUTOCS IS ENABLED
 *
  MPI_host* host_object_ptr = (MPI_host*)host_object;
  volatile int(*host_spi_cs)() = host_object_ptr->_periph_periphconf._gpio_data;
  
   host_spi_cs(host_object, WRITE, 0, 5);
*/

  //callback to host usart
  //
  int ret = host_usart(host_object, WRITE, buffer_out, buffer_len);

  /*************************************************************************/
  //  re-assert CS line here
  /*************************************************************************/
/*
 * INSERT CONDITIONAL TO CHECK IF AUTOCS IS ENABLED
 
 host_spi_cs(host_object, TGL, 0, 5);
*/

  return ret;
}


uint32_t dw_Rx(void* host_object, int(*host_usart)(), void* ext_dev_object, uint8_t* buffer_in, uint32_t buffer_len){
 
  MPI_ext_dev* ext_dev_ptr = (MPI_ext_dev*)ext_dev_object;
  DW_config* dw_config = (DW_config*)ext_dev_ptr->MPI_conf[DW_CONFIG_INDEX];
  DW_nodelist* dw_nodelist = (DW_nodelist*)ext_dev_ptr->MPI_data[NODE_LIST_INDEX];
  
  //build message that requests a read from a given register (pre-configured in reg_id_index)
  int frame_len = dw_buildMessageHeader(dw_nodelist, dw_config, DW_READ);
  //int frame_len = 5;
    
  /*************************************************************************/
  //de-assert CS line here
  /*************************************************************************/
/*
 * INSERT CONDITIONAL TO CHECK IF AUTOCS IS ENABLED
 *
  MPI_host* host_object_ptr = (MPI_host*)host_object;
  volatile int(*host_spi_cs)() = host_object_ptr->_periph_periphconf._gpio_data;

  host_spi_cs(host_object, WRITE, 0, 5);
*/
  
  //make tx call to request frame
  host_usart(host_object, WRITE, dw_nodelist->frame_out, frame_len);

  //callback to host usart
  //
  int ret = host_usart(host_object, READ, buffer_in, buffer_len);

  /*************************************************************************/
  //re-assert CS line here
  /*************************************************************************/
/*
 * INSERT CONDITIONAL TO CHECK IF AUTOCS IS ENABLED
 *
  host_spi_cs(host_object, TGL, 0, 5);
*/
  return ret;
}


/***********************************************************
 *
 *          CALL THESE FUNCTIONS FROM DW_INIT()
 *
 ***********************************************************/

void dw_lpol_lpha_high(void(*device_gpio)(),
						uint32_t* port,
						uint32_t* mode)
{
	device_gpio(port, mode);
}

void dw_lpol_hpha_high(void(*device_gpio)(),
						uint32_t* port,
						uint32_t* mode)
{
	device_gpio(port, mode);
}

void dw_hpol_lpha_high(void(*device_gpio)(),
						uint32_t* port,
						uint32_t* mode)
{
	device_gpio(port, mode);
}

void dw_hpol_hpha_high(void(*device_gpio)(),
						uint32_t* port,
						uint32_t* mode)
{
	device_gpio(port, mode);
}

void dw_lpol_lpha_low(void(*device_gpio)(),
					   uint32_t* port,
					   uint32_t* mode)
{
	device_gpio(port, mode);
}

void dw_lpol_hpha_low(void(*device_gpio)(),
					   uint32_t* port,
					   uint32_t* mode)
{
	device_gpio(port, mode);
}

void dw_hpol_lpha_low(void(*device_gpio)(),
					   uint32_t* port,
					   uint32_t* mode)
{
	device_gpio(port, mode);
}

void dw_hpol_hpha_low(void(*device_gpio)(),
					   uint32_t* port,
					   uint32_t* mode)
{
	device_gpio(port, mode);
}


void(* dw_PolAlphaAssert[DW_SPI_POLALPA_VARIANTS])() = {
  dw_lpol_lpha_low,
	dw_lpol_hpha_low,
	dw_hpol_lpha_low,
	dw_hpol_hpha_low
};

void(* dw_PolAlphaDeAssert[DW_SPI_POLALPA_VARIANTS])() = {
  dw_lpol_lpha_high,
	dw_lpol_hpha_high,
	dw_hpol_lpha_high,
	dw_hpol_hpha_high
};


