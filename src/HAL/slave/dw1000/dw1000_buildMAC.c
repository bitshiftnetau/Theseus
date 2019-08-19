 /* # SpongeCake, an embedded software design philosophy for bare-metal systems
 * Copyright (C) 2018 Aidan Millar-Powell
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 *
 */
#include <stddef.h> 
#include <stdint.h>

#include "mpi_port.h"

#include "dw1000_types.h"
#include "dw1000_regs.h"

#include "dw1000_buildMAC.h"
#include "dw1000_tofCalcs.h"

/**********************************************************************
 *                 MESSAGE BUILDERS / DECODERS
 **********************************************************************/

/*
 * Steps to transmit or receive a message or data
 *
 *  1. Build the header
 *  2. Build the body starting at index stored in dw_data->header_len
 *  3. If read operation then pass message_in to callback. If write, 
 *  pass message_out to callback
 */


uint32_t dw_buildMessageOut(void* host_object, int(* host_usart)(), void* ext_dev_object, uint32_t read_write, uint32_t nodelist_index){
   
  /* Build the message 
   *
   *    R/W           SI=y/n?       reg-id
   *  <- bit #0 -> <- bit #1 -> <--- bitfield 2:7 --->
   *
   *     ext?         sub-index/ext. addr. (0-7-LSBs)
   *  <- bit #0 -> <--------- bitfield 1:7 ---------->
   *
   *               extended address
   * <--------------- bitfield 0:7 ------------------>
   */
  
  uint32_t node_index = nodelist_index;
  int rw = read_write;
  
  MPI_ext_dev* dw_slave_ptr = (MPI_ext_dev*)ext_dev_object;

  DW_nodelist* dw_nodelist = (DW_nodelist*)dw_slave_ptr->MPI_data[NODE_LIST_INDEX];
  DW_config* dw_config = (DW_config*)dw_slave_ptr->MPI_conf[DW_CONFIG_INDEX];
  
 
  // MAKE SURE THIS VALUE IS BEING SET UPON READING IN A FRAME AND ALSO WHEN INITIALIZING
   // ANY AND ALL UNSOLICITED TX COMMUNICATION
   

  if(node_index == DW_CONFIG){
    uint32_t msg_header_end = dw_buildMessageHeader(dw_nodelist, dw_config, rw);
    uint32_t(*dw_config_query_ptr)() = dw_config_query_table[rw];
    return dw_config_query_ptr(dw_nodelist, dw_config, msg_header_end);
  } else {
    DW_data* dw_data = &dw_nodelist->list[node_index]; 
    uint32_t handler_index = dw_data->handler_index;
    uint32_t msg_header_end = dw_buildMessageHeader(dw_nodelist, dw_config, rw);
    //fire frame builder based on handler_index 
    uint32_t(*frame_builder_ptr)() = dw_frame_build_table[handler_index]; 
    int ret = frame_builder_ptr(host_object, host_usart, ext_dev_object, msg_header_end, node_index);
    if(ret == EXIT_SUCCESS){
      return node_index; 
    }
  }
  return EXIT_SUCCESS;
}


uint32_t dw_buildMessageHeader(DW_nodelist* dw_nodelist, DW_config* dw_config,  uint32_t read_write){

  //Each spi read/write is conducted by writing a transaction header, followed by a variable
  //number of data octets. The transaction header does not need to repeat for each data octet

  uint32_t rw = read_write;
  DW_nodelist* nodelist = dw_nodelist;
  DW_config* config = dw_config;
  int header_len = 1; //has to start at 1 for loop logic to work

  // header_build_ptr will return 1 if another octet, and thus another loop, is to be 
  // written. Otherwise it will return a 0 and table_index == header_len
  for(int table_index = 0; table_index < header_len; table_index++){
    uint32_t(*header_builder_ptr)() = dw_frame_header_read_write_table[table_index];
    int ret = header_builder_ptr(nodelist, config, rw); 
    header_len += ret; 
  }

  //return the starting index 
  //
  return header_len; 
}



/************************************************************
 *                       Builders
 ***********************************************************/

/*
 * SPI TRANSACTION HEADER BUILDERS
 */

uint32_t dw_reg_read_write(DW_nodelist* dw_nodelist, DW_config* dw_config, uint32_t read_write){

  DW_reg_id_enum reg_id_index = dw_config->reg_id_index;

  dw_nodelist->frame_out[0]  = dw_rw_bool_table[read_write];
  dw_nodelist->frame_out[0] |= dw_reg_id_table[(int)reg_id_index];
  
  if(dw_config->sub_addr_index > sub_addr_0){
    dw_nodelist->frame_out[0] |= MSG_SUB_ADDR_TRUE;
  } else {
    dw_nodelist->frame_out[0] |= MSG_SUB_ADDR_FALSE;
  }
  
  
  return (MSG_SUB_ADDR_TRUE & dw_nodelist->frame_out[0]);
}

uint32_t dw_sub_read_write(DW_nodelist* dw_nodelist, DW_config* dw_config, uint32_t read_write){
  
  DW_sub_addr_enum sub_addr_index = dw_config->sub_addr_index;
   
  dw_nodelist->frame_out[1] |= sub_addr_index;
 
  if(dw_config->sub_addr_index > (DW_sub_addr_enum)sub_addr_0){
    dw_nodelist->frame_out[1] |= MSG_EXT_ADDR_TRUE;
  } else {
    dw_nodelist->frame_out[1] |= MSG_EXT_ADDR_FALSE;
  }

  return (MSG_EXT_ADDR_TRUE & dw_nodelist->frame_out[1]);
  //because other bits will be set in the frame_out member, even if the boolean is set to false: it will return true. Therefore bitwise AND'ing with extract the bit and render true or false
}

uint32_t dw_ext_read_write(DW_nodelist* dw_nodelist, DW_config* dw_config, uint32_t read_write){
  
  DW_ext_addr_enum ext_addr_index = dw_config->sub_addr_index;
  dw_nodelist->frame_out[2] = ext_addr_index;
  
  return 0;
  //return 0 so that the return value and the parent loop iterator will be equal and the loop will stop 
}


/*
 * CONFIG BUILDERS
 */

uint32_t dw_buildConfig(DW_nodelist* dw_nodelist, DW_config* dw_config, uint32_t frame_index_start){

  uint32_t frame_index = frame_index_start;
  uint32_t len = dw_config->config_buffer_len;

  for(int i = 0; i < len; i++){
    dw_nodelist->frame_out[++frame_index] = dw_config->config_buffer[i];
  }
  dw_nodelist->frame_out_len = ++frame_index;  
  
  return EXIT_SUCCESS;
}



uint32_t dw_buildQuery(DW_nodelist* dw_nodelist, DW_config* dw_config, uint32_t frame_index_start){

  uint32_t frame_index = frame_index_start;
  uint32_t len = dw_config->query_buffer_len;

  for(int i = 0; i < len; i++){
    dw_nodelist->frame_out[++frame_index] = dw_config->config_buffer[i];
  }
  dw_nodelist->frame_out_len = ++frame_index;
  
  return EXIT_SUCCESS;
}


/*
 * FULL FRAME BUILDERS
 */


uint32_t dw_buildBlinkFrame(void* host_object, int(* host_usart)(), void* ext_dev_object, uint32_t frame_index_start, uint32_t nodelist_index){

  host_object = NULL;
  uint32_t node_index = nodelist_index;
  MPI_ext_dev* dw_slave_ptr = (MPI_ext_dev*)ext_dev_object;

  DW_config* dw_config = (DW_config*)dw_slave_ptr->MPI_conf[DW_CONFIG_INDEX]; 
  DW_nodelist* dw_nodelist = (DW_nodelist*)dw_slave_ptr->MPI_data[NODE_LIST_INDEX];
  DW_data* dw_data = &dw_nodelist->list[node_index]; 

  dw_config->ranging_mode = DWMODE_DISCOVERY;

  //send frame to put receiver into blink mode
  //
 
  dw_data->dev_status = DW_DEV_ACTIVE; 
  dw_data->sequence_num = (dw_data->sequence_num % 256) +1; 
  dw_data->handler_index = BLINK_INDEX;
  uint32_t frame_index = frame_index_start;

  dw_nodelist->frame_out[frame_index] = dw_frame_ctrl_table[FC_BLINK_INDEX][FC_BLINK_OCTET_0_INDEX];
  dw_nodelist->frame_out[++frame_index] = dw_data->sequence_num; //find out about auto-generated sequence number;
  dw_nodelist->frame_out[++frame_index] = dw_config->unique_id[0];
  dw_nodelist->frame_out[++frame_index] = dw_config->unique_id[1];
  dw_nodelist->frame_out[++frame_index] = dw_config->unique_id[2];
  dw_nodelist->frame_out[++frame_index] = dw_config->unique_id[3];
  dw_nodelist->frame_out[++frame_index] = dw_config->unique_id[4];
  dw_nodelist->frame_out[++frame_index] = dw_config->unique_id[5];
  dw_nodelist->frame_out[++frame_index] = dw_config->unique_id[6];
  dw_nodelist->frame_out[++frame_index] = dw_config->unique_id[7];

  dw_nodelist->frame_out_len = ++frame_index;

  return EXIT_SUCCESS;
}



uint32_t dw_buildRangeInitFrame(void* host_object, int(* host_usart)(), void* ext_dev_object, uint32_t frame_index_start, uint32_t nodelist_index){

  host_object = NULL;

  uint32_t node_index = nodelist_index;
  MPI_ext_dev* dw_slave_ptr = (MPI_ext_dev*)ext_dev_object;

  DW_config* dw_config = (DW_config*)dw_slave_ptr->MPI_conf[DW_CONFIG_INDEX]; 
  DW_nodelist* dw_nodelist = (DW_nodelist*)dw_slave_ptr->MPI_data[NODE_LIST_INDEX];
  DW_data* dw_data = &dw_nodelist->list[node_index]; 

  dw_config->ranging_mode = DWMODE_RANGEINIT;

  //insert the following:
  // bit 0   - function code: 0x20
  // bit 1-2 - tag short address 
  // bit 3-4 - calculated response delay
  //
  dw_data->sequence_num = (dw_data->sequence_num % 256) +1; 
  dw_data->handler_index = RANGE_INDEX;
  dw_data->resp_delay[0] = SINGLE_BYTE & dw_config->rf_tx_delay[0];
  dw_data->resp_delay[1] = SINGLE_BYTE & dw_config->rf_tx_delay[1]; 
  uint32_t frame_index = frame_index_start;

  dw_nodelist->frame_out[frame_index] = dw_frame_ctrl_table[FC_RANGE_INDEX][FC_RANGE_OCTET_0_INDEX];
  dw_nodelist->frame_out[++frame_index] = dw_frame_ctrl_table[FC_RANGE_INDEX][FC_RANGE_OCTET_1_INDEX];
  dw_nodelist->frame_out[++frame_index] = dw_data->sequence_num; //find out about auto-generated sequence number
  dw_nodelist->frame_out[++frame_index] = dw_data->pan_id[0]; //dest PAN ID octet 1 
  dw_nodelist->frame_out[++frame_index] = dw_data->pan_id[1]; //dest PAN ID octet 2
  dw_nodelist->frame_out[++frame_index] = dw_data->tag_id[0]; //dest addr octet 1
  dw_nodelist->frame_out[++frame_index] = dw_data->tag_id[1]; //dest addr octet 2
  dw_nodelist->frame_out[++frame_index] = dw_data->tag_id[2]; //dest addr octet 3
  dw_nodelist->frame_out[++frame_index] = dw_data->tag_id[3]; //dest addr octet 4
  dw_nodelist->frame_out[++frame_index] = dw_data->tag_id[4]; //dest addr octet 5
  dw_nodelist->frame_out[++frame_index] = dw_data->tag_id[5]; //dest addr octet 6
  dw_nodelist->frame_out[++frame_index] = dw_data->tag_id[6]; //dest addr octet 7
  dw_nodelist->frame_out[++frame_index] = dw_data->tag_id[7]; //dest addr octet 8
  dw_nodelist->frame_out[++frame_index] = dw_config->unique_id[0]; //src addr octet 1
  dw_nodelist->frame_out[++frame_index] = dw_config->unique_id[1]; //src addr octet 2
  dw_nodelist->frame_out[++frame_index] = dw_fn_code_table[RANGE_INDEX]; //message octet 1
  dw_nodelist->frame_out[++frame_index] = dw_data->tag_id[0]; //message octet 2
  dw_nodelist->frame_out[++frame_index] = dw_data->tag_id[1]; //message octet 3
  dw_nodelist->frame_out[++frame_index] = dw_data->resp_delay[0]; //message octet 4
  dw_nodelist->frame_out[++frame_index] = dw_data->resp_delay[1]; //message octet 5
 
  dw_nodelist->frame_out_len = ++frame_index;

  return EXIT_SUCCESS;
}



uint32_t dw_buildPollFrame(void* host_object, int(* host_usart)(), void* ext_dev_object, uint32_t frame_index_start, uint32_t nodelist_index){

  uint32_t node_index = nodelist_index;
  MPI_ext_dev* dw_slave_ptr = (MPI_ext_dev*)ext_dev_object;

  DW_config* dw_config = (DW_config*)dw_slave_ptr->MPI_conf[DW_CONFIG_INDEX]; 
  DW_nodelist* dw_nodelist = (DW_nodelist*)dw_slave_ptr->MPI_data[NODE_LIST_INDEX];
  DW_data* dw_data = &dw_nodelist->list[node_index]; 

  dw_config->ranging_mode = DWMODE_RANGING;
  
  //insert the following:
  // bit 0 - function code: 0x61
  //

  dw_data->sequence_num = (dw_data->sequence_num % 256) +1; 
  dw_data->handler_index = POLL_INDEX;
  uint32_t frame_index = frame_index_start;
 
  dw_nodelist->frame_out[frame_index] = dw_frame_ctrl_table[FC_POLL_RESP_FINAL_INDEX][FC_POLL_RESP_FINAL_OCTET_0_INDEX];
  dw_nodelist->frame_out[++frame_index] = dw_frame_ctrl_table[FC_POLL_RESP_FINAL_INDEX][FC_POLL_RESP_FINAL_OCTET_1_INDEX];
  dw_nodelist->frame_out[++frame_index] = dw_data->sequence_num; //find out about auto-generated sequence number
  dw_nodelist->frame_out[++frame_index] = dw_data->pan_id[0]; 
  dw_nodelist->frame_out[++frame_index] = dw_data->pan_id[1];
  dw_nodelist->frame_out[++frame_index] = dw_data->short_addr[0]; //dest addr (src addr range init)
  dw_nodelist->frame_out[++frame_index] = dw_data->short_addr[1]; //dest addr (src addr range init)
  dw_nodelist->frame_out[++frame_index] = dw_config->unique_id[0]; //src addr octet 1
  dw_nodelist->frame_out[++frame_index] = dw_config->unique_id[1]; //src addr octet 2
  dw_nodelist->frame_out[++frame_index] = dw_fn_code_table[POLL_INDEX]; //poll fn code

  dw_nodelist->frame_out_len = ++frame_index;

  return EXIT_SUCCESS;
}



uint32_t dw_buildResponseFrame(void* host_object, int(* host_usart)(), void* ext_dev_object, uint32_t frame_index_start, uint32_t nodelist_index){

  uint32_t node_index = nodelist_index;
  MPI_ext_dev* dw_slave_ptr = (MPI_ext_dev*)ext_dev_object;

  DW_config* dw_config = (DW_config*)dw_slave_ptr->MPI_conf[DW_CONFIG_INDEX]; 
  DW_nodelist* dw_nodelist = (DW_nodelist*)dw_slave_ptr->MPI_data[NODE_LIST_INDEX];
  DW_data* dw_data = &dw_nodelist->list[node_index]; 

  //insert the following:
  // bit 0    - function code: 0x50
  // bit 1-4  - calculated ToF
  //

  dw_data->sequence_num = (dw_data->sequence_num % 256) +1; 
  dw_data->handler_index = RESP_INDEX;
  uint32_t frame_index = frame_index_start;

  dw_nodelist->frame_out[frame_index] = dw_frame_ctrl_table[FC_POLL_RESP_FINAL_INDEX][FC_POLL_RESP_FINAL_OCTET_0_INDEX];
  dw_nodelist->frame_out[++frame_index] = dw_frame_ctrl_table[FC_POLL_RESP_FINAL_INDEX][FC_POLL_RESP_FINAL_OCTET_1_INDEX];  
  dw_nodelist->frame_out[++frame_index] = dw_data->sequence_num; //find out about auto-generated sequence number
  dw_nodelist->frame_out[++frame_index] = dw_data->pan_id[0]; 
  dw_nodelist->frame_out[++frame_index] = dw_data->pan_id[1];
  dw_nodelist->frame_out[++frame_index] = dw_data->short_addr[0]; //dest addr octet 1
  dw_nodelist->frame_out[++frame_index] = dw_data->short_addr[1]; //dest addr octet 2
  dw_nodelist->frame_out[++frame_index] = dw_config->unique_id[0]; //src addr octet 1
  dw_nodelist->frame_out[++frame_index] = dw_config->unique_id[1]; //src addr octet 2
  dw_nodelist->frame_out[++frame_index] = dw_fn_code_table[RESP_INDEX]; //poll fn code

  void(*tof_ptr)() = dw_ts_handler_table[RESP_INDEX];  
  tof_ptr(host_object, host_usart, ext_dev_object, nodelist_index);

  dw_nodelist->frame_out[++frame_index] = (SINGLE_BYTE & dw_data->tof.treplyx._1);

  for(int i = 1; i < RESP_MSG_WORD_LEN; i++){
    dw_nodelist->frame_out[++frame_index] = (SINGLE_BYTE & (dw_data->tof.treplyx._1 >> SINGLE_BYTE_SHIFT));
  }

  dw_nodelist->frame_out_len = ++frame_index;
  
  return EXIT_SUCCESS;
}



uint32_t dw_buildFinalFrame(void* host_object, int(* host_usart)(), void* ext_dev_object, uint32_t frame_index_start, uint32_t nodelist_index){

  uint32_t node_index = nodelist_index;
  MPI_ext_dev* dw_slave_ptr = (MPI_ext_dev*)ext_dev_object;

  DW_config* dw_config = (DW_config*)dw_slave_ptr->MPI_conf[DW_CONFIG_INDEX]; 
  DW_nodelist* dw_nodelist = (DW_nodelist*)dw_slave_ptr->MPI_data[NODE_LIST_INDEX];
  DW_data* dw_data = &dw_nodelist->list[node_index]; 
  
  //insert the following:
  // bit 0    - function code: 0x69
  // bit 1-4  - resp RX time minus poll TX time
  // bit 5-8  - final TX time minus resp RX time
  //
  dw_data->sequence_num = (dw_data->sequence_num % 256) +1; 
  dw_data->handler_index = FINAL_INDEX;
  uint32_t frame_index = frame_index_start;

  dw_nodelist->frame_out[frame_index] = dw_frame_ctrl_table[FC_POLL_RESP_FINAL_INDEX][FC_POLL_RESP_FINAL_OCTET_0_INDEX];
  dw_nodelist->frame_out[++frame_index] = dw_frame_ctrl_table[FC_POLL_RESP_FINAL_INDEX][FC_POLL_RESP_FINAL_OCTET_1_INDEX];
  dw_nodelist->frame_out[++frame_index] = dw_data->sequence_num; //find out about auto-generated sequence number
  dw_nodelist->frame_out[++frame_index] = dw_data->pan_id[0]; 
  dw_nodelist->frame_out[++frame_index] = dw_data->pan_id[1];
  dw_nodelist->frame_out[++frame_index] = dw_data->short_addr[0]; //dest addr octet 1
  dw_nodelist->frame_out[++frame_index] = dw_data->short_addr[1]; //dest addr octet 2
  dw_nodelist->frame_out[++frame_index] = dw_config->unique_id[0]; //src addr octet 1
  dw_nodelist->frame_out[++frame_index] = dw_config->unique_id[1]; //src addr octet 2
  dw_nodelist->frame_out[++frame_index] = dw_fn_code_table[FINAL_INDEX]; //poll fn code 

  void(*tof_ptr)() = dw_ts_handler_table[FINAL_INDEX];  
  tof_ptr(host_object, host_usart, ext_dev_object, nodelist_index);

  dw_nodelist->frame_out[++frame_index] = (SINGLE_BYTE & dw_data->tof.troundx._1);
  for(int i = 1; i < FINAL_MSG_WORD_LEN; i++){
    dw_nodelist->frame_out[++frame_index] = (SINGLE_BYTE & (dw_data->tof.troundx._1 >> SINGLE_BYTE_SHIFT));
  }
  dw_nodelist->frame_out[++frame_index] = (SINGLE_BYTE & dw_data->tof.treplyx._2);
  for(int i = 1; i < FINAL_MSG_WORD_LEN; i++){
    dw_nodelist->frame_out[++frame_index] = (SINGLE_BYTE & (dw_data->tof.treplyx._2 >> SINGLE_BYTE_SHIFT));
  }

  dw_nodelist->frame_out_len = ++frame_index;
  
  return EXIT_SUCCESS;
}

/*
 * FRAME BUILDER TABLES
 */

uint32_t(* dw_config_query_table[DW_READ_WRITE +1])() = {
  dw_buildQuery,
  dw_buildConfig,
  NULL
};


uint32_t(*const dw_frame_build_table[BUILD_TABLE_LEN])() = {
  dw_buildBlinkFrame,
  dw_buildRangeInitFrame,
  dw_buildPollFrame,
  dw_buildResponseFrame,
  dw_buildFinalFrame,
  NULL
};





/*
 * SPI TRANSACTION BUILDER TABLES
 */

//read write table
uint8_t dw_rw_bool_table[3] = {
  MESSAGE_READ,
  MESSAGE_WRITE,
};

/*
uint8_t dw_ext_bool_table[3] = {
  MSG_EXT_ADDR_FALSE,
  MSG_EXT_ADDR_TRUE,
};
*/

bool sub_addr_bool_table[REG_IDS_LEN] = {
  MSG_SUB_ADDR_FALSE,
  MSG_SUB_ADDR_TRUE,
  NULL
};
bool ext_addr_bool_table[REG_IDS_LEN] = {
  MSG_SUB_ADDR_FALSE,
  MSG_SUB_ADDR_TRUE,
  NULL
};

uint32_t(*const dw_frame_header_read_write_table[REG_SUB_EXT])() = {
  dw_reg_read_write,
  dw_sub_read_write,
  dw_ext_read_write,
  NULL
};


