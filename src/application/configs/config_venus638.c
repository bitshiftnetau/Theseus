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

#include "mpi_port.h"
#include "mpi_types.h"

#include "config_venus638.h"

#include "venus638.h"
#include "venus638_adaptor.h"

register_enum venus_config_query;

VENUS_message_io venus_message; 
VENUS_response_store venus_response;
VENUS_nmea_store venus_nmea;

/*
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
*/

VENUS_op_mode venus_op_mode = nmea;
VENUS_config venus_config;

MPI_ext_dev venus638 = {

  ._interface = {
  
    ._dev_init = &venus638_Init,
    ._dev_reg_dump = &venus638_RegDump,
    ._dev_data = &venus638_Data,
    ._dev_config_reg = &venus638_ConfigReg,
    ._dev_query_reg = &venus638_QueryReg,
    ._dev_wakeup = &venus638_Wakeup,
    ._dev_sleep = &venus638_Sleep,
    ._dev_mode_level = &venus638_ModeLevel,
    ._dev_reset = &venus638_Reset,
    ._dev_off = &venus638_Off

  },
  .MPI_data = {
    &venus_message, 
    &venus_response, 
    &venus_nmea, 
    NULL
  },
  .MPI_conf = {
    &venus_config, 
    &venus_op_mode,
    NULL 
  }
};
  

