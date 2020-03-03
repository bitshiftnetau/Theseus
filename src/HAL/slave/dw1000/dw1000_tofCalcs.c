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
 

#include <stdint.h>
#include <stddef.h>

#include "mpi_port.h"
#include "dw1000_tofCalcs.h"
#include "dw1000_types.h"
#include "dw1000_commRxTx.h"

/*
 *  RANGING AND TIMESTAMP FUNCTIONS
 */

    /*  
    T_REPLY_1_DELAY_UUS is a critical value for porting to different processors. 
    For slower platforms where the SPI is at a slower speed or the processor is operating 
    at a lower frequency (Comparing to STM32F, SPI of 18MHz and Processor internal 72MHz)
    this value needs to be increased. Knowing the exact time when the responder is going 
    to send its response is vital for time of flight calculation. The specification of 
    the time of respnse must allow the processor enough time to do its calculations and 
    put the packet in the Tx buffer. So more time required for a slower system(processor).
    */

  /*
   * REMEMBER TO INITIALIZE THE DELAY REGISTER ON THE DW1000 WITH THIS VALUE 
   */
#define T_REPLY_1_DELAY_UUS   1100  //poll Rx - resp Tx delay (microseconds)
#define T_REPLY_2_DELAY_UUS   1100  //resp Rx - final Tx delay (microseconds)

  /* UWB microsecond (uus) to device time unit (dtu, around 15.65 ps) conversion factor.
     1 uus = 512 / 499.2 µs and 1 µs = 499.2 * 128 dtu. */
#define UUS_TO_DW_TIME 65536

  /* Speed of light in air, in metres per second. */
#define SPEED_OF_LIGHT 299702547
void dw_tx_poll_ts(void* host_object, int(*host_usart)(), void* ext_dev_object, uint32_t nodelist_index);
void dw_tx_resp_ts(void* host_object, int(*host_usart)(), void* ext_dev_object, uint32_t nodelist_index);
void dw_tx_final_ts(void* host_object, int(*host_usart)(), void* ext_dev_object, uint32_t nodelist_index);
void dw_tof_dist(void* host_object, int(*host_usart)(), void* ext_dev_object, uint32_t nodelist_index);
uint32_t dw_deviceStore(DW_nodelist* dw_nodelist, uint32_t node_index);


void dw_tx_poll_ts(void* host_object, int(*host_usart)(), void* ext_dev_object, uint32_t nodelist_index){

  uint32_t node_index = nodelist_index;
  
  MPI_ext_dev* dw_slave_ptr = (MPI_ext_dev*)ext_dev_object;

  DW_config* dw_config = (DW_config*)dw_slave_ptr->MPI_conf[DW_CONFIG_INDEX]; 
  DW_nodelist* dw_nodelist = (DW_nodelist*)dw_slave_ptr->MPI_data[NODE_LIST_INDEX];
  DW_data* dw_data = &dw_nodelist->list[node_index]; 

  // get the transmission timestamp after sending Poll frame (from where I don't know)
  DW_reg_id_enum enum_member = tx_send_time;
  dw_config->reg_id_index = enum_member;
  dw_config->sub_addr_index = 0;
  
  uint8_t tx_marker[TX_MARKER_TOTAL_LEN];
  dw_Rx(host_object, host_usart, dw_slave_ptr, tx_marker, TX_MARKER_TOTAL_LEN - 1);
  
  //dw_data->tof.poll.tx_marker = tx_marker[0];
  for(int i = T_REPLY_LEN; i < 0; i--){
    dw_data->tof.poll.tx_marker = (dw_data->tof.poll.tx_marker << SINGLE_BYTE_SHIFT) | tx_marker[i];
  }

}


void dw_tx_resp_ts(void* host_object, int(*host_usart)(), void* ext_dev_object, uint32_t nodelist_index){

  uint32_t node_index = nodelist_index;

  MPI_ext_dev* dw_slave_ptr = (MPI_ext_dev*)ext_dev_object;

  DW_config* dw_config = (DW_config*)dw_slave_ptr->MPI_conf[DW_CONFIG_INDEX]; 
  DW_nodelist* dw_nodelist = (DW_nodelist*)dw_slave_ptr->MPI_data[NODE_LIST_INDEX];
  DW_data* dw_data = &dw_nodelist->list[node_index]; 

  uint32_t poll_rx_ts = dw_data->tof.poll.rx_marker;
  //uint32_t resp_tx_time = (poll_rx_ts + (T_REPLY_1_DELAY_UUS * UUS_TO_DW_TIME));
  uint64_t resp_tx_delay = (poll_rx_ts + (T_REPLY_1_DELAY_UUS * UUS_TO_DW_TIME)) >> 8;

  uint16_t tx_antenna_delay = dw_config->tx_ant_delay[1];
  tx_antenna_delay = (tx_antenna_delay << SINGLE_BYTE_SHIFT) | dw_config->tx_ant_delay[0];
  
  //store resp_tx_time in the config struct and then write to device
  dw_config->rf_tx_delay[0] = (resp_tx_delay & SINGLE_BYTE);
  for(int i = 1; i < 8; i++){
    dw_config->rf_tx_delay[i] |= (resp_tx_delay >> SINGLE_BYTE_SHIFT) & SINGLE_BYTE;
  }


  //Build the message header and transmit configuration to device 
  DW_reg_id_enum enum_member = tx_ant_delay;
  dw_config->reg_id_index = enum_member;
  dw_config->sub_addr_index = 0;

  //put the data in the config buffer
  void(*config_member_ptr)() = config_table[(int)enum_member]; 
  config_member_ptr(dw_config, enum_member);
  
  //build the spi transaction header and frame
  volatile uint32_t(* build_msg_ptr)() = dw_decode_build_table[WRITE];
  int ret = build_msg_ptr(host_object, host_usart, ext_dev_object, WRITE, DW_CONFIG);
  
  //callback to host usart to send config
  if(ret == EXIT_SUCCESS){
    dw_Tx(host_object, host_usart, dw_slave_ptr, dw_nodelist->frame_out, dw_nodelist->frame_out_len);
  }
  
  dw_data->tof.resp.tx_marker = (resp_tx_delay & 0xFFFFFFFEUL) + tx_ant_delay; // TX_ANT_DLY; (this value could also be the ant_delay member so check on that)
  dw_data->tof.treplyx._1 = dw_data->tof.resp.tx_marker - poll_rx_ts; 
}


void dw_tx_final_ts(void* host_object, int(*host_usart)(), void* ext_dev_object, uint32_t nodelist_index){

  uint32_t node_index = nodelist_index;

  MPI_ext_dev* dw_slave_ptr = (MPI_ext_dev*)ext_dev_object;

  DW_config* dw_config = (DW_config*)dw_slave_ptr->MPI_conf[DW_CONFIG_INDEX]; 
  DW_nodelist* dw_nodelist = (DW_nodelist*)dw_slave_ptr->MPI_data[NODE_LIST_INDEX];
  DW_data* dw_data = &dw_nodelist->list[node_index]; 


  uint32_t poll_tx_ts = dw_data->tof.poll.tx_marker; 
  uint32_t resp_rx_ts = dw_data->tof.resp.rx_marker;
  //uint32_t final_tx_time = (resp_rx_ts + (T_REPLY_2_DELAY_UUS * UUS_TO_DW_TIME));
  uint64_t final_tx_delay = (resp_rx_ts + (T_REPLY_2_DELAY_UUS * UUS_TO_DW_TIME)) >> 8;

  uint16_t tx_antenna_delay = dw_config->tx_ant_delay[1];
  tx_antenna_delay = (tx_antenna_delay << SINGLE_BYTE_SHIFT) | dw_config->tx_ant_delay[0];

  //store resp_tx_time in the config struct and then write to device
  dw_config->rf_tx_delay[0] = (final_tx_delay & SINGLE_BYTE);
  for(int i = 1; i < 8; i++){
    dw_config->rf_tx_delay[i] |= (final_tx_delay >> SINGLE_BYTE_SHIFT) & SINGLE_BYTE;
  }

  //Build the message header and transmit configuration to device 
  DW_reg_id_enum enum_member = tx_ant_delay;
  dw_config->reg_id_index = enum_member;
  dw_config->sub_addr_index = 0;

  //put the data in the config buffer
  void(*config_member_ptr)() = config_table[(int)enum_member]; 
  config_member_ptr(dw_config, enum_member);
  
  //build the spi transaction header and frame
  volatile uint32_t(* build_msg_ptr)() = dw_decode_build_table[WRITE];
  int ret = build_msg_ptr(host_object, host_usart, ext_dev_object, WRITE, DW_CONFIG);
  
  //callback to host usart and send frame
  //
  if(ret == EXIT_SUCCESS){
    dw_Tx(host_object, host_usart, dw_slave_ptr, dw_nodelist->frame_out, dw_nodelist->frame_out_len);
  }

  dw_data->tof.final.tx_marker = (final_tx_delay & 0xFFFFFFFEUL) + tx_ant_delay;
  dw_data->tof.treplyx._2 = dw_data->tof.final.tx_marker - resp_rx_ts;
  dw_data->tof.troundx._1 = resp_rx_ts - poll_tx_ts; 
}


void dw_tof_dist(void* host_object, int(*host_usart)(), void* ext_dev_object, uint32_t nodelist_index){

  uint32_t node_index = nodelist_index;

  MPI_ext_dev* dw_slave_ptr = (MPI_ext_dev*)ext_dev_object;

  DW_nodelist* dw_nodelist = (DW_nodelist*)dw_slave_ptr->MPI_data[NODE_LIST_INDEX];
  DW_data* dw_data = &dw_nodelist->list[node_index]; 

  // printf("Reception # : %d\r\n",rx_count);

  uint32_t resp_tx_ts = dw_data->tof.resp.tx_marker;
  uint32_t final_rx_ts = dw_data->tof.resp.rx_marker;

  dw_data->tof.troundx._2 = final_rx_ts - resp_tx_ts;

  uint32_t treply_1 = dw_data->tof.treplyx._1; 
  uint32_t treply_2 = dw_data->tof.treplyx._2;
  uint32_t tround_1 = dw_data->tof.troundx._1;
  uint32_t tround_2 = dw_data->tof.troundx._2;

  double tof = (((tround_1 * tround_2) - (treply_1 * treply_2)) / (tround_1 + tround_2 + treply_1 + treply_2));

  dw_data->tof.final_distance = (tof * SPEED_OF_LIGHT);

  //printf("Distance : %f\r\n",distance);
}


/*******************************************************
 *          FINAL DISTACE DATA STRUCTURE MGMT
 ******************************************************/

uint32_t dw_deviceStore(DW_nodelist* dw_nodelist, uint32_t nodelist_index){
  
  if(nodelist_index > NODELIST_LEN){
    return ERROR;
  }

 uint32_t node_index = nodelist_index;

//UNCOMMENT ALL CODE FOR STORING AND AGGREGATING DEVICES IN NEW DEVICE LIST

// DW_data dw_data;
// memcpy(&dw_data, &dw_nodelist->list[node_index], sizeof(DW_data))

 DW_nodelist* node_list = dw_nodelist;
// DW_network_dev* dev_list = &dw_nodelist->devices[0];
  
// DW_network_dev tmp_1;
// DW_network_dev tmp_2;
 
//double new_distance = dw_data.tof.final_distance;
// float active_distance = dev_list[0].distance;

dw_nodelist->list[node_index].distance = dw_nodelist->list[node_index].tof.final_distance;

/*
 int i = 0; 
 
 while(active_distance <= new_distance){
   i++;
   active_distance = dev_list[i].distance;
 }
 
 //memcpy(&tmp_1, &dev_list[i], sizeof(DW_network_dev));
 tmp_1 = dev_list[i];
*/

/*
 for(int j = 0; j < BLINK_SHORT_ADDR_LEN; j++){
  node_list->devices[i].tag_id[j] = dw_data.tag_id[j];
 }
 node_list->devices[i].distance = new_distance;
*/

/*
 if(i+1 != ACTIVE_DEVICES_LEN){
  active_distance = dev_list[i+1].distance;
 } else {
  return EXIT_SUCCESS;
 }
*/

/*
 while(active_distance >= tmp_1.distance){
   //memcpy(&tmp_2, &dev_list[i], sizeof(DW_network_dev));
   //memcpy(&dev_list[i], &tmp_1, sizeof(DW_network_dev));
   //memcpy(&tmp_1, &tmp_2, sizeof(DW_network_dev));
   
   tmp_2 = dev_list[i];
   dev_list[i] = tmp_1;
   tmp_1 = tmp_2;
   
   i++;
   if((i) != ACTIVE_DEVICES_LEN){
    active_distance = dev_list[i].distance;
   } else {
     return EXIT_SUCCESS;
   }
 }
 
 return ERROR;
 */
 return EXIT_SUCCESS;
}

void (* dw_ts_handler_table[TS_HANDLER_TABLE_LEN])() = {
  NULL, // blink does not have a timestamp requirement
  NULL, // range_init does not have a timestamp requirement
  dw_tx_poll_ts,
  dw_tx_resp_ts,
  dw_tx_final_ts,
  dw_tof_dist,
  NULL
};

