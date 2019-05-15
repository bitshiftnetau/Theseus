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

#include <stdint.h>

#include "mpi_gpio.h"
#include "mpi_types.h"
#include "mpi_port.h"

int mpi_gpioInit(void* host_object, uint32_t read_write_clear, int(*host_gpio_interface_global_fn)()){
  return host_gpio_interface_global_fn(host_object, read_write_clear); 
}

int mpi_gpioConfigReg(void* host_object, uint32_t read_write_clear, int(*host_gpio_interface_single_reg_fn)()){
  return host_gpio_interface_single_reg_fn(host_object, read_write_clear); 
}

int mpi_gpioRead(void* host_object, int(*host_gpio_interface_spi_fn)(), void* ext_dev_object, int(*ext_dev_interface_fn)()){
	return ext_dev_interface_fn(host_object, READ, host_gpio_interface_spi_fn, ext_dev_object);
}

int mpi_gpioWrite(void* host_object, int(*host_gpio_interface_spi_fn)(), void* ext_dev_object, int(*ext_dev_interface_fn)()){
	return ext_dev_interface_fn(host_object, WRITE, host_gpio_interface_spi_fn, ext_dev_object);
}

int mpi_gpioToggle(void* host_object, int(*host_gpio_interface_spi_fn)(), void* ext_dev_object, int(*ext_dev_interface_fn)()){
	return ext_dev_interface_fn(host_object, TOGGLE, host_gpio_interface_spi_fn, ext_dev_object);
}


