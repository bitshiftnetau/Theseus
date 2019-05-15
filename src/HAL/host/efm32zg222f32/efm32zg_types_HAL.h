/*
 * efm32zg_types.h
 *
 *  Created on: Oct 3, 2018
 *      Author: access
 */

#ifndef EFM32ZG_TYPES_HPI_H_
#define EFM32ZG_TYPES_HPI_H_

#include <stdbool.h>
#include "efm32zg222f32.h"

extern CMU_TypeDef* cmu;
extern USART_TypeDef* usart;
extern GPIO_TypeDef* gpio;
extern TIMER_TypeDef* timer0;

#define SINGLE_BIT_SHIFT    1
#define SINGLE_BYTE_SHIFT   8
#define DOUBLE_BYTE_SHIFT   16
#define TRIPLE_BYTE_SHIFT   24

#define READ 	  0
#define WRITE 	1
#define CLEAR 	2
#define TGL 	  3

#define PERIPH_REGISTER_TABLE_MEMBERS   32

#define GPIO_READ_WRITE_CLEAR 		3
#define USART_READ_WRITE_CLEAR 		3
#define CMU_READ_WRITE_CLEAR 		  3


/********************
 * CMU TABLE INDEXES
 ********************/

#define CMU_CTRL 			0
#define CMU_HFCORECLKDIV 1
#define CMU_HFRCOCTRL 2
#define CMU_LFCROCTRL 3
#define CMU_AUXHFRCOCTRL 4
#define CMU_CALCTRL 5
#define CMU_CALCNT 6
#define CMU_OSCENCMD 7
#define CMU_CMD 8 
#define CMU_LFCLKSEL 9
#define CMU_STATUS 10
#define CMU_IF 11
#define CMU_IFS 12
#define CMU_IFC 13
#define CMU_IEN 14
#define CMU_HFCORECLKEN0 15
#define CMU_HFPERCLKEN0 16
#define CMU_SYNCBUSY 17
#define CMU_FREEZE 18
#define CMU_LFACLKEN0 19
#define CMU_LFBCLKEN0 20
#define CMU_LFAPRESC0 21
#define CMU_LFBPRESC0 22
#define CMU_PCNTCTRL 23
#define CMU_ROUTE 24
#define CMU_LOCK 25

/**********************
 *      USART
 **********************/

#define USART_READ      0
#define USART_WRITE     1

#define USART_CTRL 			0
#define USART_FRAME 			1
#define USART_TRIG_CTRL 		2
#define USART_STATUS_CMD 	3
#define USART_CLKDIV 		4
#define USART_INT_FLAG 		5
#define USART_IR_CTRL 		6
#define USART_ROUTE 			7
#define USART_INPUT 			8
#define USART_I2S_CTRL 		9
#define USART_SET_GPIO_PINS 	10

/*********************
 *       GPIO 
 *********************/

#define GPIO_CTRL				0
#define GPIO_LOW_PINMODE			1
#define GPIO_HIGH_PINMODE		2
#define GPIO_OUT					3
#define GPIO_PINLOCK				4
#define GPIO_INT_CTRL			5
#define GPIO_EXTINT_LOW_PINS		6
#define GPIO_EXTINT_HIGH_PINS	7
#define GPIO_EXTINT_RISE_EDGE	8
#define GPIO_EXTINT_FALL_EDGE	9
#define GPIO_INT_FLAG			10
#define GPIO_SERIAL_WIRE			11
#define GPIO_INSENSE				12
#define GPIO_CONF_LOCK			13
#define GPIO_EM4_RET				14
#define GPIO_EM4_WAKEUP			15
#define GPIO_EM4_POL				16
#define GPIO_PININ_READ			17
#define GPIO_PINOUT_TGL			18
#define GPIO_EM4_CLR_ALL			19
#define GPIO_EM4_CAUSE			20

#ifndef EFM32ZG222F32_PERIPHERALS
#define EFM32ZG222F32_PERIPHERALS 10
#endif

#define DEVICE_SPECIFIC_NO_OF_PERIPHERALS EFM32ZG222F32_PERIPHERALS

/*
#define acmp0 	1
#define adc0 	  2
#define gpio0  	3
#define i2c0 	  4
#define idac0	  5
#define prs  	  6
#define timer0 	7
#define timer1 	8
#define usart1  9
#define vcmp   	10
*/
typedef struct {
	bool acmp0_on;
	bool adc0_on;
	bool gpio0_on;
	bool i2c0_on;
	bool idac0_on;
	bool prs_on;
	bool timer0_on;
	bool timer1_on;
	bool usart1_on;
	bool vcmp_on;
}EFM32ZG_peripherals;


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



/***********************************************************************
 *                               GPIO
 ***********************************************************************/

typedef struct { 
	uint32_t ctrl;
	uint32_t pinmodeL;
	uint32_t pinmodeH;
	uint32_t pinlockn;
	uint32_t extipselectL;
	uint32_t extipselectH;
	uint32_t extirise;
	uint32_t extifall;
	uint32_t ien;
	uint32_t intf;
	uint32_t swdswc;
	uint32_t insense;
	uint32_t lock;
	uint32_t em4ret;
	uint32_t em4wuen;
	uint32_t em4wupol;
	uint32_t em4wucause;
	uint32_t ports;
}GPIO_periphconf;

typedef struct {
	const uint32_t douttgl;
	uint32_t dout;
	uint32_t din;
	uint32_t ports;
}GPIO_data;

#define GPIO_PERIPHCONF_INDEX   5
#define GPIO_DATA_INDEX         6



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
