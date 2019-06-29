#ifndef DW1000_FRAME_BUILD_H_
#define DW1000_FRAME_BUILD_H_

#include <stdint.h>
#include "mpi_port.h"

extern uint32_t(*const dw_frame_header_read_write_table[])();
extern uint32_t(* const dw_frame_build_table[])(); 
extern uint32_t(* dw_config_query_table[])(); 

extern uint8_t dw_rw_bool_table[];
extern bool sub_addr_bool_table[];
extern bool ext_addr_bool_table[];


uint32_t dw_buildBlinkFrame(void* host_object, int(* host_usart)(), void* ext_dev_object, uint32_t frame_index_start, uint32_t nodelist_index);
uint32_t dw_buildRangeInitFrame(void* host_object, int(* host_usart)(), void* ext_dev_object, uint32_t frame_index_start, uint32_t nodelist_index);
uint32_t dw_buildPollFrame(void* host_object, int(* host_usart)(), void* ext_dev_object, uint32_t frame_index_start, uint32_t nodelist_index);
uint32_t dw_buildResponseFrame(void* host_object, int(* host_usart)(), void* ext_dev_object, uint32_t frame_index_start, uint32_t nodelist_index);
uint32_t dw_buildFinalFrame(void* host_object, int(* host_usart)(), void* ext_dev_object, uint32_t frame_index_start, uint32_t nodelist_index);
uint32_t dw_buildMessageOut(void* host_object, int(* host_usart)(), void* ext_dev_object, uint32_t read_write, uint32_t node_index);
uint32_t dw_buildMessageHeader(DW_nodelist* dw_nodelist, DW_config* dw_config, uint32_t read_write);



#endif
