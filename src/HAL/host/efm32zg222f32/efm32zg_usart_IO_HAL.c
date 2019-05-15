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
#include "efm32zg222f32.h"

#include "efm32zg_usart_IO_HAL.h"
#include "efm32zg_types_HAL.h"


/* RXDATAX */
const uint8_t USART_RXDATAX_DATABITS 		= _USART_RXDATAX_DATABITS;
const uint16_t USART_RXDATAX_CTRLBIT		= _USART_RXDATAX_CTRLBIT;

/* RXDATAXP */
const uint8_t USART_RXDATAXP_DATABITS 		= _USART_RXDATAXP_DATABITS;
const uint16_t USART_RXDATAXP_CTRLBIT		= _USART_RXDATAXP_CTRLBIT;

/* RXDOUBLEX */
const uint8_t USART_RXDOUBLEX_DATA_0	 	= 0xFF;
const uint8_t USART_RXDOUBLEX_DATA_1	 	= 0xFF;
const uint16_t USART_RXDOUBLEX_CTRLBIT_0	= _USART_RXDOUBLEX_CTRLBIT_0;
const uint32_t USART_RXDOUBLEX_CTRLBIT_1	= _USART_RXDOUBLEX_CTRLBIT_1;

/* RXDOUBLEXP */
const uint8_t USART_RXDOUBLEXP_DATA_0		= 0xFF;
const uint8_t USART_RXDOUBLEXP_DATA_1		= 0xFF;
const uint16_t USART_RXDOUBLEXP_CTRLBIT_0	= _USART_RXDOUBLEXP_CTRLBIT_0;
const uint32_t USART_RXDOUBLEXP_CTRLBIT_1	= _USART_RXDOUBLEXP_CTRLBIT_1;

/* TXDATAX */
const uint8_t USART_TXDATAX_DATABITS 		  = 0xFF;

/* TXDATAXP */
const uint8_t USART_TXDOUBLEX_DATABITS_0 	= 0xFF;

const uint8_t USART_TXDATA_DATABITS       = 0xFF;


/* RXDATAX */
int zg_usartRxdataxRead(USART_data* 		MPI_buffer,
						USART_frameconf* 	MPI_config,
						USART_error* 		MPI_error,
            USART_status* MPI_status)
{

  if((MPI_status->rxfull = ((usart->STATUS & USART_STATUS_RXFULL) >> _USART_STATUS_RXFULL_SHIFT)) > 0){

	//READ FROM RX REGISTER INTO BUFFER
	uint32_t temp_data_buffer = usart->RXDATAX;

		if((MPI_error->rxdataxPERR = (temp_data_buffer & USART_RXDATAX_PARITY_ERR) >> USART_RXDATAX_PARITY_ERR_SHIFT) == 1)
  		{return -1;}
		else if((MPI_error->rxdataxFERR = (temp_data_buffer & USART_RXDATAX_FRAME_ERR) >> USART_RXDATAX_FRAME_ERR_SHIFT) == 1)
			{return -2;}
		else 
      {
				MPI_buffer->rxdatax 	  	= temp_data_buffer;
				MPI_config->rxdatax_ctrl = ((temp_data_buffer & USART_RXDATAX_CTRLBIT) >> USART_RXDATAX_CTRLBIT_SHIFT);
			}
		}
  return 0;
}



/* RXDATA */
int zg_usartRxdataRead(USART_data* 		MPI_buffer,
						USART_frameconf* 	MPI_config,
						USART_error* 		MPI_error,
            USART_status* MPI_status)
{
	MPI_error = NULL;
	MPI_config = NULL;

	if((MPI_status->rxfull = ((usart->STATUS & USART_STATUS_RXFULL) >> _USART_STATUS_RXFULL_SHIFT)) > 0){
		MPI_buffer->rxdata = usart->RXDATA;
	}
	
  return 0;
}


/* RXDATAXP */
int zg_usartRxdataxpRead(USART_data* 		MPI_buffer,
		USART_frameconf* 	MPI_config,
		USART_error* 		MPI_error,
    USART_status* MPI_status)
{
			if((MPI_status->rxfull = ((usart->STATUS & USART_STATUS_RXFULL) >> _USART_STATUS_RXFULL_SHIFT)) > 0){

				//READ FROM RX REGISTER INTO BUFFER
				uint32_t temp_data_buffer = usart->RXDATAXP;

				if((MPI_error->rxdataxpPERR = (temp_data_buffer & USART_RXDATAXP_PARITY_ERR_P) >> USART_RXDATAXP_PARITY_ERR_SHIFT_P) == 1)
				{return -1;}
        else if((MPI_error->rxdataxpFERR = (temp_data_buffer & USART_RXDATAXP_FRAME_ERR_P) >> USART_RXDATAXP_FRAME_ERR_SHIFT_P) == 1)
				{return -2;}
				else {
					MPI_buffer->rxdataxp 		 = temp_data_buffer;
					MPI_config->rxdataxp_ctrl = ((temp_data_buffer & USART_RXDATAXP_CTRLBIT) >> USART_RXDATAXP_CTRLBIT_SHIFT);
				}
			}

	return 0;
}


/* RXDOUBLEX */
int zg_usartRxdoublexRead(USART_data* 		  MPI_buffer,
		                      USART_frameconf* 	MPI_config,
		                      USART_error* 		  MPI_error,
                          USART_status*     MPI_status)
{
				if((MPI_status->rxfull = ((usart->STATUS & USART_STATUS_RXFULL) >> _USART_STATUS_RXFULL_SHIFT)) > 0){

					//READ FROM RX REGISTER INTO BUFFER
					uint32_t temp_data_buffer = usart->RXDOUBLEX;

					if((MPI_error->rxdoublexPERR0 = (temp_data_buffer & USART_RXDOUBLEX_PARITY_ERR_0) >> USART_RXDOUBLEX_PARITY_ERR_SHIFT_0) == 1)
					{return -1;}
					else if((MPI_error->rxdoublexFERR0 = (temp_data_buffer & USART_RXDOUBLEX_FRAME_ERR_0) >> USART_RXDOUBLEX_FRAME_ERR_SHIFT_0) == 1)
					{return -2;}
					else if((MPI_error->rxdoublexPERR1 = (temp_data_buffer & USART_RXDOUBLEX_PARITY_ERR_1) >> USART_RXDOUBLEX_PARITY_ERR_SHIFT_1) == 1)
          {return -3;}
					else if((MPI_error->rxdoublexFERR1 = (temp_data_buffer & USART_RXDOUBLEX_FRAME_ERR_1) >> USART_RXDOUBLEX_FRAME_ERR_SHIFT_1) == 1)
					{return -4;}
					{
						MPI_buffer->rxdoublex = (temp_data_buffer & USART_RXDOUBLEX_DATA_0) | (((temp_data_buffer >> USART_RXDOUBLEX_DATA_SHIFT_1) & USART_RXDOUBLEX_DATA_1) << SINGLE_BYTE_SHIFT);
						MPI_config->rxdoublex_ctrl_0 = ((temp_data_buffer & USART_RXDOUBLEX_CTRLBIT_0) >> USART_RXDOUBLEX_CTRLBIT_SHIFT_0);
						MPI_config->rxdoublex_ctrl_1 = ((temp_data_buffer & USART_RXDOUBLEX_CTRLBIT_1) >> USART_RXDOUBLEX_CTRLBIT_SHIFT_1);
					}
				}
		return 0;

}



/* RXDOUBLE */
int zg_usartRxdoubleRead(USART_data* 		MPI_buffer,
		USART_frameconf* 	MPI_config,
		USART_error* 		MPI_error,
    USART_status* MPI_status)
{
	MPI_error = NULL;
	MPI_config = NULL;

		if((MPI_status->rxfull = ((usart->STATUS & USART_STATUS_RXFULL) >> _USART_STATUS_RXFULL_SHIFT)) > 0){
				MPI_buffer->rxdouble = usart->RXDOUBLE;
		}
	return 0;
}



/* RXDOUBLEXP */
int zg_usartRxdoublexpRead(USART_data* 		MPI_buffer,
		USART_frameconf* 	MPI_config,
		USART_error* 		MPI_error,
    USART_status* MPI_status)
{
			if((MPI_status->rxfull = ((usart->STATUS & USART_STATUS_RXFULL) >> _USART_STATUS_RXFULL_SHIFT)) > 0){

				//READ FROM RX REGISTER INTO BUFFER
				uint32_t temp_data_buffer = usart->RXDOUBLEXP;

				if((MPI_error->rxdoublexpPERRP0 = (temp_data_buffer & USART_RXDOUBLEXP_PARITY_ERR_0) >> USART_RXDOUBLEXP_PARITY_ERR_SHIFT_0) == 1)
				{return -1;}
				else if((MPI_error->rxdoublexpFERRP0 = (temp_data_buffer & USART_RXDOUBLEXP_FRAME_ERR_0) >> USART_RXDOUBLEXP_FRAME_ERR_SHIFT_0) == 1)
				{return -2;}
				else if((MPI_error->rxdoublexpPERRP1 = (temp_data_buffer & USART_RXDOUBLEXP_PARITY_ERR_1) >> USART_RXDOUBLEXP_PARITY_ERR_SHIFT_1) == 1)
				{return -3;}
				else if((MPI_error->rxdoublexpFERRP1 = (temp_data_buffer & USART_RXDOUBLEXP_FRAME_ERR_1) >> USART_RXDOUBLEXP_FRAME_ERR_SHIFT_1) == 1)
				{return -4;}
        else {

					MPI_buffer->rxdoublexp = (temp_data_buffer & USART_RXDOUBLEXP_DATA_0) | (((temp_data_buffer >> USART_RXDOUBLEXP_DATA_SHIFT_1) & USART_RXDOUBLEXP_DATA_1) << SINGLE_BYTE_SHIFT);
          MPI_config->rxdoublexp_ctrl_0 = ((temp_data_buffer & USART_RXDOUBLEXP_CTRLBIT_0) >> USART_RXDOUBLEXP_CTRLBIT_SHIFT_0);
					MPI_config->rxdoublexp_ctrl_1 = ((temp_data_buffer & USART_RXDOUBLEXP_CTRLBIT_1) >> USART_RXDOUBLEXP_CTRLBIT_SHIFT_1);
				}
			}
	return 0;
}



/* TXDATAX */
int zg_usartTxdataxWrite(USART_data* 		MPI_buffer,
	   	   	   	   	   	 USART_frameconf* 	MPI_config,
	   	   	   	   	   	 USART_error* 		MPI_error,
                       USART_status* MPI_status)
{
	MPI_error = NULL;

	if(MPI_config != NULL){

  	uint16_t temp_tx_buffer = (MPI_buffer->txdatax & USART_TXDATAX_DATABITS) 
    | (MPI_config->txdatax_ctrl << SINGLE_BYTE_SHIFT) 
    | MPI_config->rxenat0 
    | MPI_config->txdisat0 
    | MPI_config->txbreak0 
    | MPI_config->txtriat0 
    | MPI_config->unbrxat0;

		if((USART_STATUS_TXC & usart->STATUS) > 0){
			usart->TXDATAX = temp_tx_buffer;
		}
  } else {
  
    uint16_t temp_tx_buffer = (MPI_buffer->txdatax & USART_TXDATAX_DATABITS) 
    | (MPI_config->txdatax_ctrl << SINGLE_BYTE_SHIFT);
 
		if((USART_STATUS_TXC & usart->STATUS) > 0){
			usart->TXDATAX = temp_tx_buffer;
		}
  }
  usart->IFC |= USART_STATUS_TXC;
	return 0;
}



/* TXDATA */
int zg_usartTxdataWrite(USART_data* 		MPI_buffer,
	   	   	   	   	      USART_frameconf* 	MPI_config,
						            USART_error* 		MPI_error,
                        USART_status* MPI_status)
{
	MPI_error = NULL;
  MPI_config = NULL;

	if((USART_STATUS_TXC & usart->STATUS) > 0){
		usart->TXDATAX = MPI_buffer->txdata & USART_TXDATA_DATABITS;
	}
	usart->IFC |= USART_STATUS_TXC;
	return 0;
}




/* TXDOUBLEX */
int zg_usartTxdoublexWrite(USART_data* 			MPI_buffer,
	 	 	   	   	   	   USART_frameconf* 	MPI_config,
	 	 	   	   	   	   USART_error* 		MPI_error,
                     USART_status* MPI_status)
{
	MPI_error = NULL;

uint32_t temp_tx_buffer;

	if(MPI_config != NULL){

    temp_tx_buffer = (MPI_buffer->txdoublex & USART_TXDOUBLEX_DATABITS_0)
							
	      |(MPI_config->txdoublex_ctrl_0 << SINGLE_BYTE_SHIFT) 
              | MPI_config->rxenat0
              | MPI_config->txdisat0
              | MPI_config->txbreak0
              | MPI_config->txtriat0
              | MPI_config->unbrxat0
              |(((MPI_buffer->txdoublex >> SINGLE_BYTE_SHIFT) & USART_TXDOUBLEX_DATABITS_0) << DOUBLE_BYTE_SHIFT)
 	      |(MPI_config->txdoublex_ctrl_1 << TRIPLE_BYTE_SHIFT)
              | MPI_config->rxenat1
              | MPI_config->txdisat1
              | MPI_config->txbreak1
              | MPI_config->txtriat1
              | MPI_config->unbrxat1;

		if((USART_STATUS_TXC & usart->STATUS) > 0){
				usart->TXDOUBLEX = temp_tx_buffer;
			}
		
  } else {
    
    temp_tx_buffer = (MPI_buffer->txdoublex & USART_TXDOUBLEX_DATABITS_0)
							|(MPI_buffer->txdoublex << DOUBLE_BYTE_SHIFT);
	
    if((USART_STATUS_TXC & usart->STATUS) > 0){
				usart->TXDOUBLEX = temp_tx_buffer;
			}
  }
  usart->IFC |= USART_STATUS_TXC;
  return 0;
}



/* TXDOUBLE */
int zg_usartTxdoubleWrite(USART_data* 		MPI_buffer,
	   	   	   	   	   	  USART_frameconf* 	MPI_config,
	   	   	   	   	   	  USART_error* 		MPI_error,
                        USART_status* MPI_status)
{
	MPI_config = NULL;
	MPI_error = NULL;

		if((USART_STATUS_TXC & usart->STATUS) > 0){
			usart->TXDATAX = MPI_buffer->txdouble;
		}
		usart->IFC |= USART_STATUS_TXC;
	return 0;
}




int (*const usart_rx_8_xp[USART_SINGLE_MEMBER])() =
	{zg_usartRxdataxpRead};

int (*const usart_rx_16_xp[USART_SINGLE_MEMBER])() = 
  {zg_usartRxdoublexpRead};

int (*const usart_rxtx_data_x[USART_READ_WRITE])() =
	{zg_usartRxdataxRead, zg_usartTxdataxWrite};

int (*const usart_rxtx_data[USART_READ_WRITE])() =
	{zg_usartRxdataRead, zg_usartTxdataWrite};

int (*const usart_rxtx_double_x[USART_READ_WRITE])() =
	{zg_usartRxdoublexRead, zg_usartTxdoublexWrite};

int (*const usart_rxtx_double[USART_READ_WRITE])() =
	{zg_usartRxdoubleRead, zg_usartTxdoubleWrite};

/*
 *  Bitwidth jump tables
 */


void usart_assign_rx_data_8_x(USART_data* host_obj_buffer, uint32_t* slave_obj_data_array, uint32_t index){
  slave_obj_data_array[index] = host_obj_buffer->rxdatax;
}

void usart_assign_rx_data_8(USART_data* host_obj_buffer, uint32_t* slave_obj_data_array, uint32_t index){
  slave_obj_data_array[index] = host_obj_buffer->rxdata;
}

void usart_assign_rx_data_16_x(USART_data* host_obj_buffer, uint32_t* slave_obj_data_array, uint32_t index){
  slave_obj_data_array[index] = host_obj_buffer->rxdoublex;
}

void usart_assign_rx_data_16(USART_data* host_obj_buffer, uint32_t* slave_obj_data_array, uint32_t index){
  slave_obj_data_array[index] = host_obj_buffer->rxdouble;
}

void usart_assign_rx_data_8_xp(USART_data* host_obj_buffer, uint32_t* slave_obj_data_array, uint32_t index){
  slave_obj_data_array[index] = host_obj_buffer->rxdataxp; 
}

void usart_assign_rx_data_16_xp(USART_data* host_obj_buffer, uint32_t* slave_obj_data_array, uint32_t index){
  slave_obj_data_array[index] = host_obj_buffer->rxdoublexp;
}



void usart_assign_tx_data_8_x(USART_data* host_obj_buffer, uint32_t* slave_obj_data_array, uint32_t index){
  host_obj_buffer->txdatax = slave_obj_data_array[index];
 }

void usart_assign_tx_data_8(USART_data* host_obj_buffer, uint32_t* slave_obj_data_array, uint32_t index){
  host_obj_buffer->txdata = slave_obj_data_array[index];
}

void usart_assign_tx_data_16_x(USART_data* host_obj_buffer, uint32_t* slave_obj_data_array, uint32_t index){
  host_obj_buffer->txdoublex = slave_obj_data_array[index];
 }

void usart_assign_tx_data_16(USART_data* host_obj_buffer, uint32_t* slave_obj_data_array, uint32_t index){
  host_obj_buffer->txdouble = slave_obj_data_array[index];
}

void(*const usart_rx_bitwidth_table[USART_REGISTER_TABLES])() = 
{
  usart_assign_rx_data_8_x, 
  usart_assign_rx_data_8, 
  usart_assign_rx_data_16_x, 
  usart_assign_rx_data_16, 
  usart_assign_rx_data_8_xp, 
  usart_assign_rx_data_16_xp, 

};

void(*const usart_tx_bitwidth_table[USART_REGISTER_TABLES])() =
{
  usart_assign_tx_data_8_x, 
  usart_assign_tx_data_8, 
  usart_assign_tx_data_16_x, 
  usart_assign_tx_data_16
};

void(*const *const usart_IO_host_slave_transfer[USART_READ_WRITE])() = 
{
  usart_rx_bitwidth_table, 
  usart_tx_bitwidth_table
};


int (*const *const usart_IO_table[USART_REGISTER_TABLES])() =
{
	usart_rxtx_data_x,
	usart_rxtx_data,
	usart_rxtx_double_x,
	usart_rxtx_double,
	usart_rx_8_xp,
  usart_rx_16_xp
};


