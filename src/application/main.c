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

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "mpi_cmu.h"
#include "mpi_gpio.h"
#include "mpi_usart.h"
#include "mpi_types.h"
#include "mpi_timer.h"
#include "mpi_port.h"
#include "mpi_ext_dev.h"

#include "_app_config.h"

#include "dw1000_adaptor.h"

//The following main file contains a number of demos for gpio, cmu, usart and timer peripherals
//as well as dummy objects for fns that require external device interaction, in order to be 
//meaningful. 
//
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
//data struct that is made for the external object.i
//
//Uncomment the following in accordance with the usart or venus638 demo (located in the infinite 
//while loop below)
//

/*
uint32_t bufferlen = 32;
uint8_t array[32] = {[0 ... 31] = 0xaa};

int test_fn(void* host_object,  uint32_t read_write, int(* host_usart_fn)(), void* ext_dev_array){

  MPI_host* host_object_ptr = (MPI_host*)host_object;
  volatile int(*host_spi_cs)() = host_object_ptr->_periph_periphconf._gpio_data;
 
  //host_spi_cs(host_object, WRITE, 2, 14);
  host_usart_fn(host_object, read_write, ext_dev_array, bufferlen -1);
  //host_spi_cs(host_object, TGL, 2, 14);

  return 0;
}
*/
  


int main(void)
{
  /* Chip errata */
  CHIP_Init();

  
  //Uncomment the following for basic setup demo with cmu, usart, timer and gpio
  //including LED initialization demo

  //Get the x_Init fns for the respective devices and peripherals
  //
  
  volatile const int(* efm32zg_cmu_init)() = efm32zg222f32_host._periph_periphconf._cmu_init;
  volatile const int(* efm32zg_usart_init)() = efm32zg222f32_host._periph_periphconf._usart_init;
  volatile const int(* efm32zg_gpio_init)() = efm32zg222f32_host._periph_periphconf._gpio_init;
  volatile const int(* efm32zg_timer_init)() = efm32zg222f32_host._periph_periphconf._timer_init;
  
  volatile const int(* efm32zg_cmu_query_reg)() = efm32zg222f32_host._periph_periphconf._cmu_query_reg;
  volatile const int(* efm32zg_cmu_config_reg)() = efm32zg222f32_host._periph_periphconf._cmu_config_reg;
  
  //Get the io functions
  // 
  volatile const int(* efm32zg_gpio_data)() = efm32zg222f32_host._periph_periphconf._gpio_data;
  volatile const int(* efm32zg_timer_delay)() = efm32zg222f32_host._periph_periphconf._timer_delay;
  volatile const int(* efm32zg_usart_data)() = efm32zg222f32_host._periph_periphconf._usart_data;
 
  //Run the x_Init fns through the middleware layer
  //
  mpi_cmuInit(&efm32zg222f32_host, efm32zg_cmu_init);

  CMU_periphconf* cmu_conf = efm32zg222f32_host.MPI_data[CMU_PERIPHCONF_INDEX];
  cmu_conf->oscencmd = CMU_OSCENCMD_HFXOEN;
  mpi_cmuConfigReg(&efm32zg222f32_host, efm32zg_cmu_config_reg, CMU_OSCENCMD);

  //check the status of the HFXO
  //
  do{
    mpi_cmuQueryReg(&efm32zg222f32_host, efm32zg_cmu_query_reg, CMU_STATUS);
  }while(!(cmu_conf->status & CMU_STATUS_HFXORDY));

  //alter the struct member from hfrco to hfxo 
  //
  cmu_conf->cmd = CMU_CMD_HFCLKSEL_HFXO;

  //change the clock by writing to the register via mpi_ConfigReg()
  //
  mpi_cmuConfigReg(&efm32zg222f32_host, efm32zg_cmu_config_reg, CMU_CMD);

  //disable hfrco
  //
  cmu_conf->oscencmd = CMU_OSCENCMD_HFRCODIS;
  mpi_cmuConfigReg(&efm32zg222f32_host, efm32zg_cmu_config_reg, CMU_OSCENCMD);

  mpi_timerInit(&efm32zg222f32_host, efm32zg_timer_init);
  mpi_gpioInit(&efm32zg222f32_host, efm32zg_gpio_init); 
  mpi_usartInit(&efm32zg222f32_host, efm32zg_usart_init);
  
  
  /********************* External Device ******************************/ 
  
  //Uncomment the following to use the Venus638 demo
  
  //volatile const int(* venus638_init)() = venus638._interface._dev_init;
  //volatile const int(* venus638_data)() = venus638._interface._dev_data;
 
  //VENUS_message_io* venus638_message = venus638.MPI_data[VENUS_MSG_INDEX];
  
  //Initiate the device 
  //
  //(NOTE: NOT NECESSARY FOR THIS PARTICULAR DEVICE IN A DEFAULT MODE.
  //       ONLY PLACING HERE AS PART OF DEMO FOR SAKE OF COMPLETENESS)
  //
  //mpi_extdevInit(&efm32zg222f32_host, efm32zg_usart_data, &venus638); 
  

  //Uncomment the following for dw1000 demo
  //volatile const int(* dw1000_init)() = dw1000._interface._dev_init;
  //volatile const int(* dw1000_data)() = dw1000._interface._dev_data;

  //volatile const dw_nodelist* dw_list_test = dw1000.MPI_data[0];

  //volatile const MPI_ext_dev_interface* interface_test = &dw1000._interface;
  
  //volatile const MPI_ext_dev* dw1000_slave = &dw1000;

  //mpi_extdevInit(&efm32zg222f32_host, efm32zg_usart_init, &dw1000, dw_Init);
  
  /********************* GPIO LEDs ************************************/ 
 
  //get the data structs
  //

  mpi_timerDelay(&efm32zg222f32_host, efm32zg_timer_delay, 250);
  mpi_gpioData(&efm32zg222f32_host, efm32zg_gpio_data, WRITE, 2, 10);
    
  mpi_timerDelay(&efm32zg222f32_host, efm32zg_timer_delay, 250);
  mpi_gpioData(&efm32zg222f32_host, efm32zg_gpio_data, WRITE, 2, 11);

  mpi_timerDelay(&efm32zg222f32_host, efm32zg_timer_delay, 250);
  mpi_gpioData(&efm32zg222f32_host, efm32zg_gpio_data, WRITE, 5, 4);

  /********************* GPIO LEDs ************************************/ 
 
   

  /* Infinite loop */
  while (1){

    //Uncomment the following for 3 LED blink with 1s delay
   
    
    mpi_timerDelay(&efm32zg222f32_host, efm32zg_timer_delay, 1000);
    mpi_gpioData(&efm32zg222f32_host, efm32zg_gpio_data, TGL, 2, 10);

    mpi_timerDelay(&efm32zg222f32_host, efm32zg_timer_delay, 1000);
    mpi_gpioData(&efm32zg222f32_host, efm32zg_gpio_data, TGL, 2, 11);
 
    mpi_timerDelay(&efm32zg222f32_host, efm32zg_timer_delay, 1000);
    mpi_gpioData(&efm32zg222f32_host, efm32zg_gpio_data, TGL, 5, 4);
    
 
    //Uncomment the following for usart read/write demo with blinking LED
    /*
    mpi_usartData(&efm32zg222f32_host, efm32zg_usart_data, &array, test_fn, READ);
    mpi_usartData(&efm32zg222f32_host, efm32zg_usart_data, &array, test_fn, WRITE);
    mpi_gpioData(&efm32zg222f32_host, efm32zg_gpio_data, TGL);
    */

    //Uncomment the following for venus gps demo with blinky LED
    /* 
    mpi_gpioData(&efm32zg222f32_host, efm32zg_gpio_data, TGL, 2, 10);
    mpi_gpioData(&efm32zg222f32_host, efm32zg_gpio_data, TGL, 2, 11);
    mpi_gpioData(&efm32zg222f32_host, efm32zg_gpio_data, TGL, 5, 4);
    
    mpi_extdevData(&efm32zg222f32_host, efm32zg_usart_data, &venus638, venus638_data, READ);
    mpi_usartData(&efm32zg222f32_host, efm32zg_usart_data, &venus638_message->message_in, test_fn, WRITE);
    */
    
    //Uncomment the following for the SPI demo with blinking LEDs
    /* 
    mpi_usartData(&efm32zg222f32_host, efm32zg_usart_data, &array, test_fn, WRITE);
  
    for(int i = 0; i < 3; i++){
      mpi_timerDelay(&efm32zg222f32_host, efm32zg_timer_delay, 50);
      mpi_gpioData(&efm32zg222f32_host, efm32zg_gpio_data, TGL, 2, 10);
      mpi_gpioData(&efm32zg222f32_host, efm32zg_gpio_data, TGL, 2, 11);
      mpi_gpioData(&efm32zg222f32_host, efm32zg_gpio_data, TGL, 5, 4);
    }
    */

    //Uncomment for dw1000 demo
    //mpi_timerDelay(&efm32zg222f32_host, efm32zg_timer_delay, 50);
    //mpi_extdevData(&efm32zg222f32_host, efm32zg_usart_data, &dw1000, venus638_data, WRITE);

   }
}

