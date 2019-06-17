#ifndef DW1000_COMM_RX_TX_H
#define DW1000_COMM_RX_TX_H


#include <stdint.h>
#include "dw1000_types.h"

extern uint32_t(*dw_comm_table[])();
extern void(* dw_PolAlphaDeAssert[DW_SPI_POLALPA_VARIANTS])();
extern void(* dw_PolAlphaAssert[DW_SPI_POLALPA_VARIANTS])();

uint32_t dw_Rx(void* host_object, int(*host_usart)(), DW_nodelist* dw_nodelist, uint32_t* buffer_in, uint32_t buffer_len);
uint32_t dw_Tx(void* host_object, int(*host_usart)(), DW_nodelist* dw_nodelist, uint32_t* buffer_in, uint32_t buffer_len);

#endif
