#ifndef _EFM32ZG_INT_HAL_H_
#define _EFM32ZG_INT_HAL_H_

#include <stdbool.h>

/**************************************************************************//**
 * @brief USART1 RX IRQ Handler Setup
 * @param receiveBuffer points to where to place recieved data
 * @param receiveBufferSize indicates the number of bytes to receive

*****************************************************************************/

void zg_RxIntSetup(bool on);


/**************************************************************************//**
 * @brief USART1 TX IRQ Handler Setup
 * @param transmitBuffer points to the data to send
 * @param transmitBufferSize indicates the number of bytes to send

*****************************************************************************/

void zg_TxIntSetup(bool on);

/**************************************************************************//**
 * @brief USART1 RX IRQ Handler
 * @param no parameters
*****************************************************************************/
//void USART1_RX_IRQHandler(void);

/**************************************************************************//**
 * @brief USART1 TX IRQ Handler
 * @param no parameters
*****************************************************************************/
//void USART1_TX_IRQHandler(void);

#endif

