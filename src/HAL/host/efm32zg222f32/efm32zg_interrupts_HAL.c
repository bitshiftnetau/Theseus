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
 *										Interrupt Config
 *
 ***************************************************************************************************/

#include <stdbool.h>

#include "efm32zg222f32.h"
#include "efm32zg_interrupts_HAL.h"
#include "efm32zg_types_HAL.h"



/***************************************************************************************************
 *
 *										USART Interrupts
 *
 ***************************************************************************************************/

/****************************************************************************
 * @brief USART1 RX IRQ Handler Setup
 * @param receiveBuffer points to where to place recieved data
 * @param receiveBufferSize indicates the number of bytes to receive

*****************************************************************************/

void zg_RxIntSetup(bool on)
{
  USART_TypeDef *usart_rxintset = USART1;

  /* Setting up pointer and indexes */

  /*
  slaveRxBuffer      = usart_rxBuffer;
  slaveRxBufferSize  = usart_rxBufferSize;
  slaveRxBufferIndex = 0;
	*/

  if(on == true){
  /* Clear RX */
  usart_rxintset->CMD = USART_CMD_CLEARRX;

  /* Enable interrupts */
  NVIC_ClearPendingIRQ(USART1_RX_IRQn);
  NVIC_EnableIRQ(USART1_RX_IRQn);
  usart_rxintset->IEN |= USART_IEN_RXDATAV;
  } else if (on == false){
	  /* turn off interrupts*/
	  NVIC_ClearPendingIRQ(USART1_RX_IRQn);
	  NVIC_DisableIRQ(USART1_RX_IRQn);
	  usart_rxintset->IEN &= ~USART_IEN_RXDATAV;
  }
}

/**************************************************************************//**
 * @brief USART1 TX IRQ Handler Setup
 * @param transmitBuffer points to the data to send
 * @param transmitBufferSize indicates the number of bytes to send

*****************************************************************************/

void zg_TxIntSetup(bool on)
{
  USART_TypeDef *usart_txintset = USART1;

  /* Setting up pointer and indexes */

  /*
  slaveTxBuffer      = usart_txBuffer;
  slaveTxBufferSize  = usart_txBufferSize;
  slaveTxBufferIndex = 0;
	*/

  if(on == true){
  /* Clear TX */
  usart_txintset->CMD = USART_CMD_CLEARTX;

  /* Enable interrupts */
  NVIC_ClearPendingIRQ(USART1_TX_IRQn);
  NVIC_EnableIRQ(USART1_TX_IRQn);
  usart_txintset->IEN |= USART_IEN_TXBL;
  } else if (on == false){
	  NVIC_ClearPendingIRQ(USART1_TX_IRQn);
	  NVIC_DisableIRQ(USART1_TX_IRQn);
	  usart_txintset->IEN &= ~USART_IEN_TXBL;

  }
}

/**************************************************************************//**
 * @brief USART1 RX IRQ Handler
 * @param no parameters
*****************************************************************************/
/*
void USART1_RX_IRQHandler(void)
{
  USART_TypeDef *usart_rxint = USART1;

  	  zg_usartRead(usart_rxint);
}
*/
/**************************************************************************//**
 * @brief USART1 TX IRQ Handler
 * @param no parameters
*****************************************************************************/
/*void USART1_TX_IRQHandler(void)
{
  USART_TypeDef *usart_txint = USART1;

  	  zg_usartWrite(usart_txint);
}*/


/**********************************************
 *          TIMER0 INTERRUPT
 *********************************************/

void TIMER0_IRQHandler(void){

  TIMER_TypeDef* timer_0 = TIMER0; 
  timer0_ms_ticks++;
  timer_0->IFC = TIMER_IFC_OF;
}

