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

int test_fn(){

  return 0;
}

int main(void)
{
  /* Chip errata */
  CHIP_Init();

  int(* test_fn_ptr)() = test_fn;


  //MPI_host* efm32zg = &efm32zg222f32_host;
  
  //Get the x_Init fns for the respective devices and peripherals
  int(* efm32zg_cmu_init)() = efm32zg222f32_host._periph_periphconf._cmu_init;
  int(* efm32zg_usart_init)() = efm32zg222f32_host._periph_periphconf._usart_init;
  int(* efm32zg_gpio_init)() = efm32zg222f32_host._periph_periphconf._gpio_init;
  int(* efm32zg_timer_init)() = efm32zg222f32_host._periph_periphconf._timer_init;
  
  //Run the x_Init fns through the middleware layer
  mpi_cmuInit(&efm32zg222f32_host, WRITE, efm32zg_cmu_init);
  mpi_timerInit(&efm32zg222f32_host, WRITE, efm32zg_timer_init);
  mpi_gpioInit(&efm32zg222f32_host, WRITE, efm32zg_gpio_init); 

  mpi_usartInit(&efm32zg222f32_host, WRITE, efm32zg_usart_init);

  //Get the x_io function 
  int(* efm32zg_gpio_data)() = efm32zg222f32_host._periph_periphconf._gpio_data;
  int(* efm32zg_timer_delay)() = efm32zg222f32_host._periph_periphconf._timer_delay;

  //get the data structs
  GPIO_data* gpio_data = efm32zg222f32_host.MPI_data[GPIO_DATA_INDEX];
  

  gpio_data->port = 2; 
  gpio_data->P[2].dout = (0x01 << 10); 
  mpi_timerDelay(&efm32zg222f32_host, 1000, efm32zg_timer_delay);
  mpi_gpioData(&efm32zg222f32_host, WRITE, efm32zg_gpio_data);
    
  gpio_data->P[2].dout = (0x01 << 11); 
  mpi_timerDelay(&efm32zg222f32_host, 1000, efm32zg_timer_delay);
  mpi_gpioData(&efm32zg222f32_host, WRITE, efm32zg_gpio_data);

  gpio_data->port = 5; 
  gpio_data->P[5].dout = (0x01 << 4);
  mpi_timerDelay(&efm32zg222f32_host, 1000, efm32zg_timer_delay);
  mpi_gpioData(&efm32zg222f32_host, WRITE, efm32zg_gpio_data);


  /* Infinite loop */
  while (1){

    gpio_data->port = 2; 
    gpio_data->P[2].douttgl = (0x01 << 10); 
    mpi_timerDelay(&efm32zg222f32_host, 1000, efm32zg_timer_delay);
    mpi_gpioData(&efm32zg222f32_host, TGL, efm32zg_gpio_data);
    
    gpio_data->P[2].douttgl = (0x01 << 11); 
    mpi_timerDelay(&efm32zg222f32_host, 1000, efm32zg_timer_delay);
    mpi_gpioData(&efm32zg222f32_host, TGL, efm32zg_gpio_data);
 
    gpio_data->port = 5; 
    gpio_data->P[5].douttgl = (0x01 << 4);
    mpi_timerDelay(&efm32zg222f32_host, 1000, efm32zg_timer_delay);
    mpi_gpioData(&efm32zg222f32_host, TGL, efm32zg_gpio_data);

   }
}






  /*
    //change cmu clock to hfxo  
  //1. set the values in the config struct
  //2. write the value to host register with _configReg()
  //3. query the status register
  //4. delay for 5ms if not ready
  //5. write the hfrco disable value to host register
  //
 
  //Get the struct and set the values
  CMU_periphconf* cmu_periphconf = efm32zg222f32_host.MPI_data[CMU_PERIPHCONF_INDEX];
  cmu_periphconf->cmd = CMU_CMD_HFCLKSEL_HFXO
  
  //Get the x_configReg() fn
  int(* efm32zg_cmu_config_reg)() = efm32zg222f32_host._periph_periphconf._cmu_config_reg;
 
  //Configure a single register
  efm32zg_cmu_fn = efm32zg222f32_host._periph_periphconf._cmu_config_reg;
  efm32zg222f32_host.config_register = CMU_OSCENCMD;
  mpi_cmuConfigReg(&efm32zg222f32_host, WRITE, efm32zg_cmu_fn); 
 
  do {
    mpi_cmuQueryReg(&efm32zg222f32, READ, efm32zg_cmu_config_reg)
    //do nothing
  } while
  
  
  while(!(CMU->STATUS & CMU_STATUS_HFXORDY));{
		} CMU->CMD = CMU_CMD_HFCLKSEL_HFXO;

	  	if((CMU->STATUS & CMU_STATUS_HFXORDY) == CMU_STATUS_HFXORDY){
	  	 	CMU->OSCENCMD = CMU_OSCENCMD_HFRCODIS;
	}
  */

























