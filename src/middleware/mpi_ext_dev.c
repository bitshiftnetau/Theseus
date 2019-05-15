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


#include "mpi_ext_dev.h"

/*
 * As you can see not all the fns are complete (missing mpi_extdevOff, mpi_extdevReset etc)
 *
 * Although initially most of the fns appear identical, I wanted to have separate middleware fns to account for future feature additions, flexibility, readability at the application level and most importantly: any potential issues with thread safety and reentrance. 
 */

int mpi_extdevInit(void* host_object, int(*host_comm_interface_fn)(), void* ext_dev_object, int(*ext_dev_interface_fn)()){
  return ext_dev_interface_fn(host_comm_interface_fn);
}

int mpi_extdevConfigReg(void* host_object, int(*host_comm_interface_fn)(), void* ext_dev_object, int(*ext_dev_interface_fn)()){
  return ext_dev_interface_fn(host_comm_interface_fn);
}

int mpi_extdevStop(void* host_object, int(*host_comm_interface_fn)(), void* ext_dev_object, int(*ext_dev_interface_fn)()){
	return ext_dev_interface_fn(host_comm_interface_fn);
}

int mpi_extdev_IO(void* host_object, int(*host_comm_interface_fn)(), void* ext_dev_object, int(*ext_dev_interface_fn)(), int(*mpi_host_comm_IO_fn)()){
  return mpi_host_comm_IO_fn(host_object, host_comm_interface_fn, ext_dev_object, ext_dev_interface_fn);
}

