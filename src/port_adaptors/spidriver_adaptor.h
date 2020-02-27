#ifndef SPIDRIVER_ADAPTOR_H
#define SPIDRIVER_ADAPTOR_H

#include <stdint.h>

#define SD_CONFIG_INDEX 0
#define SD_STATUS_INDEX 0
#define SD_DATA_INDEX   0

#define SD_READ         0
#define SD_WRITE        1
#define SD_READ_WRITE   2

typedef struct {
    char rxtx[8];
}SD_DATA;

typedef struct {
    const char port[8];
}SD_CONF;

//ext_dev_object of type SPIDriver*
int sd_Init(void* host_object);
int sd_Data(void* host_ptr, uint32_t RW, void* ext_dev_array, uint32_t array_len);
int sd_RegDump(void* host_object);

#endif