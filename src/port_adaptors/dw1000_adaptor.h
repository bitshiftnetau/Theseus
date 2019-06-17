#ifndef _DECA_DEVICE_API_H_
#define _DECA_DEVICE_API_H_

#include "dw1000_types.h"

int dw_Init(void* host_object, int(*host_usart)(), void* ext_dev_object);
int dw_RegDump(void* host_object, int(*host_usart)(), void* ext_dev_object);
int dw_ConfigReg(void* host_object, int(*host_usart)(), void* ext_dev_object, uint32_t config_register);
int dw_QueryReg(void* host_object, int(*host_usart)(), void* ext_dev_object, uint32_t config_register);
int dw_Reset(void* host_object, int(*host_usart)(), void* ext_dev_object);
int dw_Off(void* host_object, int(*host_usart)(), void* ext_dev_object);
int dw_Wakeup(void* host_object, int(*host_usart)(), void* ext_dev_object);
int dw_Sleep(void* host_object, int(*host_usart)(), void* ext_dev_object);
int dw_ModeLevel(void* host_object, int(*host_usart)(), void* ext_dev_object);
int dw_Data(void* host_object, int(*host_usart)(), void* ext_dev_object, uint32_t read_write);

#endif /* _DECA_DEVICE_API_H_ */
