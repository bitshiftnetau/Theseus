#ifndef DW_TOF_CALCS_H_
#define DW_TOF_CALCS_H_

#include <stdint.h>

#include "dw1000_types.h"

extern void (* dw_ts_handler_table[])();
uint32_t dw_deviceStore(DW_nodelist* dw_nodelist, uint32_t nodelist_index);

#endif 
