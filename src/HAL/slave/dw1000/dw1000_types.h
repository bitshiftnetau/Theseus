#ifndef DW1000_TYPES_H_
#define DW1000_TYPES_H_

#include <stdint.h>
#include <stdbool.h>

#include "dw1000_regs.h"


#define DWMODE_DISCOVERY        0
#define DWMODE_RANGEINIT        1
#define DWMODE_RANGING          2

#define READ                    0
#define WRITE                   1
#define TGL                     2

#define DW_READ_WRITE           2 
#define DW_DEV_ACTIVE           1
#define DW_DEV_DISABLED         -1

#define DW_CONF_DISCOVERY_MODE  0
#define DW_CONF_RANGING_MODE    1

#define SINGLE_BYTE             0xFF
#define SINGLE_BYTE_SHIFT       8


#define STD_FRAME_LEN           127
#define EXT_FRAME_LEN           1024
#define FRAME_BUFFER_SIZE       STD_FRAME_LEN 

/*
 * NUMBER OF OCTETS REQUIRED TO WRITE FOR EACH REGISTER READ/WRITE OPERATION
 */
#define MSG_RX_REGISTER_LEN     1
#define MSG_TX_REGISTER_LEN     1


/*
 * REG IDs
 */

#define REG_IDS_LEN             40
#define SUB_EXT_ADDR_LEN        32 

#define REG_ID_
#define REG_ID_TX_BUFFER        0x09
#define REG_ID__
#define REG_ID_RX_BUFFER        0x11

#define REG_ID_RX_MARKER        0x15

#define REG_ID_TX_MARKER        0x17

#define REG_ID_RX_BUFFER_LEN    FRAME_BUFFER_SIZE
#define REG_ID_RX_MARKER_LEN    14

#define SUB_ADDR_RX_MARKER_0    0x00
#define SUB_ADDR_RX_MARKER_1    0x01
#define SUB_ADDR_RX_MARKER_2    0x02
#define SUB_ADDR_RX_MARKER_3    0x03
#define SUB_ADDR_RX_MARKER_4    0x04

// for rx/tx_maker use this len -1 
#define RX_MARKER_TOTAL_LEN     5     //five octets
#define TX_MARKER_TOTAL_LEN     5

#define T_ROUND_TOTAL_LEN       4     
#define T_REPLY_TOTAL_LEN       4

#define TS_HANDLER_TABLE_LEN    7

/*
 * config_table_len[] indexes
 */ 


#define EUI_64_LEN_INDEX                  0                  
#define PAN_ID_LEN_INDEX                  1
#define SYS_CONFIG_LEN_INDEX              2   
#define TX_FRAME_CTRL_LEN_INDEX           3
#define RF_TX_DELAY_LEN_INDEX             4
#define SYS_CTRL_REG_LEN_INDEX            5
#define SYS_EVENT_MASK_LEN_INDEX          6
#define SYS_EVENT_STATUS_LEN_INDEX        7
#define TX_ANT_DELAY_LEN_INDEX            8
#define ACK_RESP_TIME_LEN_INDEX           9
#define PREAMBLE_RX_CONFIG_LEN_INDEX      10
#define TX_POWER_CTRL_LEN_INDEX           11
#define CHAN_CTRL_LEN_INDEX               12
#define DEVICE_ID_LEN_INDEX               13
#define SYS_TIME_LEN_INDEX                14
#define RX_FRAME_TIMEOUT_LEN_INDEX        15
#define RX_FRAME_QUAL_LEN_INDEX           16
#define RX_TIME_INTERVAL_LEN_INDEX        17
#define SYS_STATE_INFO_LEN_INDEX          18


/*
 * REG ID INDEXES FOR JUMP TABLE
 */

//register id addr table
extern uint8_t dw_reg_id_table[];

//initiate length = 11 starting at 0
//regdump length = 17 starting at 0

/*
 * register ids as indexed in 'dw_reg_id_table'
 * 
  0x01, //eui
  0x03, //pan addr
  0x04, //sys cfg
  0x08, //tx frame ctrl
  0x0A, //delayed send or receive time
  0x0D, //sys ctrl reg
  0x0E, //sys event mask
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
*/

typedef enum {
  unique_id,
  pan_id,
  sys_conf,
  tx_frame_ctrl,
  rf_tx_delay,
  sys_ctrl_reg,
  sys_event_mask,
  sys_event_status,
  tx_ant_delay,
  ack_resp_time,
  preamble_rx_config,
  tx_power_ctrl,
  chan_ctrl,
  device_id,
  sys_time,
  rx_frame_timeout,
  rx_frame_qual,
  rx_time_tracking_interval,
  sys_state_info,
  //end of config/query for loop, the remaining entries are for universal access via a single enum type
  tx_buffer,
  rx_frame_info,
  rx_buffer,
  rx_time_tracking_offset,
  rx_arrival_time,
  tx_send_time,
  user_sfd,
  auto_gain_ctrl_config,
  ext_clk_sync,
  accum_read,
  gpio_ctrl,
  digi_rx_config,
  analog_rf_config,
  tx_calib,
  freq_synth_ctrl,
  aon_reg,
  otp,
  lde_ctrl,
  digi_diag,
  pwr_mgmt_sys_ctrl,
}DW_reg_id_enum;


//Make this a member of the dw_nodelist struct and the conditional 
//operand as part of building a transaction header

typedef enum {
 sub_addr_0 = 0x00,
 sub_addr_1 = 0x01,
 sub_addr_2 = 0x02,
 sub_addr_3 = 0x03,
 sub_addr_4 = 0x04,
 sub_addr_5 = 0x05,
 sub_addr_6 = 0x06,
 sub_addr_7 = 0x07,
 sub_addr_8 = 0x08,
 sub_addr_9 = 0x09,
 sub_addr_10 = 0xA,
 sub_addr_11 = 0xB,
 sub_addr_12 = 0xC,
 sub_addr_13 = 0xD,
 sub_addr_14 = 0xE,
 sub_addr_15 = 0xF,
 sub_addr_16 = 0x10,
 sub_addr_17 = 0x11,
 sub_addr_18 = 0x12,
 sub_addr_19 = 0x13,
 sub_addr_20 = 0x14,
 sub_addr_21 = 0x15,
 sub_addr_22 = 0x16,
 sub_addr_23 = 0x17,
 sub_addr_24 = 0x18,
 sub_addr_25 = 0x19,
 sub_addr_26 = 0x1A,
 sub_addr_27 = 0x1B,
 sub_addr_28 = 0x1C,
 sub_addr_29 = 0x1D,
 sub_addr_30 = 0x1E,
 sub_addr_31 = 0x1F,
 sub_addr_32 = 0x20
}DW_sub_addr_enum;


typedef enum {
 ext_addr_0 = 0x00,
 ext_addr_1 = 0x01,
 ext_addr_2 = 0x02,
 ext_addr_3 = 0x03,
 ext_addr_4 = 0x04,
 ext_addr_5 = 0x05,
 ext_addr_6 = 0x06,
 ext_addr_7 = 0x07,
 ext_addr_8 = 0x08,
 ext_addr_9 = 0x09,
 ext_addr_10 = 0xA,
 ext_addr_11 = 0xB,
 ext_addr_12 = 0xC,
 ext_addr_13 = 0xD,
 ext_addr_14 = 0xE,
 ext_addr_15 = 0xF,
 ext_addr_16 = 0x10,
 ext_addr_17 = 0x11,
 ext_addr_18 = 0x12,
 ext_addr_19 = 0x13,
 ext_addr_20 = 0x14,
 ext_addr_21 = 0x15,
 ext_addr_22 = 0x16,
 ext_addr_23 = 0x17,
 ext_addr_24 = 0x18,
 ext_addr_25 = 0x19,
 ext_addr_26 = 0x1A,
 ext_addr_27 = 0x1B,
 ext_addr_28 = 0x1C,
 ext_addr_29 = 0x1D,
 ext_addr_30 = 0x1E,
 ext_addr_31 = 0x1F,
 ext_addr_32 = 0x20
}DW_ext_addr_enum;


/*
 * INDEXES
 */

// FRAME INDEXES + LENGTHS

#define BLINK_FRAME_LEN                         12
#define RANGE_FRAME_LEN                         22
#define POLL_RESP_FINAL_FRAME_LEN               20

#define RANGE_PAN_ID_INDEX                      3
#define POLL_RESP_FINAL_PAN_ID_INDEX            3

#define BLINK_DEST_ADDR_INDEX                   2
#define RANGE_DEST_ADDR_INDEX                   5
#define POLL_RESP_FINAL_DEST_ADDR_INDEX         5

#define BLINK_SRC_ADDR_INDEX                    2
#define RANGE_SRC_ADDR_INDEX                    13
#define POLL_RESP_FINAL_SRC_ADDR_INDEX          7

#define RANGE_MSG_INDEX                         15
#define POLL_RESP_FINAL_MSG_INDEX               9

#define BLINK_SHORT_ADDR_INDEX                  2
#define BLINK_SHORT_ADDR_LEN                    2
#define BLINK_SRC_ADDR_LEN                      8
#define RANGE_PAN_ID_LEN                        2
#define RANGE_DEST_ADDR_LEN                     8
#define RANGE_SRC_ADDR_LEN                      2
#define RANGE_MSG_LEN                           5

#define POLL_RESP_FINAL_PAN_ID_LEN              2
#define POLL_RESP_FINAL_ADDR_LEN                2

#define POLL_PAYLOAD_LEN                        1
#define RESP_PAYLOAD_LEN                        5
#define FINAL_PAYLOAD_LEN                       9



// CONFIGURATION REGISTER LENS
//length in octets
//
#define DEVICE_ID_LEN                        4 
#define SYSTEM_TIME_LEN                      5
#define RX_FRAME_TIMEOUT_LEN              2
#define RX_FRAME_QUAL_LEN                 4 
#define RX_TIME_INTERVAL_LEN              4
#define RX_TS_SUB_ADDR_5_LEN              4 
#define RX_TS_SUB_ADDR_9_LEN              5    
#define TX_TS_SUB_ADDR_5_LEN              5
#define TX_FRAME_CTRL_SUB_ADDR_4_LEN      1
#define RX_TIME_INTERVAL_OFFSET_LEN       5
#define RX_FRAME_QUAL_SUB_REG_4_LEN       4
#define SYS_EVENT_STATUS_SUB_REG_4_LEN    5      
#define SYS_STATE_INFO_LEN                5

#define SYS_CONFIG_LEN                4
#define TX_FRAME_CTRL_LEN             4
#define TX_FRAME_CTRL_SUB_REG_4_LEN   1
#define RF_TX_DELAY_LEN               5
#define SYS_CTRL_REG_LEN              4
#define SYS_EVENT_MASK_LEN            4
#define SYS_EVENT_STATUS_LEN          5
#define TX_ANT_DELAY_LEN              2
#define ACK_RESP_TIME_LEN             4
#define PREAMBLE_RX_CONFIG_LEN        4
#define TX_POWER_CTRL_LEN             4
//#define CHAN_CTRL_LEN                 4


// MESSAGE INDEXES + LENGTHS


#define RANGE_MSG_1_INDEX   16
#define RANGE_MSG_2_INDEX   18
#define RESP_MSG_1_INDEX    10
#define FINAL_MSG_1_INDEX   10
#define FINAL_MSG_2_INDEX   14

#define RANGE_MSG_WORD_LEN  2
#define RESP_MSG_WORD_LEN   4
#define FINAL_MSG_WORD_LEN  4


#define T_REPLY_LEN   4
#define T_ROUND_LEN   4

#define DW_TWR_FN_INDEX   2

#define DW_CONFIG   -1 

#ifdef DW_CONFIG_VA_INDEX 
  #define DW_CONFIG_INDEX(x)  x
#else
  #define DW_CONFIG_INDEX 0
#endif

#define NODE_LIST_INDEX   0

#define DECODE_TABLE_LEN                6
#define HANDLER_TABLE_LEN               4
#define BUILD_TABLE_LEN                 6
#define DECODE_FRAME_CTRL_TABLE_LEN     4
#define DECODE_FRAME_CTRL_TABLE_WIDTH   2 

#define EXIT_SUCCESS         0
#define ERROR                -1

#define ACTIVE_DEVICES_LEN   32

#define NODELIST_LEN          1 
#define NODELIST_LEN_COUNT    (NODELIST_LEN -1)

#define NODELIST_INDEX  0
#define CONFIG_INDEX    1
#define INCOMING_INDEX  2

#define READ_WRITE        2
#define READ_WRITE_CLEAR  3

#define DW_READ_BITMASK   0b00000000
#define DW_WRITE_BITMASK  0b00000001 << 7
#define DW_SUB_INDEX      0b00000001 << 6
#define DW_EXTENDED       0b00000001 << 7

#define DW_READ   0
#define DW_WRITE  1
#define DW_CLEAR  2

#define SUB_BOOL_INDEX  0
#define EXT_BOOL_INDEX  0

#define EXT_FALSE 0
#define EXT_TRUE  1

#define SUB_FALSE 0
#define SUB_TRUE  1

#define REG_TABLE_REG_ADDR_TABLE_INDEX  0
#define REG_TABLE_SUB_ADDR_TABLE_INDEX  1
#define REG_TABLE_EXT_ADDR_TABLE_INDEX  2

#define DECODE_TABLE_LEN                6
#define HANLDER_TABLE_LEN               4
#define BUILD_TABLE_LEN                 6
#define DECODE_FRAME_CTRL_TABLE_LEN     4
#define DECODE_FRAME_CTRL_TABLE_WIDTH   2 

#define REG_SUB_EXT   4   //jump table length for dw_frame_header_read_write_table

#define MSG_RW_BOOL_INDEX   7
#define MSG_SUB_ADDR_BOOL_INDEX  6
#define MSG_EXT_ADDR_BOOL_INDEX  7

#define MESSAGE_READ        0 << MSG_RW_BOOL_INDEX
#define MESSAGE_WRITE       1 << MSG_RW_BOOL_INDEX
#define MSG_SUB_ADDR_FALSE  0 << MSG_SUB_ADDR_BOOL_INDEX
#define MSG_SUB_ADDR_TRUE   1 << MSG_SUB_ADDR_BOOL_INDEX
#define MSG_EXT_ADDR_FALSE  0 << MSG_EXT_ADDR_BOOL_INDEX
#define MSG_EXT_ADDR_TRUE   1 << MSG_EXT_ADDR_BOOL_INDEX


#define FN_CODE_RANGE 0x20
#define FN_CODE_POLL  0x61
#define FN_CODE_RESP  0x50
#define FN_CODE_FINAL 0x69

#define FN_CODE_POLL_INDEX         0
#define FN_CODE_RESP_INDEX         1
#define FN_CODE_FINAL_INDEX        2

#define FN_CODE_BLINK_INDEX            0
#define FN_CODE_POLL_RESP_FINAL_INDEX  9
#define FN_CODE_RANGE_INDEX            14

/*
 * Universal table indexes
 */
#define BLINK_INDEX           0
#define RANGE_INDEX           1
#define POLL_RESP_FINAL_INDEX 2

#define POLL_INDEX            2
#define RESP_INDEX            3
#define FINAL_INDEX           4

#define TOF_DIST_INDEX        5

/*
 * FIX THESE DEFINES 
 */

#define FRAME_CTRL_INDEX_0  0
#define FRAME_CTRL_INDEX_1  1
#define SEQ_NUM_INDEX       2
#define PAN_ID_INDEX_0      3
#define PAN_ID_INDEX_1      4
#define RANGE_DEST_ADDR     //make a macro that calls to a relevant data point??? 
#define SHORT_ADDR_INDEX_0  15
#define SHORT_ADDR_INDEX_1  16
#define RESP_DELAY_INDEX_0  17
#define RESP_DELAY_INDEX_1  18


//OCTET 0 DEFINES
#define FRAME_CTRL_DATA_DATA     0x01 << 0
#define FRAME_CTRL_DATA_ACK      0x01 << 1
#define FRAME_CTRL_DATA_BEACON   0x01 << 2
#define FRAME_CTRL_SEC_DIS       0x00
#define FRAME_CTRL_SEC_EN        0x01 << 3
#define FRAME_CTRL_PEND          0x01 << 4
#define FRAME_CTRL_ACK           0x01 << 5
#define FRAME_CTRL_INTRA_PAN     0x01 << 6 //transmission between PANs
#define FRAME_CTRL_RESERVED      0x01 << 7 //unknown bit encoding, details found in 802.15.4e ammendment, section 5.2.2.7 "multipurpose blink frame" 


//OCTET 1 DEFINES
#define FRAME_CTRL_RESERVED_1    0x01 << 0 
#define FRAME_CTRL_RESERVED_2    0x01 << 1 
#define FRAME_CTRL_DEST_ADDR_16  0x01 << 3 
#define FRAME_CTRL_DEST_ADDR_64  (0x01 << 2) | (FRAME_CTRL_DEST_ADDR_16)
#define FRAME_CTRL_RESERVED_3    0x01 << 4
#define FRAME_CTRL_RESERVED_4    0x01 << 5
#define FRAME_CTRL_SRC_ADDR_16   0x01 << 6
#define FRAME_CTRL_SRC_ADDR_64   (0x01 << 7) | (FRAME_CTRL_SRC_ADDR_16)

/*
 * dw_frame_ctrl_table[] defines
 */
#define FC_BLINK                (FRAME_CTRL_DATA_DATA | FRAME_CTRL_DATA_BEACON | FRAME_CTRL_INTRA_PAN | FRAME_CTRL_RESERVED)
#define FC_RANGE_0              (FRAME_CTRL_DATA_DATA | FRAME_CTRL_INTRA_PAN)
#define FC_RANGE_1              (FRAME_CTRL_DEST_ADDR_64 | FRAME_CTRL_SRC_ADDR_16)
#define FC_POLL_RESP_FINAL_0    (FRAME_CTRL_DATA_DATA | FRAME_CTRL_INTRA_PAN) 
#define FC_POLL_RESP_FINAL_1    (FRAME_CTRL_DEST_ADDR_16 | FRAME_CTRL_SRC_ADDR_16)

#define FC_BLINK_INDEX  0
#define FC_RANGE_INDEX  1
#define FC_POLL_RESP_FINAL_INDEX 2

#define FC_BLINK_OCTET_0_INDEX            0
#define FC_RANGE_OCTET_0_INDEX            0
#define FC_RANGE_OCTET_1_INDEX            1
#define FC_POLL_RESP_FINAL_OCTET_0_INDEX  0
#define FC_POLL_RESP_FINAL_OCTET_1_INDEX  1

#define FC_COMMON_LEN   2


#define LDOTUNE_ADDRESS (0x04)
#define PARTID_ADDRESS (0x06)
#define LOTID_ADDRESS  (0x07)
#define VBAT_ADDRESS   (0x08)
#define VTEMP_ADDRESS  (0x09)
#define TXCFG_ADDRESS  (0x10)
#define ANTDLY_ADDRESS (0x1C)
#define XTRIM_ADDRESS  (0x1E)

#define TREK_ANTDLY_1  (0xD)
#define TREK_ANTDLY_2  (0xE)
#define TREK_ANTDLY_3  (0xF)
#define TREK_ANTDLY_4  (0x1D)

typedef int decaIrqStatus_t; // type for remembering IRQ status

#define DW_SPI_POLALPA_VARIANTS 4
#define DW_SPI_POLPHA_MASK 0xFFFFUL

#define DW_SPI_LPOL_LPHA_MASK	(DW_SPI_POLPHA_MASK & 0)
#define DW_SPI_LPOL_HPHA_MASK	(DW_SPI_POLPHA_MASK & 64)
#define DW_SPI_HPOL_LPHA_MASK	(DW_SPI_POLPHA_MASK & 128)
#define DW_SPI_HPOL_HPHA_MASK	(DW_SPI_POLPHA_MASK & 192)

#define DW_SPI_MODE_LPOL_LPHA		0
#define DW_SPI_MODE_LPHA_HPHA		1
#define DW_SPI_MODE_HPOL_LPHA		2
#define DW_SPI_MODE_HPOL_HPHA		3

#define FRAME_INDEX_TABLE  3

#define DW_DEV_TABLE_LEN    5 
#define DW_NODE_TABLE_LEN   5

#define DW_DEV_STORE   0
#define DW_DEV_CREATE  1
#define DW_DEV_DELETE  2
#define DW_DEV_SORT    3

#define DW_NODE_SEARCH    0
#define DW_NODE_CREATE    1
#define DW_NODE_DELETE    2
#define DW_NODE_SORT      3

#define NOT_YET_RANGED   -1



typedef union{
  uint32_t rx_marker;
  uint32_t tx_marker;
}DW_final_timestamp;

typedef union{
  uint32_t rx_marker;
  uint32_t tx_marker;
}DW_resp_timestamp;

typedef union{
  uint32_t rx_marker;
  uint32_t tx_marker;
}DW_poll_timestamp;

typedef union{
  uint32_t _1;
  uint32_t _2;
}DW_TroundX;

typedef union{
  uint32_t _1;
  uint32_t _2;
}DW_TreplyX;

typedef struct{
  double final_distance;
  DW_final_timestamp final;
  DW_resp_timestamp  resp;
  DW_poll_timestamp  poll;
  DW_TroundX         troundx;
  DW_TreplyX         treplyx;
}DW_TOF;


/* A device in a list of immediately registered devices */
typedef struct {
  int dev_status;
  int dev_index;
  float distance;
  uint8_t pan_id[2];
  uint8_t tag_id[8]; // <--- store the tag ID from the initial blink message, in here and re-transmit
  uint8_t short_addr[2]; //store from range init and use in ranging phase
  uint8_t resp_delay[2]; //store from range init and use in ranging phase
  uint8_t sequence_num;
  uint8_t handler_index;
  uint8_t build_message[4];
  uint8_t rx_frame_info[4]; 
  uint32_t frame_len;
  uint8_t frame_in[FRAME_BUFFER_SIZE];
  uint8_t frame_out[FRAME_BUFFER_SIZE];
  DW_TOF  tof; 
}DW_data; 

typedef struct{
  uint8_t tag_id[BLINK_SHORT_ADDR_LEN];
  float distance;
}DW_network_dev;

/* list of devices both in the process of ranging and those that are ranged */

typedef struct{
  uint8_t frame_in[FRAME_BUFFER_SIZE];
  uint8_t frame_out[FRAME_BUFFER_SIZE];
  uint32_t frame_in_len;
  uint32_t frame_out_len;
  uint32_t node_index;
  DW_data list[NODELIST_LEN];
  //DW_network_dev devices[NODELIST_LEN]; 
}DW_nodelist;

#define QUERY_BUFFER_LEN    32
#define CONFIG_BUFFER_LEN   32

/*
 * NOTE: make sure you start the enums and config tables at 1 NOT zero!!! That way we can assign 0 to the 
 * sub_addr_index member of dw_config and it will signify that there is no sub address for that regfile
 *
 */

#define CONFIG_STRUCT_MEMBERS   13 
#define QUERY_STRUCT_MEMBERS    24 

/*
  config_unique_id,
  config_pan_id,
  config_sys_conf,
  config_tx_frame_ctrl,
  config_tx_frame_ctrl_sub_reg_4,
  config_rf_tx_delay,
  config_sys_ctrl_reg,
  config_sys_event_status,
  config_tx_ant_delay,
  config_ack_resp_time,
  config_preamble_rx_config,
  config_tx_power_ctrl,
  config_chan_ctrl
*/
/*
typedef enum {
  config_unique_id,
  config_pan_id,
  config_sys_conf,
  config_tx_frame_ctrl,
  config_tx_frame_ctrl_sub_reg_4,
  config_rf_tx_delay,
  config_sys_ctrl_reg,
  config_sys_event_status,
  config_tx_ant_delay,
  config_ack_resp_time,
  config_preamble_rx_config,
  config_tx_power_ctrl,
  config_chan_ctrl
}DW_config_index_enum;
//regid for registers pertanent to config and query fns  
*/

/*
  query_dev_id,
  query_sys_time,
  query_rx_frame_timeout,
  query_rx_frame_qual,
  query_rx_time_interval,
  query_rx_ts_sub_addr_5,
  query_rx_ts_sub_addr_9,
  query_tx_ts_sub_addr_5,
  query_tx_frame_ctrl_sub_addr_4,
  query_rx_time_interval_offset,
  query_rx_frame_qual_sub_reg_4,
  query_sys_status_sub_reg_4,
  query_sys_state_info
*/
/*
typedef enum {
  query_unique_id,
  query_pan_id,
  query_sys_conf,
  query_tx_frame_ctrl,
  query_tx_frame_ctrl_sub_reg_4,
  query_rf_tx_delay,
  query_sys_ctrl_reg,
  query_sys_event_status,
  query_tx_ant_delay,
  query_ack_resp_time,
  query_preamble_rx_config,
  query_tx_power_ctrl,
  query_chan_ctrl,
  query_device_id,
  query_rx_frame_timeout,
  query_rx_frame_qual,
  query_rx_time_interval,
  query_rx_ts_sub_addr_5,
  query_rx_ts_sub_addr_9,
  query_tx_ts_sub_addr_5,
  query_tx_frame_ctrl_sub_addr_4,
  query_rx_time_interval_offset,
  query_rx_frame_qual_sub_reg_4,
  query_sys_status_sub_reg_4,
  query_sys_state_info
}DW_query_index_enum;
//regid for registers pertanent to config and query fns  
*/

typedef struct {
  DW_reg_id_enum reg_id_index;
  DW_sub_addr_enum sub_addr_index;
  DW_ext_addr_enum ext_addr_index;
  bool config_query_bool;
  bool ranging_mode;            //discovery or twr phase
  uint8_t query_buffer[32];
  uint8_t config_buffer[32];
  uint8_t config_buffer_len;
  uint8_t query_buffer_len;
  uint8_t device_id[DEVICE_ID_LEN]; 
  uint8_t unique_id[EUI_64_LEN]; // device id (ieee unique 64-bit identifier)
  uint8_t pan_id[PAN_ID_LEN];
  uint8_t sys_conf[SYS_CFG_LEN];
  uint8_t sys_time[SYS_TIME_LEN];
  uint8_t tx_frame_ctrl[TX_FRAME_CTRL_LEN]; 
  uint8_t tx_frame_ctrl_sub_reg_4;
  uint32_t rf_tx_delay[RF_TX_DELAY_LEN];         // used to specficy a time in the future to turn on rx or send tx   
  uint8_t rx_frame_timeout[RX_FRAME_TIMEOUT_LEN];
  uint8_t sys_ctrl_reg[SYS_CTRL_REG_LEN];
  uint8_t sys_event_mask[SYS_EVENT_MASK_LEN];
  uint8_t sys_event_status[SYS_EVENT_STATUS_LEN];
  uint8_t sys_status_sub_reg_4;
  uint8_t rx_frame_qual[RX_FRAME_QUAL_LEN]; 
  uint8_t rx_frame_qual_sub_reg_4[RX_FRAME_QUAL_SUB_REG_4_LEN];
  uint8_t rx_time_interval[RX_TIME_INTERVAL_LEN];
  uint8_t rx_time_interval_offset[RX_TIME_INTERVAL_OFFSET_LEN];
  uint8_t rx_ts_sub_addr_5[RX_TS_SUB_ADDR_5_LEN]; //first path index + first path amplitude point 1
  uint8_t rx_ts_sub_addr_9[RX_TS_SUB_ADDR_9_LEN]; //raw timestamp 
  uint8_t tx_ts_sub_addr_5[TX_TS_SUB_ADDR_5_LEN]; //raw timestamp
  uint8_t tx_ant_delay[TX_ANT_DELAY_LEN];
  uint8_t sys_state_info[SYS_STATE_INFO_LEN];
  uint8_t ack_resp_time[ACK_RESP_TIME_LEN];
  uint8_t preamble_rx_config[PREAMBLE_RX_CONFIG_LEN];
  uint8_t tx_power_ctrl[TX_POWER_CTRL_LEN];
  uint8_t chan_ctrl[CHAN_CTRL_LEN];
  //user-defined SFD pointer
  //AGC control pointer
  //external sync control pointer
  //Accum CIR status pointer
  //GPIO ctrl & status pointer
  //Digital rx config pointer
  //Analog rf config pointer
  //transmitter calib block pointer
  //freq synth ctrl pointer
  //AON sys ctrl pointer
  //OTP memory interface pointer
  //leading edge detectin interface pointer
  //digital diagnostics pointer
  //power management and sys ctrl pointer
}DW_config;

/*
 ** - regfile 0x01: device id (EUI)        RO (hard-coded to silicon)
 * - regfile 0x02: reserved               --
 ** - regfile 0x03: PAN                    RW
 ** - regfile 0x04: Sys config             RW
 * - regfile 0x05: reserved               --
 ** - regfile 0x06: Sys time counter       RO
 * - regfile 0x07: reserved               --
 ** - regfile 0x08: transmit frame ctrl    RW
 **    - regfile 0x08:04: IFSDELAY          
 MEMBER IS IN DW_DATA - regfile 0x09: tx data buffer         W

 ** - regfile 0x0A: Delayed tx or rx time  RW
 * - regfile 0x0B: reserved               --
 ** - regfile 0x0C: Rx frame wait timeout  RW
 ** - regfile 0x0D: Sys ctrl reg           SRW
 ** - regfile 0x0E: sys event mask         RW
 ** - regfile 0x0F: Sys status:    
 **    - Receiver Reed-solomon correction status: bit 0 reg:0F:04
 **    - Receiver preamble rejection:             bit 1 reg:0F:04
 **    - Tranmit power up time error:             bit 2 reg:0F:04 
 MEMBER IS IN DW_DATA * - regfile 0x10: rx frame info          ROD
 MEMBER IS IN DW_DATA * - regfile 0x11: rx data buffer         ROD
 ** - regfile 0x12: Rx frame quality info:
 **    - first path amplitude point 3:            bits 15-0  reg:12:04
 **    - channel impulse response power:          bits 31-16 reg:12:04
 ** - regfile 0x13: rx time interval       ROD
 ** - regfile 0x14: Receiver time tracking offset bits 6-0   reg:14:04
 MEMBER IS IN DW_DATA * - regfile 0x15: Receive time stamp:
 **    - first path index:                        bits 15-0  reg:15:05
 **    - first path amplitude point 1:            bits 31-16 reg:15:05
 **    - raw timestamp:                           bits 39-0  reg:15:09 (probably want 15:08 for 32 bit value)
 * - regfile 0x16: reserved               -- 
 MEMBER IS IN DW_DATA * - regfile 0x17: tx timestamp
 **    - tx_stamp:                                bits 39-0  reg:17:00
 **    - tx_raw:                                  bits 39-0  reg:17:05
 ** - regfile 0x18: tx antenna delay       RW
 ** - regfile 0x19: sys state info         RO
 ** - regfile 0x1A: ack & resp 19:02       RW
 ** - regfile 0x1B: reserved               --
 ** - regfile 0x1C: reserved               --
 ** - regfile 0x1D: preamble rx config     RW
 ** - regfile 0x1E: tx power ctrl          RW
 ** - regfile 0x1F: channel ctrl           RW
 ** - regfile 0x20: reserved               --
 
 -- regfile 0x21 - user defined SFD
    -- bits 0-40 hex sub-addr range: 0-28 all have sub addressable space
 * - regfile 0x22: reserved               --
 -- regfile 0x23: AGC Control
   -- Disable AGC management                    bit 0      reg:23:02
   -- AGC_TUNE1                                 bits 0-16  reg:23:04 
   -- AGC status
      -- EDG1                                   bits 10-6  reg:23:1E
      -- EDV2                                   bits 19-11 reg:23:1E
 -- regfile 0x24 external sync control
   -- counter config                            reg:24:00 //32-bits
   -- counter capture on RMARKER                reg:24:04 //32-bits
   -- clock offset to first path 1GHz counter   reg:24:08 //32-bits
 -- regfile 0x25: accumulator CIR               octets 4063-0 correspond to sub-addr 4063-0
 -- regfile 0x26: GPIO ctrl and status:         reg:26:00-28
   - MODE  00
   - DIR   08
   - DOUT  0C
   - IRQE  10
   - ISEN  14
   - IMODE 18
   - IBES  1C
   - ICLR  20
   - IDBE  24
   - RAW   28 
 -- regfile 0x27: Digital receiver config
   - DRX_TUNE0b   02
   - DRX_TUNE1a   04
   - DRX_TUNE1b   06
   - DRX_TUNE2    08
   - DRX_SFDTOC   20
   - DRX_PRETOC   24
   - DRX_TUNE4H   26
   - RXPACC_NOSAT 2C
 -- regfile 0x28: Analog RF config 
   - RF_CONF      00
   - RF_RES1      04
   - RF_RXCTRLH   0B
   - RF_TXCTRL    0C
   - RF_RES2      10
   - RF_STATUS    2C
   - LDOTUNE      30
 * - regfile 0x29: reserved                 --
 - regfile 0x2A: transmitter calib block
   - TC_SARC      00
   - TC_SARL      03
   - TC_SARW      06
   - TC_RES2      08
   - TC_PGDELAY   0B
   - TC_PGTEST    0C
 - regfile 0x2B: freq synth control block
   - FS_RES1      00
   - FS_PLLCFG    07
   - FS_PLLTUNE   0B
   - FS_RES2      0C
   - FS_XTALT     0E
   - FS_RES3      0F
 - regfile 0x2C: Always-on system control
   - AON_WCFG     00
   - AON_CTRL     02
   - AON_RDAT     03
   - AON_ADDR     04
   - AON_CFG0     06
   - AON_CFG1     0A
 - regfile 0x2D: OTP memory interface
   - OTP_WDAT     00
   - OTP_ADDR     04
   - OTP_CTRL     06
   - OTP_STAT     08
   - OTP_RDAT     0A
   - OTP_SRDAT    0E
   - OTP_SF       12
 - regfile 0x2E: Leading Edge detection interface
   - LDE_THRESH   0000
   - LDE_CFG1     0806
   - LDE_PPINDX   1000
   - LDE_PPAMPL   1002
   - LDE_RXANTD   1804
   - LDE_CFG2     1806
   - LDE_REPC     2804
 - regfile 0x2F: digital diagnostics interface
   - EVC_CTRL     00
   - EVC_PHE      04
   - EVC_RSE      06
   - EVC_FCG      08
   - EVC_FCE      0A
   - EVC_FFR      0C
   - EVC_OVR      0E
   - EVC_STO      10
   - EVC_PTO      12
   - EVC_FWTO     14
   - EVC_TXFS     16
   - EVC_HPW      18
   - EVC_TPW      1A
   - EVC_RES1     1C
   - DIAG_TMC     24
 * - regfile 0x30: reserved               --
 * - regfile 0x31: reserved               --
 * - regfile 0x32: reserved               --
 * - regfile 0x33: reserved               --
 * - regfile 0x34: reserved               --
 * - regfile 0x35: reserved               --
 - regfile 0x36: power management and system control
   - PMSC_CTRL0   00 
   - PMSC_CTRL1   04
   - PMSC_RES1    08
   - PMSC_SNOZT   0C
   - PMSC_RES2    10
   - PMSC_TXFSEQ  26
   - PMSC_LEDC    28
 * - regfile 0x37: reserved               --
 * - regfile 0x38: reserved               --
 * - regfile 0x39: reserved               --
 * - regfile 0x3A: reserved               --
 * - regfile 0x3B: reserved               --
 * - regfile 0x3C: reserved               --
 * - regfile 0x3D: reserved               --
 * - regfile 0x3E: reserved               --
 * - regfile 0x3F: reserved               --
 *
 */


/*
 *  JUMP TABLES
 *
 */

extern uint32_t (*dw_decode_build_table[3])(); 
extern uint8_t dw_frame_ctrl_table[][2]; 
extern const uint32_t dw_fn_code_table[]; 
extern void (*config_table[])(); 
extern void (*query_table[])();









/*
typedef struct{

    uint32_t status;      //initial value of register as ISR is entered
    uint8_t  event;       //event type
    uint8_t  aatset;      //auto ACK TX bit is set
    uint16_t datalength;  //length of frame
    uint8_t  fctrl[2];    //frame control bytes
    uint8_t  dblbuff;    //set if double buffer is enabled

}dwt_callback_data_t;

typedef enum {
     CHAN_CTRL_TXCHAN_1 = 0x01,  //Selects the transmit channel 1 
     CHAN_CTRL_TXCHAN_2 = 0x02,  //Selects the transmit channel 2 
     CHAN_CTRL_TXCHAN_3 = 0x03,  //Selects the transmit channel 3 
     CHAN_CTRL_TXCHAN_4 = 0x04,  //Selects the transmit channel 4 
     CHAN_CTRL_TXCHAN_5 = 0x05,  //Selects the transmit channel 5 
     CHAN_CTRL_TXCHAN_7 = 0x07   //Selects the transmit channel 7 
}eCHAN;
*/

/*! ------------------------------------------------------------------------------------------------------------------
 * Structure typedef: dwt_config_t
 *
 * Structure for setting device configuration via dwt_configure() function
 *
 */
/*
#pragma pack(1)
typedef struct
{
    uint8_t   chan ;          //!< channel number {1, 2, 3, 4, 5, 7 }
    uint8_t   prf ;           //!< Pulse Repetition Frequency {DWT_PRF_16M or DWT_PRF_64M}

    uint8_t txPreambLength;   //!< DWT_PLEN_64..DWT_PLEN_4096
    uint8_t rxPAC ;           //!< Acquisition Chunk Size (Relates to RX preamble length)

    uint8_t txCode ;        //!< TX preamble code
    uint8_t rxCode ;        //!< RX preamble code

    uint8_t   nsSFD ;         //!< Boolean should we use non-standard SFD for better performance
    uint8_t dataRate ;        //!< Data Rate {DWT_BR_110K, DWT_BR_850K or DWT_BR_6M8}

    uint8_t phrMode ;         //!< PHR mode {0x0 - standard DWT_PHRMODE_STD, 0x3 - extended frames DWT_PHRMODE_EXT}

    uint8_t   smartPowerEn ;  //!< Smart Power enable / disable

    uint16_t sfdTO ;          //!< SFD timeout value (in symbols)

}__attribute__ ((packed))  dwt_config_t ;
#pragma pack()


typedef struct
{
    uint8_t   PGdly;
    //TX POWER
    //31:24     BOOST_0.125ms_PWR
    //23:16     BOOST_0.25ms_PWR-TX_SHR_PWR
    //15:8      BOOST_0.5ms_PWR-TX_PHR_PWR
    //7:0       DEFAULT_PWR-TX_DATA_PWR
    uint32_t  power;
}
dwt_txconfig_t ;


typedef struct
{

    uint16_t      maxNoise ;          // LDE max value of noise
    uint16_t      firstPathAmp1 ;     // Amplitude at floor(index FP) + 1
    uint16_t      stdNoise ;          // Standard deviation of noise
    uint16_t      firstPathAmp2 ;     // Amplitude at floor(index FP) + 2
    uint16_t      firstPathAmp3 ;     // Amplitude at floor(index FP) + 3
    uint16_t      maxGrowthCIR ;      // Channel Impulse Response max growth CIR
    uint16_t      rxPreamCount ;      // Count of preamble symbols accumulated
    //uint32_t        debug1;
    //uint32_t        debug2;
    double      firstPath ;         // First path index
}dwt_rxdiag_t ;


typedef struct
{
    //all of the below are mapped to a 12-bit register in DW1000
    uint16_t PHE ;                    //number of received header errors
    uint16_t RSL ;                    //number of received frame sync loss events
    uint16_t CRCG ;                   //number of good CRC received frames
    uint16_t CRCB ;                   //number of bad CRC (CRC error) received frames
    uint16_t ARFE ;                   //number of address filter errors
    uint16_t OVER ;                   //number of receiver overflows (used in double buffer mode)
    uint16_t SFDTO ;                  //SFD timeouts
    uint16_t PTO ;                    //Preamble timeouts
    uint16_t RTO ;                    //RX frame wait timeouts
    uint16_t TXF ;                    //number of transmitted frames
    uint16_t HPW ;                    //half period warn
    uint16_t TXW ;                    //power up warn

} dwt_deviceentcnts_t ;
*/








/*
// Defines for enable_clocks function
#define FORCE_SYS_XTI  0
#define ENABLE_ALL_SEQ 1
#define FORCE_SYS_PLL  2
#define READ_ACC_ON    7
#define READ_ACC_OFF   8
#define FORCE_OTP_ON   11
#define FORCE_OTP_OFF  12
#define FORCE_TX_PLL   13

#ifdef OT_CLI_NCP_APP
uint8_t read_data[150]    =   {0};
uint8_t header_write[150] =   {0};
uint8_t header_read[150]  =   {0};
#endif

#define DECA_MAX_SPI_HEADER_LENGTH   (3)   // max number of bytes in header (for formating & sizing)

#define SHORT_ADDRESS_SIZE    2    // Size of Short Mac Address 
#define EXTENDED_ADDRESS_SIZE 8    // Size of Extended Mac Address 


#define REG_DUMP (0) //set to 1 to enable register dump functions
#if (REG_DUMP == 1)
#include "string.h"
#endif


#define DWT_SUCCESS (0)
#define DWT_ERROR   (-1)

#define DWT_TIME_UNITS          (1.0/499.2e6/128.0) //!< = 15.65e-12 s

#define DWT_DEVICE_ID   (0xDECA0130)        //!< DW1000 MP device ID

//! constants for selecting the bit rate for data TX (and RX)
//! These are defined for write (with just a shift) the TX_FCTRL register
#define DWT_BR_110K     0   //!< UWB bit rate 110 kbits/s
#define DWT_BR_850K     1   //!< UWB bit rate 850 kbits/s
#define DWT_BR_6M8      2   //!< UWB bit rate 6.8 Mbits/s

//! constants for specifying the (Nominal) mean Pulse Repetition Frequency
//! These are defined for direct write (with a shift if necessary) to CHAN_CTRL and TX_FCTRL regs
#define DWT_PRF_16M     1   //!< UWB PRF 16 MHz
#define DWT_PRF_64M     2   //!< UWB PRF 64 MHz

//! constants for specifying Preamble Acquisition Chunk (PAC) Size in symbols
#define DWT_PAC8        0   //!< PAC  8 (recommended for RX of preamble length  128 and below
#define DWT_PAC16       1   //!< PAC 16 (recommended for RX of preamble length  256
#define DWT_PAC32       2   //!< PAC 32 (recommended for RX of preamble length  512
#define DWT_PAC64       3   //!< PAC 64 (recommended for RX of preamble length 1024 and up

//! constants for specifying TX Preamble length in symbols
//! These are defined to allow them be directly written into byte 2 of the TX_FCTRL register
//! (i.e. a four bit value destined for bits 20..18 but shifted left by 2 for byte alignment)
#define DWT_PLEN_4096   0x0C    //! Standard preamble length 4096 symbols
#define DWT_PLEN_2048   0x28    //! Non-standard preamble length 2048 symbols
#define DWT_PLEN_1536   0x18    //! Non-standard preamble length 1536 symbols
#define DWT_PLEN_1024   0x08    //! Standard preamble length 1024 symbols
#define DWT_PLEN_512    0x34    //! Non-standard preamble length 512 symbols
#define DWT_PLEN_256    0x24    //! Non-standard preamble length 256 symbols
#define DWT_PLEN_128    0x14    //! Non-standard preamble length 128 symbols
#define DWT_PLEN_64     0x04    //! Standard preamble length 64 symbols

//! callback events
#define DWT_SIG_RX_NOERR            0
#define DWT_SIG_TX_DONE             1       // Frame has been sent
#define DWT_SIG_RX_OKAY             2       // Frame Received with Good CRC
#define DWT_SIG_RX_ERROR            3       // Frame Received but CRC is wrong
#define DWT_SIG_RX_TIMEOUT          4       // Timeout on receive has elapsed
#define DWT_SIG_TX_AA_DONE          6       // ACK frame has been sent (as a result of auto-ACK)

#define DWT_SIG_RX_PHR_ERROR        8       // Error found in PHY Header
#define DWT_SIG_RX_SYNCLOSS         9       // Un-recoverable error in Reed Solomon Decoder
#define DWT_SIG_RX_SFDTIMEOUT       10      // Saw preamble but got no SFD within configured time
#define DWT_SIG_RX_PTOTIMEOUT       11      // Got preamble detection timeout (no preamble detected)

#define DWT_SIG_TX_PENDING          12      // TX is pending
#define DWT_SIG_TX_ERROR            13      // TX failed
#define DWT_SIG_RX_PENDING          14      // RX has been re-enabled
#define DWT_SIG_DW_IDLE             15      // DW radio is in IDLE (no TX or RX pending)

#define DWT_SFDTOC_DEF              0x1041  // default SFD timeout value

#define DWT_PHRMODE_STD             0x0     // standard PHR mode
#define DWT_PHRMODE_EXT             0x3     // DW proprietary extended frames PHR mode

// Defined constants for "mode" bitmask parameter passed into dwt_starttx() function.
#define DWT_START_TX_IMMEDIATE      0
#define DWT_START_TX_DELAYED        1
#define DWT_RESPONSE_EXPECTED       2

#define DWT_START_RX_IMMEDIATE      0
#define DWT_START_RX_DELAYED        1
#define DWT_REENABLE_ON_DLY_ERR     2               // if delayed RX failed due to "late" error then this
                                                    // flag will re-enable RX immediately if set else RX is off on function return

//frame filtering configuration options
#define DWT_FF_NOTYPE_EN            0x000           // no frame types allowed (FF disabled)
#define DWT_FF_COORD_EN             0x002           // behave as coordinator (can receive frames with no dest address (PAN ID has to match))
#define DWT_FF_BEACON_EN            0x004           // beacon frames allowed
#define DWT_FF_DATA_EN              0x008           // data frames allowed
#define DWT_FF_ACK_EN               0x010           // ack frames allowed
#define DWT_FF_MAC_EN               0x020           // mac control frames allowed
#define DWT_FF_RSVD_EN              0x040           // reserved frame types allowed

//DW1000 interrupt events
#define DWT_INT_TFRS            0x00000080          // frame sent
#define DWT_INT_LDED            0x00000400          // micro-code has finished execution
#define DWT_INT_RFCG            0x00004000          // frame received with good CRC
#define DWT_INT_RPHE            0x00001000          // receiver PHY header error
#define DWT_INT_RFCE            0x00008000          // receiver CRC error
#define DWT_INT_RFSL            0x00010000          // receiver sync loss error
#define DWT_INT_RFTO            0x00020000          // frame wait timeout
#define DWT_INT_RXOVRR          0x00100000          // receiver overrun
#define DWT_INT_RXPTO           0x00200000          // preamble detect timeout
#define DWT_INT_SFDT            0x04000000          // SFD timeout
#define DWT_INT_ARFE            0x20000000          // frame rejected (due to frame filtering configuration)


//DW1000 SLEEP and WAKEUP configuration parameters
#define DWT_LOADLDO      0x1000                      // ONW_LLDO - on wakeup load the LDO tune value
#define DWT_LOADUCODE    0x0800                      // ONW_LLDE - on wakeup load the LDE ucode
#define DWT_PRESRV_SLEEP 0x0100                      // PRES_SLEEP - on wakeup preserve sleep bit
#define DWT_LOADOPSET    0x0080                      // ONW_L64P - on wakeup load operating parameter set for 64 PSR
#define DWT_CONFIG       0x0040                      // ONW_LDC - on wakeup restore (load) the saved configurations (from AON array into HIF)
#define DWT_TANDV        0x0001                      // ONW_RADC - on wakeup run ADC to sample temperature and voltage sensor values

#define DWT_XTAL_EN      0x10                       // keep XTAL running during sleep
#define DWT_WAKE_SLPCNT  0x8                        // wake up after sleep count
#define DWT_WAKE_CS      0x4                        // wake up on chip select
#define DWT_WAKE_WK      0x2                        // wake up on WAKEUP PIN
#define DWT_SLP_EN       0x1                        // enable sleep/deep sleep functionality

//DW1000 INIT configuration parameters
#define DWT_LOADLDOTUNE   0x8
#define DWT_LOADTXCONFIG  0x4
#define DWT_LOADANTDLY    0x2
#define DWT_LOADXTALTRIM  0x1
#define DWT_LOADNONE      0x0

//DW1000 OTP operating parameter set selection
#define DWT_OPSET_64LEN   0x0
#define DWT_OPSET_TIGHT   0x1
#define DWT_OPSET_DEFLT   0x2
*/

/* dw_status is used for printing debug logs */
//uint8_t *dw_status;


#endif /* DW1000_TYPES_H_ */


