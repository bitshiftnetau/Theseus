/*
 * efm32zg_spi.h
 *
 *  Created on: Oct 3, 2018
 *      Author: access
 */


#ifndef EFM32ZG_USART_HPI_H_
#define EFM32ZG_USART_HPI_H_

#include <stdbool.h>

#include "efm32zg222f32.h"
#include "efm32zg_types_HPI.h"



/*
 * fns for usart HPI
 *
 * ctrl: 				RWC
 * frame: 				RWC
 * trigctrl: 			RWC
 * cmd: 				W
 * status:				R
 * clkdiv:				RWC
 * rxdatax:				R
 * rxdata:				R
 * rxdoublex:			R
 * rxdouble:			R
 * rxdataxp:			R
 * rxdoublexp:			R
 * txdatax:				W
 * txdata:				W
 * txdoublex:			W
 * txdouble:			W
 * int flag read:		R
 * int flag set:			W
 * int flag clr:			C
 * irctrl:				RWC
 * route:				RWC
 * input:				RWC
 * i2sctrl:				RWC
 *
 * jump tables:
 *
 * ctrl					rwc
 * frame				rwc
 * trigctrl				rwc
 * status + cmd			read status, write cmd, clear cmd
 * datax: 				rwc
 * data:  				rwc
 * doublex:				rwc
 * double:				rwc
 * rxdataxp/rxdoublexp  8bit/16bit read
 * int flag: 			rwc
 * irctrl:				rwc
 * route: 				rwc
 * input:				rwc
 * i2sctrl:				rwc
 *
 **/

int (*const *const usart_config_table[PERIPH_REGISTER_TABLE_MEMBERS])();

/*
int zg_usartPeriperalRWC(uint32_t RWC,
						USART_periphconf *usart_periphconf,
						int (*const *const usart_register_table[])(),
						int peripheral,
						uint32_t bitmask);
*/

#endif /* EFM32ZG_SPI_H_ */
