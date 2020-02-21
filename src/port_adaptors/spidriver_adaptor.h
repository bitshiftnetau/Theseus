#ifndef SPIDRIVER_ADAPTOR_H
#define SPIDRIVER_ADAPTOR_H

#include <stdint.h>

#define SD_CONFIG_INDEX 0

int sd_Init(void* host_object, int(*host_usart)(), void* ext_dev_object);
int sd_Data(void* host_object, int(*host_usart)(), void* ext_dev_object, uint32_t read_write);
int sd_RegDump(void* host_object, int(*host_usart)(), void* ext_dev_object);
int sd_QueryReg(void* host_object, int(*host_usart)(), void* ext_dev_object);
int sd_ConfigReg(void* host_object, int(*host_usart)(), void* ext_dev_object);

#endif