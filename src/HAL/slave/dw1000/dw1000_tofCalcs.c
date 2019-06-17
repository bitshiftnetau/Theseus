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


void dw_tx_poll_ts(void* host_object, int(*host_usart)(), DW_nodelist* dw_nodelist, DW_data* dw_data){

  // get the transmission timestamp after sending Poll frame (from where I don't know)

  dw_nodelist->reg_id_index = REG_ID_TX_MARKER;
  dw_nodelist->sub_addr_index = 0;

  uint32_t tx_marker[TX_MARKER_TOTAL_LEN];
  dw_Rx(host_object, host_usart, dw_nodelist, tx_marker, TX_MARKER_TOTAL_LEN - 1);
  
  //dw_data->tof.poll.tx_marker = tx_marker[0];
  for(int i = T_REPLY_LEN; i < 0; i--){
    dw_data->tof.poll.tx_marker = (dw_data->tof.poll.tx_marker << SINGLE_BYTE_SHIFT)  | (SINGLE_BYTE & tx_marker[i]);
  }

}


void dw_tx_resp_ts(DW_data* dw_data, DW_config* dw_config){

  uint32_t poll_rx_ts = dw_data->tof.poll.rx_marker;
  //uint32_t resp_tx_time = (poll_rx_ts + (T_REPLY_1_DELAY_UUS * UUS_TO_DW_TIME));
  uint64_t resp_tx_time = (poll_rx_ts + (T_REPLY_1_DELAY_UUS * UUS_TO_DW_TIME)) >> 8;

  uint16_t rf_tx_delay = (SINGLE_BYTE & dw_config->rf_tx_delay[0]);
  rf_tx_delay |= (SINGLE_BYTE & (dw_config->rf_tx_delay[1] << SINGLE_BYTE_SHIFT));

  dw_data->tof.resp.tx_marker = ((resp_tx_time & 0xFFFFFFFEUL) << 8) + rf_tx_delay; // TX_ANT_DLY; (this value could also be the ant_delay member so check on that)
  dw_data->tof.treplyx._1 = dw_data->tof.resp.tx_marker - poll_rx_ts; 
}


void dw_tx_final_ts(DW_data* dw_data, DW_config* dw_config){

  uint32_t poll_tx_ts = dw_data->tof.poll.tx_marker; 
  uint32_t resp_rx_ts = dw_data->tof.resp.rx_marker;
  //uint32_t final_tx_time = (resp_rx_ts + (T_REPLY_2_DELAY_UUS * UUS_TO_DW_TIME));
  uint64_t final_tx_time = (resp_rx_ts + (T_REPLY_2_DELAY_UUS * UUS_TO_DW_TIME)) >> 8;
 
  uint16_t rf_tx_delay = (SINGLE_BYTE & dw_config->rf_tx_delay[0]);
  rf_tx_delay |= (SINGLE_BYTE & (dw_config->rf_tx_delay[1] << SINGLE_BYTE_SHIFT));
 
  dw_data->tof.final.tx_marker = ((final_tx_time & 0xFFFFFFFEUL) << 8) + rf_tx_delay;
  dw_data->tof.treplyx._2 = dw_data->tof.final.tx_marker - resp_rx_ts;
  dw_data->tof.troundx._1 = resp_rx_ts - poll_tx_ts; 
}


void dw_tof_dist(DW_data* dw_data, DW_config* dw_config){

  dw_config = NULL;

  // printf("Reception # : %d\r\n",rx_count);

  uint32_t resp_tx_ts = dw_data->tof.resp.tx_marker;
  uint32_t final_rx_ts = dw_data->tof.resp.rx_marker;

  dw_data->tof.troundx._2 = final_rx_ts - resp_tx_ts;

  uint32_t treply_1 = dw_data->tof.treplyx._1; 
  uint32_t treply_2 = dw_data->tof.treplyx._2;
  uint32_t tround_1 = dw_data->tof.troundx._1;
  uint32_t tround_2 = dw_data->tof.troundx._2;

  double tof = (((tround_1 * tround_2) - (treply_1 * treply_2)) / (tround_1 + tround_2 + treply_1 + treply_2));

  dw_data->tof.final_distance = tof * SPEED_OF_LIGHT;

  //printf("Distance : %f\r\n",distance);
}


/*******************************************************
 *          FINAL DISTACE DATA STRUCTURE MGMT
 ******************************************************/

uint32_t dw_deviceStore(DW_nodelist* dw_nodelist, uint32_t node_index){
  
 DW_data dw_data = dw_nodelist->list[node_index]; 
 DW_nodelist* node_list = dw_nodelist;
 DW_network_dev* dev_list = &dw_nodelist->devices[0];
  
 DW_network_dev tmp_1;
 DW_network_dev tmp_2;
 
 float new_distance = dw_data.tof.final_distance;
 float active_distance = dev_list[0].distance;
 int i = 0; 

 while(active_distance <= new_distance){
   i++;
   active_distance = dev_list[i].distance;
 }
 
 memcpy(&tmp_1, &dev_list[i], sizeof(DW_network_dev));

 for(int j = 0; j < BLINK_SHORT_ADDR_LEN; j++){
  node_list->devices[i].tag_id[j] = dw_data.tag_id[j];
 }
 node_list->devices[i].distance = new_distance;

 if(i+1 != ACTIVE_DEVICES_LEN){
  active_distance = dev_list[i+1].distance;
 } else {
  return EXIT_SUCCESS;
 }

 while(active_distance >= tmp_1.distance){
   memcpy(&tmp_2, &dev_list[i], sizeof(DW_network_dev));
   memcpy(&dev_list[i], &tmp_1, sizeof(DW_network_dev));
   memcpy(&tmp_1, &tmp_2, sizeof(DW_network_dev));
   i++;
   if((i) != ACTIVE_DEVICES_LEN){
    active_distance = dev_list[i].distance;
   } else {
     return EXIT_SUCCESS;
   }
 }
 
 return ERROR;
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

