#ifndef RPI2_ADAPTOR_H
#define RPI2_ADAPTOR_H

#include <stdint.h>

int spi_Data(void* host_ptr, uint32_t RW, void* ext_dev_array, uint32_t array_len);
int spi_Init(void* host_ptr);
int spi_Off();

int gpio_Init(void* host_ptr);
int gpio_Data(void* host_ptr, uint32_t read_write_tgl, uint32_t port, uint32_t pin);

int timer_Init(void* host_ptr);
int timer_Delay(uint32_t delay_ms);

#endif
