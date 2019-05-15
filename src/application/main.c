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

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "mpi_cmu.h"
#include "mpi_gpio.h"
#include "mpi_usart.h"
#include "mpi_types.h"
#include "mpi_port.h"
#include "_app_config.h"

int main(void)
{
  /* Chip errata */
  CHIP_Init();


  /*
   * Here is a rather contrived example of initializing a peripheral.
   * Obviously I would set struct values for a bootup configuration such
   * as this, in the configuration layer but you I think you get the point.
   *
   * If we were using an RTOS we could wrap a function call within a task
   * i.e. a USART read and write cycle.
   *
   */

  //get cmu_periphconf struct from host object
  CMU_periphconf* cmu_periphconf = efm32zg222f32_host.MPI_data[CMU_PERIPHCONF_INDEX];
  
  //setup mask with define (preferably found in the device's CMSIS files)
  uint32_t cmu_oscencmd_mask = CMU_OSCENCMD_HFRCOEN;
  
  //Initialize the data in the host object (again, for a CMU I would do this in the config layer)
  //(also yes I realise that the config struct should be in the MPI_conf array, need to refactor) 
  cmu_periphconf->oscencmd = cmu_oscencmd_mask;
  efm32zg222f32_host.config_register = CMU_OSCENCMD;

  //Configure a single register
  int(* efm32zg_cmu_fn)() = efm32zg222f32_host._periph_periphconf._cmu_config_reg;
  mpi_cmuConfigReg(&efm32zg222f32_host, WRITE, efm32zg_cmu_fn); 

  /* Infinite loop */
  while (1);

}

































