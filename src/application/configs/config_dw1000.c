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



/*
  DW_config_index_table config_index;
  DW_config_index_table query_index;
  bool config_query_bool;
  bool ranging_mode;            //discovery or twr phase
  uint8_t query_buffer[16];
  uint8_t config_buffer[16];
  uint32_t config_buffer_len;
  uint32_t query_buffer_len;
  uint32_t device_id[EUI_64_LEN]; // device id (ieee unique 64-bit identifier)
  uint32_t part_id;             // part id ???
  uint32_t lot_id;              // lot id ???
  uint32_t pan_id[2];
  uint32_t channel;              // added chan here - used in the reading of acc
  uint32_t otp_rev;              // otp revision number (read during initialisation)
  uint32_t tx_fctrl;            // keep tx_fctrl register config
  uint32_t rf_rx_delay[2];         // rf delay (delay though the rf blocks before the signal comes out of the antenna)
  uint32_t rf_tx_delay[2];         // rf delay (delay though the rf blocks before the signal comes out of the antenna)
  uint32_t ant_delay;           // antenna delay read from otp 64 prf value is in high 16 bits and 16m prf in low 16 bits
  uint32_t xtrim;               // xtrim value read from otp
  uint32_t dbl_buff_on;          // double rx buffer mode flag
  uint32_t sys_config_reg;     // local copy of system config register
  uint32_t tx_pow_config[12];   // stores the tx power configuration read from otp (6 channels consecutively with prf16 then 64, e.g. ch 1 prf16 is index 0 and 64 index 1)
   int prf_index;               //prf index ???
  uint32_t ldo_tune_low32;      //low 32 bits of ldo tune value
  uint32_t long_frames;  // flag in non-standard long frame mode
*/

DW_config dw_devconf = {
  .unique_id = {
    [0] = 0x48,
    [1] = 0x32,
    [2] = 0x3E,
    [3] = 0x8F, 
    [4] = 0xAC,
    [5] = 0x3B,
    [6] = 0xA8,
    [7] = 0x81
  }
};


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
    ._dev_wakeup = &dw_Wakeup,
    ._dev_sleep = &dw_Sleep,
    ._dev_mode_level = &dw_ModeLevel,
    ._dev_reset = &dw_Reset,
    ._dev_off = &dw_Off

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
