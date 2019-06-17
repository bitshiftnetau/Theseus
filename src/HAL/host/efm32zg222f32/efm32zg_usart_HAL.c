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

#include "efm32zg_usart_HAL.h"
#include "efm32zg_types_HAL.h"

int (*const usart_ctrl_table[USART_READ_WRITE_CLEAR])();
int (*const usart_frame_table[USART_READ_WRITE_CLEAR])();
int (*const usart_trig_ctrl_table[USART_READ_WRITE_CLEAR])();
int (*const usart_status_cmd_table[USART_READ_WRITE_CLEAR])();
int (*const usart_clkdiv_table[USART_READ_WRITE_CLEAR])();
int (*const usart_int_flag_table[USART_READ_WRITE_CLEAR])();
int (*const usart_ir_ctrl_table[USART_READ_WRITE_CLEAR])();
int (*const usart_route_table[USART_READ_WRITE_CLEAR])();
int (*const usart_input_table[USART_READ_WRITE_CLEAR])();
int (*const usart_i2s_ctrl_table[USART_READ_WRITE_CLEAR])();

int (*const *const usart_config_table[PERIPH_REGISTER_TABLE_MEMBERS])() =
{
		usart_ctrl_table,
		usart_frame_table,
		usart_trig_ctrl_table,
		usart_status_cmd_table,
		usart_clkdiv_table,
		usart_int_flag_table,
		usart_ir_ctrl_table,
		usart_route_table,
		usart_input_table,
		usart_i2s_ctrl_table,
		NULL
};


int zg_usartCtrlRead(USART_periphconf* MPI_conf)
{
	MPI_conf->ctrl = usart->CTRL;
  return 0;
}

int zg_usartCtrlWrite(USART_periphconf* MPI_conf)
{
	usart->CTRL |= MPI_conf->ctrl;
	return 0;
}

int zg_usartCtrlClr(USART_periphconf* MPI_conf)
{
	usart->CTRL &= ~MPI_conf->ctrl;
	return 0;
}



/* FRAME */

int zg_usartFrameRead(USART_periphconf* MPI_conf)
{
	MPI_conf->frame = usart->FRAME;
	return 0;
}

int zg_usartFrameWrite(USART_periphconf* MPI_conf)
{
	usart->FRAME |= MPI_conf->frame;
	return 0;
}

int zg_usartFrameClr(USART_periphconf* MPI_conf)
{
	usart->FRAME &= ~MPI_conf->frame;
	return 0;
}


/* TRIGCTRL */

int zg_usartTrigctrlRead(USART_periphconf* MPI_conf)
{
	MPI_conf->trigctrl = usart->TRIGCTRL;
	return 0;
}

int zg_usartTrigctrlWrite(USART_periphconf* MPI_conf)
{
	usart->TRIGCTRL |= MPI_conf->trigctrl;
	return 0;
}

int zg_usartTrigctrlClr(USART_periphconf* MPI_conf)
{
	usart->TRIGCTRL &= ~MPI_conf->trigctrl;
	return 0;
}



/* STATUS */

int zg_usartStatusRead(USART_periphconf* MPI_conf)
{
	MPI_conf->status = usart->STATUS;
	return 0;
}

/* CMD */

int zg_usartCmdWrite(USART_periphconf* MPI_conf)
{
	usart->CMD |= MPI_conf->cmd;
	return 0;
}

int zg_usartCmdClr(USART_periphconf* MPI_conf)
{
	usart->CMD &= ~MPI_conf->cmd;
	return 0;
}

/* CLKDIV */

int zg_usartClkdivRead(USART_periphconf* MPI_conf)
{
	MPI_conf->clkdiv = usart->CLKDIV;
	return 0;
}

int zg_usartClkdivWrite(USART_periphconf* MPI_conf)
{
	usart->CLKDIV |= MPI_conf->clkdiv;
	return 0;
}

int zg_usartClkdivClr(USART_periphconf* MPI_conf)
{
	usart->CLKDIV &= ~MPI_conf->clkdiv;
	return 0;
}



/* Interrupt flag read */
int zg_usartIntflagRead(USART_periphconf* MPI_conf)
{
	MPI_conf->intflag = usart->IF;
	return 0;

}

/* Interrupt flag write */
int zg_usartIntflagWrite(USART_periphconf* MPI_conf)
{
	usart->IFS |= MPI_conf->intflag;
	return 0;
}

/* Interrupt flag clear */
int zg_usartIntflagClr(USART_periphconf* MPI_conf)
{
	usart->IFS &= ~MPI_conf->intflag;
	return 0;
}


/* ir ctrl read */
int zg_usartIrctrlRead(USART_periphconf* MPI_conf)
{
	MPI_conf->irctrl = usart->IRCTRL;
	return 0;
}

/* ir ctrl write */
int zg_usartIrctrlWrite(USART_periphconf* MPI_conf)
{
	usart->IRCTRL |= MPI_conf->irctrl;
	return 0;
}
/* ir ctrl clear */
int zg_usartIrctrlClr(USART_periphconf* MPI_conf)
{
	usart->IRCTRL &= ~MPI_conf->irctrl;
	return 0;
}


/* route read */
int zg_usartRouteRead(USART_periphconf* MPI_conf)
{
	MPI_conf->route = usart->ROUTE;
	return 0;
}

/* route write */
int zg_usartRouteWrite(USART_periphconf* MPI_conf)
{
	usart->ROUTE |= MPI_conf->route;
	return 0;
}

/* route clear */
int zg_usartRouteClr(USART_periphconf* MPI_conf)
{
	usart->ROUTE &= ~MPI_conf->route;
	return 0;
}

/* input read */
int zg_usartInputRead(USART_periphconf* MPI_conf)
{
	MPI_conf->input = usart->INPUT;
	return 0;
}

/* input write */
int zg_usartInputWrite(USART_periphconf* MPI_conf)
{
	usart->INPUT |= MPI_conf->input;
	return 0;
}

/* input clear */
int zg_usartInputClr(USART_periphconf* MPI_conf)
{
	usart->INPUT &= ~MPI_conf->input;
	return 0;
}

/* i2sctrl read */
int zg_usartI2sctrlRead(USART_periphconf* MPI_conf)
{
	MPI_conf->i2sctrl = usart->I2SCTRL;
	return 0;
}

/* i2sctrl write */
int zg_usartI2sctrlWrite(USART_periphconf* MPI_conf)
{
	usart->I2SCTRL |= MPI_conf->i2sctrl;
	return 0;
}

/* i2sctrl clear */
int zg_usartI2sctrlClr(USART_periphconf* MPI_conf)
{
	usart->I2SCTRL &= ~MPI_conf->i2sctrl;
	return 0;
}


	/*
	gpio->P[PORTC].CTRL = GPIO_P_CTRL_DRIVEMODE_STANDARD;
					gpio->P[PORTA].MODEL = GPIO_P_MODEL_MODE1_PUSHPULL; //GPIO used for CS as AUTOCS is disabled
					gpio->P[PORTC].MODEH = GPIO_P_MODEH_MODE15_PUSHPULL ;//| GPIO_P_MODEH_MODE14_PUSHPULL; //CLK15 + CS14
					gpio->P[PORTD].MODEL = GPIO_P_MODEL_MODE7_PUSHPULL | GPIO_P_MODEL_MODE6_INPUT; //MOSI7 + MISO6

	*/

int (*const usart_ctrl_table[USART_READ_WRITE_CLEAR])() =
	{zg_usartCtrlRead, zg_usartCtrlWrite, zg_usartCtrlClr};

int (*const usart_frame_table[USART_READ_WRITE_CLEAR])() =
	{zg_usartFrameRead, zg_usartFrameWrite, zg_usartFrameClr};

int (*const usart_trig_ctrl_table[USART_READ_WRITE_CLEAR])() =
	{zg_usartTrigctrlRead, zg_usartTrigctrlWrite, zg_usartTrigctrlClr};

int (*const usart_status_cmd_table[USART_READ_WRITE_CLEAR])() =
	{zg_usartStatusRead, zg_usartCmdWrite, zg_usartCmdClr};

int (*const usart_clkdiv_table[USART_READ_WRITE_CLEAR])() =
	{zg_usartClkdivRead, zg_usartClkdivWrite, zg_usartClkdivClr};

int (*const usart_int_flag_table[USART_READ_WRITE_CLEAR])() =
	{zg_usartIntflagRead, zg_usartIntflagWrite, zg_usartIntflagClr};

int (*const usart_ir_ctrl_table[USART_READ_WRITE_CLEAR])() =
	{zg_usartIrctrlRead, zg_usartIrctrlWrite, zg_usartIrctrlClr};

int (*const usart_route_table[USART_READ_WRITE_CLEAR])() =
	{zg_usartRouteRead, zg_usartRouteWrite, zg_usartRouteClr};

int (*const usart_input_table[USART_READ_WRITE_CLEAR])() =
	{zg_usartInputRead, zg_usartInputWrite, zg_usartInputClr};

int (*const usart_i2s_ctrl_table[USART_READ_WRITE_CLEAR])() =
	{zg_usartI2sctrlRead, zg_usartI2sctrlWrite, zg_usartI2sctrlClr};


