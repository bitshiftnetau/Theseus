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
#include "config_venus638.h"

#include "venus638.h"
#include "venus_adaptor.h"

VENUS_message_io venus_message; 
VENUS_response_store venus_response;
VENUS_nmea_store venus_nmea;
VENUS_config venus_config;

MPI_ext_dev venus638 = {
  .MPI_data = {
    &venus_message, 
    &venus_response, 
    &venus_nmea, 
    NULL
  },
  .MPI_conf = {
    &venus_config, 
    NULL
  }
};
  

