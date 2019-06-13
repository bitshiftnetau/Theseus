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
   

#include "em_device.h"
#include "em_chip.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "mpi_cmu.h"
#include "mpi_gpio.h"
#include "mpi_usart.h"
#include "mpi_types.h"
#include "mpi_timer.h"
#include "mpi_port.h"
#include "_app_config.h"


//Lets say I have an external device that sets a spi pol/alpha through the gpio 
//Instead of writing a new fn for every single host that I use, just have one
//external device object that does some stuff and calls back to the host when 
//it's ready.
//
//The perceived disadvantage to this approach is that every time I want to do 
//something strictly related to the host i.e. blink an LED, I have to make a 
//new fn just for that even though there is no external device involved. 
//
//However, I believe this promotes good coding practice by forcing you to 
//separate out your concerns. Also, this is fairly standard when dealing with
//FreeRTOS and other RTOS', so transitioning to those libraries will be much
//smoother. 
//

//We need a dummy object for this example but this would basically be your
//data struct that is made for the external object

uint32_t bufferlen = 512;
uint8_t array[512];

int test_fn(void* host_ptr, uint32_t read_write, int(* host_usart_fn)(), void* ext_dev_obj){

  return host_usart_fn(host_ptr, read_write, ext_dev_obj, bufferlen -1);
}

int main(void)
{
  /* Chip errata */
  CHIP_Init();

  //Uncomment the following for basic setup demo with cmu, usart, timer and gpio
  //including LED initialization demo
  /*
  //Get the x_Init fns for the respective devices and peripherals
  volatile const int(* efm32zg_cmu_init)() = efm32zg222f32_host._periph_periphconf._cmu_init;
  volatile const int(* efm32zg_usart_init)() = efm32zg222f32_host._periph_periphconf._usart_init;
  volatile const int(* efm32zg_gpio_init)() = efm32zg222f32_host._periph_periphconf._gpio_init;
  volatile const int(* efm32zg_timer_init)() = efm32zg222f32_host._periph_periphconf._timer_init;
  
  //Run the x_Init fns through the middleware layer
  mpi_cmuInit(&efm32zg222f32_host, efm32zg_cmu_init);


  CMU_periphconf* cmu_periphconf = efm32zg222f32_host.MPI_data[CMU_PERIPHCONF_INDEX];
  volatile const int(* efm32zg_cmu_query_reg)() = efm32zg222f32_host._periph_periphconf._cmu_query_reg;
  volatile const int(* efm32zg_cmu_config_reg)() = efm32zg222f32_host._periph_periphconf._cmu_config_reg;
  
  cmu_periphconf->oscencmd = CMU_OSCENCMD_HFXOEN;
  mpi_cmuConfigReg(&efm32zg222f32_host, efm32zg_cmu_config_reg, CMU_OSCENCMD);

  //check the status of the HFXO
  do{
    mpi_cmuQueryReg(&efm32zg222f32_host, efm32zg_cmu_query_reg, CMU_STATUS);
  }while(!(cmu_periphconf->status & CMU_STATUS_HFXORDY));

  //alter the struct member from hfrco to hfxo 
  cmu_periphconf->cmd = CMU_CMD_HFCLKSEL_HFXO;

  //change the clock by writing to the register via mpi_ConfigReg()
  mpi_cmuConfigReg(&efm32zg222f32_host, efm32zg_cmu_config_reg, CMU_CMD);

  //disable hfrco
  cmu_periphconf->oscencmd = CMU_OSCENCMD_HFRCODIS;
  mpi_cmuConfigReg(&efm32zg222f32_host, efm32zg_cmu_config_reg, CMU_OSCENCMD);

  mpi_timerInit(&efm32zg222f32_host, efm32zg_timer_init);
  mpi_gpioInit(&efm32zg222f32_host, efm32zg_gpio_init); 
  mpi_usartInit(&efm32zg222f32_host, efm32zg_usart_init);

  //Get the io functions 
  volatile const int(* efm32zg_gpio_data)() = efm32zg222f32_host._periph_periphconf._gpio_data;
  volatile const int(* efm32zg_timer_delay)() = efm32zg222f32_host._periph_periphconf._timer_delay;
  volatile const int(* efm32zg_usart_data)() = efm32zg222f32_host._periph_periphconf._usart_data;
    
  //get the data structs
  GPIO_data* gpio_data = efm32zg222f32_host.MPI_data[GPIO_DATA_INDEX];

  gpio_data->port = 2; 
  gpio_data->P[gpio_data->port].dout = (0x01 << 10); 
  mpi_timerDelay(&efm32zg222f32_host, efm32zg_timer_delay, 1000);
  mpi_gpioData(&efm32zg222f32_host, efm32zg_gpio_data, WRITE);
    
  gpio_data->P[gpio_data->port].dout = (0x01 << 11); 
  mpi_timerDelay(&efm32zg222f32_host, efm32zg_timer_delay, 1000);
  mpi_gpioData(&efm32zg222f32_host, efm32zg_gpio_data, WRITE);

  gpio_data->port = 5; 
  gpio_data->P[gpio_data->port].dout = (0x01 << 4);
  mpi_timerDelay(&efm32zg222f32_host, efm32zg_timer_delay, 1000);
  mpi_gpioData(&efm32zg222f32_host, efm32zg_gpio_data, WRITE);
  */

  /* Infinite loop */
  while (1){

    //Uncomment the following for 3 LED blink with 1s delay
    /*
    gpio_data->port = 2; 
    gpio_data->P[gpio_data->port].douttgl = (0x01 << 11 | 0x01 << 10);
    mpi_timerDelay(&efm32zg222f32_host, efm32zg_timer_delay, 1000);
    mpi_gpioData(&efm32zg222f32_host, efm32zg_gpio_data, TGL);

    gpio_data->P[gpio_data->port].douttgl = (0x01 << 11); 
    mpi_timerDelay(&efm32zg222f32_host, efm32zg_timer_delay, 1000);
    mpi_gpioData(&efm32zg222f32_host, efm32zg_gpio_data, TGL);
 
    gpio_data->port = 5; 
    gpio_data->P[gpio_data->port].douttgl = (0x01 << 4);
    mpi_timerDelay(&efm32zg222f32_host, efm32zg_timer_delay, 1000);
    mpi_gpioData(&efm32zg222f32_host, efm32zg_gpio_data, TGL);
    */
 
    //Uncomment the following for usart read/write demo with blinking LED
    /*
    mpi_usartData(&efm32zg222f32_host, efm32zg_usart_data, &array, test_fn, READ);
    mpi_usartData(&efm32zg222f32_host, efm32zg_usart_data, &array, test_fn, WRITE);
    mpi_gpioData(&efm32zg222f32_host, efm32zg_gpio_data, TGL);
    */

   }
}

