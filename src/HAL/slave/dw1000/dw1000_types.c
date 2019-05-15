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
 

#include <stdbool.h>
#include <stdint.h>

#include "mpi_port.h"
#include "dw1000_types.h"
#include "dw1000_param_types.h"
#include "dw1000_regs.h"
#include "dw1000_mutex.h"

#include "dw1000_nodeMgmt.h"
#include "dw1000_buildMAC.h"
#include "dw1000_decodeMAC.h"
#include "dw1000_commRxTx.h"
#include "dw1000_tofCalcs.h"



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


uint32_t(* dw_decode_build_table[READ_WRITE])() = {
  dw_decodeFrameIn,
  dw_buildMessageOut
};


#define DW_PART_ID_LEN        1
#define DW_LOT_ID_LEN         1
#define DW_PAN_ID_LEN         2
#define DW_CHAN_LEN           1
#define DW_OTP_REV_LEN        1
#define DW_TX_FCTRL_LEN       1
#define DW_TX_DELAY_LEN       2
#define DW_RX_DELAY_LEN       2
#define DW_ANT_DELAY_LEN      1
#define DW_XTRIM_LEN          1
#define DW_DBL_BUFF_LEN       1
#define DW_TX_POW_LEN         12
#define DW_SYS_CONFIG_LEN     1
#define DW_PRF_INDEX_LEN      1
#define DW_LDO_TUNE_LOW32_LEN 1
#define DW_LONG_FRAMES_LEN    1


uint32_t config_table_reg_id_table[CONFIG_STRUCT_MEMBERS] = {
  //regid for registers pertanent to config and query fns  
};


uint32_t config_table_len[CONFIG_STRUCT_MEMBERS] = {
  EUI_64_LEN,
  DW_PART_ID_LEN,
  DW_LOT_ID_LEN,
  DW_PAN_ID_LEN,
  DW_CHAN_LEN,
  DW_OTP_REV_LEN,
  DW_TX_FCTRL_LEN,
  DW_TX_DELAY_LEN,
  DW_RX_DELAY_LEN,
  DW_ANT_DELAY_LEN,
  DW_XTRIM_LEN,
  DW_DBL_BUFF_LEN,
  DW_SYS_CONFIG_LEN,
  DW_TX_POW_LEN,
  DW_SYS_CONFIG_LEN,     
  DW_PRF_INDEX_LEN,      
  DW_LDO_TUNE_LOW32_LEN, 
  DW_LONG_FRAMES_LEN    
};

void config_device_id(DW_config* dw_config){
  for(int i = 0; i < EUI_64_LEN; i++){ 
    dw_config->config_buffer[i] = dw_config->device_id[i];
  }
}
void config_part_id(DW_config* dw_config){
  dw_config->config_buffer[0] = dw_config->part_id;
}
void config_lot_id(DW_config* dw_config){
  dw_config->config_buffer[0] = dw_config->lot_id;
}
void config_pan_id(DW_config* dw_config){
  for(int i = 0; i < DW_PAN_ID_LEN; i++){
    dw_config->config_buffer[i] = dw_config->pan_id[2];
  }
}
void config_channel(DW_config* dw_config){
  //change this to accommodate for eCHAN enum 
  dw_config->config_buffer[0] = dw_config->channel;
}
void config_otp_rev(DW_config* dw_config){
  dw_config->config_buffer[0] = dw_config->otp_rev;
}
void config_tx_fctrl(DW_config* dw_config){
  dw_config->config_buffer[0] = dw_config->tx_fctrl;
}
void config_rf_tx_delay(DW_config* dw_config){
  for(int i = 0; i < DW_RX_DELAY_LEN; i++){
    dw_config->config_buffer[i] = dw_config->rf_tx_delay[i];
  }
}
void config_rf_rx_delay(DW_config* dw_config){
  for(int i = 0; i < DW_TX_DELAY_LEN; i++){
    dw_config->config_buffer[i] = dw_config->rf_rx_delay[i];
  }
}
void config_ant_delay(DW_config* dw_config){
  dw_config->config_buffer[0] = dw_config->ant_delay;
}
void config_xtrim(DW_config* dw_config){
  dw_config->config_buffer[0] = dw_config->xtrim;
}
void config_dbl_buff_on(DW_config* dw_config){
  dw_config->config_buffer[0] = dw_config->dbl_buff_on;
}
void config_sys_config_reg(DW_config* dw_config){
  dw_config->config_buffer[0] = dw_config->sys_config_reg;
}
void config_tx_pow_config(DW_config* dw_config){
  for(int i = 0; i < DW_TX_POW_LEN; i++){
    dw_config->config_buffer[i] = dw_config->tx_pow_config[i];
  }
}
void config_prf_index(DW_config* dw_config){
  dw_config->config_buffer[0] = dw_config->prf_index;
}
void config_ldo_tune_low32(DW_config* dw_config){
  dw_config->config_buffer[0] = dw_config->ldo_tune_low32;
}
void config_long_frames(DW_config* dw_config){
  dw_config->config_buffer[0] = dw_config->long_frames;
}

void (*config_table[CONFIG_STRUCT_MEMBERS +1])() = {
  config_device_id,
  config_part_id,
  config_lot_id,
  config_pan_id,
  config_channel,
  config_otp_rev,
  config_tx_fctrl,
  config_rf_tx_delay,
  config_rf_rx_delay,
  config_ant_delay,
  config_xtrim,
  config_dbl_buff_on,
  config_sys_config_reg,
  config_tx_pow_config,
  config_prf_index,
  config_ldo_tune_low32,
  config_long_frames
};

/*  Place this enum as a member of the dw_config struct.
 *  Use this enum to set a desired register, to be configured, prior calling the interface fn 
 *
 *  example:
 *
 *  - setting the pan_id 
 *
 *    dw_config->config_index = pan_id; // for the interface function
 *    
 *    //CONSIDER MOVING THE FOLLOWING INTO THE RELEVANT STRUCT MEMBER FUNCTIONS
 *    dw_nodelist->reg_id_index = REG_ID_PAN_ID; // for the message header builder
 *    dw_nodelist->sub_addr_index = SUB_ADDR_PAN_ID;
 *    dw_ConfigReg(host_object, WRITE, host_usart, ext_dev_object);
 *    
 */

uint32_t query_table_reg_id_table[QUERY_STRUCT_MEMBERS] = {
  //regid for registers pertanent to config and query fns  
};


uint32_t query_table_len[QUERY_STRUCT_MEMBERS] = {
  EUI_64_LEN,
  DW_PART_ID_LEN,
  DW_LOT_ID_LEN,
  DW_PAN_ID_LEN,
  DW_CHAN_LEN,
  DW_OTP_REV_LEN,
  DW_TX_FCTRL_LEN,
  DW_TX_DELAY_LEN,
  DW_RX_DELAY_LEN,
  DW_ANT_DELAY_LEN,
  DW_XTRIM_LEN,
  DW_DBL_BUFF_LEN,
  DW_SYS_CONFIG_LEN,
  DW_TX_POW_LEN,
  DW_SYS_CONFIG_LEN,     
  DW_PRF_INDEX_LEN,      
  DW_LDO_TUNE_LOW32_LEN, 
  DW_LONG_FRAMES_LEN    
};

void query_device_id(DW_config* dw_config){
  for(int i = 0; i < EUI_64_LEN; i++){ 
    dw_config->config_buffer[i] = dw_config->device_id[i];
  }
  dw_config->config_buffer_len = EUI_64_LEN; 
}
void query_part_id(DW_config* dw_config){
  dw_config->config_buffer[0] = dw_config->part_id;
}
void query_lot_id(DW_config* dw_config){
  dw_config->config_buffer[0] = dw_config->lot_id;
}
void query_pan_id(DW_config* dw_config){
  for(int i = 0; i < DW_PAN_ID_LEN; i++){
    dw_config->config_buffer[i] = dw_config->pan_id[2];
  }
}
void query_channel(DW_config* dw_config){
  dw_config->config_buffer[0] = dw_config->channel;
}
void query_otp_rev(DW_config* dw_config){

}
void query_tx_fctrl(DW_config* dw_config){

}
void query_rf_tx_delay(DW_config* dw_config){

}
void query_rf_rx_delay(DW_config* dw_config){

}
void query_ant_delay(DW_config* dw_config){

}
void query_xtrim(DW_config* dw_config){

}
void query_dbl_buff_on(DW_config* dw_config){

}
void query_sys_config_reg(DW_config* dw_config){

}
void query_tx_pow_config(DW_config* dw_config){

}
void query_prf_index(DW_config* dw_config){

}
void query_ldo_tune_low32(DW_config* dw_config){

}
void query_long_frames(DW_config* dw_config){

}

void (*query_table[QUERY_STRUCT_MEMBERS +1])() = {
  query_device_id,
  query_part_id,
  query_lot_id,
  query_pan_id,
  query_channel,
  query_otp_rev,
  query_tx_fctrl,
  query_rf_tx_delay,
  query_rf_rx_delay,
  query_ant_delay,
  query_xtrim,
  query_dbl_buff_on,
  query_sys_config_reg,
  query_tx_pow_config,
  query_prf_index,
  query_ldo_tune_low32,
  query_long_frames
};


