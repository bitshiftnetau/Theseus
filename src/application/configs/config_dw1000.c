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

DW_config dw_devconf;
DW_nodelist dw_list;


DW_nodelist dw_list = {
  .list[0 ... NODELIST_LEN -1].dev_status = DW_DEV_DISABLED,
  .list[0 ... NODELIST_LEN -1].dev_index = 0,
  .list[0 ... NODELIST_LEN -1].sequence_num = 0, 
  .list[0 ... NODELIST_LEN -1].handler_index = RANGE_INDEX,
  .list[0 ... NODELIST_LEN -1].pan_id = {0},
  .list[0 ... NODELIST_LEN -1].tag_id = {0},
  .list[0 ... NODELIST_LEN -1].short_addr = {0},
  .list[0 ... NODELIST_LEN -1].resp_delay = {0},
  .list[0 ... NODELIST_LEN -1].build_message = {0},
  .list[0 ... NODELIST_LEN -1].frame_len = 0,
  .list[0 ... NODELIST_LEN -1].frame_in = {0},
  .list[0 ... NODELIST_LEN -1].frame_out = {0}
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


