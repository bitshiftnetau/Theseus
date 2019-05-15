/*
 * device_xxx_spi.h
 *
 *  Created on: Oct 9, 2018
 *      Author: access
 */

#ifndef EFM32ZG_USART_IO_HAL_H_
#define EFM32ZG_USART_IO_HAL_H_

#include "efm32zg_types_HAL.h"

#define USART_LOCATION_VARIANTS 	4
#define USART_POL_PHA_VARIANTS 		4

#define SPI_CONNECTED_DEVICES 		2
#define SPI_CS_TGL_COMBINATIONS 		(SPI_CONNECTED_DEVICES * 2)

#define FERR0_ERROR -1
#define PERR0_ERROR -2
#define FERR1_ERROR -3
#define PERR1_ERROR -4


#define USART_RX_XP 		0
#define USART_RX_8		  0
#define USART_RX_16		  1

#define USART_DATA_X 	  1
#define USART_DATA 		  2
#define USART_DOUBLE_X 	3
#define USART_DOUBLE		4

/*
 * whole-register bit-widths for tx/rx registers
 *
 * rxdatax 		= 16
 * rxdata 		= 8
 * rxdoublex	= 32
 * rxdouble 	= 16
 * rxdataxp		= 16
 * rxdoublexp	= 32
 * txdatax 		= 16
 * txdata		= 8
 * txdoublex	= 32
 * txdouble		= 16
 *
 * data-length bitwidths for tx/rx registers
 *
 * rxdatax 		= 8
 * rxdata 		= 8
 * rxdoublex	= 2 separated 8-bit fields
 * rxdouble 	= 16
 * rxdataxp		= 8
 * rxdoublexp	= 2 separated 8-bit fields
 * txdatax 		= 8
 * txdata		= 8
 * txdoublex	= 2 separated 8-bit fields
 * txdouble		= 16
 *
 */


#define USART_RXDATAX_BUFFERSIZE 	16
#define USART_RXDATAXP_BUFFERSIZE 	16
#define USART_RXDATA_BUFFERSIZE 		8
#define USART_RXDOUBLEX_BUFFERSIZE 	32
#define USART_RXDOUBLE_BUFFERSIZE	16
#define USART_RXDOUBLEXP_BUFFERSIZE 	32

#define USART_TXDATAX_BUFFERSIZE 	16
#define USART_TXDATA_BUFFERSIZE 		8
#define USART_TXDOUBLEX_BUFFERSIZE 	32
#define USART_TXDOUBLE_BUFFERSIZE	16

/*
#define USART_RXDATAX_LOOP 			4
#define USART_RXDATAXP_LOOP 		4
#define USART_RXDATA_LOOP 			4

#define USART_RXDOUBLEX_LOOP 		2
#define USART_RXDOUBLE_LOOP			2
#define USART_RXDOUBLEXP_LOOP 	2

#define USART_TXDATAX_LOOP 			4
#define USART_TXDATA_LOOP 		  4
#define USART_TXDOUBLEX_LOOP 		2
#define USART_TXDOUBLE_LOOP			2
*/

#define _USART_RXDATAX_DATABITS  0b0000000011111111
#define _USART_RXDATAXP_DATABITS 0b0000000011111111

#define _USART_RXDATAX_CTRLBIT 		              (1 << 8)
#define _USART_RXDATAXP_CTRLBIT 		            (1 << 8)
#define USART_RXDATAX_CTRLBIT_SHIFT             8
#define USART_RXDATAXP_CTRLBIT_SHIFT            8

#define _USART_RXDOUBLEX_CTRLBIT_0 	            (1 << 8)
#define _USART_RXDOUBLEX_CTRLBIT_1 	            (1 << 24)
#define _USART_RXDOUBLEXP_CTRLBIT_0 	          (1 << 8)
#define _USART_RXDOUBLEXP_CTRLBIT_1 	          (1 << 24)

#define USART_RXDOUBLEX_CTRLBIT_SHIFT_0         8
#define USART_RXDOUBLEX_CTRLBIT_SHIFT_1         24
#define USART_RXDOUBLEXP_CTRLBIT_SHIFT_0        8
#define USART_RXDOUBLEXP_CTRLBIT_SHIFT_1        24

#define USART_RXDATAX_FRAME_ERR_SHIFT 		      15
#define USART_RXDATAX_PARITY_ERR_SHIFT 		      14

#define USART_RXDATAXP_FRAME_ERR_SHIFT 		      15
#define USART_RXDATAXP_PARITY_ERR_SHIFT 		    14

#define USART_RXDOUBLEX_FRAME_ERR_SHIFT_1 	    31
#define USART_RXDOUBLEX_PARITY_ERR_SHIFT_1 	    30
#define USART_RXDOUBLEX_FRAME_ERR_SHIFT_0  	    15
#define USART_RXDOUBLEX_PARITY_ERR_SHIFT_0 	    14

#define USART_RXDATAXP_FRAME_ERR_SHIFT_P  	    15
#define USART_RXDATAXP_PARITY_ERR_SHIFT_P 	    14

#define USART_RXDOUBLEXP_FRAME_ERR_SHIFT_1 	    31
#define USART_RXDOUBLEXP_PARITY_ERR_SHIFT_1     30
#define USART_RXDOUBLEXP_FRAME_ERR_SHIFT_0      15
#define USART_RXDOUBLEXP_PARITY_ERR_SHIFT_0     14

#define USART_RXDOUBLEXP_DATA_SHIFT_0		        0
#define USART_RXDOUBLEXP_DATA_SHIFT_1 	        16
#define USART_RXDOUBLEX_DATA_SHIFT_0 		        0
#define USART_RXDOUBLEX_DATA_SHIFT_1            16	

#define USART_RXDATAX_FRAME_ERR 	              (1 << USART_RXDATAX_FRAME_ERR_SHIFT)
#define USART_RXDATAX_PARITY_ERR                (1 << USART_RXDATAX_PARITY_ERR_SHIFT)

#define USART_RXDOUBLEX_FRAME_ERR_1             (1 << 31)
#define USART_RXDOUBLEX_PARITY_ERR_1            (1 << 30)
#define USART_RXDOUBLEX_FRAME_ERR_0             (1 << 15)
#define USART_RXDOUBLEX_PARITY_ERR_0            (1 << 14)

#define USART_RXDATAXP_FRAME_ERR_P              (1 << 15)
#define USART_RXDATAXP_PARITY_ERR_P             (1 << 14)

#define USART_RXDOUBLEXP_FRAME_ERR_1            (1 << 31)
#define USART_RXDOUBLEXP_PARITY_ERR_1           (1 << 30)
#define USART_RXDOUBLEXP_FRAME_ERR_0            (1 << 15)
#define USART_RXDOUBLEXP_PARITY_ERR_0           (1 << 14)


char   transmitBuffer[3];
#define BUFFERSIZE    				(sizeof(transmitBuffer) / sizeof(char))
char   receiveBuffer[BUFFERSIZE];

#define USART_REGISTER_TABLES 6

#ifndef READ
#define READ		0
#endif

#ifndef WRITE
#define WRITE	1
#endif

#ifndef CLEAR
#define CLEAR	2
#endif

//Index defines for usart_rx_tx_table
//
#define USART_RXTX_X_8     0
#define USART_RXTX_8       1
#define USART_RXTX_X_16    2
#define USART_RXTX_16      3  
#define USART_RXDATA_XP_8  4
#define USART_RXDATA_XP_16 5

int(*const usart_frameconf_rwc[USART_READ_WRITE_CLEAR])();
int(*const *const usart_IO_table[USART_REGISTER_TABLES])();
void(*const *const usart_IO_host_slave_transfer[USART_READ_WRITE])();


#endif /* EFM32ZG_SPI_H_ */



