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
//#include <string.h>

#include "mpi_port.h"
#include "dw1000_types.h"
#include "dw1000_nodeMgmt.h"

/*******************************************************
 *          RANGING / NODE  DATA STRUCTURE MGMT
 ******************************************************/

/*
 * Sequence description:
 *
 * - application calls middleware -> middleware calls ext_dev HAL -> ext_dev HAL
 *   makes callback to host comm port -> host comm port gets data -> ext_dev HAL
 *   needs to determine the following:
 *
 * (Blink)
 *    - is this a known device?
 *    - if so, where are we in the ranging sequence?
 *    - if not, is this an authorized device?
 *    - if so, add the device
 *
 *  - Maybe we just need to check from each phase i.e. if it's a blink message 
 *    then do X. If it's a ranging init message do Y etc...
 *
 *    - Blink: (We never need to check if this is a known device, because blinks
 *    are ONLY for discovery, so we only need to do auth checks)
 *
 *      - is this an authorized device?
 *      - if so, add it to the list and send ranging init message.
 *
 *    - Ranging Init: 
 *
 *      - Is this device authed?
 *      - Check whether this is filtered automatically if we didn't send the 
 *      initial blink message, otherwise
 *      - add sequence to list of known device
 *
 *    - Poll:
 *
 *      - Is this a known device? If so, is this package authed?
 *      - if so, find it in the list, send response message, add a sequence to 
 *      the node
 *    
 *    - Response:
 *
 *      - Auth check
 *      - find in list, send final, add sequence to node
 *
 *    - Final:
 *
 *      - auth check
 *      - find in list, add sequence to node
 *      - calculate distance, return data, destroy ranging portion of node tree
 *
 */

uint32_t dw_nodeCreate(DW_nodelist* dw_nodelist, uint8_t* tag_id){

  /*
   * Upon successful acknowledgement of a blink, and subsequent reply with a 
   * ranging_init message, create a node for that device. 
   *
   * The same thing should be done for the receipt of a ranging_init message, if 
   * that device is not already in the list.  
   *
   */
  uint32_t i = 0;

  while((dw_nodelist->list[i].dev_status == DW_DEV_ACTIVE) && (++i < NODELIST_LEN)){
    ++i;
  }

  for(int j = 0; j < BLINK_SRC_ADDR_LEN; j++){
    dw_nodelist->list[i].tag_id[j] = tag_id[j];
  }
  dw_nodelist->list[i].dev_status = DW_DEV_ACTIVE;
 
  return i; 
}  


uint32_t dw_nodeSort(DW_nodelist* dw_nodelist, uint32_t node_index){

  uint32_t i = 0; //node_index;

  while((dw_nodelist->list[i].dev_status == DW_DEV_ACTIVE) && (i < NODELIST_LEN)){
    //memcpy(&dw_nodelist->list[i], &dw_nodelist->list[i+1], sizeof(DW_data));
    dw_nodelist->list[i] = dw_nodelist->list[i+1];
    ++i;
  }
  return i;
}

uint32_t dw_nodeDelete(DW_nodelist* dw_nodelist, uint8_t* tag_id){


  /*
   * When the device is shut down, send a msg to other nodes to delete this node 
   * from the list.
   *
   */

  uint32_t(* node_search)() = node_list_table[DW_NODE_SEARCH];
  uint32_t node_index = node_search(dw_nodelist, tag_id);
  
  if(node_index <= NODELIST_LEN_COUNT){
    dw_nodelist->list[node_index].dev_status = DW_DEV_DISABLED;
  
    uint32_t(* node_sort)() = node_list_table[DW_NODE_SORT];
    uint32_t index = node_sort(dw_nodelist, node_index);
    dw_nodelist->list[index].dev_status = DW_DEV_DISABLED;
    return EXIT_SUCCESS; 
  } else {
    dw_nodelist->list[node_index].dev_status = DW_DEV_DISABLED;
  }

  return EXIT_SUCCESS;
}



/********************************************************************************
 * REFACTOR:
 *
 * - This may or may not scale well
 * - At the very least it will affect the real time performance
 *   of the discovery and TWR procedure.
 *
 * IDEAS:
 *
 * - We could set the time for this task to be in accordance with
 *   a full array i.e. 2048 nodes. 
 * - Perhaps consider sending a non-standard frame with information
 *   regarding the node's index
 * - What about dividing the list into smaller lists based on device
 *   address?
 * - Or we could just scrap it altogether and design a different
 *   scheme for identifying known nodes, but how?
 *
 */
uint32_t dw_nodeSearch(DW_nodelist* dw_nodelist, uint8_t* tag_id){

  /*
   * search for a device in the node list
   */
  
  uint32_t node_index = 0; 

  while((dw_nodelist->list[node_index].dev_status == DW_DEV_ACTIVE) && (node_index < NODELIST_LEN)){
    for(int j = 0; j < EUI_64_LEN; j++){
      if((dw_nodelist->list[node_index].tag_id[j] & tag_id[j]) == 0){
        if(j == EUI_64_LEN){
          return node_index;
        }
        continue;
      } else {
        ++node_index;
        j = 0;
      }
    } //end for loop
  } //end while loop

  return ERROR; 
}


uint32_t(* node_list_table[DW_NODE_TABLE_LEN])() = {
  dw_nodeSearch,
  dw_nodeCreate,
  dw_nodeDelete,
  dw_nodeSort,
  NULL
};


