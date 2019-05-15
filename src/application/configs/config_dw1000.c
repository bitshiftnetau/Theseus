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
   

#include "mpi_port.h"
#include "mpi_types.h"

#include "config_dw1000.h"

#include "dw1000_device_api.h"
#include "dw1000_types.h"
#include "dw1000_tofCalcs.h"

DW_config dw_devconf;

DW_nodelist dw_list = {
  .list[0 ... NODELIST_LEN].dev_status = DW_DISABLED,
  .list[0 ... NODELIST_LEN].dev_index = 0,
  .list[0 ... NODELIST_LEN].sequence_number = 0, 
  .list[0 ... NODELIST_LEN].handler_index = RANGE_INDEX,
  .list[0 ... NODELIST_LEN].pan_id = {0},
  .list[0 ... NODELIST_LEN].tag_id = {0},
  .list[0 ... NODELIST_LEN].short_addr = {0},
  .list[0 ... NODELIST_LEN].resp_delay = {0},
  .list[0 ... NODELIST_LEN].build_message = {0},
  .list[0 ... NODELIST_LEN].frame_len = 0,
  .list[0 ... NODELIST_LEN].frame_in = {0},
  .list[0 ... NODELIST_LEN].frame_out = {0}
};

MPI_ext_dev dw1000 = {
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


