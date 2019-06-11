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

#include "mpi_port.h"
#include "mpi_types.h"
#include "config_efm32zg222f32.h"
#include "efm32zg_app.h"

#include "efm32zg222f32.h"
#include "efm32zg_types_HAL.h"
#include "efm32zg222f32_adaptor.h"


/*******************************
 *          TIMER
 ******************************/

int timer_Delay(void* host_ptr, uint32_t dlyTicks)
{
  host_ptr = NULL;

  /*
  MPI_host* efm32zg_host_ptr = (MPI_host*)host_ptr;
  TIMER_periphconf* timer_periphconf = (TIMER_periphconf*)efm32zg_host_ptr->MPI_data[TIMER_PERIPHCONF_INDEX];

  efm32zg_host_ptr->config_register = ;
  timer_ConfigReg(host_ptr, WRITE);
  */
 
  TIMER_TypeDef * timer_0 = TIMER0; 
  timer0_ms_ticks = 0;
  timer_0->CMD = TIMER_CMD_START;
  while (timer0_ms_ticks < dlyTicks);
  timer_0->CMD = TIMER_CMD_STOP;

  return 0;
}


