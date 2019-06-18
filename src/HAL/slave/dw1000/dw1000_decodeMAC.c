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
#include "dw1000_decodeMAC.h"
#include "dw1000_nodeMgmt.h"
#include "dw1000_tofCalcs.h"
#include "dw1000_commRxTx.h"

typedef struct {
  uint8_t pan_id_index;
  uint8_t dest_addr_index;
  uint8_t src_addr_index;
  uint8_t msg_start_index;
  uint32_t frame_type_index;
  uint8_t fn_code_index;
}DW_frame_index;
static DW_frame_index frame_index;

uint32_t dw_handlerBlink(void* host_object, int(*host_usart)(), DW_nodelist* dw_nodelist, DW_config* dw_config);
uint32_t dw_handlerRangeInit(void* host_object, int(*host_usart)(), DW_nodelist* dw_nodelist, DW_config* dw_config);
uint32_t dw_handlerPollRespFinal(void* host_object, int(*host_usart)(), DW_nodelist* dw_nodelist, DW_config* dw_config);
uint32_t dw_handlerPoll(void* host_object, int(*host_usart)(), DW_nodelist* dw_nodelist, DW_config* dw_config);
uint32_t dw_handlerResp(void* host_object, int(*host_usart)(), DW_nodelist* dw_nodelist, DW_config* dw_config);
uint32_t dw_handlerFinal(void* host_object, int(*host_usart)(), DW_nodelist* dw_nodelist, DW_config* dw_config);


uint32_t dw_decodeFrameCtrl(DW_nodelist* dw_nodelist){

  uint8_t frame_ctrl_octet_0 = dw_nodelist->frame_in[FRAME_CTRL_INDEX_0];
  uint8_t frame_ctrl_octet_1 = dw_nodelist->frame_in[FRAME_CTRL_INDEX_1];

  //check the first octet of frame control 
  for(uint32_t i = 0; i < DECODE_TABLE_LEN; i++){
   
    //if the first octets match and the iterator is still 0, then it's a blink frame 
    if(((dw_frame_ctrl_table[i][0] & frame_ctrl_octet_0) == 0) && (i == FC_BLINK_INDEX)){
      return i;
    }
    
    //but if it matches an entry in the table, then move onto the second octet 
    //and do the same type of checks again to identify which of range_init v Poll/Resp/Final
    //which specific Poll/Response/Final will be examined in the Poll/Resp/Final parent handler
    if((dw_frame_ctrl_table[i][0] & frame_ctrl_octet_0) == 0){
      for(uint32_t j = i; j < DECODE_FRAME_CTRL_TABLE_WIDTH; i++){
        if((dw_frame_ctrl_table[j][1] & frame_ctrl_octet_1) == 0){
          return j;
        } 
      }
    } //end if conditional

  } //end for loop

  return ERROR;
}

uint32_t dw_decodeFrameIn(void* host_object, int(*host_usart)(), void* ext_dev_object){
 
  MPI_ext_dev* dw_slave_ptr = (MPI_ext_dev*)ext_dev_object;
  DW_config* dw_config = (DW_config*)dw_slave_ptr->MPI_conf[DW_CONFIG_INDEX]; 
  DW_nodelist* dw_nodelist = (DW_nodelist*)dw_slave_ptr->MPI_data[NODE_LIST_INDEX];

  frame_index.frame_type_index = dw_decodeFrameCtrl(dw_nodelist); 

  //Call to jump table to extract bits based on frame length, then call to the rest
  //of the data tables to extract the necessary values based on the frame type
  //
  dw_nodelist->frame_in_len = frame_len_table[frame_index.frame_type_index];//call to jump table to get frame length
  dw_nodelist->reg_id_index = REG_ID_RX_BUFFER;
  
  frame_index.pan_id_index = pan_id_index_table[frame_index.frame_type_index];
  frame_index.dest_addr_index = dest_addr_index_table[frame_index.frame_type_index];
  frame_index.src_addr_index = src_addr_index_table[frame_index.frame_type_index];
  frame_index.msg_start_index = msg_index_table[frame_index.frame_type_index];
  frame_index.fn_code_index = fn_code_index_table[frame_index.frame_type_index];

  //make rx call to read frame
  dw_Rx(host_object, host_usart, dw_nodelist, dw_nodelist->frame_in, dw_nodelist->frame_in_len);

  //Call to handler jump table (move all code below into the handlers
  //and poll/resp/final into one parent handler
  //
  uint32_t(*handler_fn_ptr)() = dw_handler_table[frame_index.frame_type_index];
  dw_nodelist->node_index = handler_fn_ptr(host_object, host_usart, dw_nodelist, dw_config); //send parameters to response handlers

  //return index
  //
  return dw_nodelist->node_index;
}

/******************************************************
 *           Message In response handlers
 ******************************************************/

  // NOTE: we must store the sequence number, that 
  // corresponds to the stage in the ranging or 
  // discovery process, in the dw_data struct member
  // 'handler_index'

/*
 * The purpose of the message in handlers is to discern which message is being
 * received, identify if the message is intended for this device, then check
 * if it is from a known device, to then call the ToF calculators which calculate 
 * the response values and store those values in the known device data node. The
 * calculator fn then finishes executing and the handlers passes back the index 
 * of said stored node.
 *
 */

uint32_t dw_handlerBlink(void* host_object, int(*host_usart)(), DW_nodelist* dw_nodelist, DW_config* dw_config){

  uint8_t tag_id[9];

  for(int i = 0; i < BLINK_SRC_ADDR_LEN; i++){
    tag_id[i] = dw_nodelist->frame_in[i+frame_index.src_addr_index];
  }

  //search the list for known node
  //
   uint32_t(* node_search)() = node_list_table[DW_NODE_SEARCH];
   uint32_t node_index = node_search(dw_nodelist, tag_id);

  // if not known, add node to list
  //
  if(node_index == ERROR){
    uint32_t(* node_create)() = node_list_table[DW_NODE_CREATE];
    uint32_t index = node_create(dw_nodelist, tag_id);

  if(index != ERROR){
    for(int i = 0; i < BLINK_SRC_ADDR_LEN; i++){
      dw_nodelist->list[index].tag_id[i] = tag_id[i];
    }
  }

  //store short address and response delay
  //
  for(int i = 0; i < BLINK_SHORT_ADDR_LEN; i++){
    dw_nodelist->list[index].short_addr[i] = dw_nodelist->frame_in[i+BLINK_SRC_ADDR_INDEX];
    dw_nodelist->list[index].resp_delay[i] = dw_config->rf_tx_delay[i];
  }

  //store the handler index
  //
  dw_nodelist->list[index].handler_index = BLINK_INDEX +1;
   
  //return node_index
  //
  return index;
} else {
  
  //store short address 
  //
  for(int i = 0; i < BLINK_SHORT_ADDR_LEN; i++){
    dw_nodelist->list[node_index].short_addr[i] = dw_nodelist->frame_in[i+BLINK_SHORT_ADDR_INDEX];
    dw_nodelist->list[node_index].resp_delay[i] = dw_config->rf_tx_delay[i];
  }

  //store the handler index
  //
  dw_nodelist->list[node_index].handler_index = BLINK_INDEX +1;
 
  //return node_index
  //   
  return node_index;
}
return ERROR;
}



uint32_t dw_handlerRangeInit(void* host_object, int(*host_usart)(), DW_nodelist* dw_nodelist, DW_config* dw_config){

  //first check if this frame is for this device
  //
  for(int i = 0; i < RANGE_DEST_ADDR_LEN; i++){
    if((dw_config->device_id[i] & dw_nodelist->frame_in[i+frame_index.dest_addr_index]) == 0){
      continue;
    } else {
      return ERROR;
    }
  }

  uint8_t tag_id[EUI_64_LEN];
  //assign src addr to tag_id
  for(int i = 0; i < BLINK_SRC_ADDR_LEN; i++){
    tag_id[i] = dw_nodelist->frame_in[i+frame_index.src_addr_index];
  }

  //search the list for known node
  //
  uint32_t(* node_search)() = node_list_table[DW_NODE_SEARCH];
  uint32_t node_index = node_search(dw_nodelist, tag_id);

  if(node_index == ERROR){
   
    return ERROR;
    
     
    uint32_t(* node_create)() = node_list_table[DW_NODE_CREATE];
    uint32_t index = node_create(dw_nodelist, tag_id);
    

    /*
     * STORE DATA FROM INCOMING NODE INTO NEW NODE
     */
    //store short address and response delay
    for(int i = 0; i < RANGE_MSG_WORD_LEN; i++){
      dw_nodelist->list[index].short_addr[i] = dw_nodelist->frame_in[i+RANGE_MSG_1_INDEX];
      dw_nodelist->list[index].resp_delay[i] = dw_nodelist->frame_in[i+RANGE_MSG_2_INDEX]; 
    }
 
    //store the handler index
    //
    dw_nodelist->list[index].handler_index = RANGE_INDEX +1;
    
     
    //return data index
    //
    return index;
      
  } else {
 
    /*
     * STORE DATA FROM INCOMING NODE INTO NEW NODE
     */
    //store short address and response delay
    for(int i = 0; i < RANGE_MSG_WORD_LEN; i++){
      dw_nodelist->list[node_index].short_addr[i] = dw_nodelist->frame_in[i+RANGE_MSG_1_INDEX];
      dw_nodelist->list[node_index].resp_delay[i] = dw_nodelist->frame_in[i+RANGE_MSG_2_INDEX]; 
    }
 
    //store the handler index
    //
    dw_nodelist->list[node_index].handler_index = RANGE_INDEX +1;
  
    //return data index
    //
    return node_index;
  } 
  return ERROR;
}




/*
 * Parent handler for poll/resp/final
 *
 * Determine which of the three needs to be executed, based on fn code at start of 
 * incoming message
 *
 */
uint32_t dw_handlerPollRespFinal(void* host_object, int(*host_usart)(), DW_nodelist* dw_nodelist, DW_config* dw_config){

//first decide if it's for this device
//
for(int i = 0; i < POLL_RESP_FINAL_ADDR_LEN; i++){
  if((dw_config->device_id[i] & dw_nodelist->frame_in[i+frame_index.dest_addr_index]) == 0){
    continue;
  } else {
    return ERROR;
  }
}

//find out which of poll, resp, final 
//
int handler_index;
for(int i = 0; i < 2; i++){
  if((dw_fn_code_table[DW_TWR_FN_INDEX+i] & dw_nodelist->frame_in[frame_index.fn_code_index]) == 0){
    handler_index = DW_TWR_FN_INDEX+i;
  } else {
    continue;
  }
}

//fire off poll/resp/final handler proper
//
uint32_t(*handler_ptr)() = poll_resp_final_handler_table[handler_index];
return handler_ptr(host_object, host_usart, dw_nodelist, dw_config);
}

uint32_t dw_handlerPoll(void* host_object, int(*host_usart)(), DW_nodelist* dw_nodelist, DW_config* dw_config){
 
//first decide if it's for this device
//
for(int i = 0; i < POLL_RESP_FINAL_ADDR_LEN; i++){
  if((dw_config->device_id[i] & dw_nodelist->frame_in[i+frame_index.dest_addr_index]) == 0){
    continue;
  } else {
    return ERROR;
  }
}

uint8_t tag_id[EUI_64_LEN];
//assign src addr to tag_id
//
for(int i = 0; i < BLINK_SRC_ADDR_LEN; i++){
  tag_id[i] = dw_nodelist->frame_in[i+frame_index.src_addr_index];
}
 
//search the list for known node
//
 uint32_t(* node_search)() = node_list_table[DW_NODE_SEARCH];
 uint32_t node_index = node_search(dw_nodelist, tag_id);

 if(node_index == ERROR){
  return ERROR;   
} else {

  DW_data dw_data = dw_nodelist->list[node_index];

  //store the handler index
  //
  dw_data.handler_index = POLL_INDEX +1;

  //create the data point
  //
  //uint32_t(*fn_ptr)() = dw_tof_table[POLL_INDEX];
  //fn_ptr(dw_nodelist->list[node_index]);

  //read the rx marker
  //
  dw_nodelist->reg_id_index = REG_ID_RX_MARKER;
  dw_nodelist->sub_addr_index = SUB_ADDR_RX_MARKER_0;
  dw_nodelist->frame_in_len = RX_MARKER_TOTAL_LEN - 1; 

  uint8_t rx_marker[RX_MARKER_TOTAL_LEN - 1];
  dw_Rx(host_object, host_usart, dw_nodelist, rx_marker, RX_MARKER_TOTAL_LEN - 1);

  for(int i = RX_MARKER_TOTAL_LEN -1; i < 0; i--){
    dw_data.tof.poll.rx_marker = (dw_data.tof.poll.rx_marker << SINGLE_BYTE_SHIFT) | rx_marker[i];
  }


  //call to tof calculator to calculate response message
  //
  void(*poll_to_resp)() = dw_ts_handler_table[RESP_INDEX];
  poll_to_resp(dw_data, dw_config);
  return node_index;
} 
return ERROR;
}



uint32_t dw_handlerResp(void* host_object, int(*host_usart)(), DW_nodelist* dw_nodelist, DW_config* dw_config){

//first decide if it's for this device
//
for(int i = 0; i < POLL_RESP_FINAL_ADDR_LEN; i++){
  if((dw_config->device_id[i] & dw_nodelist->frame_in[i+frame_index.dest_addr_index]) == 0){
    continue;
  } else {
    return ERROR;
  }
}

uint32_t tag_id[EUI_64_LEN];
//assign src addr to tag_id
for(int i = 0; i < POLL_RESP_FINAL_ADDR_LEN; i++){
  tag_id[i] = dw_nodelist->frame_in[i+frame_index.src_addr_index];
}

//search the list for known node
 uint32_t(* node_search)() = node_list_table[DW_NODE_SEARCH];
 uint32_t node_index = node_search(dw_nodelist, tag_id);

 if(node_index == ERROR){
  return ERROR;   
} else {

  DW_data dw_data = dw_nodelist->list[node_index];

  //store the handler index
  //
  dw_data.handler_index = RESP_INDEX +1;

 //create the data point
 //
 //uint32_t(*fn_ptr)() = dw_tof_table[RESP_INDEX];
 //fn_ptr(dw_nodelist->list[node_index]);
 
 /*
  * STORE DATA FROM INCOMING NODE INTO NEW NODE
  */
  for(int i = RESP_MSG_WORD_LEN -1; i > 1; i--){
    dw_data.tof.treplyx._1 = (dw_data.tof.treplyx._1 << SINGLE_BYTE_SHIFT) | (SINGLE_BYTE & dw_nodelist->frame_in[i+RESP_MSG_1_INDEX]); 
  }

  //read the rx marker
  //
  dw_nodelist->reg_id_index = REG_ID_RX_MARKER;
  dw_nodelist->sub_addr_index = SUB_ADDR_RX_MARKER_0;
  dw_nodelist->frame_in_len = RX_MARKER_TOTAL_LEN - 1; 

  uint8_t rx_marker[RX_MARKER_TOTAL_LEN - 1];
  dw_Rx(host_object, host_usart, dw_nodelist, rx_marker, RX_MARKER_TOTAL_LEN - 1);

  for(int i = RX_MARKER_TOTAL_LEN -1; i < 0; i--){
    dw_data.tof.poll.rx_marker = (dw_data.tof.poll.rx_marker << SINGLE_BYTE_SHIFT) | rx_marker[i];
  }


  //call to tof calculator to calculate response message
  //
  void(*resp_to_final)() = dw_ts_handler_table[FINAL_INDEX];
  resp_to_final(dw_data, dw_config);
  return node_index;
} 
return ERROR;
}



uint32_t dw_handlerFinal(void* host_object, int(*host_usart)(), DW_nodelist* dw_nodelist, DW_config* dw_config){

  //first decide if it's for this device
  //
  for(int i = 0; i < POLL_RESP_FINAL_ADDR_LEN; i++){
    if((dw_config->device_id[i] & dw_nodelist->frame_in[i+frame_index.dest_addr_index]) == 0){
      continue;
    } else {
      return ERROR;
    }
  }

  uint8_t tag_id[EUI_64_LEN];
  //assign src addr to tag_id
  for(int i = 0; i < POLL_RESP_FINAL_ADDR_LEN; i++){
    tag_id[i] = dw_nodelist->frame_in[i+frame_index.src_addr_index];
  }

  //search the list for known node
  uint32_t(* node_search)() = node_list_table[DW_NODE_SEARCH];
  uint32_t node_index = node_search(dw_nodelist, tag_id);

  if(node_index == ERROR){
    return ERROR;   
  } else {

    DW_data dw_data = dw_nodelist->list[node_index];

    //store the handler index
    //
    dw_data.handler_index = FINAL_INDEX +1;

    //create the data point
    //
    //uint32_t(*fn_ptr)() = dw_tof_table[FINAL_INDEX];
    //fn_ptr(dw_nodelist->list[node_index]);

    /*
     * STORE DATA FROM INCOMING NODE INTO NEW NODE
     */
    for(int i = FINAL_MSG_WORD_LEN; i > 0; i--){
      dw_data.tof.troundx._1 = (dw_data.tof.troundx._1 << SINGLE_BYTE_SHIFT) | (SINGLE_BYTE & dw_nodelist->frame_in[i+FINAL_MSG_1_INDEX]); 
      dw_data.tof.treplyx._2 = (dw_data.tof.treplyx._2 << SINGLE_BYTE_SHIFT) | (SINGLE_BYTE & dw_nodelist->frame_in[i+FINAL_MSG_2_INDEX]); 
    }

    //read the rx marker
    //
    dw_nodelist->reg_id_index = REG_ID_RX_MARKER;
    dw_nodelist->sub_addr_index = SUB_ADDR_RX_MARKER_0;
    dw_nodelist->frame_in_len = RX_MARKER_TOTAL_LEN - 1; 

    uint8_t rx_marker[RX_MARKER_TOTAL_LEN - 1];
    dw_Rx(host_object, host_usart, dw_nodelist, rx_marker, RX_MARKER_TOTAL_LEN - 1);
 
    for(int i = RX_MARKER_TOTAL_LEN -1; i < 0; i--){
      dw_data.tof.poll.rx_marker = (dw_data.tof.poll.rx_marker << SINGLE_BYTE_SHIFT) | rx_marker[i];
    }

    //fire off the final distance measuring function
    //
    void (* final_dist_ptr)() = dw_ts_handler_table[TOF_DIST_INDEX];
    final_dist_ptr(dw_nodelist->list[node_index], dw_config);

    /*
    uint32_t(*device_store)() = device_list_table[DW_DEV_STORE];
    uint32_t network_index = device_store(dw_nodelist, node_index);
    */
    
    int ret = dw_deviceStore(dw_nodelist, node_index);

    if(ret == EXIT_SUCCESS){
      dw_nodelist->list[node_index].handler_index = POLL_INDEX;
      return EXIT_SUCCESS;
    } else {
      return ERROR;
    }
  } 
  return ERROR;
}



uint8_t frame_src_addr_index_start_table[FRAME_INDEX_TABLE] = {
  BLINK_SRC_ADDR_INDEX,
  RANGE_SRC_ADDR_INDEX,
  POLL_RESP_FINAL_SRC_ADDR_INDEX
};

uint8_t pan_id_index_table[FRAME_INDEX_TABLE] = {
  0, //blink does not have a pan id
  RANGE_PAN_ID_INDEX,
  POLL_RESP_FINAL_PAN_ID_INDEX
};

uint8_t dest_addr_index_table[FRAME_INDEX_TABLE] = {
  BLINK_DEST_ADDR_INDEX,
  RANGE_DEST_ADDR_INDEX,
  POLL_RESP_FINAL_DEST_ADDR_INDEX
};

uint8_t src_addr_index_table[FRAME_INDEX_TABLE] = {
  BLINK_SRC_ADDR_INDEX,
  RANGE_SRC_ADDR_INDEX,
  POLL_RESP_FINAL_SRC_ADDR_INDEX
};

uint8_t msg_index_table[FRAME_INDEX_TABLE] = {
  0, //blink does not have a payload
  RANGE_MSG_INDEX,
  POLL_RESP_FINAL_MSG_INDEX
};

uint8_t fn_code_index_table[3] = {
  FN_CODE_BLINK_INDEX,
  FN_CODE_RANGE_INDEX,
  FN_CODE_POLL_RESP_FINAL_INDEX
};



uint32_t(*const dw_handler_table[HANDLER_TABLE_LEN])() = {
  dw_handlerBlink,
  dw_handlerRangeInit,
  dw_handlerPollRespFinal,
  NULL  
};


uint32_t (*poll_resp_final_handler_table[3])() = {
  dw_handlerPoll,
  dw_handlerResp,
  dw_handlerFinal
};

uint8_t frame_len_table[FRAME_INDEX_TABLE] = {
  BLINK_FRAME_LEN,
  RANGE_FRAME_LEN,
  POLL_RESP_FINAL_FRAME_LEN
};


