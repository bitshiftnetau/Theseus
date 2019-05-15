#ifndef _DECA_DEVICE_API_H_
#define _DECA_DEVICE_API_H_

#include "dw1000_types.h"

uint32_t dw_Init(void* host_object, uint32_t read_write, int(*host_usart)(), void* ext_dev_object);
uint32_t dw_RegDump(void* host_object, uint32_t read_write, int(*host_usart)(), void* ext_dev_object);
uint32_t dw_ConfigReg(void* host_object, uint32_t read_write, int(*host_usart)(), void* ext_dev_object);
uint32_t dw_QueryReg(void* host_object, uint32_t read_write, int(*host_usart)(), void* ext_dev_object);
uint32_t dw_Reset(void* host_object, uint32_t read_write, int(*host_usart)(), void* ext_dev_object);
uint32_t dw_Off(void* host_object, uint32_t read_write, int(*host_usart)(), void* ext_dev_object);
uint32_t dw_Wakeup(void* host_object, uint32_t read_write, int(*host_usart)(), void* ext_dev_object);
uint32_t dw_ModeLevel(void* host_object, uint32_t read_write, int(*host_usart)(), void* ext_dev_object);
uint32_t dw_Data(void* host_object, uint32_t read_write, int(*host_usart)(), void* ext_dev_object);

#endif /* _DECA_DEVICE_API_H_ */
