#ifndef DW1000_FRAME_BUILD_H_
#define DW1000_FRAME_BUILD_H_

#include <stdint.h>
#include "mpi_port.h"

extern uint32_t(*const dw_frame_header_read_write_table[])();
extern uint32_t(* const dw_frame_build_table[])(); 
extern uint32_t(* dw_config_query_table[])(); 

extern uint8_t dw_rw_bool_table[];
extern uint8_t dw_reg_addr_table[];
extern bool sub_addr_bool_table[];
extern bool ext_addr_bool_table[];


uint32_t dw_buildBlinkFrame(DW_nodelist* dw_nodelist, DW_data* dw_data, DW_config* dw_config, uint32_t frame_index_start);
uint32_t dw_buildRangeInitFrame(DW_nodelist* dw_nodelist, DW_data* dw_data, DW_config* dw_config, uint32_t frame_index_start);
uint32_t dw_buildPollFrame(DW_nodelist* dw_nodelist, DW_data* dw_data, DW_config* dw_config, uint32_t frame_index_start);
uint32_t dw_buildResponseFrame(DW_nodelist* dw_nodelist, DW_data* dw_data, DW_config* dw_config, uint32_t frame_index_start);
uint32_t dw_buildFinalFrame(DW_nodelist* dw_nodelist, DW_data* dw_data, DW_config* dw_config, uint32_t frame_index_start);
uint32_t dw_buildMessageOut(void* ext_dev_object, uint32_t read_write, uint32_t node_index);
uint32_t dw_buildMessageHeader(DW_nodelist* dw_nodelist, uint32_t read_write);



#endif
