/**************************************************
 *
 *   \_____            \_____
 *       \_____            \_____
 *          \_____            \_____
 *             \_____            \_____
 *                /_____            /_____
 *             /_____            /_____
 *          /_____            /_____
 *       /_____            /_____
 *   /_____            /_____
 *      
 *   bitshift.net.au 
 *  
 *
 *  This file serves as a skeleton header library for the 
 *  SkyTrak Venus638 GPS Reciever. The programmer will have 
 *  to fill in the gaps where no values are actually defined. 
 *  
 *  This file covers all available functionality as stated in
 *  the datasheet, however no ROM or flash programming logic
 *  has been considered here nor provided by the vendor. 
 *
 *  The chip is capable of a sleep mode through external components, 
 *  I refer you to the datasheet to view the specific regulators.
 *  
 *  As for control and initialization of the unit, SkyTraq have 
 *  provided a binary message interface which this library
 *  encapsulates.
 *
 *  KEY NOTES:
 *
 *   - This device reads and writes as BigEndian, please ensure
 *     your UART/USART port is set accordingly
 *   - Default baud rate is 115200
 *   - Basic hookup and usage is simple serial and power
 *   - If you want to store logs, best option is external flash
 *     as internal is only accessible via proprietary tools
 *     or rolling your own accoring to the binary message protocol
 *     found in this file.
 *   - 
 *   
 *
 *  For further details, please see the datasheets and application 
 *  notes within this repo.
 *  
 *  Copyright (C) 2019 Aidan Millar-Powell aka medicineman25
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 * 
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <https://www.gnu.org/licenses/>.
 *
 *
 *
 **************************************************/

#ifndef VENUS638_H_
#define VENUS638_H_

#include <stdint.h>

#define EXIT_SUCCESS 0

typedef enum {
  command,
  nmea
}VENUS_op_mode;


//Jump tables
//
extern uint8_t venus_response_lookup_table[];
extern uint8_t venus_query_lookup_table[];
extern uint8_t venus_response_lookup_table_member_length[];
extern uint8_t venus_query_lookup_table_member_length[];
extern int (*const venus_handler_table[])();
extern int(*const venus_message_body_fn_table[])(); 
extern int(*const venus638_rx_tx_table[])();
extern int(*const nmea_decode_table[])();
extern int(*const venus_config_query_fn_table[])(); 

typedef enum {
 config_serial,
 config_nmea,
 config_message,
 config_sys_pwr,
 config_update_rate,
 config_datum,
 config_set_eph,
 config_waas,
 config_pos_pin,
 config_pos_pin_param,
 config_nav_mode,
 config_1pps_mode,
 query_sw_rev,
 query_sw_crc,
 query_update_rate,
 query_datum,
 query_get_eph,
 query_waas,
 query_pos_pin,
 query_nav_mode,
 query_1pps_mode
}venus_config_query_enum;

typedef venus_config_query_enum register_enum;


typedef struct VENUS_MESSAGE_IO{
  uint8_t sequence_start[2];
  uint8_t sequence_end[2];
  uint32_t message_id;
  uint8_t message_body[64];
  uint32_t payload_len;
  uint32_t checksum;
  uint8_t message_out[64];
  uint8_t message_in[256];
  uint32_t final_message_len;
  uint8_t last_known;
}VENUS_message_io;


typedef struct VENUS_MESSAGE_BODY{
  uint8_t sys_reset_start_mode;
  uint16_t sys_reset_utc_year;
  uint8_t sys_reset_utc_month;
  uint8_t sys_reset_utc_day;
  uint8_t sys_reset_utc_hour;
  uint8_t sys_reset_utc_minute;
  uint8_t sys_reset_utc_second;
  int16_t sys_reset_latitude;
  int16_t sys_reset_longitude;
  int16_t sys_reset_altitude;
  uint8_t query_software_version_type;
  uint8_t query_software_crc_type;
  uint8_t set_factory_defaults_type;
  uint8_t config_serial_port_port;
  uint8_t config_serial_port_baud;
  uint8_t config_serial_port_attr;
  uint8_t config_nmea_gga;
  uint8_t config_nmea_gsa;
  uint8_t config_nmea_gsv;
  uint8_t config_nmea_gll;
  uint8_t config_nmea_rmc;
  uint8_t config_nmea_vtg;
  uint8_t config_nmea_zda;
  uint8_t config_nmea_attr;
  uint8_t config_message_type;
  uint8_t config_sys_power_mode;
  uint8_t config_sys_power_attr;
  uint8_t config_sys_pos_rate;
  uint8_t config_sys_pos_attr;
  uint16_t config_datum_index;
  uint8_t config_datum_ellip;  
  int8_t config_datum_delta_x;
  int8_t config_datum_delta_y;
  int8_t config_datum_delta_z;
  uint32_t config_datum_semi_major_axis;
  uint32_t config_datum_inversed_flat;
  uint8_t config_datum_attr;
  uint8_t config_get_eph_data_sv;
  uint16_t config_set_eph_data_sv;
  uint8_t config_set_eph_data_sfd[3][28];
  uint8_t config_waas_enable;
  uint8_t config_waas_attr;
  uint8_t config_pos_pin_enable;
  uint16_t config_pos_pin_speed;
  uint16_t config_pos_pin_cnt;
  uint16_t config_pos_unpin_speed;
  uint16_t config_pos_unpin_cnt;
  uint16_t config_pos_unpin_distance;
  uint8_t config_nav_mode;
  uint8_t config_nav_attr;
  uint8_t config_1pps_mode;
  uint8_t config_1pps_attr;
}VENUS_config;


typedef struct VENUS_ERROR{

 int err;

}VENUS_error;

/*
typedef struct VENUS_NMEA_STORE{

 uint32_t nmea_string1; 

}VENUS_nmea_store;
*/

typedef struct VENUS_RESPONSE_STORE{
  uint32_t software_version_type;
  uint32_t kernel_version;
  uint32_t odm_version;
  uint32_t revision;
  uint32_t software_crc_type;
  uint32_t crc;
  uint32_t ack_message_id;
  uint32_t nack_message_id;
  uint32_t update_rate;
  uint32_t sv_id;
  uint32_t sfd_1[28];
  uint32_t sfd_2[28];
  uint32_t sfd_3[28];
  uint32_t datum_index;
  uint32_t waas_status;
  uint32_t pos_pin_status;
  uint32_t nav_mode;
  uint32_t gps_1pps_mode;
  uint32_t response_id;
}VENUS_response_store;

/**************************
 *
 *     NMEA SENTENCES    
 *
 **************************/

#define NMEA_LEN               512

#define ID_HEADER_LEN          1
#define NMEA_SENTENCE_BEGIN    0x24
#define ID_NMEA_LEN            6

#define GGA_LEN  ID_NMEA_LEN
#define GLL_LEN  ID_NMEA_LEN
#define GSA_LEN  ID_NMEA_LEN
#define GSV_LEN  ID_NMEA_LEN
#define RMC_LEN  ID_NMEA_LEN
#define VTG_LEN  ID_NMEA_LEN

#define GGA_INDEX 0
#define GLL_INDEX 1
#define GSA_INDEX 2
#define GSV_INDEX 3
#define RMC_INDEX 4
#define VTG_INDEX 5

#define GGA_SENT_LEN 52
#define GLL_SENT_LEN 39 
#define GSA_SENT_LEN 50
#define GSV_SENT_LEN 34
#define RMC_SENT_LEN 55
#define VTG_SENT_LEN 22

//#define test ( uint32_t testing = PGGA);

extern const uint8_t venus_nmea_id_table [ID_NMEA_LEN][ID_NMEA_LEN]; 

typedef struct {

 uint8_t decode_id[ID_NMEA_LEN];
 uint8_t decode_id_index;
 uint8_t nmea_len;
 uint8_t decode_gga[32];
 uint8_t decode_gll[32];
 uint8_t decode_gsa[32];
 uint8_t decode_gsv[32];
 uint8_t decode_rmc[32];
 uint8_t decode_vtg[32];

}VENUS_nmea_store;


/**************************
 *
 *   DEFINES AND BITMASKS    
 *
 **************************/

#define VENUS_QUERY_LOOKUP_TABLE_LENGTH     24 
#define VENUS_RESPONSE_LOOKUP_TABLE_LENGTH  12 

#define VENUS_MESSAGE_INDEX   0
#define VENUS_RESPONSE_INDEX  1
#define VENUS_NMEA_INDEX      2

#define VENUS_CONFIG_INDEX    0
#define VENUS_OP_INDEX        1


#define VENUS_READ_WRITE  2
#define VENUS_READ        0
#define VENUS_WRITE       1

#define BOOT_SEL_ROM      1
#define BOOT_SEL_FLASH    0

#define BOOT_SEL_PIN 

#define MOSI_PIN  
#define MISO_PIN  
#define SPI_CLK   
#define SPI_CS    

#define USART_RXD 
#define USART_TXC 

#define SDA_PIN   
#define SCL_PIN   

#define VCC33I    
#define GND       

#define P1PPS_RATE_DEFAULT 1000 //1 pulse per second time-mark
#define P1PPS_RATE_2MHZ    2000 //2 pulse per second time-mark
#define P1PPS_RATE_4MHZ    4000 //4 pulse per second time-mark
#define P1PPS_RATE_5MHZ    5000 //5 pulse per second time-mark
#define P1PPS_RATE_8MHZ    8000 //8 pulse per second time-mark
#define P1PPS_RATE_10MHZ   10000 //10 pulse per second time-mark
#define P1PPS_RATE_20MHZ   20000 //20 pulse per second time-mark

//pin #8
#define SE_MODE_SEL_LP 1 //search engine mode low power mode
#define SE_MODE_SEL_EA 0 //search engine mode enhanced acquisition mode

#define COLD_START_TTFF 29000 //29s time to first fix on cold start
#define HOT_START_TTFF 1000   //1s time to first fix on hot start
#define AGPS_TTFF 3600        //3.5s time to first fix with AGPS
#define SBAS 1                //SBAS support true

#define BR_4800   4800    
#define BR_9600   9600    
#define BR_38400  38400   
#define BR_115200 115200  //default baud rate

/***********************
 *
 *  MESSAGE INDEXES    
 *
 **********************/

#define PAYLOAD_LEN_BYTE_ZERO_INDEX   2
#define PAYLOAD_LEN_BYTE_ONE_INDEX    3
#define MESSAGE_ID_INDEX              4
#define MESSAGE_BODY_START            5

/***********************
 *
 *    BYTE LENGTHS
 *
 **********************/

#define LEN_SEQ_START             2
#define LEN_SEQ_END               2
#define LEN_PAYLOAD_LEN_LEN       2
#define LEN_MESSAGE_ID            1
#define LEN_CHECKSUM              1

#define NO_BYTE_SHIFT             0
#define SINGLE_BYTE_SHIFT         8
#define DOUBLE_BYTE_SHIFT         16
#define TRIPLE_BYTE_SHIFT         24

/**********************
 *
 *  START/STOP
 *
 *********************/

#define SEQUENCE_START_0          0xA0 
#define SEQUENCE_START_1          0xA1 
#define SEQUENCE_END_0            0x0D
#define SEQUENCE_END_1            0x0A 


/******************************************************
 *
 * QUERY MESSAGES i.e. HOST CONTROLLER -> GPS RECEIVER
 *
 *****************************************************/

/*****************************
 *
 *        MESSAGE IDs
 *
 *****************************/

//System Messages
#define ID_SYS_RESET              0x1 //system reset
#define ID_QUERY_SW_REV           0x2 //query software revision
#define ID_QUERY_SW_CRC           0x3 //query crc of software
#define ID_FACTORY_RESET          0x4 //set factory defaults
#define ID_CONFIG_SERIAL_PORT     0x5 //configure the serial port
#define ID_CONFIG_NMEA_MESSAGE    0x8 //configure the NMEA output message
#define ID_CONFIG_MESSAGE_TYPE    0x9 //configure the output message format
#define ID_CONFIG_SYS_PWR         0xC //configure power mode
#define ID_CONFIG_UPDATE_RATE     0xE //configure how often the device updates position
#define ID_QUERY_UPDATE_RATE      0x10 //query how often the device updates position

//GPS Messages
#define ID_CONFIG_DATUM           0x29 //configure the datum of GPS reciever
#define ID_QUERY_DATUM            0x2D //query the datum of reciever
#define ID_EPH_DATA_GET           0x30 //retrieve ephemeris data of the reciever
#define ID_EHP_DATA_SET           0x31 //set the ephemeris data of reciever
#define ID_CONFIG_WAAS            0x37 //enable or disable WAAS
#define ID_QUERY_WAAS_STATUS      0x38 //query status of WAAS
#define ID_CONFIG_PIN             0x39 //enable or disable position pinning 
#define ID_QUERY_PIN_STATUS       0x3A //query position pinning status
#define ID_CONFIG_PIN_PARAMS      0x3B //config position pinning parameters
#define ID_CONFIG_NAV_MODE        0x3C //configure navigation mode of GPS
#define ID_QUERY_NAV_MODE         0x3D //query navigation mode
#define ID_CONFIG_1PPS_MODE       0x3E //configure 1PPS mode 
#define ID_QUERY_1PPS_MODE        0x3F //query 1PPS mode



/*******************************
 *
 *    MESSAGE BODY DEFINES
 *
 *******************************/

//ID_SYS_RESET
//
#define SYSTEM_RESTART_START_MODE_HOT       0x01
#define SYSTEM_RESTART_START_MODE_WARM      0x02
#define SYSTEM_RESTART_START_MODE_COLD      0x03
#define SYSTEM_RESTART_UTC_YEAR(X,Y)        ( uint8_t utc_year[] = { (X),(Y) }; )   // >=1970
#define SYSTEM_RESTART_UTC_MONTH(X)         ( (X) )                                 // 1-12
#define SYSTEM_RESTART_UTC_DAY(X)           ( (X) )                                 // 1-31
#define SYSTEM_RESTART_UTC_HOUR(X)          ( (X) )                                 // 0-23
#define SYSTEM_RESTART_UTC_MINUTE(X)        ( (X) )                                 // 0-59
#define SYSTEM_RESTART_UTC_SECOND(X)        ( (X) )                                 // 0-59
#define SYSTEM_RESTART_LATITUDE(X,Y)        ( uint8_t latitude[] = { (X),(Y) }; )   // -9000 to 9000   (<0: sth hemi, >0: nth hemi)  
#define SYSTEM_RESTART_LONGITUDE(X,Y)       ( uint8_t longitude[] = { (X),(Y) }; )  // -18000 to 18000 (<0: west hemi, >0: east hemi)
#define SYSTEM_RESTART_ALTITUDE(X,Y)        ( uint8_t altitude[]  = { (X),(Y) }; )  // -1000 to 18300  (mtrs)
#define SYSTEM_RESTART_PL_LEN               15


//ID_QUERY_SW_REV
//
#define QUERY_SOFTWARE_VERSION              0x01
#define QUERY_SOFTWARE_VERSION_PL_LEN       2


//ID_QUERY_SW_CRC
//
#define QUERY_SOFTWARE_CRC                  0x01
#define QUERY_SOFTWARE_CRC_PL_LEN           2


//ID_FACTORY_RESET
//
#define SET_FACTORY_DEFAULTS                0x01
#define SET_FACTORY_DEFAULTS_PL_LEN         2


//ID_CONFIG_SERIAL_PORT
//
#define CONFIG_SERIAL_PORT_COM_1            0x00
#define CONFIG_SERIAL_PORT_BR_4800          0X00
#define CONFIG_SERIAL_PORT_BR_9600          0X01
#define CONFIG_SERIAL_PORT_BR_19200         0X02
#define CONFIG_SERIAL_PORT_BR_38400         0X03
#define CONFIG_SERIAL_PORT_BR_57600         0X04
#define CONFIG_SERIAL_PORT_BR_115200        0X05
#define CONFIG_SERIAL_PORT_UPDATE_SRAM      0x00
#define CONFIG_SERIAL_PORT_UPDATE_SRAM_FLASH  0x01
#define CONFIG_SERIAL_PORT_PL_LEN           4


//ID_CONFIG_NMEA_MESSAGE
//
#define CONFIG_NMEA_GGA_INTERVAL_DISABLED   0x00
#define CONFIG_NMEA_GGA_INTERVAL(X)         ( (X) ) //0-255
#define CONFIG_NMEA_GSA_INTERVAL(X)         ( (X) )
#define CONFIG_NMEA_GSV_INTERVAL(X)         ( (X) )
#define CONFIG_NMEA_GLL_INTERVAL(X)         ( (X) )
#define CONFIG_NMEA_RMC_INTERVAL(X)         ( (X) )
#define CONFIG_NMEA_VTG_INTERVAL(X)         ( (X) )
#define CONFIG_NMEA_ZDA_INTERVAL(X)         ( (X) )
#define CONFIG_NMEA_UPDATE_SRAM             0x00
#define CONFIG_NMEA_UPDATE_SRAM_FLASH       0x01
#define CONFIG_NMEA_UPDATE_PL_LEN           9


//ID_CONFIG_MESSAGE_TYPE
//
#define CONFIG_MESSAGE_TYPE_NONE            0x00
#define CONFIG_MESSAGE_TYPE_NMEA            0x01
#define CONFIG_MESSAGE_TYPE_BINARY          0x02
#define CONFIG_MESSAGE_TYPE_PL_LEN          2


//ID_CONFIG_SYS_PWR
//
#define CONFIG_SYS_POWER_MODE_NORMAL                  0x00
#define CONFIG_SYS_POWER_MODE_SAVE                    0x00
#define CONFIG_SYS_POWER_MODE_UPDATE_SRAM             0x00
#define CONFIG_SYS_POWER_MODE_UPDATE_SRAM_FLASH       0x01
#define CONFIG_SYS_POWER_MODE_TEMP_EN                 0x02
#define CONFIG_SYS_POWER_MODE_PL_LEN                  3


//ID_CONFIG_UPDATE_RATE
//
/*
 * The following settings need to match the given baud rates
 */
/* baud rates <= 19200 */
#define CONFIG_SYSTEM_POS_RATE_1HZ                 0x01
#define CONFIG_SYSTEM_POS_RATE_2HZ                 0x02
/* baud rates >= 38400 */
#define CONFIG_SYSTEM_POS_RATE_4HZ                 0x04
#define CONFIG_SYSTEM_POS_RATE_5HZ                 0x05
#define CONFIG_SYSTEM_POS_RATE_8HZ                 0x08
#define CONFIG_SYSTEM_POS_RATE_10HZ                0x10
/* baud rate == 115200 */
#define CONFIG_SYSTEM_POS_RATE_20HZ                0x20
#define CONFIG_SYSTEM_POS_UPDATE_SRAM              0x00
#define CONFIG_SYSTEM_POS_UPDATE_SRAM_FLASH        0x01
#define CONFIG_SYSTEM_POS_RATE_PL_LEN              3


//ID_QUERY_POS_UPDATE_RATE
//
#define QUERY_POS_UPDATE_RATE_PL_LEN               1


//ID_CONFIG_DATUM
//
/******************************* REVISIT AND APPLY CALCULATIONS FROM DATASHEET *******************************/
#define CONFIG_DATUM_INDEX(X,Y)               ( uint8_t datum_index[2] = { (X),(Y) }; )
#define CONFIG_DATUM_ELLIP_IDX(X)             ( (X) )
#define CONFIG_DATUM_DELTA_X(X,Y)             ( uint8_t datum_delta_x[2] = { (X),(Y) }; )
#define CONFIG_DATUM_DELTA_Y(X,Y)             ( uint8_t datum_delta_y[2] = { (X),(Y) }; )
#define CONFIG_DATUM_DELTA_Z(X,Y)             ( uint8_t datum_delta_z[2] = { (X),(Y) }; )
#define CONFIG_DATUM_SEMI_MAJOR_AXIS(X,Y,Z)   ( uint8_t datum_axis[3]    = { (X),(Y),(Z) }; )
#define CONFIG_DATUM_INVERSED_FLAT(X,Y,Z)     ( uint8_t datum_flat[3]    = { (X),(Y),(Z) }; )
#define CONFIG_DATUM_UPDATE_SRAM              0x00
#define CONFIG_DATUM_UPDATE_SRAM_FLASH        0x01
#define CONFIG_DATUM_PL_LEN                   19

/*
1.  In order to reduce number of bytes to send in the configure datum command, the Semi-Major Axis is to be deducted by 6,370,000, with the result multiplied by 1,000. Thus if converting 6,378,249.145 the result would be: 6,378,249.145 – 6,370,000 equals 8,249.145 And converting 8,249.145 x 1000 to hex is 007DDF39.   
2.    Same as for Inversed Flattening which is to be deducted by 293; with the result multiplied by 10,000,000 then converted to hex. 
3.    The exception is: the Inversed Flattening for Ellipsoid index 20 and 23 will lose precision after deducting by 293, multiply by 10,000,000 and convert to hex. Therefore, upon receiving the configure datum command, our firmware will use the internal hardcoded inversed flattening values for of 20 and 23, regardless of what is sent in the set datum command
*/
/******************************* REVISIT AND APPLY CALCULATIONS FROM DATASHEET *******************************/

//ID_QUERY_DATUM
//
#define QUERY_DATUM_PL_LEN         1


//ID_EPH_DATA_GET
//
/******************************* LEARN MORE ABOUT EPHEMERIS DATA AND UNDERSTAND HOW MANY SUB FRAMES ARE POSSIBLE ********************/
#define QUERY_EPH_DATA_GET(X)          ( (X) )      //range 1-32 for particular space vehicle
#define QUERY_EPH_DATA_GET_PL_LEN      2


//ID_EPH_DATA_SET
//
#define CONFIG_EPH_DATA_SET_SV_ID(X,Y)  ( (X),(Y) )  //SV Id in hex format  
#define CONFIG_EPH_DATA_SET_SFD(X)(Y)   ( (X),(Y) )  // X = subframe range 0-2, Y = bitfield of subframe range 0-27
#define CONFIG_EPH_DATA_SET_PL_LEN      87
/******************************* LEARN MORE ABOUT EPHEMERIS DATA AND UNDERSTAND HOW MANY SUB FRAMES ARE POSSIBLE ********************/

#define EPH_SUB_FRAME_DATA_LEN 27

//ID_CONFIG_WAAS
//
#define CONFIG_WAAS_EN_ENABLE      0x00
#define CONFIG_WAAS_EN_DISABLE     0x01
#define CONFIG_WAAS_PL_LEN         3


//ID_QUERY_WAAS_STATUS
//
#define QUERY_WAAS_STATUS_PL_LEN   1


//ID_CONFIG_PIN
//
#define CONFIG_POSITION_PIN_DISABLE      0x00
#define CONFIG_POSITION_PIN_ENABLE       0x01
#define CONFIG_POSITION_PIN_PL_LEN       2


//ID_QUERY_PIN_STATUS
//
#define QUERY_POS_PIN_PL_LEN             1


//ID_CONFIG_PIN_PARAMS
//
#define CONFIG_POS_PIN_PARAMS_PIN_SPEED(X,Y)        ( (X),(Y) ) // 2 bytes
#define CONFIG_POS_PIN_PARAMS_PIN_CNT(X,Y)          ( (X),(Y) ) // 2 bytes
#define CONFIG_POS_PIN_PARAMS_UNPIN_SPEED(X,Y)      ( (X),(Y) ) // 2 bytes
#define CONFIG_POS_PIN_PARAMS_UNPIN_CNT(X,Y)        ( (X),(Y) ) // 2 bytes
#define CONFIG_POS_PIN_PARAMS_UNPIN_DISTANCE(X,Y)   ( (X),(Y) ) // 2 bytes
#define CONFIG_POS_PIN_PARAMS_PL_LEN                11


//ID_CONFIG_NAV_MODE
//
#define CONFIG_NAV_MODE_CAR                       0x00
#define CONFIG_NAV_MODE_PEDESTRIAN                0x01
#define CONFIG_NAV_MODE_UPDATE_SRAM               0x00
#define CONFIG_NAV_MODE_UPDATE_SRAM_FLASH         0x01
#define CONFIG_NAV_MODE_PL_LEN                    3


//ID_QUERY_NAV_MODE
//
#define QUERY_NAV_MODE_PL_LEN                     1


//ID_CONFIG_1PPS_MODE
//
#define CONFIG_1PPS_MODE_OFF                      0x00 
#define CONFIG_1PPS_MODE_ON_3SV                   0x01 //on when fixed to 3 SVs
#define CONFIG_1PPS_MODE_ON_1SV                   0x02 //on when fixed to 1 SV
#define CONFIG_1PPS_MODE_UPDATE_SRAM              0x00
#define CONFIG_1PPS_MODE_UPDATE_SRAM_FLASH        0x01
#define CONFIG_1PPS_MODE_PL_LEN                   3


//ID_QUERY_1PPS_MODE
//
#define QUERY_1PPS_MODE_PL_LEN                    1






/*******************************************************
 *
 * RESPONSE MESSAGES i.e. HOST CONTROLLER <- GPS RECEIVER
 *
 ******************************************************/

//System Messages
#define RES_ID_STATUS_SW_VERSION  0x80 //software revivison
#define RES_ID_STATUS_SW_CRC      0x81 //software CRC 
#define RES_ID_STATUS_ACK         0x83 //ACK to a successful input message
#define RES_ID_STATUS_NACK        0x84 //NACK to unsuccessful input message
#define RES_ID_STATUS_PIN_INFO    0x86 //position update rate

//GPS Messages
#define RES_ID_GET_EPH_DATA       0xB1 //get ephemeris data          
#define RES_ID_STATUS_DATUM       0xAE //datum used by GPS receiver
#define RES_ID_STATUS_WAAS        0xB3 //WAAS status of GPS receiver
#define RES_STATUS_PIN            0xB4 //status of pinning position
#define RES_STATUS_NAV            0xB5 //navigation mode of GPS
#define RES_STATUS_1PPS           0xB6 //1PPS mode of GPS

//ID_STATUS_SW_VERSION
//
#define STATUS_SW_VERSION_PL_LEN   14
#define ID_STATUS_SW_VERSION      0x80 //software revivison

//ID_STATUS_SW_CRC
//
#define STATUS_SW_CRC_PL_LEN       4
#define ID_STATUS_SW_CRC          0x81 //software CRC 

//ID_STATUS_ACK
//
#define STATUS_ACK_PL_LEN          2
#define ID_STATUS_ACK             0x83 //ACK to a successful input message

//ID_STATUS_NACK
//
#define STATUS_NACK_PL_LEN         2
#define ID_STATUS_NACK            0x84 //NACK to unsuccessful input message


//ID_STATUS_PIN_INFO
//
#define STATUS_PIN_INFO_PL_LEN     2
#define ID_STATUS_PIN_INFO        0x86 //position update rate

//ID_EPH_DATA_GET
//
#define STATUS_GET_EPH_DATA_PL_LEN 87

//GPS Messages

//ID_STATUS_DATUM
//
#define STATUS_DATUM_PL_LEN        3
#define ID_STATUS_DATUM           0xAE //datum used by GPS receiver

//ID_STATUS_WAAS
//
#define STATUS_WAAS_PL_LEN         2
#define ID_STATUS_WAAS            0xB3 //WAAS status of GPS receiver

//ID_STATUS_PIN
//
#define STATUS_POS_PIN_PL_LEN      2
#define ID_STATUS_PIN             0xB4 //status of pinning position

//ID_STATUS_NAV
//
#define STATUS_NAV_MODE_PL_LEN     2
#define ID_STATUS_NAV             0xB5 //navigation mode of GPS

//ID_STATUS_1PPS
//
#define STATUS_1PPS_MODE_PL_LEN    2
#define ID_STATUS_1PPS            0xB6 //1PPS mode of GPS


int(*const usart_rx_tx_table[VENUS_READ_WRITE+1])();

#endif

