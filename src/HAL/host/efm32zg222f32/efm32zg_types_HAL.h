/*
 * efm32zg_types.h
 *
 *  Created on: Oct 3, 2018
 *      Author: access
 */

#ifndef EFM32ZG_TYPES_HAL_H_
#define EFM32ZG_TYPES_HAL_H_

#include <stdbool.h>
#include "efm32zg222f32.h"

extern CMU_TypeDef* cmu;
extern USART_TypeDef* usart;
extern GPIO_TypeDef* gpio;
extern TIMER_TypeDef* timer0;
extern TIMER_TypeDef* timer1;

#define SINGLE_BIT_SHIFT    1
#define SINGLE_BYTE_SHIFT   8
#define DOUBLE_BYTE_SHIFT   16
#define TRIPLE_BYTE_SHIFT   24

#define READ 	  0
#define WRITE 	1
#define CLEAR 	2
//#define TGL 	  3
#define TGL     2

#define PERIPH_REGISTER_TABLE_MEMBERS   32

#define GPIO_READ_WRITE_CLEAR 		3
#define USART_READ_WRITE_CLEAR 		3
#define CMU_READ_WRITE_CLEAR 		  3


/********************
 * CMU TABLE INDEXES
 ********************/

#define CMU_CTRL            0
#define CMU_HFCORECLKDIV    1
#define CMU_HFPERCLKDIV     2
#define CMU_HFRCOCTRL       3
#define CMU_LFRCOCTRL       4
#define CMU_AUXHFRCOCTRL    5
#define CMU_CALCTRL         6
#define CMU_CALCNT          7
#define CMU_LFCLKSEL        8
#define CMU_INTF            9 
#define CMU_INTEN           10
#define CMU_HFCORECLKEN0    11
#define CMU_HFPERCLKEN0     12
#define CMU_FREEZE          13
#define CMU_LFACLKEN0       14
#define CMU_LFBCLKEN0       15
#define CMU_LFAPRESC0       16
#define CMU_LFBPRESC0       17
#define CMU_PCNTCTRL        18
#define CMU_ROUTE           19
#define CMU_LOCK            20
//NULL                      21
#define CMU_OSCENCMD        22
#define CMU_CMD             23
#define CMU_STATUS          24
#define CMU_SYNCBUSY        25


/**********************
 *      USART
 **********************/

#define USART_READ          0
#define USART_WRITE         1

#define USART_CTRL          0
#define USART_FRAME         1
#define USART_TRIGCTRL      2
#define USART_STATUSCMD     3
#define USART_CLKDIV        4
#define USART_INTF          5
#define USART_IRCTRL        6
#define USART_ROUTE         7
#define USART_INPUT         8
#define USART_I2SCTRL       9


/*********************
 *      GPIO 
 *********************/

#define GPIO_INTCTRL      0
#define GPIO_EXTINTL      1
#define GPIO_EXTINTH      2
#define GPIO_EXTINTRISE   3
#define GPIO_EXTINTFALL   4
#define GPIO_INTF         5
#define GPIO_ROUTE        6
#define GPIO_INSENSE      7
#define GPIO_CONFLOCK     8 
#define GPIO_EM4RET       9 
#define GPIO_EM4WU        10
#define GPIO_EM4POL       11
//NULL                  12
#define GPIO_EM4CLR       13
#define GPIO_EM4CAUSE     14


/*********************
 *      TIMER 
 *********************/

#define TIMER_CTRL        1
#define TIMER_IEN         2
#define TIMER_IFRSC       3
#define TIMER_TOP         4
#define TIMER_TOPB        5
#define TIMER_CNT         6
#define TIMER_ROUTE       7
#define TIMER_CC0_CTRL    8
#define TIMER_CC0_CCV     9
#define TIMER_CC0_CCVB    10
#define TIMER_CC1_CTRL    11
#define TIMER_CC1_CCV     12
#define TIMER_CC1_CCVB    13
#define TIMER_CC2_CTRL    14
#define TIMER_CC2_CCV     15
#define TIMER_CC2_CCVB    16
//NULL                  17
#define TIMER_CC0_CCVP    18
#define TIMER_CC1_CCVP    19
#define TIMER_CC2_CCVP    20
#define TIMER_CMD         21
#define TIMER_STATUS      22



#ifndef EFM32ZG222F32_PERIPHERALS
#define EFM32ZG222F32_PERIPHERALS 10
#endif

#define DEVICE_SPECIFIC_NO_OF_PERIPHERALS EFM32ZG222F32_PERIPHERALS


/***********************************************************************
 *                              USART 
 ***********************************************************************/

typedef struct {
	uint32_t rxdatax;
	uint32_t rxdata;
	uint32_t rxdoublex;
	uint32_t rxdouble;
	uint32_t rxdataxp;
	uint32_t rxdoublexp;
	uint32_t txdatax;
	uint32_t txdata;
	uint32_t txdoublex;
	uint32_t txdouble;
}USART_data;

typedef struct {
	bool rxdataxFERR;
	bool rxdataxPERR;
	bool rxdataxpFERR;
	bool rxdataxpPERR;
	bool rxdoublexFERR0;
	bool rxdoublexPERR0;
	bool rxdoublexFERR1;
	bool rxdoublexPERR1;
	bool rxdataxpFERRP;
	bool rxdataxpPERRP;
	bool rxdoublexpFERRP0;
	bool rxdoublexpPERRP0;
	bool rxdoublexpFERRP1;
	bool rxdoublexpPERRP1;
}USART_error;

typedef struct {
	bool rxfullright;
	bool rxdatavright;
	bool txbsright;
	bool txbdright;
	bool rxfull;
	bool rxdatav;
	bool txbl;
	bool txc;
	bool txtri;
	bool rxblock;
	bool master;
	bool txens;
	bool rxens;
}USART_status;

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

#define USART_DATA_INDEX        0
#define USART_PERIPHCONF_INDEX  1
#define USART_ERROR_INDEX       2
#define USART_FRAMECONF_INDEX   3
#define USART_STATUS_INDEX      4

#define USART_READ_WRITE_CLEAR    3
#define USART_READ_WRITE				  2
#define USART_SINGLE_MEMBER			  1
#define USART_DOUBLE_MEMBER			  2

//assign one of these values to the .bitwidth propery of usart_data
#define USART_8_X     0
#define USART_8_N     1
#define USART_16_X    2
#define USART_16_N    3
#define USART_8_XP    4
#define USART_16_XP   5


#define LPOL_LPHA		0
#define LPHA_HPHA		1
#define HPOL_LPHA		2
#define HPOL_HPHA		3

#define USART_SPI_PERCLK_FREQUENCY   CMU_HFRCO_FREQ_24MHZ
#define USART_SPI_BAUDRATE           20000000

#define USART_LPOL_LPHA_MASK			(USART_CTRL_CLKPOL_DEFAULT | USART_CTRL_CLKPHA_DEFAULT)
#define USART_LPOL_HPHA_MASK 		  (USART_CTRL_CLKPOL_DEFAULT | USART_CTRL_CLKPHA_SAMPLETRAILING)
#define USART_HPOL_LPHA_MASK			(USART_CTRL_CLKPOL_IDLEHIGH | USART_CTRL_CLKPHA_DEFAULT)
#define USART_HPOL_HPHA_MASK			(USART_CTRL_CLKPOL_IDLEHIGH | USART_CTRL_CLKPHA_SAMPLETRAILING)

#define USART_SPIMODE_LPOL_LPHA		0
#define USART_SPIMODE_LPOL_HPHA		1
#define USART_SPIMODE_HPOL_LPHA		2
#define USART_SPIMODE_HPOL_HPHA 	3

#define USART_LOC0 0
#define USART_LOC1 1
#define USART_LOC2 2
#define USART_LOC3 3

#define USART_BAUD_9600 (0b00000010011001UL << 6)
#define USART_BAUD_19200 (0b00000010011001UL << 6)


/***********************************************************************
 *                               GPIO
 ***********************************************************************/

#define GPIO_DATA_INDEX         5
#define GPIO_PERIPHCONF_INDEX   6

#define GPIO_PORTS  6

typedef struct {
  uint16_t douttgl;
	uint16_t dout;
	uint16_t din;
}GPIO_port_data;

typedef struct {
  GPIO_port_data P[GPIO_PORTS];
  uint32_t port;
}GPIO_data;

typedef struct {
	uint32_t ctrl;
	uint32_t pinmodeL;
	uint32_t pinmodeH;
	uint32_t pinlockn;
}GPIO_port_conf;

typedef struct { 
  GPIO_port_conf P[GPIO_PORTS];
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


/***********************************************************************
 *                               CMU
 ***********************************************************************/

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


#define CMU_PERIPHCONF_INDEX    7



/***********************************************************************
 *                             TIMER
 ***********************************************************************/

#define TIMERn_TOPms 21277
//#define TIMERn_TOPus 


volatile uint16_t timer0_ms_ticks;
volatile uint16_t timer0_us_ticks;
volatile uint16_t timer1_ms_ticks;
volatile uint16_t timer1_us_ticks;

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

#define TIMER_PERIPHCONF_INDEX 8



#endif /* EFM32ZG_TYPES_H_ */
