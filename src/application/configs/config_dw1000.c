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

/*
 * Configurations:
 *
 * - GPIO 5 + 6 sampled
 * - SPICSn needs to be active low 
 * - RSTn pin default active low, so wait for high signal (DW will de-assert on wakeup)
 * - GPIO default to input on reset, config LEDs and IRQ
 * - check PLL is locked
 *
 *
 */

#include <stddef.h>

#include "mpi_port.h"
#include "mpi_types.h"
#include "config_dw1000.h"

#include "dw1000_adaptor.h"
#include "dw1000_types.h"
#include "dw1000_tofCalcs.h"

//ALL DW_CONFIG MEMBERS
/*
  bool config_query_bool;
  bool ranging_mode;            //discovery, range init, or ranging
  uint8_t query_buffer[32];
  uint8_t config_buffer[32];
  uint8_t config_buffer_len;
  uint8_t query_buffer_len;

  uint8_t device_id[4]; 
  uint8_t unique_id[EUI_64_LEN]; // device id (ieee unique 64-bit identifier)
  uint8_t pan_id[PAN_ID_LEN];
  uint8_t sys_conf[SYS_CFG_LEN];
  uint8_t sys_time[SYS_TIME_LEN];
  uint8_t tx_frame_ctrl[TX_FRAME_CTRL_LEN]; 
  uint8_t tx_frame_ctrl_sub_reg_4;
  uint32_t rf_tx_delay[2];         // used to specficy a time in the future to turn on rx or send tx   
  uint8_t rx_frame_timeout[2];
  uint8_t sys_ctrl_reg[4];
  uint8_t sys_event_mask[4];
  uint8_t sys_event_status[4];
  uint8_t sys_status_sub_reg_4;
  uint8_t rx_frame_qual[8]; 
  uint8_t rx_frame_qual_sub_reg_4[4];
  uint8_t rx_time_interval[4];
  uint8_t rx_time_interval_offset[5];
  uint8_t rx_ts_sub_addr_5[4]; //first path index + first path amplitude point 1
  uint8_t rx_ts_sub_addr_9[5]; //raw timestamp 
  uint8_t tx_ts_sub_addr_5[5]; //raw timestamp
  uint8_t tx_ant_delay[2];
  uint8_t sys_state_info[5];
  uint8_t ack_resp_time[4];
  uint8_t preamble_rx_config[4];
  uint8_t tx_power_ctrl[4];
  uint8_t chan_ctrl[4];
*/

//CONFIG_TABLE members
/*
  uint8_t unique_id[EUI_64_LEN]; // device id (ieee unique 64-bit identifier)
  uint8_t pan_id[PAN_ID_LEN];
  uint8_t sys_conf[SYS_CFG_LEN];
  uint8_t tx_frame_ctrl[TX_FRAME_CTRL_LEN]; 
  uint8_t sys_ctrl_reg[4];
  uint8_t sys_event_mask[4];
  uint8_t sys_event_status[4];
  uint8_t tx_ant_delay[2];
  uint8_t sys_state_info[5];
  uint8_t ack_resp_time[4];
  uint8_t preamble_rx_config[4];
  uint8_t tx_power_ctrl[4];
  uint8_t chan_ctrl[4];
*/

DW_config dw_devconf = {
  .unique_id = {
    [0] = 0x08,
    [1] = 0x0A,
    [2] = 0x0B,
    [3] = 0x0C, 
    [4] = 0x0D,
    [5] = 0x0E,
    [6] = 0x0F,
    [7] = 0x1A
  },
  .pan_id = {
    [0] = 0x04,
    [1] = 0x0A,
    [2] = 0x0B,
    [3] = 0x0C
  },
  .sys_conf = {
    [0] = 0x04,
    [1] = 0x0A,
    [2] = 0x0B,
    [3] = 0x0C
  },
  .tx_frame_ctrl = {
    [0] = 0x04,
    [1] = 0x0A,
    [2] = 0x0B,
    [3] = 0x0C,
  },
  .rf_tx_delay = {
    [0] = 0x05,
    [1] = 0x0A,
    [2] = 0x0B,
    [3] = 0x0C, 
    [4] = 0x0D,
  },
  .sys_ctrl_reg = {
    [0] = 0x04,
    [1] = 0x0A,
    [2] = 0x0B,
    [3] = 0x0C
  },
  .sys_event_mask = {
    [0] = 0x04,
    [1] = 0x0A,
    [2] = 0x0B,
    [3] = 0x0C
  },
  .sys_event_status = {
    [0] = 0x05,
    [1] = 0x0A,
    [2] = 0x0B,
    [3] = 0x0C,
    [4] = 0x0D
  },
  .tx_ant_delay = {
    [0] = 0x02,
    [1] = 0x0A
  },
  .sys_state_info = {
    [0] = 0x05,
    [1] = 0x0A,
    [2] = 0x0B,
    [3] = 0x0C,
    [4] = 0x0D
  },
  .ack_resp_time = {
    [0] = 0x04,
    [1] = 0x0A,
    [2] = 0x0B,
    [3] = 0x0C
  },
  .preamble_rx_config = {
    [0] = 0x04,
    [1] = 0x0A,
    [2] = 0x0B,
    [3] = 0x0C
  },
  .tx_power_ctrl = {
    [0] = 0x04,
    [1] = 0x0A,
    [2] = 0x0B,
    [3] = 0x0C
  },
  .chan_ctrl = {
    [0] = 0x04,
    [1] = 0x0A,
    [2] = 0x0B,
    [3] = 0x0C
  }
};

//The entire state of the node is controlled by the above and below objects 
//Config sets bootup state (and can be changed at runtime from a higher layer)
//Dw_nodelist is runtime state, DW_DEV_DISABLED needs to be set in order for 
//that node to be found and used as a store. This is a static memory replacement
//for NULL checking a pointer list. 

DW_nodelist dw_list = {
  .list[0 ... NODELIST_LEN -1].dev_status = DW_DEV_DISABLED,
  .list[0 ... NODELIST_LEN -1].dev_index = 0,
  .list[0 ... NODELIST_LEN -1].sequence_num = 0, 
  .list[0 ... NODELIST_LEN -1].handler_index = BLINK_INDEX,
  .list[0 ... NODELIST_LEN -1].pan_id = {0},
  .list[0 ... NODELIST_LEN -1].tag_id = {0},
  .list[0 ... NODELIST_LEN -1].short_addr = {0},
  .list[0 ... NODELIST_LEN -1].resp_delay = {0},
  .list[0 ... NODELIST_LEN -1].build_message = {0},
  .list[0 ... NODELIST_LEN -1].frame_len = 0,
  .list[0 ... NODELIST_LEN -1].frame_in = {0},
  .list[0 ... NODELIST_LEN -1].frame_out = {0},
  .frame_in = {0},
  .frame_out = {0},
  .frame_out_len = 3,
  .node_index = 0
};


MPI_ext_dev dw1000 = {

  ._interface = {

    ._dev_init = &dw_Init,
    ._dev_reg_dump = &dw_RegDump,
    ._dev_data = &dw_Data,
    ._dev_config_reg = &dw_ConfigReg,
    ._dev_query_reg = &dw_QueryReg,
    //._dev_wakeup = &dw_Wakeup,
    //._dev_sleep = &dw_Sleep,
    //._dev_mode_level = &dw_ModeLevel,
    //._dev_reset = &dw_Reset,
    //._dev_off = &dw_Off

  },
  .MPI_data = {
    &dw_list,
    NULL
  },
  .MPI_conf = {
    &dw_devconf,
    NULL
  }
  
};


#ifdef DW_CONFIG_VA_INDEX
  DW_CONFIG_INDEX(0)
#endif
