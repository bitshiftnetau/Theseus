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
#include "efm32zg222f32.h"

#include "efm32zg_types_HAL.h"
#include "efm32zg_gpio_HAL.h"


int zg_gpioExtIntRiseEdgeClr(GPIO_periphconf* MPI_conf);
int zg_gpioExtIntFallEdgeClr(GPIO_periphconf* MPI_conf);

int(*const gpio_ctrl[GPIO_READ_WRITE_CLEAR])();
int(*const gpio_low_pinmode[GPIO_READ_WRITE_CLEAR])();
int(*const gpio_high_pinmode[GPIO_READ_WRITE_CLEAR])();
int(*const gpio_pinlock[GPIO_READ_WRITE_CLEAR])();
int(*const gpio_int_ctrl[GPIO_READ_WRITE_CLEAR])();
int(*const gpio_extint_low_pins[GPIO_READ_WRITE_CLEAR])();
int(*const gpio_extint_high_pins[GPIO_READ_WRITE_CLEAR])();
int(*const gpio_extint_rise_edge[GPIO_READ_WRITE_CLEAR])();
int(*const gpio_extint_fall_edge[GPIO_READ_WRITE_CLEAR])();
int(*const gpio_int_flag[GPIO_READ_WRITE_CLEAR])();
int(*const gpio_serial_wire[GPIO_READ_WRITE_CLEAR])();
int(*const gpio_insense[GPIO_READ_WRITE_CLEAR])();
int(*const gpio_conf_lock[GPIO_READ_WRITE_CLEAR])();
int(*const gpio_em4retention[GPIO_READ_WRITE_CLEAR])();
int(*const gpio_em4wake[GPIO_READ_WRITE_CLEAR])();
int(*const gpio_em4polarity[GPIO_READ_WRITE_CLEAR])();

int(*const *const gpio_config_table[PERIPH_REGISTER_TABLE_MEMBERS])() =
{
		gpio_ctrl,
		gpio_low_pinmode,
		gpio_high_pinmode,
		gpio_pinlock,
		gpio_int_ctrl,
		gpio_extint_low_pins,
		gpio_extint_high_pins,
		gpio_extint_rise_edge,
		gpio_extint_fall_edge,
		gpio_int_flag,
		gpio_serial_wire,
		gpio_insense,
		gpio_conf_lock,
		gpio_em4retention,
		gpio_em4wake,
		gpio_em4polarity,
};



int zg_gpioPCtrlRead(GPIO_periphconf* MPI_conf)
{
	MPI_conf->P[MPI_conf->port].ctrl = gpio->P[MPI_conf->port].CTRL;
	return 0;
}

int zg_gpioPCtrlWrite(GPIO_periphconf* MPI_conf)
{
	gpio->P[MPI_conf->port].CTRL |= MPI_conf->P[MPI_conf->port].ctrl;
	return 0;
}

int zg_gpioPCtrlClr(GPIO_periphconf* MPI_conf)
{
	gpio->P[MPI_conf->port].CTRL &= ~MPI_conf->P[MPI_conf->port].ctrl;
	return 0;
}





int zg_gpioPinModeLowRead(GPIO_periphconf* MPI_conf)
{
	MPI_conf->P[MPI_conf->port].pinmodeL = gpio->P[MPI_conf->port].MODEL;
	return 0;
}

int zg_gpioPinModeLowWrite(GPIO_periphconf* MPI_conf)
{
	gpio->P[MPI_conf->port].MODEL |= MPI_conf->P[MPI_conf->port].pinmodeL;
	return 0;
}

int zg_gpioPinModeLowClear(GPIO_periphconf* MPI_conf)
{
	gpio->P[MPI_conf->port].MODEL &= ~MPI_conf->P[MPI_conf->port].pinmodeL;
	return 0;
}




int zg_gpioPinModeHighRead(GPIO_periphconf* MPI_conf)
{
	MPI_conf->P[MPI_conf->port].pinmodeH = gpio->P[MPI_conf->port].MODEH;
	return 0;
}

int zg_gpioPinModeHighWrite(GPIO_periphconf* MPI_conf)
{
	gpio->P[MPI_conf->port].MODEH |= MPI_conf->P[MPI_conf->port].pinmodeH;
	return 0;
}

int zg_gpioPinModeHighClear(GPIO_periphconf* MPI_conf)
{
	gpio->P[MPI_conf->port].MODEH &= ~MPI_conf->P[MPI_conf->port].pinmodeH;
	return 0;
}





int zg_gpioPinLockRead(GPIO_periphconf* MPI_conf)
{
	/* Locks pinNumber in gpio port*/
	MPI_conf->P[MPI_conf->port].pinlockn = gpio->P[MPI_conf->port].PINLOCKN;
	return 0;
}

int zg_gpioPinLockWrite(GPIO_periphconf* MPI_conf)
{
	/* Locks pinNumber in gpio port*/
	gpio->P[MPI_conf->port].PINLOCKN |= MPI_conf->P[MPI_conf->port].pinlockn;
	return 0;
}

int zg_gpioPinLockClr(GPIO_periphconf* MPI_conf)
{
	/* Locks pinNumber in gpio port*/
	gpio->P[MPI_conf->port].PINLOCKN &= ~MPI_conf->P[MPI_conf->port].pinlockn;
	return 0;
}






int zg_gpioExtIntPinLowRead(GPIO_periphconf* MPI_conf)
{
	MPI_conf->extipselectL = gpio->EXTIPSELL;
	return 0;
}

int zg_gpioExtIntPinLowWrite(GPIO_periphconf* MPI_conf)
{
	gpio->EXTIPSELL |= MPI_conf->extipselectL;
	return 0;
}

int zg_gpioExtIntPinLowClr(GPIO_periphconf* MPI_conf)
{
	gpio->EXTIPSELL &= ~MPI_conf->extipselectL;
;	return 0;
}





int zg_gpioExtIntPinHighRead(GPIO_periphconf* MPI_conf)
{
	MPI_conf->extipselectH = gpio->EXTIPSELL;
	return 0;
}

int zg_gpioExtIntPinHighWrite(GPIO_periphconf* MPI_conf)
{
	gpio->EXTIPSELH |= MPI_conf->extipselectH;
	return 0;
}

int zg_gpioExtIntPinHighClr(GPIO_periphconf* MPI_conf)
{
	gpio->EXTIPSELH &= ~MPI_conf->extipselectH;
	return 0;
}




int zg_gpioExtIntRiseEdgeRead(GPIO_periphconf* MPI_conf)
{
	MPI_conf->extirise = gpio->EXTIRISE;
	return 0;
}

int zg_gpioExtIntRiseEdgeWrite(GPIO_periphconf* MPI_conf)
{
	gpio->EXTIRISE |= MPI_conf->extirise;
	zg_gpioExtIntFallEdgeClr(MPI_conf);
	return 0;
}

int zg_gpioExtIntRiseEdgeClr(GPIO_periphconf* MPI_conf)
{
	gpio->EXTIRISE &= ~MPI_conf->extirise;
	return 0;
}




int zg_gpioExtIntFallEdgeRead(GPIO_periphconf* MPI_conf)
{
	MPI_conf->extifall = gpio->EXTIRISE;
	return 0;

}

int zg_gpioExtIntFallEdgeWrite(GPIO_periphconf* MPI_conf)
{
	gpio->EXTIFALL |= MPI_conf->extifall;
	zg_gpioExtIntRiseEdgeClr(MPI_conf);
	return 0;
}

int zg_gpioExtIntFallEdgeClr(GPIO_periphconf* MPI_conf)
{
	gpio->EXTIFALL &= ~MPI_conf->extifall;
	return 0;
}








int zg_gpioIntEnRead(GPIO_periphconf* MPI_conf)
{
	MPI_conf->ien = gpio->IEN;
	return 0;

}

int zg_gpioIntEnWrite(GPIO_periphconf* MPI_conf)
{
	gpio->IEN |= MPI_conf->ien;
	return 0;
}

int zg_gpioIntClr(GPIO_periphconf* MPI_conf)
{
	gpio->IEN &= ~MPI_conf->ien;
	return 0;
}






int zg_gpioIntFlagRead(GPIO_periphconf* MPI_conf)
{
	MPI_conf->intf = gpio->IF;
	return 0;

}

int zg_gpioIntFlagWrite(GPIO_periphconf* MPI_conf)
{
	gpio->IFS |= MPI_conf->intf;
	return 0;
}

int zg_gpioIntFlagClr(GPIO_periphconf* MPI_conf)
{
	gpio->IFC = MPI_conf->intf;
	return 0;
}





int zg_gpioSerialWireEnRead(GPIO_periphconf* MPI_conf)
{
	MPI_conf->route = gpio->ROUTE;
	return 0;

}

int zg_gpioSerialWireEnWrite(GPIO_periphconf* MPI_conf)
{
	gpio->ROUTE |= MPI_conf->route;
	return 0;
}

int zg_gpioSerialWireEnClr(GPIO_periphconf* MPI_conf)
{
	/*enable register &= inverted value*/
	gpio->ROUTE &= ~MPI_conf->route;
	return 0;
}




int zg_gpioSenseRead(GPIO_periphconf* MPI_conf)
{
	MPI_conf->insense = gpio->INSENSE;
	return 0;

}

int zg_gpioSenseWrite(GPIO_periphconf* MPI_conf)
{
	gpio->INSENSE |= MPI_conf->insense;
	return 0;
}

int zg_gpioSenseClr(GPIO_periphconf* MPI_conf)
{
	/*enable register &= inverted value*/
	gpio->INSENSE &= ~MPI_conf->insense;
	return 0;
}




int zg_gpioConfLockRead(GPIO_periphconf* MPI_conf)
{
	MPI_conf->lock = gpio->LOCK;
	return 0;

}

int zg_gpioConfLockWrite(GPIO_periphconf* MPI_conf)
{
	gpio->LOCK = MPI_conf->lock;
	return 0;
}

int zg_gpioConfLockClr(GPIO_periphconf* MPI_conf)
{
	/*enable register &= inverted value*/
	gpio->LOCK = ~MPI_conf->lock;
	return 0;
}



int zg_gpioEm4RetRead(GPIO_periphconf* MPI_conf)
{
	MPI_conf->em4ret = gpio->CTRL;
	return 0;
}

int zg_gpioEm4RetWrite(GPIO_periphconf* MPI_conf)
{
	gpio->CTRL |= MPI_conf->em4ret;
	return 0;
}

int zg_gpioEm4RetClr(GPIO_periphconf* MPI_conf)
{
	/*enable register &= inverted value*/
	gpio->CTRL &= MPI_conf->em4ret;
	return 0;
}







int zg_EM4WakeRead(GPIO_periphconf* MPI_conf)
{
	MPI_conf->em4wuen = gpio->EM4WUEN;
	return 0;

}

int zg_EM4WakeWrite(GPIO_periphconf* MPI_conf)
{
	gpio->EM4WUEN |= MPI_conf->em4wuen;
	return 0;
}

int zg_EM4WakeClr(GPIO_periphconf* MPI_conf)
{
	gpio->EM4WUEN &= MPI_conf->em4wuen;
	return 0;
}




int zg_EM4PolRead(GPIO_periphconf* MPI_conf)
{
	MPI_conf->em4wupol = gpio->EM4WUPOL;
	return 0;
}

int zg_EM4PolWrite(GPIO_periphconf* MPI_conf)
{
	gpio->EM4WUPOL |= MPI_conf->em4wupol;
	return 0;
}

int zg_EM4PolClr(GPIO_periphconf* MPI_conf)
{
	gpio->EM4WUPOL &= MPI_conf->em4wupol;
	return 0;
}



int zg_gpioClrEm4Request(void)
{
	gpio->CMD = GPIO_CMD_EM4WUCLR;
	return 0;
}

int zg_EM4Cause(GPIO_periphconf* MPI_conf)
{
	MPI_conf->em4wucause = gpio->EM4WUCAUSE;
	return 0;
}



int(*const gpio_ctrl[GPIO_READ_WRITE_CLEAR])()=
	{zg_gpioPCtrlRead, zg_gpioPCtrlWrite, zg_gpioPinModeLowRead};

int(*const gpio_low_pinmode[GPIO_READ_WRITE_CLEAR])()=
	{zg_gpioPinModeLowRead, zg_gpioPinModeLowWrite, zg_gpioPinModeLowClear};

int(*const gpio_high_pinmode[GPIO_READ_WRITE_CLEAR])()=
	{zg_gpioPinModeHighRead, zg_gpioPinModeHighWrite, zg_gpioPinModeHighClear};


int(*const gpio_pinlock[GPIO_READ_WRITE_CLEAR])() =
	{zg_gpioPinLockRead, zg_gpioPinLockWrite, zg_gpioPinLockClr};

int(*const gpio_int_ctrl [GPIO_READ_WRITE_CLEAR])() =
	{zg_gpioIntEnRead, zg_gpioIntEnWrite, zg_gpioIntClr};

int(*const gpio_extint_low_pins[GPIO_READ_WRITE_CLEAR])()=
	{zg_gpioExtIntPinLowRead, zg_gpioExtIntPinLowWrite, zg_gpioExtIntPinLowClr};

int(*const gpio_extint_high_pins[GPIO_READ_WRITE_CLEAR])()=
	{zg_gpioExtIntPinHighRead, zg_gpioExtIntPinHighWrite, zg_gpioExtIntPinHighClr};

int(*const gpio_extint_rise_edge[GPIO_READ_WRITE_CLEAR])()=
	{zg_gpioExtIntRiseEdgeRead, zg_gpioExtIntRiseEdgeWrite, zg_gpioExtIntRiseEdgeClr};

int(*const gpio_extint_fall_edge[GPIO_READ_WRITE_CLEAR])()=
	{zg_gpioExtIntFallEdgeRead, zg_gpioExtIntFallEdgeWrite, zg_gpioExtIntFallEdgeClr};

int(*const gpio_int_flag[GPIO_READ_WRITE_CLEAR])()=
	{zg_gpioIntFlagRead, zg_gpioIntFlagWrite, zg_gpioIntFlagClr};

int(*const gpio_serial_wire[GPIO_READ_WRITE_CLEAR])()=
	{zg_gpioSerialWireEnRead, zg_gpioSerialWireEnWrite, zg_gpioSerialWireEnClr};

int(*const gpio_insense[GPIO_READ_WRITE_CLEAR])()=
	{zg_gpioSenseRead, zg_gpioSenseWrite, zg_gpioSenseClr};

int(*const gpio_conf_lock[GPIO_READ_WRITE_CLEAR])()=
	{zg_gpioConfLockRead, zg_gpioConfLockWrite, zg_gpioConfLockClr};

int(*const gpio_em4retention [GPIO_READ_WRITE_CLEAR])()=
	{zg_gpioEm4RetRead, zg_gpioEm4RetWrite, zg_gpioEm4RetClr};

int(*const gpio_em4wake[GPIO_READ_WRITE_CLEAR])()=
	{zg_EM4WakeRead, zg_EM4WakeWrite, zg_EM4WakeClr};

int(*const gpio_em4polarity[GPIO_READ_WRITE_CLEAR])()=
	{zg_EM4PolRead, zg_EM4PolWrite, zg_EM4PolClr};

int(*const gpio_em4clr_all[1])()= {zg_gpioClrEm4Request};
int(*const gpio_em4cause[1])()= {zg_EM4Cause};





