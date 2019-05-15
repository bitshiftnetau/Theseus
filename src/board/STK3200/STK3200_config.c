#include <stdint.h>
#include "STK3200_config.h"
//#include "efm32zg_gpio.h"


/*
void lcd_Setup(){


	gpioModeMosi = gpioModePushPull;
	gpioModeMiso = gpioModeInput;
	gpioModeCs   = gpioModePushPull;
	gpioModeClk  = gpioModePushPull;


	//set pins

  gpio->P[PORTA].MODEH = GPIO_P_MODEH_MODE8_PUSHPULL | GPIO_P_MODEH_MODE10_PUSHPULL; //PA8-SELECT, PA10-PWR
	//GPIO->P[PORTD].MODEL = GPIO_P_MODEL_MODE7_PUSHPULL; //PD7-MOSI
	gpio->P[PORTE].MODEH = GPIO_P_MODEH_MODE11_PUSHPULL; //PE11-CS
	
	//GPIO->P[PORTC].MODEH = GPIO_P_MODEH_MODE15_PUSHPULL;
	//PC15-CLK

	//set logic for static build-up

	uint16_t lcdinit = EFM_DISP_PWR | EFM_DISP_SELECT;

	//gpio->P[PORTA].DOUTSET = lcdinit;

}
*/
