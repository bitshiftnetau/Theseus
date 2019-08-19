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

#include "_app_fns.h"

#include "mpi_types.h"
#include "mpi_port.h"

#include "efm32zg222f32.h"
#include "efm32zg_usart_IO_HAL.h"
#include "efm32zg_cmu_HAL.h"
#include "efm32zg_gpio_HAL.h"
#include "efm32zg_interrupts_HAL.h"
#include "efm32zg_types_HAL.h"
#include "efm32zg_usart_HAL.h"
#include "efm32zg_gpio_IO_HAL.h"
#include "efm32zg_timer_HAL.h"
#include "efm32zg222f32_adaptor.h"


/**************** USART *******************/

/******************************************************************
 *
 * @breif usart_Init 
 *
 * Call to read/write/clear child members of usart jump table 
 * peripheral members. 
 *
 * Each member in peripheral's parent jump table is mapped 1:1 
 * with 'Register Table' from USART section of efm32zg 
 * reference manual. Each peripheral member contains a 
 * read/write/clear function.
 *
 * Jump table structure is as follows: 
 *
 *  usart_register_table = {
 *
 *    register_1: [r] [w] [c],
 *    register_2: [r] [w] [c],
 *    register_3: [r] [w] [c],
 *    reg...
 *  }
 *
 * @param uint32_t RWC
 *
 * access the read/write/clear function in each sub-jump table
 *
 * @param uint32_t usart_register
   *
 * DEFINE for accessing single USART peripheral register
 * 
 * * @USART_frameconf* MPI_frameconf
 *
 * pass in frameconf struct from middleware layer, struct should 
 * reflect configuration bits in usart extended registers.
 *
 * @USART_periphconf* MPI_usart_periphconf
 *
 * pass in periphconf struct from middleware layer, struct should 
 * reflect USART peripheral registers 1:1. 
 *
 * (See 'Register Table' at the start of USART section in efm32zg
 *  reference manual, for corresponding registers)
 *
 */

int usart_Init(void* host_ptr){

  MPI_host* efm32zg_host_ptr = (MPI_host*)host_ptr;
  USART_periphconf* MPI_usart_periphconf = (USART_periphconf*)efm32zg_host_ptr->MPI_data[USART_PERIPHCONF_INDEX];

  NVIC_ClearPendingIRQ(USART1_TX_IRQn);
  NVIC_ClearPendingIRQ(USART1_RX_IRQn);

  //zg_TxIntSetup(false);
  //zg_RxIntSetup(false);

  if(MPI_usart_periphconf	!= NULL){

    int(*fn_ptr)();
		int ret = 0;
		int i = 0;

			while(usart_config_table[i] != NULL){
				
        fn_ptr = usart_config_table[i][WRITE];
				ret = fn_ptr(MPI_usart_periphconf);
          if(ret > 0){
            return 1;
          }
        i+=1;
			}
  }
	return 0;
}


int usart_ConfigReg(void* host_ptr, uint32_t config_register){

  MPI_host* efm32zg_host_ptr = (MPI_host*)host_ptr;
  USART_periphconf* MPI_usart_periphconf = (USART_periphconf*)efm32zg_host_ptr->MPI_data[USART_PERIPHCONF_INDEX];
  uint32_t conf_reg = config_register;
  
  int(*fn_ptr)();
	fn_ptr = usart_config_table[conf_reg][WRITE];
	return fn_ptr(MPI_usart_periphconf);
}

int usart_QueryReg(void* host_ptr, uint32_t config_register){

  MPI_host* efm32zg_host_ptr = (MPI_host*)host_ptr;
  USART_periphconf* MPI_usart_periphconf = (USART_periphconf*)efm32zg_host_ptr->MPI_data[USART_PERIPHCONF_INDEX];
  uint32_t conf_reg = config_register;
  
  int(*fn_ptr)();
	fn_ptr = usart_config_table[conf_reg][READ];
	return fn_ptr(MPI_usart_periphconf);
}


/*****************************************************************
 *
 * @ breif usart_IO 
 * @ description Pass this function to the middleware layer
 * which will pass it to the external device layer, which will 
 * it turn execute this function as a callback. 
 *
 * Interface to rx/tx registers
 *
 * @param uint32_t RW
 *
 * boolean for accessing Read/Write functions in usart_IO_table[]
 *
 * @param uint32_t array_len 
 *
 */

int usart_Data(void* host_ptr, uint32_t RW, void* ext_dev_array, uint32_t array_len){

  MPI_host* efm32zg_host_ptr = (MPI_host*)host_ptr;
  USART_data* MPI_buffer = (USART_data*)efm32zg_host_ptr->MPI_data[USART_DATA_INDEX];
  USART_error* MPI_error = (USART_error*)efm32zg_host_ptr->MPI_data[USART_ERROR_INDEX];
  USART_frameconf* MPI_frameconf = (USART_frameconf*)efm32zg_host_ptr->MPI_data[USART_FRAMECONF_INDEX];
  USART_status* MPI_status = (USART_status*)efm32zg_host_ptr->MPI_data[USART_STATUS_INDEX];

  uint32_t bitwidth = MPI_frameconf->bitwidth;
  int(*usart_IO_ptr)() = usart_IO_table[bitwidth][RW];
  void(*transfer_data_host_slave_ptr)() = usart_IO_host_slave_transfer[RW][bitwidth];

  if(RW == USART_READ){
    for(int slave_obj_buffer_index = 0; slave_obj_buffer_index < array_len; slave_obj_buffer_index++){
      usart_IO_ptr(MPI_buffer, MPI_frameconf, MPI_error, MPI_status);
      transfer_data_host_slave_ptr(MPI_buffer, ext_dev_array, slave_obj_buffer_index);    
    }
  } else if(RW == USART_WRITE){
    for(int slave_obj_buffer_index = 0; slave_obj_buffer_index < array_len; slave_obj_buffer_index++){
      transfer_data_host_slave_ptr(MPI_buffer, ext_dev_array, slave_obj_buffer_index); 
	    usart_IO_ptr(MPI_buffer, MPI_frameconf, MPI_error, MPI_status);
    }
  }
  return 0;  
}


/************** GPIO *****************/

/******************************************************************
 *
 * @breif gpio_Init 
 *
 * Call to read/write/clear child members of gpio jump table 
 * peripheral members. 
 *
 * Each member in peripheral's parent jump table 
 * is mapped 1:1 with 'Register Table' from GPIO section of efm32zg 
 * reference manual. Each peripheral member contains a 
 * read/write/clear function
 *
 *  Jump table structure is as follows: 
 *
 *  gpio_register_table = {
 *
 *    register_1: [r] [w] [c],
 *    register_2: [r] [w] [c],
 *    register_3: [r] [w] [c],
 *    reg...
 *  }
 *
 * @param uint32_t RWC
 *
 * access the read/write/clear function in each sub-jump table
 *
 * @param uint32_t gpio_register
 *
 * DEFINE for accessing single GPIO peripheral register
 * 
 * @param GPIO_periphconf* MPI_gpio_periphconf
 *
 * Pass in peripheral configuration struct from middleware later.
 *
 * (Struct should reflect the GPIO peripheral registers 1:1. See 
 * efm32zg reference manual under GPIO -> 'Register Table' for 
 * registers)
 *
 */


int gpio_Init(void* host_ptr){

  MPI_host* efm32zg_host_ptr = (MPI_host*)host_ptr;
  GPIO_periphconf* MPI_gpio_periphconf = (GPIO_periphconf*)efm32zg_host_ptr->MPI_data[GPIO_PERIPHCONF_INDEX];

  if(MPI_gpio_periphconf != NULL){

	  int(*fn_ptr)();
	  int ret = 0;
	  int i = 0;

	  while(gpio_config_table[i] != NULL){
	  	fn_ptr = gpio_config_table[i][WRITE];
	  	ret = fn_ptr(MPI_gpio_periphconf);
	  	  if(ret > 0){
          return 1;
        }
      i+=1;
	  }

    MPI_gpio_periphconf->port = 0;
    i = 0;

    while(gpio_port_config_table[i] != NULL){
	  	for(int j = 0; j < 6; j++){
        MPI_gpio_periphconf->port = j;
        fn_ptr = gpio_port_config_table[i][WRITE];
	  	  ret = fn_ptr(MPI_gpio_periphconf);
	  	    if(ret > 0){
            return 1;
          }
      }
      i+=1;
	  }


  }
	return 0;
}


int gpio_ConfigReg(void* host_ptr, uint32_t config_register){

  MPI_host* efm32zg_host_ptr = (MPI_host*)host_ptr;
  GPIO_periphconf* MPI_gpio_periphconf = (GPIO_periphconf*)efm32zg_host_ptr->MPI_data[GPIO_PERIPHCONF_INDEX];
  uint32_t conf_reg = config_register;
  
  int(*fn_ptr)();
	fn_ptr = gpio_config_table[conf_reg][WRITE];
  return fn_ptr(MPI_gpio_periphconf);
}

int gpio_QueryReg(void* host_ptr, uint32_t config_register){

  MPI_host* efm32zg_host_ptr = (MPI_host*)host_ptr;
  GPIO_periphconf* MPI_gpio_periphconf = (GPIO_periphconf*)efm32zg_host_ptr->MPI_data[GPIO_PERIPHCONF_INDEX];
  uint32_t conf_reg = config_register;
  
  int(*fn_ptr)();
	fn_ptr = gpio_config_table[conf_reg][READ];
  return fn_ptr(MPI_gpio_periphconf);
}

/*******************************************************************************
 *
 * @brief gpio_IO 
 * 
 * Call to read, write or clear child jump table in the din, dout, or toggle 
 * parent jump table 
 *
 * Jump table structure is as follows: 
 *
 *  gpio_I_O_TGL = { 
 *
 *    in_read: [r]    [NULL] [NULL],
 *    out_rwc: [NULL] [w]    [NULL],
 *    out_tgl: [NULL] [NULL] [tgl]
 *
 *  }
 *
 *
 * @param uint32_t RWC
 *
 * pass in DEFINE for accessing the read, write, or clear function in
 * each sub-jump table. READ/WRITE/CLEAR should always be defined 
 * as 0/1/2 
 *
 *
 * @param uint32_t IO_TGL
 *
 * pass in DEFINE for accessing DIN, DOUT, DTGL function in parent jump table 
 *
 *
 * @param GPIO_data* MPI_data
 *
 * struct defined at MPI level for passing values down to gpio registers
 * 
 * (Struct should reflect the GPIO peripheral registers 1:1. See 
 * efm32zg reference manual under GPIO -> 'Register Table' for 
 * registers)
 *
 */

/*
 * ATTN: USE THIS FN FOR BIT-BASHING
 *
 *  FEELING USELESS MIGHT SCRAP THIS FN LATER IUNNO 
 *  I DON'T NEED A TRANSFER FUNCTION, THAT IS ONLY FOR 
 *  USE BETWEEN DEVICES, BUT THIS FN IS INTERNAL
 *
 */ 
int gpio_Data(void* host_ptr, uint32_t RWT, uint32_t port, uint16_t pin){

  MPI_host* efm32zg_host_ptr = (MPI_host*)host_ptr;
  GPIO_data* gpio_data = (GPIO_data*)efm32zg_host_ptr->MPI_data[GPIO_DATA_INDEX];
  
  if(RWT == READ){
      int(*const gpio_IO_ptr)() = gpio_pinin_read[0]; 
      gpio_IO_ptr(gpio_data);
    } else if(RWT == WRITE){
      gpio_data->port = port; 
      gpio_data->P[port].dout = (0x01 << pin); 
	    int(*const gpio_IO_ptr)() = gpio_out[RWT];
      gpio_IO_ptr(gpio_data);
    } else if(RWT == TGL){
      gpio_data->port = port; 
      gpio_data->P[port].douttgl = (0x01 << pin); 
      int(*const gpio_IO_ptr)() = gpio_pinout_tgl[0];
      gpio_IO_ptr(gpio_data);
  }
  return 0;
}

/**********************************************************************************
 *
 * @brief cmu_Init
 *
 * Call to read/write/clear child members of cmu jump table 
 * peripheral members. 
 *
 * Each member in peripheral's parent jump table 
 * is mapped 1:1 with 'Register Table' from CMU section of efm32zg 
 * reference manual. Each peripheral member contains a 
 * read/write/clear function.
 *
 *  Jump table structure is as follows: 
 *
 *  cmu_config_table = {
 *
 *    register_1: [r] [w] [c],
 *    register_2: [r] [w] [c],
 *    register_3: [r] [w] [c],
 *    reg...
 *  }
 *
 * @param uint32_t RWC 
 *
 * pass in DEFINE for accessing the read, write, or clear function in
 * each sub-jump table. READ/WRITE/CLEAR should always be defined 
 * as 0/1/2 
 *
 *
 * @param uint32_t cmu_register
 *
 * pass in DEFINE for accessing single peripheral register in parent jump table
 *
 * @param CMU_periphconf MPI_cmu_periphconf
 *
 * pass in the configuration struct from the middleware layer
 *
 */

int cmu_Init(void* host_ptr){

  MPI_host* efm32zg_host_ptr = (MPI_host*)host_ptr;
  CMU_periphconf* cmu_periphconf = (CMU_periphconf*)efm32zg_host_ptr->MPI_data[CMU_PERIPHCONF_INDEX];

  int(*fn_ptr)() = NULL;
  int ret = 0;
  int i = 0;

  //cmu_periphconf->hfrcoctrl = *CMU_DEFAULT_BOOT_TUNE; //DEFAULT_BOOT_TUNE is defined in the cmu HAL header
  //cmu_periphconf->tuningval = CMU_DEFAULT_BOOT_TUNE;

  fn_ptr = cmu_config_table[CMU_OSCENCMD][WRITE];
  ret = fn_ptr(cmu_periphconf);
  fn_ptr = cmu_config_table[CMU_CMD][WRITE];
  ret = fn_ptr(cmu_periphconf);
  
	while(cmu_config_table[i] != NULL){
		fn_ptr = cmu_config_table[i][WRITE];
		ret = fn_ptr(cmu_periphconf);
    	if(ret > 0){
        return 1;
      }
    i+=1;
	}
	return 0;
}

int cmu_ConfigReg(void* host_ptr, uint32_t config_register){

    MPI_host* efm32zg_host_ptr = (MPI_host*)host_ptr;
    CMU_periphconf* cmu_periphconf = (CMU_periphconf*)efm32zg_host_ptr->MPI_data[CMU_PERIPHCONF_INDEX];
    uint32_t conf_reg = config_register;
    
    int(*fn_ptr)() = cmu_config_table[conf_reg][WRITE];
		return fn_ptr(cmu_periphconf);
}
 
int cmu_QueryReg(void* host_ptr, uint32_t config_register){

    MPI_host* efm32zg_host_ptr = (MPI_host*)host_ptr;
    CMU_periphconf* cmu_periphconf = (CMU_periphconf*)efm32zg_host_ptr->MPI_data[CMU_PERIPHCONF_INDEX];
    uint32_t conf_reg = config_register;
    
    int(*fn_ptr)() = cmu_config_table[conf_reg][READ];
		return fn_ptr(cmu_periphconf);
}
   
    

/*******************************************************************************
 *
 * Call to read/write/clear child members of timer jump table 
 * peripheral members. 
 *
 * Each member in peripheral's parent jump table 
 * is mapped 1:1 with 'Register Table' from TIMER section of efm32zg 
 * reference manual. Each peripheral member contains a 
 * read/write/clear function.
 *
 * Jump table structure is as follows: 
 *
 *  timer_register_table = {
 *
 *    register_1: [r] [w] [c],
 *    register_2: [r] [w] [c],
 *    register_3: [r] [w] [c],
 *    reg...
 *  }
 *
 * @param uint32_t RWC 
 *
 * pass in DEFINE for accessing the read, write, or clear function in
 * each sub-jump table. READ/WRITE/CLEAR should always be defined 
 * as 0/1/2 
 *
 *
 * @param uint32_t timer_register
 *
 * pass in DEFINE for accessing single peripheral register in parent jump table
 * 
 * @param CMU_periphconf MPI_cmu_periphconf
 *
 * pass in the configuration struct from the middleware layer
 *
 */

int timer_Init(void* host_ptr){
   
  MPI_host* efm32zg_host_ptr = (MPI_host*)host_ptr;
  TIMER_periphconf* timer_periphconf = (TIMER_periphconf*)efm32zg_host_ptr->MPI_data[TIMER_PERIPHCONF_INDEX];
  

  NVIC_ClearPendingIRQ(TIMER0_IRQn);
  NVIC_EnableIRQ(TIMER0_IRQn);

  int(*fn_ptr)();
	int ret = 0;
	int i = 0;

	while(timer_config_table[i] != NULL){
		fn_ptr = timer_config_table[i][WRITE];
		ret = fn_ptr(timer_periphconf);
		  if(ret > 0){
        return 1;
      }
	i+=1;
  }
	return 0;
}

int timer_ConfigReg(void* host_ptr, uint32_t config_register){
    
  MPI_host* efm32zg_host_ptr = (MPI_host*)host_ptr;
  TIMER_periphconf* timer_periphconf = (TIMER_periphconf*)efm32zg_host_ptr->MPI_data[TIMER_PERIPHCONF_INDEX];
  uint32_t conf_reg = config_register;

  int(*fn_ptr)();

	fn_ptr = timer_config_table[conf_reg][WRITE];
	return fn_ptr(timer_periphconf);
}

int timer_QueryReg(void* host_ptr, uint32_t config_register){
    
  MPI_host* efm32zg_host_ptr = (MPI_host*)host_ptr;
  TIMER_periphconf* timer_periphconf = (TIMER_periphconf*)efm32zg_host_ptr->MPI_data[TIMER_PERIPHCONF_INDEX];
  uint32_t conf_reg = config_register;

  int(*fn_ptr)();

	fn_ptr = timer_config_table[conf_reg][READ];
	return fn_ptr(timer_periphconf);
}



