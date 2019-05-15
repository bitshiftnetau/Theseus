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

#include "config_example.h"

/*
 *  As you can see, all instances of all device-centric data types are declared at this layer. 
 */

// example_type_1 example_data_1 = { /* Any data initialization that needs doing */ };
// example_type_2 example_config_1 = { /* Any boot config data that needs doing */ };

/*
MPI_ext_dev example_device = {
  .MPI_data = {
    &example_data_1,
    NULL
  },
  .MPI_conf = {
    &example_config_1,
    NULL
  }
}
*/
