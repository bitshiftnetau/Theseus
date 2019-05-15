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

#include "efm32zg222f32.h"
#include "efm32zg_types_HPI.h"
#include "efm32zg222f32_adaptor.h"

USART_data usart_data;
USART_error usart_error;
USART_periphconf usart_periphconf;
USART_frameconf usart_frameconf;
USART_status usart_status;
GPIO_data gpio_data;
GPIO_periphconf gpio_periphconf;
CMU_periphconf cmu_periphconf;
TIMER_periphconf timer_periphconf;

MPI_host efm3zg222f32_host = {
  .MPI_data = {
    &usart_data, &usart_periphconf, &usart_error,  &usart_frameconf, &usart_status,
    &gpio_data, &gpio_periphconf,
    &cmu_periphconf,
    &timer_periphconf,
    NULL
  }
};


