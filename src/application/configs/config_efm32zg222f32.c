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
#include "efm32zg_types_HAL.h"
#include "efm32zg222f32_adaptor.h"

/**************
 *    CMU 
 **************/
/*
typedef struct {
  uint32_t ctrl;
  uint32_t hfcoreclkdiv;
  uint32_t hfperclkdiv;
  uint32_t hfrcoctrl;
  uint32_t lfrcoctrl;
  uint32_t auxhfrcoctrl;
  uint32_t calctrl;
  uint32_t calcnt;
  uint32_t oscencmd;
  uint32_t cmd;
  uint32_t lfclksel;
  uint32_t status;
  uint32_t intfread;
  uint32_t intfset;
  uint32_t intfclear;
  uint32_t inten;
  uint32_t hfcoreclken0;
  uint32_t hfperclken0;
  uint32_t syncbusy;
  uint32_t freeze;
  uint32_t lfaclken0;
  uint32_t lfbclken0;
  uint32_t lfapresc0;
  uint32_t lfbpresc0;
  uint32_t pcntctrl;
  uint32_t route;
  uint32_t lock;
  uint32_t* tuningval;
}CMU_periphconf;
*/

// NOTE: 
// .hfcoreclken0 is for DMA, AES and LEUART


CMU_periphconf cmu_periphconf = {

 .hfperclkdiv = CMU_HFPERCLKDIV_HFPERCLKEN, 
 .hfrcoctrl = _CMU_HFRCOCTRL_SUDELAY_DEFAULT | CMU_HFRCOCTRL_BAND_21MHZ,
 .oscencmd = CMU_OSCENCMD_HFRCOEN,
 .cmd = CMU_CMD_HFCLKSEL_HFRCO,
 .hfperclken0 = (CMU_HFPERCLKEN0_USART1 | CMU_HFPERCLKEN0_TIMER0 | CMU_HFPERCLKEN0_GPIO),
 //.intfclear = ???;
 //.inten = ???;

};


/**************
 *    TIMER 
 **************/
/*
typedef struct {
  uint32_t ctrl;
  uint32_t cmd;
  uint32_t status;
  uint32_t ien;
  uint32_t ifr;
  uint32_t ifs;
  uint32_t ifc;
  uint32_t top;
  uint32_t topb;
  uint32_t cnt;
  uint32_t route;
  uint32_t cc0_ctrl;
  uint32_t cc0_ccv;
  uint32_t cc0_ccvp;
  uint32_t cc0_ccvb;
  uint32_t cc1_ctrl;
  uint32_t cc1_ccv;
  uint32_t cc1_ccvp;
  uint32_t cc1_ccvb;
  uint32_t cc2_ctrl;
  uint32_t cc2_ccv;
  uint32_t cc2_ccvp;
  uint32_t cc2_ccvb;
}TIMER_periphconf;
*/

TIMER_periphconf timer_periphconf;


/**************
 *    USART
 **************/
/*
typedef struct {
	uint8_t rxdatax_ctrl;
	uint8_t rxdataxp_ctrl;
	uint8_t rxdoublex_ctrl_0;
	uint8_t rxdoublex_ctrl_1;
	uint8_t rxdoublexp_ctrl_0;
	uint8_t rxdoublexp_ctrl_1;
	uint16_t txdatax_ctrl;
	uint16_t txdataxp_ctrl;
	uint32_t txdoublex_ctrl_0;
	uint32_t txdoublex_ctrl_1;
	uint32_t txdoublexp_ctrl_0;
	uint32_t txdoublexp_ctrl_1;
	uint16_t rxenat0;
	uint16_t txdisat0;
	uint16_t txbreak0;
	uint16_t txtriat0;
	uint16_t unbrxat0;
	uint32_t rxenat1;
	uint32_t txdisat1;
	uint32_t txbreak1;
	uint32_t txtriat1;
	uint32_t unbrxat1;
  uint32_t bitwidth;
}USART_frameconf;

typedef struct {
	uint32_t ctrl;
	uint32_t frame;
	uint32_t trigctrl;
	uint32_t status;
	uint32_t cmd;
	uint32_t clkdiv;
	uint32_t intflag;
	uint32_t irctrl;
	uint32_t route;
	uint32_t input;
	uint32_t i2sctrl;
	uint32_t polalpha;
	uint32_t location;
	uint32_t pins;
}USART_periphconf;
*/


USART_data usart_data;
USART_error usart_error;
USART_status usart_status;

USART_periphconf usart_periphconf = {
    
};

USART_frameconf usart_frameconf = {
  
};


/**************
 *    GPIO 
 **************/
/*
typedef struct {
	uint32_t ctrl;
  uint32_t douttgl;
	uint32_t dout;
	uint32_t din;
 	uint32_t pinmodeL; //pins 0-7
	uint32_t pinmodeH; //pins 8-15
	uint32_t pinlockn; //pins 0-15
}GPIO_data;


typedef struct {
  GPIO_data P[GPIO_PORTS];
  uint32_t extipselectL;
	uint32_t extipselectH;
	uint32_t extirise;
	uint32_t extifall;
	uint32_t ien;
	uint32_t intf;
	uint32_t route; 
	uint32_t insense;
	uint32_t lock;
	uint32_t em4ret;
	uint32_t em4wuen;
	uint32_t em4wupol;
	uint32_t em4wucause;
	uint32_t port;
}GPIO_periphconf;
*/



GPIO_data gpio_data = {
  //.dout = ; 
};
GPIO_periphconf gpio_periphconf = {
  
};


/***********************************
 *    EFM32ZG222F32 HOST OBJECT 
 ***********************************/


MPI_host efm32zg222f32_host = { 
  ._periph_periphconf = {

    ._cmu_init = cmu_Init,
    ._timer_init = timer_Init,
    ._usart_init = usart_Init,
    ._gpio_init = gpio_Init,

    ._cmu_config_reg = cmu_ConfigReg,
    ._timer_config_reg = timer_ConfigReg,
    ._usart_config_reg = usart_ConfigReg,
    ._gpio_config_reg = gpio_ConfigReg,

    ._usart_io = usart_IO,
    ._gpio_io = gpio_IO,
    ._gpio_tgl = gpio_Tgl

  },
  .MPI_data = {
    &usart_data, &usart_periphconf, &usart_error,  &usart_frameconf, &usart_status,
    &gpio_data, &gpio_periphconf,
    &cmu_periphconf,
    &timer_periphconf,
    NULL
  }
};

