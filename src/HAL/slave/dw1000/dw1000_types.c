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
#include "dw1000_types.h"
#include "dw1000_regs.h"


#include "dw1000_nodeMgmt.h"
#include "dw1000_buildMAC.h"
#include "dw1000_decodeMAC.h"
#include "dw1000_commRxTx.h"
#include "dw1000_tofCalcs.h"

uint8_t dw_reg_id_table[REG_IDS_LEN] = { 
  
  0x01, //eui
  0x03, //pan addr
  0x04, //sys cfg
  0x08, //tx frame ctrl
  0x0A, //delayed send or receive time
  0x0D, //sys ctrl reg
  0x0F, //sys event status
  0x18, //ant delay
  0x1A, //ack resp time
  0x1D, //pulsed preamble rx config
  0x1E, //tx power ctrl
  0x1F, //channel ctrl
  0x00, //device id 
  0x0C, //rx frame wait timeout
  0x12, //rx frame quality info
  0x13, //rx time tracking interval
  0x19, //sys state
  
  0x06, //sys time
  0x09, //tx buffer,
  0x10, //rx frame info
  0x11, //rx data
  0x14, //rx time tracking offset
  0x15, //rx msg time of arrival
  0x17, //tx message time of sending
  
  0x21, //user-defined SFD
  0x23, //auto gain ctrl config
  0x24, //ext sync
  0x25, //accum read acces
  0x26, //gpio ctrl 
  0x27, //digital rx config
  0x28, //analog rf config
  0x2A, //tx calibration
  0x2B, //freq synth ctrl 
  0x2C, //AON reg
  0x2D, //OTP
  0x2E, //LDE ctrl
  0x2F, //digital diagnostics
  0x36, //power mgmt system ctrl 
};



uint32_t(* dw_decode_build_table[3])() = {
  dw_decodeFrameIn,
  dw_buildMessageOut,
  NULL
};


uint8_t dw_frame_ctrl_table[3][2] = {
  {FC_BLINK},   
  {FC_RANGE_0, FC_RANGE_1},             
  {FC_POLL_RESP_FINAL_0, FC_POLL_RESP_FINAL_1}
}; 

const uint32_t dw_fn_code_table[DECODE_TABLE_LEN] = {
  0, //blink message does not transmit payload
  FN_CODE_RANGE,
  FN_CODE_POLL,
  FN_CODE_RESP,
  FN_CODE_FINAL 
};


//#define EUI_64_LEN                       
//#define PAN_ID_LEN                 

uint32_t config_table_len[CONFIG_STRUCT_MEMBERS] = {
  EUI_64_LEN,                   // config_unique_id
  PAN_ID_LEN,                   // config_pan_id
  SYS_CONFIG_LEN,               // config_sys_conf
  TX_FRAME_CTRL_LEN,            // config_tx_frame_ctrl
  TX_FRAME_CTRL_SUB_REG_4_LEN,  // config_tx_frame_ctrl_sub_reg_4
  RF_TX_DELAY_LEN,              // rf_tx_delay
  SYS_CTRL_REG_LEN,             // sys_ctrl_reg
  SYS_EVENT_MASK_LEN,           // sys_event_mask
  TX_ANT_DELAY_LEN,             // tx_ant_delay
  ACK_RESP_TIME_LEN,            // ack_resp_time
  PREAMBLE_RX_CONFIG_LEN,       // preamble_rx_config
  TX_POWER_CTRL_LEN,            // tx_power_ctrl
  CHAN_CTRL_LEN                 // chan_ctrl
};

void config_unique_id(DW_config* dw_config, DW_reg_id_enum reg_id_table){
  
  //dw_config->reg_id_addr =   

}
void config_pan_id(DW_config* dw_config, DW_reg_id_enum reg_id_table){

}
void config_sys_conf(DW_config* dw_config, DW_reg_id_enum reg_id_table){

}
void config_tx_frame_ctrl(DW_config* dw_config, DW_reg_id_enum reg_id_table){

}
void config_rf_tx_delay(DW_config* dw_config, DW_reg_id_enum reg_id_table){
  
}
void config_sys_ctrl_reg(DW_config* dw_config, DW_reg_id_enum reg_id_table){

}
void config_sys_event_status(DW_config* dw_config, DW_reg_id_enum reg_id_table){

  //write zero so we have no effect on this register

}
void config_tx_ant_delay(DW_config* dw_config, DW_reg_id_enum reg_id_table){
  
}
void config_ack_resp_time(DW_config* dw_config, DW_reg_id_enum reg_id_table){

}
void config_preamble_rx_config(DW_config* dw_config, DW_reg_id_enum reg_id_table){

}
void config_tx_power_ctrl(DW_config* dw_config, DW_reg_id_enum reg_id_table){

}
void config_chan_ctrl(DW_config* dw_config, DW_reg_id_enum reg_id_table){

}


void (*config_table[CONFIG_STRUCT_MEMBERS +1])() = {
  &config_unique_id,
  &config_pan_id,
  &config_sys_conf,
  &config_tx_frame_ctrl,
  &config_rf_tx_delay,
  &config_sys_ctrl_reg,
  &config_sys_event_status,
  &config_tx_ant_delay,
  &config_ack_resp_time,
  &config_preamble_rx_config,
  &config_tx_power_ctrl,
  &config_chan_ctrl,
};

/***************************************************************************************/





uint32_t query_table_len[QUERY_STRUCT_MEMBERS] = {
  DEVICE_ID_LEN,
  SYSTEM_TIME_LEN,
  RX_FRAME_TIMEOUT_LEN,
  RX_FRAME_QUAL_LEN,
  RX_TIME_INTERVAL_LEN,
  SYS_STATE_INFO_LEN
};


void query_dev_id(DW_config* dw_config, DW_reg_id_enum reg_id_table){

}
void query_sys_time(DW_config* dw_config, DW_reg_id_enum reg_id_table){

}
void query_rx_frame_timeout(DW_config* dw_config, DW_reg_id_enum reg_id_table){

}
void query_rx_frame_qual(DW_config* dw_config, DW_reg_id_enum reg_id_table){

}
void query_rx_time_interval(DW_config* dw_config, DW_reg_id_enum reg_id_table){

}
void query_sys_state_info(DW_config* dw_config, DW_reg_id_enum reg_id_table){

}
void query_unique_id(DW_config* dw_config, DW_reg_id_enum reg_id_table){
  
  //dw_config->reg_id_addr =   

}
void query_pan_id(DW_config* dw_config, DW_reg_id_enum reg_id_table){

}
void query_sys_conf(DW_config* dw_config, DW_reg_id_enum reg_id_table){

}
void query_tx_frame_ctrl(DW_config* dw_config, DW_reg_id_enum reg_id_table){

}
void query_rf_tx_delay(DW_config* dw_config, DW_reg_id_enum reg_id_table){
  
}
void query_sys_ctrl_reg(DW_config* dw_config, DW_reg_id_enum reg_id_table){

}
void query_sys_event_status(DW_config* dw_config, DW_reg_id_enum reg_id_table){

  //write zero so we have no effect on this register

}
void query_tx_ant_delay(DW_config* dw_config, DW_reg_id_enum reg_id_table){
  
}
void query_ack_resp_time(DW_config* dw_config, DW_reg_id_enum reg_id_table){

}
void query_preamble_rx_config(DW_config* dw_config, DW_reg_id_enum reg_id_table){

}
void query_tx_power_ctrl(DW_config* dw_config, DW_reg_id_enum reg_id_table){

}
void query_chan_ctrl(DW_config* dw_config, DW_reg_id_enum reg_id_table){

}

void (*query_table[QUERY_STRUCT_MEMBERS +1])() = {
  &query_unique_id,
  &query_pan_id,
  &query_sys_conf,
  &query_tx_frame_ctrl,
  &query_rf_tx_delay,
  &query_sys_ctrl_reg,
  &query_sys_event_status,
  &query_tx_ant_delay,
  &query_ack_resp_time,
  &query_preamble_rx_config,
  &query_tx_power_ctrl,
  &query_chan_ctrl,
  
  &query_dev_id,
  &query_sys_time,
  &query_rx_frame_timeout,
  &query_rx_frame_qual,
  &query_rx_time_interval,
  &query_sys_state_info,
};


