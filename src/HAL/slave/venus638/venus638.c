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

#include "venus638.h"
#include "mpi_port.h"

/**********************************************************
 *
 * TODO: Change all struct pointer parameters to uin32_t* 
 * array where you are calling the function from another layer
 *
 *********************************************************/


const uint8_t nmea_sent_len[ID_NMEA_LEN] = {
  52, 
  39, 
  50,
  34, 
  55, 
  22
};  

const uint8_t venus_nmea_id_table [ID_NMEA_LEN][ID_NMEA_LEN] = {

  {'G','P','G','G','A'},
  {'G','P','G','L','L'},
  {'G','P','G','S','A'},
  {'G','P','G','S','V'},
  {'G','P','R','M','C'},
  {'G','P','V','T','G'}

};
int venus638_Tx(void* host_object, int (*host_usart)(), void* ext_dev_object);
int venus638_Rx(void* host_object, int (*host_usart)(), void* ext_dev_object);

int(*const venus638_rx_tx_table[VENUS_READ_WRITE+1])() = {
  venus638_Rx,
  venus638_Tx,
  NULL
};

void venus_nullMessageArray();
int venus_buildPlLen(VENUS_message_io* venus_message);
int venus_makeChecksum(VENUS_message_io* venus_message);
int venus_decodeNmeaId(VENUS_message_io* venus_message, VENUS_nmea_store* nmea_store);
int venus_decodeNmeaMessage(VENUS_message_io* venus_message, VENUS_nmea_store* nmea_store);
int venus_buildMessageOut(VENUS_message_io* venus_message, VENUS_config* venus_config);
int venus_buildMessageBody(VENUS_message_io* venus_message, VENUS_config* venus_config);

int venus_sys_reset();
int venus_query_sw_rev();
int venus_query_sw_crc();
int venus_factory_reset();
int venus_config_serial();
int venus_config_nmea();
int venus_config_message();
int venus_config_sys_pwr();
int venus_config_update_rate();
int venus_query_update_rate();
int venus_config_datum();
int venus_query_datum();
int venus_config_get_eph();
int venus_config_set_eph();
int venus_config_waas();
int venus_query_waas();
int venus_config_pos_pin();
int venus_query_pos_pin();
int venus_config_pos_pin_param();
int venus_config_nav_mode();
int venus_query_nav_mode();
int venus_config_1pps_mode();
int venus_query_1pps_mode();

/**********************************
 *
 *    Read/Write to/from Venus
 *
 **********************************/


int venus638_Tx(void* host_object, int (*host_usart)(), void* ext_dev_object){
  
   int read_write = VENUS_WRITE;
   
   //Get the VENUS_message_io struct from the slave_object
   //
   MPI_ext_dev* venus_object = (MPI_ext_dev*)ext_dev_object;

   if(venus_object != NULL){

     VENUS_message_io* venus_message = venus_object->MPI_data[VENUS_MESSAGE_INDEX];  
     VENUS_response_store* venus_response = venus_object->MPI_data[VENUS_RESPONSE_INDEX];
     VENUS_nmea_store* venus_nmea = venus_object->MPI_data[VENUS_NMEA_INDEX];
     VENUS_config* venus_config = venus_object->MPI_conf[VENUS_CONFIG_INDEX];
  
     if((venus_message == NULL) || (venus_response == NULL) || (venus_nmea == NULL) || (venus_config == NULL)){
         return -1;
     } else {
        venus_buildMessageOut(venus_message, venus_config);
    
        //Send the right parameters through to the usart
        //
        return host_usart(host_object, read_write, venus_message->message_out, venus_message->final_message_len);
     }
  }
  return EXIT_SUCCESS;
}



int venus638_Rx(void* host_object, int (*host_usart)(), void* ext_dev_object){

  int read_write = VENUS_READ;
  MPI_ext_dev* venus_object = (MPI_ext_dev*)ext_dev_object;
  
  VENUS_message_io* venus_message = venus_object->MPI_data[VENUS_MESSAGE_INDEX];  
  VENUS_response_store* venus_response = venus_object->MPI_data[VENUS_RESPONSE_INDEX];
  VENUS_nmea_store* venus_nmea = venus_object->MPI_data[VENUS_NMEA_INDEX];    
  VENUS_op_mode* venus_mode = (VENUS_op_mode*)venus_object->MPI_conf[VENUS_OP_INDEX];


  //re-write this section to operate based on a mode i.e. command mode or 

  if(*venus_mode == nmea){
       /* if the first byte is a nmea sentence begin, store the nmea sentence*/
    if((venus_message->message_in[0] & NMEA_SENTENCE_BEGIN) == 0){
    
       //call to usart again to check which nmea sentence it is 
       host_usart(host_object, read_write, venus_message->message_in, NMEA_LEN);  
     
       //Call to decoding nmea id fn
       //
       int ret = venus_decodeNmeaId(venus_message, venus_nmea);

       if(ret){
         return 1;
       } 

       host_usart(host_object, read_write, venus_message->message_in, venus_nmea->nmea_len);

       //Call to decoding nmea sentence fn
       //
       ret = venus_decodeNmeaMessage(venus_message, venus_nmea);

       if(ret){
         return 1;
       }
    }
  } else if (*venus_mode == command){

     if((venus_message->message_in[0] & RES_ID_STATUS_ACK ) == 0){
       venus_response->ack_message_id = venus_message->message_in[1];
       return 0;
     } else if((venus_message->message_in[0] & RES_ID_STATUS_NACK ) == 0) {
       venus_response->nack_message_id = venus_message->message_in[1];
       return -1;
     } else {
       uint8_t* table = venus_response_lookup_table; 
            
       for(int i = 0; i < 10; i++){
         if((venus_message->message_in[0] & table[i]) == 0){
         //store Id in struct
         venus_response->response_id = venus_message->message_in[0]; 
         venus_message->payload_len = venus_query_lookup_table_member_length[i];
         //call to usart again to get message body
         host_usart(host_object, read_write, venus_message->message_in, venus_message->payload_len);
         //store in struct member appropriately 
         int(*response_handler)() = venus_handler_table[i];
         response_handler(venus_message, venus_response);
         } else {
           continue;
         } 
       }
     }
  }
  return EXIT_SUCCESS;
}



int venus_buildMessageOut(VENUS_message_io* venus_message, VENUS_config* venus_config){

  venus_nullMessageArray(venus_message);
  
  /*
   * buid the message:
   * <start of sequene><payload length><message ID><message body><checksum><end of sequence>
   *      2 bytes           2 byte       1 byte       n bytes      1 byte       2 bytes
   */


  //<start of sequence>
  venus_message->message_out[0] = SEQUENCE_START_0;
  venus_message->message_out[1] = SEQUENCE_START_1;

  //<message id and payload length>
  for(int i = 0; i < VENUS_QUERY_LOOKUP_TABLE_LENGTH; i++){
     if(venus_message->message_id == venus_query_lookup_table[i]){
        venus_message->payload_len = venus_query_lookup_table_member_length[i];          
     }
  } 
  venus_message->message_out[2] = venus_message->payload_len;

  //<message ID>
  venus_message->message_out[3] = venus_message->message_id;    

  //<message body>
  //
  venus_buildMessageBody(venus_message, venus_config);

  for(int i = 0; i < venus_message->payload_len; i++){
    venus_message->message_out[i+4] = venus_message->message_body[i];
  }
 
  //<checksum>
  //
  venus_makeChecksum(venus_message);
  venus_message->message_out[venus_message->payload_len + 5] = venus_message->checksum; 
 
  //<ending sequence>
  //
  venus_message->message_out[venus_message->payload_len + 6] = venus_message->sequence_end[0];
  venus_message->message_out[venus_message->payload_len + 7] = venus_message->sequence_end[1];
 
  return 0;
}



int venus_decodeNmeaId(VENUS_message_io* venus_message, VENUS_nmea_store* nmea_store){

  for(int i = 0; i < ID_NMEA_LEN; i++){
    for(int j = 0; j < ID_NMEA_LEN; j++){
      if((venus_message->message_in[j] & venus_nmea_id_table[i][j]) == 0){
       if(j == ID_NMEA_LEN){
         
         //assign i and that will give us our index for the jump table to identify which nmea string it is
         nmea_store->decode_id_index = i;
          
         //call to nmea jump table
         //get the message length
         nmea_store->nmea_len = nmea_sent_len[i];
         
         return 0;
       } else {
         continue; //if j != ID_NMEA_LEN then we are still parsing the id array
       }  
      } else {
        continue; //if the characters do not match then simply move to the next loop
      }
    }
  }
  return 1;
}



int venus_decodeNmeaMessage(VENUS_message_io* venus_message, VENUS_nmea_store* nmea_store){

   int(*const nmea_handler)() = nmea_decode_table[nmea_store->decode_id_index];
   nmea_handler(venus_message, nmea_store);

   return 0;
}



void venus_nullMessageArray(VENUS_message_io* venus_message){

  for(int i = 2; i < 1024; i++){
    venus_message->message_out[i] = '\0';     
  }
}



int venus_buildMessageBody(VENUS_message_io* venus_message,  VENUS_config* venus_config){

  //call to query jump table, run the function of the same index
  for(int i = 0; i < VENUS_QUERY_LOOKUP_TABLE_LENGTH; i++){
     if(venus_message->message_id == venus_query_lookup_table[i]){
       int(*build_msg)() = venus_config_query_fn_table[i];
       build_msg(venus_message, venus_config);
     }
  } 
  return 0;
}



int venus_makeChecksum(VENUS_message_io* venus_message){

  int CS = 0;
  
  for(int i = 0; i < venus_message->payload_len ; i++){
    CS ^= venus_message->message_body[i];
  }

  venus_message->checksum = CS; 
  return 0;
}

/*****************************************
 *
 *        Venus nmea handlers
 *
 *****************************************/

int decode_gga_fn(VENUS_message_io* venus_message, VENUS_nmea_store* nmea_store){

  int len = nmea_store->nmea_len;

  for(int i = 0; i < len; i++){
    nmea_store->decode_gga[i] = venus_message->message_in[i];
  }   
  return 0;
}

int decode_gll_fn(VENUS_message_io* venus_message, VENUS_nmea_store* nmea_store){
 
  int len = nmea_store->nmea_len;

  for(int i = 0; i < len; i++){
    nmea_store->decode_gll[i] = venus_message->message_in[i];
  } 
  return 0; 
}

int decode_gsa_fn(VENUS_message_io* venus_message, VENUS_nmea_store* nmea_store){
 
  int len = nmea_store->nmea_len;

  for(int i = 0; i < len; i++){
    nmea_store->decode_gsa[i] = venus_message->message_in[i];
  }  
  return 0;
}

int decode_gsv_fn(VENUS_message_io* venus_message, VENUS_nmea_store* nmea_store){
 
  int len = nmea_store->nmea_len;

  for(int i = 0; i < len; i++){
    nmea_store->decode_gsv[i] = venus_message->message_in[i];
  } 
  return 0; 
}

int decode_rmc_fn(VENUS_message_io* venus_message, VENUS_nmea_store* nmea_store){
 
  int len = nmea_store->nmea_len;

  for(int i = 0; i < len; i++){
    nmea_store->decode_rmc[i] = venus_message->message_in[i];
  } 
  return 0;
}

int decode_vtg_fn(VENUS_message_io* venus_message, VENUS_nmea_store* nmea_store){

  int len = nmea_store->nmea_len;

  for(int i = 0; i < len; i++){
    nmea_store->decode_vtg[i] = venus_message->message_in[i];
  } 
  return 0;
};


/**********************************************************************************************
 *
 *                            Venus Message_Id response handlers
 *
 *********************************************************************************************/

int venus_status_sw_version(VENUS_message_io* venus_message, VENUS_response_store* venus_response){

  /*
   * software version type  1
   * kernel version         2-5
   * odm version            6-9
   * revision               10-13
   */
  venus_response->software_version_type = venus_message->message_in[1];
  venus_response->kernel_version        = venus_message->message_in[2];
  venus_response->odm_version           = venus_message->message_in[3];
  venus_response->revision              = venus_message->message_in[4]; 
  return 0;
}

int venus_status_sw_crc(VENUS_message_io* venus_message, VENUS_response_store* venus_response){

  /*
   * software type 1
   * crc           2-3 
   */
  venus_response->software_crc_type     = venus_message->message_in[1];
  venus_response->crc                   = venus_message->message_in[2];
  return 0;
}

int venus_status_ack(VENUS_message_io* venus_message, VENUS_response_store* venus_response){

  /*
   * message id of the initial request message  1
   */
  venus_response->ack_message_id    = venus_message->message_in[1];
  return 0;
}

int venus_status_nack(VENUS_message_io* venus_message, VENUS_response_store* venus_response){

  /*
   * message id of the initial request message  1
   */
  venus_response->nack_message_id       = venus_message->message_in[1];
  return 0;
}

int venus_status_pin_info(VENUS_message_io* venus_message, VENUS_response_store* venus_response){

  /*
   * update rate  1
   */
  venus_response->update_rate           = venus_message->message_in[1];
  return 0;
}


int venus_status_eph_data(VENUS_message_io* venus_message, VENUS_response_store* venus_response){

  /*
   * SV id                   1-2 
   * subframedata[0][0-27]   3-30 
   * subframedata[1][0-27]   31-58
   * subframedata[2][0-27]   59-86
   *
   */
  venus_response->sv_id                 = venus_message->message_in[1];
  //sfd_1 for loop
  for(int i = 0; i < EPH_SUB_FRAME_DATA_LEN; i++){
  venus_response->sfd_1[i]              = venus_message->message_in[i+4];
  }
  //sfd_2 for loop
  for(int i = 0; i < EPH_SUB_FRAME_DATA_LEN; i++){
  venus_response->sfd_2[i]              = venus_message->message_in[i+32];
  }
  //sfd_3 for loop
  for(int i = 0; i < EPH_SUB_FRAME_DATA_LEN; i++){
  venus_response->sfd_2[i]              = venus_message->message_in[i+60];
  }
  return 0;
}


int venus_status_datum(VENUS_message_io* venus_message, VENUS_response_store* venus_response){

  /*
   * datum index 1-2 //refer to appendix A & B
   */
  venus_response->datum_index           = venus_message->message_in[1];
  return 0;
}


int venus_status_waas(VENUS_message_io* venus_message, VENUS_response_store* venus_response){

  /*
   * WAAS status  1
   */
  venus_response->waas_status           = venus_message->message_in[1];
  return 0;
}


int venus_status_pin(VENUS_message_io* venus_message, VENUS_response_store* venus_response){

  /*
   * status     1
   */
  venus_response->pos_pin_status        = venus_message->message_in[1];
  return 0;
}


int venus_status_nav(VENUS_message_io* venus_message, VENUS_response_store* venus_response){

  /*
   * navigation mode  1
   */
  venus_response->nav_mode              = venus_message->message_in[1];
  return 0;
}


int venus_status_1pps(VENUS_message_io* venus_message, VENUS_response_store* venus_response){

  /*
   * 1pps mode  1
   */
  venus_response->gps_1pps_mode         = venus_message->message_in[1];
  return 0;
}


/********************************************************************************************
 *
 *                        Venus message_body builders 
 *
 *******************************************************************************************/ 

int venus_sys_reset(VENUS_message_io* message_instance, VENUS_config* venus_config){

  message_instance->message_body[0] = venus_config->sys_reset_start_mode; 
  message_instance->message_body[1] = venus_config->sys_reset_utc_year; 
  message_instance->message_body[2] = venus_config->sys_reset_utc_month; 
  message_instance->message_body[3] = venus_config->sys_reset_utc_day; 
  message_instance->message_body[4] = venus_config->sys_reset_utc_hour; 
  message_instance->message_body[5] = venus_config->sys_reset_utc_minute; 
  message_instance->message_body[6] = venus_config->sys_reset_utc_second; 
  message_instance->message_body[7] = venus_config->sys_reset_latitude;
  message_instance->message_body[8] = venus_config->sys_reset_longitude;
  message_instance->message_body[9] = venus_config->sys_reset_altitude; 
  
  return 0;
}

int venus_query_sw_rev(VENUS_message_io* message_instance, VENUS_config* venus_config){
  
  message_instance->message_body[0] = venus_config->query_software_version_type;
  return 0;
}

int venus_query_sw_crc(VENUS_message_io* message_instance, VENUS_config* venus_config){

  message_instance->message_body[0] = venus_config->query_software_crc_type;
  return 0;
}

int venus_factory_reset(VENUS_message_io* message_instance, VENUS_config* venus_config){

  message_instance->message_body[0] = venus_config->set_factory_defaults_type;
  return 0;
}

int venus_config_serial(VENUS_message_io* message_instance, VENUS_config* venus_config){

  message_instance->message_body[0] = venus_config->config_serial_port_port;
  message_instance->message_body[1] = venus_config->config_serial_port_baud;
  message_instance->message_body[2] = venus_config->config_serial_port_attr;


  return 0;
}

int venus_config_nmea(VENUS_message_io* message_instance, VENUS_config* venus_config){

  message_instance->message_body[0] = venus_config->config_nmea_gga;
  message_instance->message_body[1] = venus_config->config_nmea_gsa;
  message_instance->message_body[2] = venus_config->config_nmea_gsv;
  message_instance->message_body[3] = venus_config->config_nmea_gll;
  message_instance->message_body[4] = venus_config->config_nmea_rmc;
  message_instance->message_body[5] = venus_config->config_nmea_vtg;
  message_instance->message_body[6] = venus_config->config_nmea_zda;
  message_instance->message_body[7] = venus_config->config_nmea_attr;

  return 0;
}

int venus_config_message(VENUS_message_io* message_instance, VENUS_config* venus_config){
    
  message_instance->message_body[0] = venus_config->config_message_type;
  return 0;
}

int venus_config_sys_pwr(VENUS_message_io* message_instance, VENUS_config* venus_config){

  message_instance->message_body[0] = venus_config->config_sys_power_mode;
  message_instance->message_body[1] = venus_config->config_sys_power_attr;
  return 0;
}

int venus_config_update_rate(VENUS_message_io* message_instance, VENUS_config* venus_config){

  message_instance->message_body[0] = venus_config->config_sys_pos_rate;
  message_instance->message_body[1] = venus_config->config_sys_pos_attr;
  return 0;
}

int venus_query_update_rate(VENUS_message_io* message_instance, VENUS_config* venus_config){

  message_instance->message_body[0] = '\0';
  return 0;
}

int venus_config_datum(VENUS_message_io* message_instance, VENUS_config* venus_config){

  message_instance->message_body[0] = venus_config->config_datum_index;
  message_instance->message_body[1] = venus_config->config_datum_ellip;  
  message_instance->message_body[2] = venus_config->config_datum_delta_x;
  message_instance->message_body[3] = venus_config->config_datum_delta_y;
  message_instance->message_body[4] = venus_config->config_datum_delta_z;
  message_instance->message_body[5] = venus_config->config_datum_semi_major_axis;
  message_instance->message_body[6] = venus_config->config_datum_inversed_flat;
  message_instance->message_body[7] = venus_config->config_datum_attr;
  return 0;
}

int venus_query_datum(VENUS_message_io* message_instance, VENUS_config* venus_config){

  message_instance->message_body[0] = '\0';
  return 0;
}

int venus_query_get_eph(VENUS_message_io* message_instance, VENUS_config* venus_config){

  message_instance->message_body[0] = venus_config->config_get_eph_data_sv;
  return 0;
}

int venus_config_set_eph(VENUS_message_io* message_instance, VENUS_config* venus_config){

  message_instance->message_body[0] = venus_config->config_set_eph_data_sv;

  //for(int i = 0; i < 3; i++){
  //  for(int j = 0; j < 27; j++){
  //    message_body->config_set_eph_data_sfd[i][j] = ;
  //  }
  //}

  return 0;
}

int venus_config_waas(VENUS_message_io* message_instance, VENUS_config* venus_config){

  message_instance->message_body[0] = venus_config->config_waas_enable;
  message_instance->message_body[1] = venus_config->config_waas_attr;

  return 0;
}

int venus_query_waas(VENUS_message_io* message_instance, VENUS_config* venus_config){

  message_instance->message_body[0] = '\0';
  return 0;
}

int venus_config_pos_pin(VENUS_message_io* message_instance, VENUS_config* venus_config){

  message_instance->message_body[0] = venus_config->config_pos_pin_enable;
  return 0;
}

int venus_query_pos_pin(VENUS_message_io* message_instance, VENUS_config* venus_config){

  message_instance->message_body[0] = '\0';
  return 0;
}

int venus_config_pos_pin_param(VENUS_message_io* message_instance, VENUS_config* venus_config){

  message_instance->message_body[0] = venus_config->config_pos_pin_speed;
  message_instance->message_body[1] = venus_config->config_pos_pin_cnt;
  message_instance->message_body[2] = venus_config->config_pos_unpin_speed;
  message_instance->message_body[3] = venus_config->config_pos_unpin_cnt;
  message_instance->message_body[4] = venus_config->config_pos_unpin_distance;
  return 0;
}

int venus_config_nav_mode(VENUS_message_io* message_instance, VENUS_config* venus_config){

  message_instance->message_body[0] = venus_config->config_nav_mode;
  message_instance->message_body[1] = venus_config->config_nav_attr;
   return 0;
}

int venus_query_nav_mode(VENUS_message_io* message_instance, VENUS_config* venus_config){

  message_instance->message_body[0] = '\0'; 
  return 0;
}

int venus_config_1pps_mode(VENUS_message_io* message_instance, VENUS_config* venus_config){
 
  message_instance->message_body[0] = venus_config->config_1pps_mode;
  message_instance->message_body[1] = venus_config->config_1pps_attr;
  return 0;
}

int venus_query_1pps_mode(VENUS_message_io* message_instance, VENUS_config* venus_config){
  
  message_instance->message_body[0] = '\0';
  return 0;
}

// venus_message table
//
int(*const venus_config_query_fn_table[24])() = 
{
 venus_config_serial,
 venus_config_nmea,
 venus_config_message,
 venus_config_sys_pwr,
 venus_config_update_rate,
 venus_config_datum,
 venus_config_set_eph,
 venus_config_waas,
 venus_config_pos_pin,
 venus_config_pos_pin_param,
 venus_config_nav_mode,
 venus_config_1pps_mode,
 venus_query_sw_rev,
 venus_query_sw_crc,
 venus_query_update_rate,
 venus_query_datum,
 venus_query_get_eph,
 venus_query_waas,
 venus_query_pos_pin,
 venus_query_nav_mode,
 venus_query_1pps_mode
};

uint8_t venus_query_lookup_table[VENUS_QUERY_LOOKUP_TABLE_LENGTH] = 
{
 ID_CONFIG_SERIAL_PORT,     
 ID_CONFIG_NMEA_MESSAGE,    
 ID_CONFIG_MESSAGE_TYPE,    
 ID_CONFIG_SYS_PWR,         
 ID_CONFIG_UPDATE_RATE,  
 ID_CONFIG_DATUM,           
 ID_EHP_DATA_SET,           
 ID_CONFIG_WAAS,            
 ID_CONFIG_PIN,              
 ID_CONFIG_PIN_PARAMS,      
 ID_CONFIG_NAV_MODE, 
 ID_CONFIG_1PPS_MODE,        
 ID_QUERY_SW_REV,           
 ID_QUERY_SW_CRC,         
 ID_QUERY_UPDATE_RATE,      
 ID_QUERY_DATUM,           
 ID_EPH_DATA_GET,           
 ID_QUERY_WAAS_STATUS,      
 ID_QUERY_PIN_STATUS,       
 ID_QUERY_NAV_MODE,         
 ID_QUERY_1PPS_MODE       
};

uint8_t venus_query_lookup_table_member_length[VENUS_QUERY_LOOKUP_TABLE_LENGTH] = 
{
 CONFIG_SERIAL_PORT_PL_LEN,           
 CONFIG_NMEA_UPDATE_PL_LEN,           
 CONFIG_MESSAGE_TYPE_PL_LEN,          
 CONFIG_SYS_POWER_MODE_PL_LEN,                  
 CONFIG_SYSTEM_POS_RATE_PL_LEN,  
 CONFIG_EPH_DATA_SET_PL_LEN,
 CONFIG_WAAS_PL_LEN,         
 CONFIG_DATUM_PL_LEN,                   
 CONFIG_POSITION_PIN_PL_LEN,       
 CONFIG_POS_PIN_PARAMS_PL_LEN,               
 CONFIG_NAV_MODE_PL_LEN,  
 CONFIG_1PPS_MODE_PL_LEN, 
 QUERY_SOFTWARE_VERSION_PL_LEN, 
 QUERY_SOFTWARE_CRC_PL_LEN,           
 QUERY_POS_UPDATE_RATE_PL_LEN,               
 QUERY_DATUM_PL_LEN,         
 QUERY_EPH_DATA_GET_PL_LEN,
 QUERY_WAAS_STATUS_PL_LEN,   
 QUERY_POS_PIN_PL_LEN,             
 QUERY_NAV_MODE_PL_LEN,                     
 QUERY_1PPS_MODE_PL_LEN                   
};

uint8_t venus_response_lookup_table[VENUS_RESPONSE_LOOKUP_TABLE_LENGTH] = 
{
 RES_ID_STATUS_ACK,         
 RES_ID_STATUS_NACK,   
 RES_ID_STATUS_SW_VERSION, 
 RES_ID_STATUS_SW_CRC,       
 RES_ID_STATUS_PIN_INFO,   
 RES_ID_GET_EPH_DATA,                 
 RES_ID_STATUS_DATUM,       
 RES_ID_STATUS_WAAS,      
 RES_STATUS_PIN,        
 RES_STATUS_NAV,            
 RES_STATUS_1PPS      
};

uint8_t venus_response_lookup_table_member_length[VENUS_RESPONSE_LOOKUP_TABLE_LENGTH] = 
{
 STATUS_ACK_PL_LEN,          
 STATUS_NACK_PL_LEN,   
 STATUS_SW_VERSION_PL_LEN,   
 STATUS_SW_CRC_PL_LEN,       
 STATUS_PIN_INFO_PL_LEN, 
 STATUS_GET_EPH_DATA_PL_LEN, 
 STATUS_DATUM_PL_LEN,        
 STATUS_WAAS_PL_LEN,         
 STATUS_POS_PIN_PL_LEN,      
 STATUS_NAV_MODE_PL_LEN,     
 STATUS_1PPS_MODE_PL_LEN   
};

// venus handler lookup table
//
int (*const venus_handler_table[VENUS_RESPONSE_LOOKUP_TABLE_LENGTH])() = 
{
 venus_status_ack,
 venus_status_nack,
 venus_status_sw_version, 
 venus_status_sw_crc,
 venus_status_pin_info,
 venus_status_eph_data,
 venus_status_datum,
 venus_status_waas,
 venus_status_pin,
 venus_status_nav,
 venus_status_1pps,
};

int(*const nmea_decode_table[ID_NMEA_LEN])() = 
{
  decode_gga_fn,  
  decode_gll_fn, 
  decode_gsa_fn, 
  decode_gsv_fn, 
  decode_rmc_fn, 
  decode_vtg_fn
};


