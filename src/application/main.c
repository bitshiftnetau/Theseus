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
//void* dummy_ext_obj = NULL;

/*
int ext_DevEx(void* host_object, uint32_t RW, int(*host_gpio_fn)(), void* ext_dev_obj){

  
  //   DO SOME RANDOM EXTERNAL DEVICE LOGIC HERE
   

  //callback to the host when you're ready :)
  return host_gpio_fn(host_object, RW);
}*/

#define GPIO_P_DOUT_DEFAULT 0x00000001UL
#define GPIO_P_DOUT_PIN_10 (GPIO_P_DOUT_DEFAULT << 9)
#define GPIO_P_DOUT_PIN_11 (GPIO_P_DOUT_DEFAULT << 10)

int main(void)
{
  /* Chip errata */
  CHIP_Init();

  int test = 0;

 CMU_TypeDef* cmu_test = CMU;
 GPIO_TypeDef* gpio_test = GPIO;

 cmu_test->CMD = CMU_CMD_HFCLKSEL_HFRCO;
 
 cmu_test->HFRCOCTRL = (_CMU_HFRCOCTRL_SUDELAY_DEFAULT | CMU_HFRCOCTRL_BAND_14MHZ);
 cmu_test->OSCENCMD = CMU_OSCENCMD_HFRCOEN;

 test = 1;

 cmu_test->HFPERCLKDIV = (CMU_HFPERCLKDIV_HFPERCLKEN | _CMU_HFPERCLKDIV_HFPERCLKDIV_HFCLK2); 
 cmu_test->HFPERCLKEN0 = (CMU_HFPERCLKEN0_USART1 | CMU_HFPERCLKEN0_TIMER0 | CMU_HFPERCLKEN0_GPIO);

 test = 2;
 
 gpio_test->P[2].CTRL = GPIO_P_CTRL_DRIVEMODE_STANDARD;
 gpio_test->P[2].MODEH = (GPIO_P_MODEH_MODE10_PUSHPULLDRIVE | GPIO_P_MODEH_MODE11_PUSHPULLDRIVE); 
 gpio_test->P[2].DOUT = 0xFFFFUL;


  /*
  //Get the x_Init fns for the respective devices and peripherals
  int(* efm32zg_cmu_init)() = efm32zg222f32_host._periph_periphconf._cmu_init;
  int(* efm32zg_usart_init)() = efm32zg222f32_host._periph_periphconf._usart_init;
  int(* efm32zg_gpio_init)() = efm32zg222f32_host._periph_periphconf._gpio_init;
  
  //Run the x_Init fns through the middleware layer
  mpi_cmuInit(&efm32zg222f32_host, WRITE, efm32zg_cmu_init);
  mpi_usartInit(&efm32zg222f32_host, WRITE, efm32zg_usart_init);
  mpi_gpioInit(&efm32zg222f32_host, WRITE, efm32zg_gpio_init); 

  //Get the x_io function 
  int(* efm32zg_gpio_io)() = efm32zg222f32_host._periph_periphconf._gpio_io;
  
  //Run the x_io function through the middleware layer
  int ret = mpi_gpioWrite(&efm32zg222f32_host, efm32zg_gpio_io, ext_DevEx, dummy_ext_obj);
  */
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

 
  /* Infinite loop */
  while (1);

}

































