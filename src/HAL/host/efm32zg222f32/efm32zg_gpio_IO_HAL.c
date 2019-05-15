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
 
#include "efm32zg_types_HPI.h"
#include "efm32zg_gpio_IO_HPI.h"


int zg_gpioReadIn(GPIO_data* MPI_data)
{
	MPI_data->din = gpio->P[MPI_data->ports].DIN;
	return 0;
}

int zg_gpioOutTgl(GPIO_data* MPI_data)
{
	gpio->P[MPI_data->ports].DOUTTGL = MPI_data->douttgl;
	return 0;
}

int zg_gpioOutRead(GPIO_data* MPI_data)
{
	MPI_data->dout = gpio->P[MPI_data->ports].DOUT;
	return 0;

}

int zg_gpioOutWrite(GPIO_data* MPI_data)
{
	gpio->P[MPI_data->ports].DOUT |= MPI_data->dout;
	return 0;
}

int zg_gpioOutClr(GPIO_data* MPI_data)
{
	gpio->P[MPI_data->ports].DOUT &= ~MPI_data->dout;
	return 0;
}

int(*const gpio_pinin_read 		[GPIO_READ_WRITE_CLEAR])()= 
{zg_gpioReadIn, NULL, NULL};

int(*const gpio_out				    [GPIO_READ_WRITE_CLEAR])()= 
{zg_gpioOutRead, zg_gpioOutWrite, zg_gpioOutClr};

int(*const gpio_pinout_tgl 		[GPIO_READ_WRITE_CLEAR])()= 
{NULL, NULL, zg_gpioOutTgl};

void gpio_assign_rx_data(GPIO_data* host_obj_buffer, uint32_t* slave_obj_data_array, uint32_t index){
  slave_obj_data_array[index] = host_obj_buffer->din;
}
void gpio_assign_tx_data(GPIO_data* host_obj_buffer, uint32_t* slave_obj_data_array, uint32_t index){
  host_obj_buffer->dout = slave_obj_data_array[index];
}

void(*const gpio_IO_host_slave_transfer[USART_READ_WRITE])() = 
{
  gpio_assign_rx_data,
  gpio_assign_tx_data  
};

int(*const *const gpio_I_O_TGL[GPIO_READ_WRITE_CLEAR])() = 
{
  gpio_pinin_read, 
  gpio_out, 
  gpio_pinout_tgl
};

