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


#include <stdbool.h>
#include <stdint.h>

#include "mpi_cmu.h"
#include "mpi_types.h"
#include "mpi_port.h"

int mpi_cmuInit(void* host_object, int (*host_cmu_interface_global_fn)()){
  return host_cmu_interface_global_fn(host_object); 
}

int mpi_cmuConfigReg(void* host_object, int (*host_cmu_interface_single_reg_fn)(), uint32_t config_register){
  return host_cmu_interface_single_reg_fn(host_object, config_register); 
}

int mpi_cmuQueryReg(void* host_object, int (*host_cmu_interface_single_reg_fn)(), uint32_t config_register){
  return host_cmu_interface_single_reg_fn(host_object, config_register); 
}


