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
#include <stdbool.h>
#include <stdint.h>

#include "mpi_port.h"

#include "dw1000_adaptor.h"
#include "dw1000_types.h"
#include "dw1000_regs.h"


#include "dw1000_nodeMgmt.h"
#include "dw1000_buildMAC.h"
#include "dw1000_decodeMAC.h"
#include "dw1000_commRxTx.h"
#include "dw1000_tofCalcs.h"


/**************************************************************
 *                  HAL API functions
 *************************************************************/

/*
 *
 * - How we write and read from registers should be addressed in the interface fns. 
 *
 *   dw_Init:
 *   - start at the first register and write the appropriate values from our config struct, whilst iterating 
 *   through an array with the corresponding register indexes
 *
 *   dw_RegDump: 
 *   - do the same as dw_Init but read as opposed to write
 *
 *   dw_ConfigReg:
 *   - write to a register pre-assigned to the config struct
 *
 *   dw_QueryReg:
 *   - read from a register pre-assigned to the config struct
 *
 *   dw_Data/Reset/Off/Sleep/Wakeup:
 *   - assign the register value within the interface fn
 *
 *   dw_ModeLevel:
 *   - the same as Data/Reset/Off/Sleep/Wakeup
 *   - pre-assign mode level in config struct
 *
 */

/*
#define ENUM(type, ...) 

enum _##type { __VA_ARGS__ }; 
enum _##type type##s[] = { __VA_ARGS__ }
*/

/*
 *  Steps to initialize device:
 *
 *  - write to the config struct members prior calling interface functions
 *  - read from the config struct members based on a function called from a jump table
 *  - iterate through that jump table and build a message from that config 
 *  - use the iterator to pull the register adddress (pertanent to that config member), from another jump table
 *  - use the same iterator to pull the length of the member from yet another jump table
 *  - it should go without saying that these three jump tables should be in a mirrored configuration
 *
 */

uint32_t(* dw_decode_build_table[3])() = {
  dw_decodeFrameIn,
  dw_buildMessageOut,
  NULL
};


int dw_Init(void* host_object, int(*host_usart)(), void* ext_dev_object){

  MPI_ext_dev* dw_slave_ptr = (MPI_ext_dev*)ext_dev_object;
  DW_config* dw_config = (DW_config*)dw_slave_ptr->MPI_conf[DW_CONFIG_INDEX];  
  DW_nodelist* dw_nodelist = (DW_nodelist*)dw_slave_ptr->MPI_data[NODE_LIST_INDEX];

  dw_config->config_index = device_id;

  //for loop with call to write into struct members
  //
  for(int i = 0; i < CONFIG_STRUCT_MEMBERS; i++){
   
    dw_nodelist->reg_id_index = config_table_reg_id_table[dw_config->config_index];
    dw_config->config_index = dw_config->config_index + 1;

    
    void(*config_member_ptr)() = config_table[i]; 
    config_member_ptr(dw_config);

    
    //if tx call to dw_buildMessage()
    //if rx call to dw_decodeMessage()
    //
    volatile uint32_t(* build_msg_ptr)() = dw_decode_build_table[WRITE];
    int ret = build_msg_ptr(ext_dev_object, WRITE, DW_CONFIG);
    
    //int ret = dw_buildMessageOut(ext_dev_object, WRITE, 0);
   
    //callback to host usart
    //
    if(ret == EXIT_SUCCESS){
      dw_Tx(host_object, host_usart, dw_nodelist, dw_nodelist->frame_out, dw_nodelist->frame_out_len);
    } else {
      return ERROR;
    } 
  }
  return EXIT_SUCCESS;
}
  

int dw_RegDump(void* host_object, int(*host_usart)(), void* ext_dev_object){
 
  MPI_ext_dev* dw_slave_ptr = (MPI_ext_dev*)ext_dev_object;
  DW_config* dw_config = (DW_config*)dw_slave_ptr->MPI_conf[DW_CONFIG_INDEX];  
  DW_nodelist* dw_nodelist = (DW_nodelist*)dw_slave_ptr->MPI_data[NODE_LIST_INDEX];

  dw_config->query_index = device_id;

  for(int i = 0; i < QUERY_STRUCT_MEMBERS; i++){
   
    dw_nodelist->reg_id_index = query_table_reg_id_table[dw_config->query_index];
    dw_config->query_index = dw_config->query_index + 1;

    uint32_t(*build_msg_ptr)() = dw_decode_build_table[READ];
    int ret = build_msg_ptr(ext_dev_object, READ, DW_CONFIG);

    //callback to host usart
    //
    if(ret == EXIT_SUCCESS){
      dw_Rx(host_object, host_usart, dw_nodelist, dw_config->query_buffer, dw_config->query_buffer_len);
      
      //Write into struct member
      //
      void(*query_member_ptr)() = query_table[dw_config->query_index]; 
      query_member_ptr(dw_config);
    } else {
      return ERROR;
    }
  } 
  return EXIT_SUCCESS;
}


/*
 * SINGLE REG/FIELD CONFIG/QUERY
 */

int dw_ConfigReg(void* host_object, int(*host_usart)(), void* ext_dev_object, uint32_t config_register){
 
  MPI_ext_dev* dw_slave_ptr = (MPI_ext_dev*)ext_dev_object;
  DW_config* dw_config = (DW_config*)dw_slave_ptr->MPI_conf[DW_CONFIG_INDEX];  
  DW_nodelist* dw_nodelist = (DW_nodelist*)dw_slave_ptr->MPI_data[NODE_LIST_INDEX];

  dw_nodelist->reg_id_index = query_table_reg_id_table[dw_config->query_index];
  
  //call to adjust struct member value
  //
  void(*config_member_ptr)() = config_table[dw_config->config_index]; 
  config_member_ptr(dw_config);
 
  //if tx call to dw_buildMessage()
  //if rx call to dw_decodeMessage()
  //
  uint32_t(*build_msg_ptr)() = dw_decode_build_table[WRITE];
  int ret = build_msg_ptr(ext_dev_object, WRITE, DW_CONFIG);

  //callback to host usart
  //
  if(ret == EXIT_SUCCESS){  
    dw_Tx(host_object, host_usart, dw_nodelist, dw_nodelist->frame_out, dw_nodelist->frame_out_len);
  } 
  return ERROR;
}

int dw_QueryReg(void* host_object, int(*host_usart)(), void* ext_dev_object, uint32_t config_register){
  
  MPI_ext_dev* dw_slave_ptr = (MPI_ext_dev*)ext_dev_object;
  DW_config* dw_config = (DW_config*)dw_slave_ptr->MPI_conf[DW_CONFIG_INDEX];  
  DW_nodelist* dw_nodelist = (DW_nodelist*)dw_slave_ptr->MPI_data[NODE_LIST_INDEX];

  dw_nodelist->reg_id_index = query_table_reg_id_table[dw_config->query_index];

  uint32_t(*build_msg_ptr)() = dw_decode_build_table[READ];
  int ret = build_msg_ptr(ext_dev_object, READ, DW_CONFIG);

  //callback to host usart
  //
  if(ret == EXIT_SUCCESS){
    dw_Rx(host_object, host_usart, dw_nodelist, dw_config->query_buffer, dw_config->query_buffer_len);
  
    //Write into struct member
    //
    void(*query_member_ptr)() = query_table[dw_config->query_index]; 
    query_member_ptr(dw_config);
    return EXIT_SUCCESS;
  } 
  return ERROR;
}



int dw_Data(void* host_object, int(*host_usart)(), void* ext_dev_object, uint32_t read_write){

  MPI_ext_dev* dw_slave_ptr = (MPI_ext_dev*)ext_dev_object;
  //DW_config* dw_config = (DW_config*)dw_slave_ptr->MPI_conf[DW_CONFIG_INDEX];  
  DW_nodelist* dw_nodelist = (DW_nodelist*)dw_slave_ptr->MPI_data[NODE_LIST_INDEX];

  if(read_write == READ){

    dw_nodelist->reg_id_index = REG_ID_RX_BUFFER;
    dw_nodelist->sub_addr_index = 0;
    dw_nodelist->ext_addr_index = 0;

    // read first two octets of frame
    dw_Rx(host_object, host_usart, dw_nodelist, dw_nodelist->frame_in, FC_COMMON_LEN);

    // decode whole frame and handle
    //
    uint32_t(*decode_frame_ptr)() = dw_decode_build_table[read_write];
    int index = decode_frame_ptr(host_object, host_usart, ext_dev_object);

    //build the next frame to be sent in accordance with frame just decoded
    //
    dw_nodelist->node_index = dw_buildMessageOut(ext_dev_object, WRITE, index);

    return (dw_nodelist->node_index == ERROR ? ERROR: EXIT_SUCCESS);

  } else if (read_write == WRITE){
   
     // MAJOR PROBLEM: WE DON'T HAVE THE INDEX OF THE DATA NODE FROM NODELIST IF WE ARE 
     // MAKING AN UNSOLICITED WRITE OPERATION
   

      //if tx call to dw_buildMessage()
      //
      uint32_t(*build_msg_ptr)() = dw_decode_build_table[read_write];
      int index = build_msg_ptr(ext_dev_object, WRITE, dw_nodelist->node_index);

      dw_Tx(host_object, host_usart, dw_nodelist, dw_nodelist->frame_out, dw_nodelist->frame_out_len);
   
      //If this was a poll message, get the tx timstamp straight after transmission
      if(dw_nodelist->list[index].handler_index == POLL_INDEX){
        DW_data dw_data = dw_nodelist->list[index];
        dw_nodelist->reg_id_index = REG_ID_TX_MARKER;      
        void(*poll_tx_ts_fn)() = dw_ts_handler_table[POLL_INDEX];
        poll_tx_ts_fn(host_object, host_usart, dw_nodelist, dw_data);
      }
  }
  return EXIT_SUCCESS;
}

int dw_Reset(void* host_object, int(*host_usart)(), void* ext_dev_object){
 
  MPI_ext_dev* dw_slave_ptr = (MPI_ext_dev*)ext_dev_object;
  DW_config* dw_config = (DW_config*)dw_slave_ptr->MPI_conf[DW_CONFIG_INDEX];  
  DW_nodelist* dw_nodelist = (DW_nodelist*)dw_slave_ptr->MPI_data[NODE_LIST_INDEX];

  
   // set dw_config->query_index member that triggers this function
 





  dw_nodelist->reg_id_index = query_table_reg_id_table[dw_config->query_index];
  
  //call to adjust struct member value
  //
  void(*config_member_ptr)() = config_table[dw_config->config_index]; 
  config_member_ptr(dw_config);
 
  //if tx call to dw_buildMessage()
  //if rx call to dw_decodeMessage()
  //
  uint32_t(*build_msg_ptr)() = dw_decode_build_table[WRITE];
  int ret = build_msg_ptr(ext_dev_object, WRITE, DW_CONFIG);

  if(ret == EXIT_SUCCESS){
    return dw_Tx(host_object, host_usart, dw_nodelist, dw_nodelist->frame_out, dw_nodelist->frame_out_len);
  }
  return ERROR;
}

int dw_Off(void* host_object, int(*host_usart)(), void* ext_dev_object){
 
  MPI_ext_dev* dw_slave_ptr = (MPI_ext_dev*)ext_dev_object;
  DW_config* dw_config = (DW_config*)dw_slave_ptr->MPI_conf[DW_CONFIG_INDEX];  
  DW_nodelist* dw_nodelist = (DW_nodelist*)dw_slave_ptr->MPI_data[NODE_LIST_INDEX];

  
   // set dw_config->query_index member that triggers this function
   






  dw_nodelist->reg_id_index = query_table_reg_id_table[dw_config->query_index];
  
  //call to adjust struct member value
  //
  void(*config_member_ptr)() = config_table[dw_config->config_index]; 
  config_member_ptr(dw_config);
 
  //if tx call to dw_buildMessage()
  //if rx call to dw_decodeMessage()
  //
  uint32_t(*build_msg_ptr)() = dw_decode_build_table[WRITE];
  int ret = build_msg_ptr(ext_dev_object, WRITE, DW_CONFIG);

  //callback to host usart
  //
  if(ret == EXIT_SUCCESS){
    return dw_Tx(host_object, host_usart, dw_nodelist, dw_nodelist->frame_out, dw_nodelist->frame_out_len);
  }
  return ERROR;
}

int dw_Sleep(void* host_object, int(*host_usart)(), void* ext_dev_object){
 
  MPI_ext_dev* dw_slave_ptr = (MPI_ext_dev*)ext_dev_object;
  DW_config* dw_config = (DW_config*)dw_slave_ptr->MPI_conf[DW_CONFIG_INDEX];  
  DW_nodelist* dw_nodelist = (DW_nodelist*)dw_slave_ptr->MPI_data[NODE_LIST_INDEX];

  
   // set dw_config->query_index member that triggers this function
 






  dw_nodelist->reg_id_index = query_table_reg_id_table[dw_config->query_index];
  
  //call to adjust struct member value
  //
  void(*config_member_ptr)() = config_table[dw_config->config_index]; 
  config_member_ptr(dw_config);
 
  //if tx call to dw_buildMessage()
  //if rx call to dw_decodeMessage()
  //
  uint32_t(*build_msg_ptr)() = dw_decode_build_table[WRITE];
  int ret = build_msg_ptr(ext_dev_object, WRITE, DW_CONFIG);

  //callback to host usart
  //
  if(ret == EXIT_SUCCESS){
    return dw_Tx(host_object, host_usart, dw_nodelist, dw_nodelist->frame_out, dw_nodelist->frame_out_len);
  }
  return ERROR;
}

int dw_Wakeup(void* host_object, int(*host_usart)(), void* ext_dev_object){
 
  MPI_ext_dev* dw_slave_ptr = (MPI_ext_dev*)ext_dev_object;
  DW_config* dw_config = (DW_config*)dw_slave_ptr->MPI_conf[DW_CONFIG_INDEX];  
  DW_nodelist* dw_nodelist = (DW_nodelist*)dw_slave_ptr->MPI_data[NODE_LIST_INDEX];

  
   // set dw_config->query_index member that triggers this function
   






  dw_nodelist->reg_id_index = query_table_reg_id_table[dw_config->query_index];
  
  //call to adjust struct member value
  //
  void(*config_member_ptr)() = config_table[dw_config->config_index]; 
  config_member_ptr(dw_config);
 
  //if tx call to dw_buildMessage()
  //if rx call to dw_decodeMessage()
  //
  uint32_t(*build_msg_ptr)() = dw_decode_build_table[WRITE];
  int ret = build_msg_ptr(ext_dev_object, WRITE, DW_CONFIG);

  //callback to host usart
  //
  if(ret == EXIT_SUCCESS){
    return dw_Tx(host_object, host_usart, dw_nodelist, dw_nodelist->frame_out, dw_nodelist->frame_out_len);
  }
  return ERROR;
}

int dw_ModeLevel(void* host_object, int(*host_usart)(), void* ext_dev_object){
 
  MPI_ext_dev* dw_slave_ptr = (MPI_ext_dev*)ext_dev_object;
  DW_config* dw_config = (DW_config*)dw_slave_ptr->MPI_conf[DW_CONFIG_INDEX];  
  DW_nodelist* dw_nodelist = (DW_nodelist*)dw_slave_ptr->MPI_data[NODE_LIST_INDEX];

  
   // set dw_config->query_index member that triggers this function
 






  dw_nodelist->reg_id_index = query_table_reg_id_table[dw_config->query_index];
  
  //call to adjust struct member value
  //
  void(*config_member_ptr)() = config_table[dw_config->config_index]; 
  config_member_ptr(dw_config);
 
  //if tx call to dw_buildMessage()
  //if rx call to dw_decodeMessage()
  //
  uint32_t(*build_msg_ptr)() = dw_decode_build_table[WRITE];
  int ret = build_msg_ptr(ext_dev_object, WRITE, DW_CONFIG);

  //callback to host usart
  //
  if(ret == EXIT_SUCCESS){
    return dw_Tx(host_object, host_usart, dw_nodelist, dw_nodelist->frame_out, dw_nodelist->frame_out_len);
  }
  return ERROR;
}

