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
   

/***************************************************************************************************
 *
 *										CMU Core Config
 *
 ***************************************************************************************************/

#include "efm32zg222f32.h"
#include "efm32zg_cmu_HAL.h"
#include "efm32zg_types_HAL.h"


//struct hfclktuning s_hfrco = {.tuningPtr = NULL};

/******************************************************************************
 * @brief enables HFRCO selects as HFCLK
 * @param no parameters
 ******************************************************************************/
/*
void zg_cmuSetCoreClk(const int source, const int freq){
	cmu->OSCENCMD |= CMU_OSCENCMD_HFRCOEN;
	s_hfrco.tuningPtr = NULL;

	while(!(cmu->STATUS & CMU_STATUS_HFRCORDY)){
		//do nothing whilst we wait for HFRCO to stabilize
	}

	cmu->CMD = CMU_CMD_HFCLKSEL_HFRCO;

	//check stability again before returning
	while(!(cmu->STATUS & CMU_STATUS_HFRCORDY)){
		//do nothing whilst we wait for HFRCO to stabilize
	}

	zg_cmuSetCoreFreq(source, freq);

}
*/
/******************************************************************************
 * @brief enables HFRCO selects as HFCLK
 * @param no parameters
 ******************************************************************************/

/*
void zg_cmuSetCoreFreq(const int clksrc, const int clkfreq){

	while(!(cmu->STATUS & CMU_STATUS_HFRCORDY)){
		//do nothing whilst we wait for HFRCO to stabilize
	}

	switch(clkfreq){
		case 0: // set HFRCO to 4MHz
			;
		break;

		case 1: // set HFRCO to 7MHz
			;
		break;

		case 2: // set HFRCO to 14MHz
			;
		break;

		case 3: // set HFRCO to 21MHz
			//set TUNING
			s_hfrco.tuningPtr = (unsigned long*)0x0FE081E0;
			//set BAND
			uint32_t tuningMask = CMU_HFRCOCTRL_SUDELAY_DEFAULT | CMU_HFRCOCTRL_BAND_21MHZ | *s_hfrco.tuningPtr;

			cmu->HFRCOCTRL = tuningMask;

		break;
	}

	//check stability again before terminating
	while(!(cmu->STATUS & CMU_STATUS_HFRCORDY)){
		//do nothing whilst we wait for HFRCO to stabilize
	}
}
*/

/***************************************************************************************************
 *
 *										CMU Peripherals Clock
 *
 ***************************************************************************************************/
/*
void zg_cmuPeriphClk(uint8_t* efm32zg_peripheralArray, bool activate){

	//Turn on HFPERCLK
	if(activate){
		cmu->HFPERCLKDIV &= CMU_HFPERCLKDIV_HFPERCLKEN;

		//assigned a mask for enabling any number of peripherals
		uint16_t enablePeripherals = 0;

		for(int i = 0; i < EFM32ZG222F32_PERIPHERALS; i++){

			if(efm32zg_peripheralArray[i] > 0){
				//pick out the value and build the enablePeripherals mask
				switch (efm32zg_peripheralArray[i]){
					case 0: enablePeripherals |= CMU_HFPERCLKEN0_TIMER0; break;	//TIMER0;
					case 1: enablePeripherals |= CMU_HFPERCLKEN0_TIMER1; break;	//TIMER1;
					case 2: enablePeripherals |= CMU_HFPERCLKEN0_ACMP0; break;	//ACMP0;
					case 3: enablePeripherals |= CMU_HFPERCLKEN0_USART1; break;	//USART1;
					case 4: enablePeripherals |= CMU_HFPERCLKEN0_PRS; break;	//PRS;
					case 5: enablePeripherals |= CMU_HFPERCLKEN0_IDAC0; break;	//IDAC0;
					case 6: enablePeripherals |= CMU_HFPERCLKEN0_GPIO; break;	//GPIO;
					case 7: enablePeripherals |= CMU_HFPERCLKEN0_VCMP; break;	//VCMP;
					case 8: enablePeripherals |= CMU_HFPERCLKEN0_ADC0; break;	//ADC0;
					case 9: enablePeripherals |= CMU_HFPERCLKEN0_I2C0; break;	//I2C0;
				}
			}

		}

		//turn on peripheral clock for GPIO and USART
		cmu->HFPERCLKEN0 = enablePeripherals;

	} else {

		cmu->HFPERCLKDIV &= ~CMU_HFPERCLKDIV_HFPERCLKEN;

		//assigned a mask for enabling any number of peripherals
		uint16_t disablePeripherals = 512;

		for(int i = 0; i < EFM32ZG222F32_PERIPHERALS; i++){

			if(efm32zg_peripheralArray[i] != 0){
				//pick out the value and build the enablePeripherals mask
				switch (efm32zg_peripheralArray[i]){
					case 0: disablePeripherals &= ~CMU_HFPERCLKEN0_TIMER0; break;	//TIMER0;
					case 1: disablePeripherals &= ~CMU_HFPERCLKEN0_TIMER1; break;	//TIMER1;
					case 2: disablePeripherals &= ~CMU_HFPERCLKEN0_ACMP0; break;	//ACMP0;
					case 3: disablePeripherals &= ~CMU_HFPERCLKEN0_USART1; break;	//USART1;
					case 4: disablePeripherals &= ~CMU_HFPERCLKEN0_PRS; break;	//PRS;
					case 5: disablePeripherals &= ~CMU_HFPERCLKEN0_IDAC0; break;	//IDAC0;
					case 6: disablePeripherals &= ~CMU_HFPERCLKEN0_GPIO; break;	//GPIO;
					case 7: disablePeripherals &= ~CMU_HFPERCLKEN0_VCMP; break;	//VCMP;
					case 8: disablePeripherals &= ~CMU_HFPERCLKEN0_ADC0; break;	//ADC0;
					case 9: disablePeripherals &= ~CMU_HFPERCLKEN0_I2C0; break;	//I2C0;
				}
			}

				cmu->HFPERCLKEN0 = disablePeripherals;
		}

	}

}

*/


int (*const cmu_ctrl_table[CMU_READ_WRITE_CLEAR])();
int (*const cmu_hfcoreclkdiv_table[CMU_READ_WRITE_CLEAR])();
int (*const cmu_hfperclkdiv_table[CMU_READ_WRITE_CLEAR])();
int (*const cmu_hfrcoctrl_table[CMU_READ_WRITE_CLEAR])();
int (*const cmu_lfrcoctrl_table[CMU_READ_WRITE_CLEAR])();
int (*const cmu_auxhfrcoctrl_table[CMU_READ_WRITE_CLEAR])();
int (*const cmu_calctrl_table[CMU_READ_WRITE_CLEAR])();
int (*const cmu_calcnt_table[CMU_READ_WRITE_CLEAR])();
int (*const cmu_oscencmd_table[CMU_READ_WRITE_CLEAR])();
int (*const cmu_cmd_table[CMU_READ_WRITE_CLEAR])();
int (*const cmu_lfclksel_table[CMU_READ_WRITE_CLEAR])();
int (*const cmu_status_table[CMU_READ_WRITE_CLEAR])();
int (*const cmu_intfread_table[CMU_READ_WRITE_CLEAR])();
int (*const cmu_intfset_table[CMU_READ_WRITE_CLEAR])();
int (*const cmu_intfclear_table[CMU_READ_WRITE_CLEAR])();
int (*const cmu_inten_table[CMU_READ_WRITE_CLEAR])();
int (*const cmu_hfcoreclken0_table[CMU_READ_WRITE_CLEAR])();
int (*const cmu_hfperclken0_table[CMU_READ_WRITE_CLEAR])();
int (*const cmu_syncbusy_table[CMU_READ_WRITE_CLEAR])();
int (*const cmu_freeze_table[CMU_READ_WRITE_CLEAR])();
int (*const cmu_lfaclken0_table[CMU_READ_WRITE_CLEAR])();
int (*const cmu_lfbclken0_table[CMU_READ_WRITE_CLEAR])();
int (*const cmu_lfapresc0_table[CMU_READ_WRITE_CLEAR])();
int (*const cmu_lfbpresc0_table[CMU_READ_WRITE_CLEAR])();
int (*const cmu_pcntctrl_table[CMU_READ_WRITE_CLEAR])();
int (*const cmu_route_table[CMU_READ_WRITE_CLEAR])();
int (*const cmu_lock_table[CMU_READ_WRITE_CLEAR])();

int (*const *const cmu_config_table[PERIPH_REGISTER_TABLE_MEMBERS])() =
{
  cmu_ctrl_table,
  cmu_hfcoreclkdiv_table,
  cmu_hfperclkdiv_table,
  cmu_hfrcoctrl_table,
  cmu_lfrcoctrl_table,
  cmu_auxhfrcoctrl_table,
  cmu_calctrl_table,
  cmu_calcnt_table,
  cmu_oscencmd_table,
  cmu_cmd_table,
  cmu_lfclksel_table,
  cmu_status_table,
  cmu_intfread_table,
  cmu_intfset_table,
  cmu_intfclear_table,
  cmu_inten_table,
  cmu_hfcoreclken0_table,
  cmu_hfperclken0_table,
  cmu_syncbusy_table,
  cmu_freeze_table,
  cmu_lfaclken0_table,
  cmu_lfbclken0_table,
  cmu_lfapresc0_table,
  cmu_lfbpresc0_table,
  cmu_pcntctrl_table,
  cmu_route_table,
  cmu_lock_table,
  NULL
};

int zg_cmuCtrlRead(CMU_periphconf* MPI_conf)
{
  MPI_conf->ctrl = cmu->CTRL;
  return 0;
}

int zg_cmuCtrlWrite(CMU_periphconf* MPI_conf)
{
  cmu->CTRL |= MPI_conf->ctrl;
  return 0;
}


int zg_cmuCtrlClr(CMU_periphconf* MPI_conf)
{
 
  cmu->CTRL &= ~MPI_conf->ctrl;
  return 0;
}



int zg_cmuHfcoreclkdivRead(CMU_periphconf* MPI_conf)
{
  MPI_conf->hfcoreclkdiv = cmu->HFCORECLKDIV;
  return 0;
}

int zg_cmuHfcoreclkdivWrite(CMU_periphconf* MPI_conf)
{
  cmu->HFCORECLKDIV |= MPI_conf->hfcoreclkdiv;
  return 0;
}

int zg_cmuHfcoreclkdivClr(CMU_periphconf* MPI_conf)
{
  cmu->HFCORECLKDIV &= ~MPI_conf->hfcoreclkdiv;
  return 0;
}


int zg_cmuHfperclkdivRead(CMU_periphconf* MPI_conf)
{
  MPI_conf->hfperclkdiv = cmu->HFPERCLKDIV;
  return 0;
}

int zg_cmuHfperclkdivWrite(CMU_periphconf* MPI_conf)
{
  cmu->HFPERCLKDIV |= MPI_conf->hfperclkdiv;
  return 0;
}

int zg_cmuHfperclkdivClr(CMU_periphconf* MPI_conf)
{
  cmu->HFPERCLKDIV &= ~MPI_conf->hfperclkdiv;
  return 0;
}


int zg_cmuHfrcoctrlRead(CMU_periphconf* MPI_conf)
{
  MPI_conf->hfrcoctrl = cmu->HFRCOCTRL;
  return 0;
}

int zg_cmuHfrcoctrlWrite(CMU_periphconf* MPI_conf)
{
  cmu->HFRCOCTRL |= MPI_conf->hfrcoctrl;
  return 0;
}

int zg_cmuHfrcoctrlClr(CMU_periphconf* MPI_conf)
{
  cmu->HFRCOCTRL &= ~MPI_conf->hfrcoctrl;
  return 0;
}


int zg_cmuLfrcoctrlRead(CMU_periphconf* MPI_conf)
{
  MPI_conf->lfrcoctrl = cmu->LFRCOCTRL;
  return 0;
}

int zg_cmuLfrcoctrlWrite(CMU_periphconf* MPI_conf)
{
  cmu->LFRCOCTRL |= MPI_conf->lfrcoctrl;
  return 0;
}

int zg_cmuLfrcoctrlClr(CMU_periphconf* MPI_conf)
{
  cmu->LFRCOCTRL |= ~MPI_conf->lfrcoctrl;
  return 0;
}


int zg_cmuAuxhfrcoctrlRead(CMU_periphconf* MPI_conf)
{
  MPI_conf->auxhfrcoctrl = cmu->AUXHFRCOCTRL;
  return 0;
}

int zg_cmuAuxhfrcoctrlWrite(CMU_periphconf* MPI_conf)
{
  cmu->AUXHFRCOCTRL |= MPI_conf->auxhfrcoctrl;
  return 0;
}

int zg_cmuAuxhfrcoctrlClr(CMU_periphconf* MPI_conf)
{
  cmu->AUXHFRCOCTRL &= ~MPI_conf->auxhfrcoctrl;
  return 0;
}


int zg_cmuCalctrlRead(CMU_periphconf* MPI_conf)
{
  MPI_conf->calctrl = cmu->CALCTRL;
  return 0;
}

int zg_cmuCalctrlWrite(CMU_periphconf* MPI_conf)
{
  cmu->CALCTRL |= MPI_conf->calctrl;
  return 0;
}

int zg_cmuCalctrlClr(CMU_periphconf* MPI_conf)
{
  cmu->CALCTRL &= ~MPI_conf->calctrl;
  return 0;
}


int zg_cmuCalcntRead(CMU_periphconf* MPI_conf)
{
  MPI_conf->calcnt = cmu->CALCNT;
  return 0;
}

int zg_cmuCalcntWrite(CMU_periphconf* MPI_conf)
{
  cmu->CALCNT |= MPI_conf->calcnt;
  return 0;
}

int zg_cmuCalcntClr(CMU_periphconf* MPI_conf)
{
  cmu->CALCNT &= ~MPI_conf->calcnt;
  return 0;
}


int zg_cmuOscencmdWrite(CMU_periphconf* MPI_conf)
{
  cmu->OSCENCMD |= MPI_conf->oscencmd;
  return 0;
}


int zg_cmuCmdWrite(CMU_periphconf* MPI_conf)
{
  cmu->CMD |= MPI_conf->cmd;
  return 0;
}


int zg_cmuLfclkselRead(CMU_periphconf* MPI_conf)
{
  MPI_conf->lfclksel = cmu->LFCLKSEL;
  return 0;
}

int zg_cmuLfclkselWrite(CMU_periphconf* MPI_conf)
{
  cmu->LFCLKSEL |= MPI_conf->lfclksel;
  return 0;
}

int zg_cmuLfclkselClr(CMU_periphconf* MPI_conf)
{
  cmu->LFCLKSEL &= ~MPI_conf->lfclksel;
  return 0;
}


int zg_cmuStatusRead(CMU_periphconf* MPI_conf)
{
  MPI_conf->status = cmu->STATUS;
  return 0;
}

int zg_cmuIntfreadRead(CMU_periphconf* MPI_conf)
{
  MPI_conf->intfread = cmu->IF;
  return 0;
}


int zg_cmuIntfsetWrite(CMU_periphconf* MPI_conf)
{
  cmu->IFS |= MPI_conf->intfset;
  return 0;
}

int zg_cmuIntfclearClr(CMU_periphconf* MPI_conf)
{
  cmu->IFC &= ~MPI_conf->intfclear;
  return 0;
}


int zg_cmuIntenRead(CMU_periphconf* MPI_conf)
{
  MPI_conf->inten = cmu->IEN;
  return 0;
}

int zg_cmuIntenWrite(CMU_periphconf* MPI_conf)
{
  cmu->IEN |= MPI_conf->inten;
  return 0;
}

int zg_cmuIntenClr(CMU_periphconf* MPI_conf)
{
  cmu->IEN &= ~MPI_conf->inten;
  return 0;
}


int zg_cmuHfcoreclken0Read(CMU_periphconf* MPI_conf)
{
  MPI_conf->hfcoreclken0 = cmu->HFCORECLKEN0;
  return 0;
}

int zg_cmuHfcoreclken0Write(CMU_periphconf* MPI_conf)
{
  cmu->HFCORECLKEN0 |= MPI_conf->hfcoreclken0;
  return 0;
}

int zg_cmuHfcoreclken0Clr(CMU_periphconf* MPI_conf)
{
  cmu->HFCORECLKEN0 &= ~MPI_conf->hfcoreclken0;
  return 0;
}


int zg_cmuHfperclken0Read(CMU_periphconf* MPI_conf)
{
  MPI_conf->hfperclken0 = cmu->HFPERCLKEN0;
  return 0;
}

int zg_cmuHfperclken0Write(CMU_periphconf* MPI_conf)
{
  cmu->HFPERCLKEN0 |= MPI_conf->hfperclken0;
  return 0;
}

int zg_cmuHfperclken0Clr(CMU_periphconf* MPI_conf)
{
  cmu->HFPERCLKEN0 &= ~MPI_conf->hfperclken0;
  return 0;
}


int zg_cmuSyncbusyRead(CMU_periphconf* MPI_conf)
{
  MPI_conf->syncbusy = cmu->SYNCBUSY;
  return 0;
}


int zg_cmuFreezeRead(CMU_periphconf* MPI_conf)
{
  MPI_conf->freeze = cmu->FREEZE;
  return 0;
}

int zg_cmuFreezeWrite(CMU_periphconf* MPI_conf)
{
  cmu->FREEZE |= MPI_conf->freeze;
  return 0;
}

int zg_cmuFreezeClr(CMU_periphconf* MPI_conf)
{
  cmu->FREEZE &= ~MPI_conf->freeze;
  return 0;
}


int zg_cmuLfaclken0Read(CMU_periphconf* MPI_conf)
{
  MPI_conf->lfaclken0 = cmu->LFACLKEN0;
  return 0;
}

int zg_cmuLfaclken0Write(CMU_periphconf* MPI_conf)
{
  cmu->LFACLKEN0 |= MPI_conf->lfaclken0;
  return 0;
}

int zg_cmuLfaclken0Clr(CMU_periphconf* MPI_conf)
{
  cmu->LFACLKEN0 &= ~MPI_conf->lfaclken0;
  return 0;
}


int zg_cmuLfbclken0Read(CMU_periphconf* MPI_conf)
{
  MPI_conf->lfbclken0 = cmu->LFBCLKEN0;
  return 0;
}

int zg_cmuLfbclken0Write(CMU_periphconf* MPI_conf)
{
  cmu->LFBCLKEN0 |= MPI_conf->lfbclken0;
  return 0;
}

int zg_cmuLfbclken0Clr(CMU_periphconf* MPI_conf)
{
  cmu->LFBCLKEN0 &= ~MPI_conf->lfbclken0;
  return 0;
}


int zg_cmuLfapresc0Read(CMU_periphconf* MPI_conf)
{
  MPI_conf->lfapresc0 = cmu->LFAPRESC0;
  return 0;
}

int zg_cmuLfapresc0Write(CMU_periphconf* MPI_conf)
{
  cmu->LFAPRESC0 |= MPI_conf->lfapresc0;
  return 0;
}

int zg_cmuLfapresc0Clr(CMU_periphconf* MPI_conf)
{
  cmu->LFAPRESC0 &= ~MPI_conf->lfapresc0;
  return 0;
}


int zg_cmuLfbpresc0Read(CMU_periphconf* MPI_conf)
{
  MPI_conf->lfbpresc0 = cmu->LFBPRESC0;
  return 0;
}

int zg_cmuLfbpresc0Write(CMU_periphconf* MPI_conf)
{
  cmu->LFBPRESC0 |= MPI_conf->lfbpresc0;
  return 0;
}

int zg_cmuLfbpresc0Clr(CMU_periphconf* MPI_conf)
{
  cmu->LFBPRESC0 &= ~MPI_conf->lfbpresc0;
  return 0;
}


int zg_cmuPcntctrlRead(CMU_periphconf* MPI_conf)
{
  MPI_conf->pcntctrl = cmu->PCNTCTRL;
  return 0;
}

int zg_cmuPcntctrlWrite(CMU_periphconf* MPI_conf)
{
  cmu->PCNTCTRL |= MPI_conf->pcntctrl;
  return 0;
}

int zg_cmuPcntctrlClr(CMU_periphconf* MPI_conf)
{
  cmu->PCNTCTRL &= ~MPI_conf->pcntctrl;
  return 0;
}


int zg_cmuRouteRead(CMU_periphconf* MPI_conf)
{
  MPI_conf->route = cmu->ROUTE;
  return 0;
}

int zg_cmuRouteWrite(CMU_periphconf* MPI_conf)
{
  cmu->ROUTE |= MPI_conf->route;
  return 0;
}

int zg_cmuRouteClr(CMU_periphconf* MPI_conf)
{
  cmu->ROUTE &= ~MPI_conf->route;
  return 0;
}


int zg_cmuLockRead(CMU_periphconf* MPI_conf)
{
  MPI_conf->lock = cmu->LOCK;
  return 0;
}

int zg_cmuLockWrite(CMU_periphconf* MPI_conf)
{
  cmu->LOCK |= MPI_conf->lock;
  return 0;
}

int zg_cmuLockClr(CMU_periphconf* MPI_conf)
{
  cmu->LOCK &= ~MPI_conf->lock;
  return 0;
}


int (*const cmu_ctrl_table[CMU_READ_WRITE_CLEAR])() = 
{zg_cmuCtrlRead, zg_cmuCtrlWrite, zg_cmuCtrlClr};

int (*const cmu_hfcoreclkdiv_table[CMU_READ_WRITE_CLEAR])() = 
{zg_cmuHfcoreclkdivRead, zg_cmuHfcoreclkdivWrite, zg_cmuHfcoreclkdivClr};

int (*const cmu_hfperclkdiv_table[CMU_READ_WRITE_CLEAR])() = 
{zg_cmuHfperclkdivRead, zg_cmuHfperclkdivWrite, zg_cmuHfperclkdivClr};

int (*const cmu_hfrcoctrl_table[CMU_READ_WRITE_CLEAR])() = 
{zg_cmuHfrcoctrlRead, zg_cmuHfrcoctrlWrite, zg_cmuHfrcoctrlClr};

int (*const cmu_lfrcoctrl_table[CMU_READ_WRITE_CLEAR])() =
{zg_cmuLfrcoctrlRead, zg_cmuLfrcoctrlWrite, zg_cmuLfrcoctrlClr};

int (*const cmu_auxhfrcoctrl_table[CMU_READ_WRITE_CLEAR])() =
{zg_cmuAuxhfrcoctrlRead, zg_cmuAuxhfrcoctrlWrite, zg_cmuAuxhfrcoctrlClr};

int (*const cmu_calctrl_table[CMU_READ_WRITE_CLEAR])() =
{zg_cmuCalctrlRead, zg_cmuCalctrlWrite, zg_cmuCalctrlClr};

int (*const cmu_calcnt_table[CMU_READ_WRITE_CLEAR])() = 
{zg_cmuCalcntRead, zg_cmuCalcntWrite, zg_cmuCalcntClr};

int (*const cmu_oscencmd_table[CMU_READ_WRITE_CLEAR])() = 
{NULL, zg_cmuOscencmdWrite, NULL};

int (*const cmu_cmd_table[CMU_READ_WRITE_CLEAR])() = 
{NULL, zg_cmuCmdWrite, NULL};

int (*const cmu_lfclksel_table[CMU_READ_WRITE_CLEAR])() = 
{zg_cmuLfclkselRead, zg_cmuLfclkselWrite, zg_cmuLfclkselClr};

int (*const cmu_status_table[CMU_READ_WRITE_CLEAR])() = 
{zg_cmuStatusRead, NULL, NULL};

int (*const cmu_intfread_table[CMU_READ_WRITE_CLEAR])() = 
{zg_cmuIntfreadRead, NULL, NULL};

int (*const cmu_intfset_table[CMU_READ_WRITE_CLEAR])() =
{NULL, zg_cmuIntfsetWrite, NULL};

int (*const cmu_intfclear_table[CMU_READ_WRITE_CLEAR])() =
{NULL, NULL, zg_cmuIntfclearClr};

int (*const cmu_inten_table[CMU_READ_WRITE_CLEAR])() = 
{zg_cmuIntenRead, zg_cmuIntenWrite, zg_cmuIntenClr};

int (*const cmu_hfcoreclken0_table[CMU_READ_WRITE_CLEAR])() = 
{zg_cmuHfcoreclken0Read, zg_cmuHfcoreclken0Write, zg_cmuHfcoreclken0Clr};

int (*const cmu_hfperclken0_table[CMU_READ_WRITE_CLEAR])() = 
{zg_cmuHfperclken0Read, zg_cmuHfperclken0Write, zg_cmuHfperclken0Clr};

int (*const cmu_syncbusy_table[CMU_READ_WRITE_CLEAR])() =
{zg_cmuSyncbusyRead, NULL, NULL};

int (*const cmu_freeze_table[CMU_READ_WRITE_CLEAR])() = 
{zg_cmuFreezeRead, zg_cmuFreezeWrite, zg_cmuFreezeClr};

int (*const cmu_lfaclken0_table[CMU_READ_WRITE_CLEAR])() = 
{zg_cmuLfaclken0Read, zg_cmuLfaclken0Write, zg_cmuLfaclken0Clr};

int (*const cmu_lfbclken0_table[CMU_READ_WRITE_CLEAR])() = 
{zg_cmuLfbclken0Read, zg_cmuLfbclken0Write, zg_cmuLfbclken0Clr};

int (*const cmu_lfapresc0_table[CMU_READ_WRITE_CLEAR])() =
{zg_cmuLfapresc0Read, zg_cmuLfapresc0Write, zg_cmuLfapresc0Clr};

int (*const cmu_lfbpresc0_table[CMU_READ_WRITE_CLEAR])() =
{zg_cmuLfbpresc0Read, zg_cmuLfbpresc0Write, zg_cmuLfbpresc0Clr};

int (*const cmu_pcntctrl_table[CMU_READ_WRITE_CLEAR])() = 
{zg_cmuPcntctrlRead, zg_cmuPcntctrlWrite, zg_cmuPcntctrlClr};

int (*const cmu_route_table[CMU_READ_WRITE_CLEAR])() = 
{zg_cmuRouteRead, zg_cmuRouteWrite, zg_cmuRouteClr};

int (*const cmu_lock_table[CMU_READ_WRITE_CLEAR])() = 
{zg_cmuLockRead, zg_cmuLockWrite, zg_cmuLockClr};





