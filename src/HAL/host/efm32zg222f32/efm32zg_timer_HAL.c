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
 
#include <stdlib.h>
#include <stdio.h>

#include "efm32zg_timer_HAL.h"
#include "efm32zg_types_HAL.h"

/*
 * Registers
 *
 * ctrl     RWC
 * cmd      W1
 * status   R
 * ien      RWC
 * ifr      R
 * ifs      W1
 * ifc      W1
 * top      RWHC
 * topb     RWC
 * cnt      RWHC
 * route    RWC
 * cc0_ctrl RWC
 * cc0_ccv  RWC
 * cc0_ccvp R
 * cc0_ccvb RWHC
 * cc1_ctrl RWC
 * cc1_ccv  RWC
 * cc1_ccvp R
 * cc1_ccvb RWHC
 * cc2_ctrl RWC
 * cc2_ccv  RWC
 * cc2_ccvp R
 * cc2_ccvb RWHC
 *
 */

int(* timer_ctrl_table[TIMER_READ_WRITE_CLEAR])();
int(* timer_ien_table[TIMER_READ_WRITE_CLEAR])();
int(* timer_ifrsc_table[TIMER_READ_WRITE_CLEAR])();
int(* timer_top_table[TIMER_READ_WRITE_CLEAR])();
int(* timer_topb_table[TIMER_READ_WRITE_CLEAR])();
int(* timer_cnt_table[TIMER_READ_WRITE_CLEAR])();
int(* timer_route_table[TIMER_READ_WRITE_CLEAR])();
int(* timer_cc0_ctrl_table[TIMER_READ_WRITE_CLEAR])();
int(* timer_cc0_ccv_table[TIMER_READ_WRITE_CLEAR])();
int(* timer_cc0_ccvb_table[TIMER_READ_WRITE_CLEAR])();
int(* timer_cc1_ctrl_table[TIMER_READ_WRITE_CLEAR])();
int(* timer_cc1_ccv_table[TIMER_READ_WRITE_CLEAR])();
int(* timer_cc1_ccvb_table[TIMER_READ_WRITE_CLEAR])();
int(* timer_cc2_ctrl_table[TIMER_READ_WRITE_CLEAR])();
int(* timer_cc2_ccv_table[TIMER_READ_WRITE_CLEAR])();
int(* timer_cc2_ccvb_table[TIMER_READ_WRITE_CLEAR])();

int(* timer_cc0_ccvp_table[1])();
int(* timer_cc1_ccvp_table[1])();
int(* timer_cc2_ccvp_table[1])();
int(* timer_cmd_table[1])();
int(* timer_status_table[1])();


int (*const *const timer_config_table[PERIPH_REGISTER_TABLE_MEMBERS])() = {
  timer_ctrl_table,
  timer_ien_table,
  timer_ifrsc_table,
  timer_top_table,
  timer_topb_table,
  timer_cnt_table,
  timer_route_table,
  timer_cc0_ctrl_table,
  timer_cc0_ccv_table,
  timer_cc0_ccvb_table,
  timer_cc1_ctrl_table,
  timer_cc1_ccv_table,
  timer_cc1_ccvb_table,
  timer_cc2_ctrl_table,
  timer_cc2_ccv_table,
  timer_cc2_ccvb_table,
  NULL,
  timer_cc0_ccvp_table,
  timer_cc1_ccvp_table,
  timer_cc2_ccvp_table,
  timer_cmd_table,
  timer_status_table
};


int zg_timerCtrlRead(TIMER_periphconf* MPI_conf){
	MPI_conf->ctrl = timer0->CTRL;
	return 0;
}

int zg_timerCtrlWrite(TIMER_periphconf* MPI_conf){
	timer0->CTRL |= MPI_conf->ctrl;
	return 0;
}

int zg_timerCtrlClr(TIMER_periphconf* MPI_conf){
	timer0->CTRL &= ~MPI_conf->ctrl;
	return 0;
}

int zg_timerCmdWrite(TIMER_periphconf* MPI_conf){
	timer0->CMD |= MPI_conf->cmd;
	return 0;
}

int zg_timerStatusRead(TIMER_periphconf* MPI_conf){
	MPI_conf->status = timer0->STATUS;
	return 0;
}

int zg_timerIenRead(TIMER_periphconf* MPI_conf){
	MPI_conf->ien = timer0->IEN;
	return 0;
}

int zg_timerIenWrite(TIMER_periphconf* MPI_conf){
	timer0->IEN |= MPI_conf->ien;
	return 0;
}

int zg_timerIenClr(TIMER_periphconf* MPI_conf){
	timer0->IEN &= ~MPI_conf->ien;
	return 0;
}

int zg_timerIfrRead(TIMER_periphconf* MPI_conf){
	MPI_conf->ifr = timer0->IF;
	return 0;
}

int zg_timerIfsWrite(TIMER_periphconf* MPI_conf){
	timer0->IFS |= MPI_conf->ifs;
	return 0;
}

int zg_timerIfcClr(TIMER_periphconf* MPI_conf){
	timer0->IFC &= ~MPI_conf->ifc;
	return 0;
}

int zg_timerTopRead(TIMER_periphconf* MPI_conf){
	MPI_conf->top = timer0->TOP;
	return 0;
}

int zg_timerTopWrite(TIMER_periphconf* MPI_conf){
	timer0->TOP |= MPI_conf->top;
	return 0;
}

int zg_timerTopClr(TIMER_periphconf* MPI_conf){
	timer0->TOP &= ~MPI_conf->top;
	return 0;
}

int zg_timerTopbRead(TIMER_periphconf* MPI_conf){
	MPI_conf->topb = timer0->TOPB;
	return 0;
}

int zg_timerTopbWrite(TIMER_periphconf* MPI_conf){
	timer0->TOPB |= MPI_conf->topb;
	return 0;
}

int zg_timerTopbClr(TIMER_periphconf* MPI_conf){
	timer0->TOPB &= ~MPI_conf->topb;
	return 0;
}

int zg_timerCntRead(TIMER_periphconf* MPI_conf){
	MPI_conf->cnt = timer0->CNT;
	return 0;
}

int zg_timerCntWrite(TIMER_periphconf* MPI_conf){
	timer0->CNT |= MPI_conf->cnt;
	return 0;
}

int zg_timerCntClr(TIMER_periphconf* MPI_conf){
	timer0->CNT &= ~MPI_conf->cnt;
	return 0;
}

int zg_timerRouteRead(TIMER_periphconf* MPI_conf){
	MPI_conf->route = timer0->ROUTE;
	return 0;
}

int zg_timerRouteWrite(TIMER_periphconf* MPI_conf){
	timer0->ROUTE |= MPI_conf->route;
	return 0;
}

int zg_timerRouteClr(TIMER_periphconf* MPI_conf){
	timer0->ROUTE &= ~MPI_conf->route;
	return 0;
}

int zg_timerCc0_ctrlRead(TIMER_periphconf* MPI_conf){
	MPI_conf->cc0_ctrl = timer0->CC[TIMER_CHANNEL_0].CTRL;
	return 0;
}

int zg_timerCc0_ctrlWrite(TIMER_periphconf* MPI_conf){
	timer0->CC[TIMER_CHANNEL_0].CTRL |= MPI_conf->cc0_ctrl;
	return 0;
}

int zg_timerCc0_ctrlClr(TIMER_periphconf* MPI_conf){
	timer0->CC[TIMER_CHANNEL_0].CTRL &= ~MPI_conf->cc0_ctrl;
	return 0;
}

int zg_timerCc0_ccvRead(TIMER_periphconf* MPI_conf){
	MPI_conf->cc0_ccv = timer0->CC[TIMER_CHANNEL_0].CCV;
	return 0;
}

int zg_timerCc0_ccvWrite(TIMER_periphconf* MPI_conf){
	timer0->CC[TIMER_CHANNEL_0].CCV |= MPI_conf->cc0_ccv;
	return 0;
}

int zg_timerCc0_ccvClr(TIMER_periphconf* MPI_conf){
	timer0->CC[TIMER_CHANNEL_0].CCV &= ~MPI_conf->cc0_ccv;
	return 0;
}

int zg_timerCc0_ccvbRead(TIMER_periphconf* MPI_conf){
	MPI_conf->cc0_ccvp = timer0->CC[TIMER_CHANNEL_0].CCVB;
	return 0;
}

int zg_timerCc0_ccvbWrite(TIMER_periphconf* MPI_conf){
	timer0->CC[TIMER_CHANNEL_0].CCVB |= MPI_conf->cc0_ccvb;
	return 0;
}

int zg_timerCc0_ccvbClr(TIMER_periphconf* MPI_conf){
	timer0->CC[TIMER_CHANNEL_0].CCVB &= ~MPI_conf->cc0_ccvb;
	return 0;
}

int zg_timerCc1_ctrlRead(TIMER_periphconf* MPI_conf){
	MPI_conf->cc1_ctrl = timer0->CC[TIMER_CHANNEL_1].CTRL;
	return 0;
}

int zg_timerCc1_ctrlWrite(TIMER_periphconf* MPI_conf){
	timer0->CC[TIMER_CHANNEL_1].CTRL |= MPI_conf->cc1_ctrl;
	return 0;
}

int zg_timerCc1_ctrlClr(TIMER_periphconf* MPI_conf){
	timer0->CC[TIMER_CHANNEL_1].CTRL &= ~MPI_conf->cc1_ctrl;
	return 0;
}

int zg_timerCc1_ccvRead(TIMER_periphconf* MPI_conf){
	MPI_conf->cc1_ccv = timer0->CC[TIMER_CHANNEL_1].CCV;
	return 0;
}

int zg_timerCc1_ccvWrite(TIMER_periphconf* MPI_conf){
	timer0->CC[TIMER_CHANNEL_1].CCV |= MPI_conf->cc1_ccv;
	return 0;
}

int zg_timerCc1_ccvClr(TIMER_periphconf* MPI_conf){
	timer0->CC[TIMER_CHANNEL_1].CCV &= ~MPI_conf->cc1_ccv;
	return 0;
}

int zg_timerCc1_ccvbRead(TIMER_periphconf* MPI_conf){
	MPI_conf->cc1_ccvp = timer0->CC[TIMER_CHANNEL_1].CCVB;
	return 0;
}

int zg_timerCc1_ccvbWrite(TIMER_periphconf* MPI_conf){
	timer0->CC[TIMER_CHANNEL_1].CCVB |= MPI_conf->cc1_ccvb;
	return 0;
}

int zg_timerCc1_ccvbClr(TIMER_periphconf* MPI_conf){
	timer0->CC[TIMER_CHANNEL_1].CCVB &= ~MPI_conf->cc1_ccvb;
	return 0;
}

int zg_timerCc2_ctrlRead(TIMER_periphconf* MPI_conf){
	MPI_conf->cc2_ctrl = timer0->CC[TIMER_CHANNEL_2].CTRL;
	return 0;
}

int zg_timerCc2_ctrlWrite(TIMER_periphconf* MPI_conf){
	timer0->CC[TIMER_CHANNEL_2].CTRL |= MPI_conf->cc2_ctrl;
	return 0;
}

int zg_timerCc2_ctrlClr(TIMER_periphconf* MPI_conf){
	timer0->CC[TIMER_CHANNEL_2].CTRL &= ~MPI_conf->cc2_ctrl;
	return 0;
}

int zg_timerCc2_ccvRead(TIMER_periphconf* MPI_conf){
	MPI_conf->cc2_ccv = timer0->CC[TIMER_CHANNEL_2].CCV;
	return 0;
}

int zg_timerCc2_ccvWrite(TIMER_periphconf* MPI_conf){
	timer0->CC[TIMER_CHANNEL_2].CCV |= MPI_conf->cc2_ccv;
	return 0;
}

int zg_timerCc2_ccvClr(TIMER_periphconf* MPI_conf){
	timer0->CC[TIMER_CHANNEL_2].CCV &= ~MPI_conf->cc2_ccv;
	return 0;
}

int zg_timerCc2_ccvbRead(TIMER_periphconf* MPI_conf){
	MPI_conf->cc2_ccvp = timer0->CC[TIMER_CHANNEL_2].CCVB;
	return 0;
}

int zg_timerCc2_ccvbWrite(TIMER_periphconf* MPI_conf){
	timer0->CC[TIMER_CHANNEL_2].CCVB |= MPI_conf->cc2_ccvb;
	return 0;
}

int zg_timerCc2_ccvbClr(TIMER_periphconf* MPI_conf){
	timer0->CC[TIMER_CHANNEL_2].CCVB &= ~MPI_conf->cc2_ccvb;
	return 0;
}

int zg_timerCc0_ccvpRead(TIMER_periphconf* MPI_conf){
	MPI_conf->cc0_ccvp = timer0->CC[TIMER_CHANNEL_0].CCVP;
	return 0;
}

int zg_timerCc1_ccvpRead(TIMER_periphconf* MPI_conf){
	MPI_conf->cc1_ccvp = timer0->CC[TIMER_CHANNEL_1].CCVP;
	return 0;
}

int zg_timerCc2_ccvpRead(TIMER_periphconf* MPI_conf){
	MPI_conf->cc2_ccvp = timer0->CC[TIMER_CHANNEL_2].CCVP;
	return 0;
}

int(* timer_ctrl_table[TIMER_READ_WRITE_CLEAR])() = 
  {zg_timerCtrlRead, zg_timerCtrlWrite, zg_timerCtrlClr};

int(* timer_ien_table[TIMER_READ_WRITE_CLEAR])() = 
  {zg_timerIenRead, zg_timerIenWrite, zg_timerIenClr};

int(* timer_ifrsc_table[TIMER_READ_WRITE_CLEAR])() = 
  {zg_timerIfrRead, zg_timerIfsWrite, zg_timerIfcClr};

int(* timer_top_table[TIMER_READ_WRITE_CLEAR])() = 
  {zg_timerTopRead, zg_timerTopWrite, zg_timerTopClr};

int(* timer_topb_table[TIMER_READ_WRITE_CLEAR])() = 
  {zg_timerTopbRead, zg_timerTopbWrite, zg_timerTopbClr};

int(* timer_cnt_table[TIMER_READ_WRITE_CLEAR])() = 
  {zg_timerCntRead, zg_timerCntWrite, zg_timerCntClr};

int(* timer_route_table[TIMER_READ_WRITE_CLEAR])() = 
  {zg_timerRouteRead, zg_timerRouteWrite, zg_timerRouteClr};

int(* timer_cc0_ctrl_table[TIMER_READ_WRITE_CLEAR])() = 
  {zg_timerCc0_ctrlRead, zg_timerCc0_ctrlWrite, zg_timerCc0_ctrlClr};

int(* timer_cc0_ccv_table[TIMER_READ_WRITE_CLEAR])() = 
  {zg_timerCc0_ccvRead, zg_timerCc0_ccvWrite, zg_timerCc0_ccvClr};

int(* timer_cc0_ccvb_table[TIMER_READ_WRITE_CLEAR])() = 
  {zg_timerCc0_ccvbRead, zg_timerCc0_ccvbWrite, zg_timerCc0_ccvbClr};

int(* timer_cc1_ctrl_table[TIMER_READ_WRITE_CLEAR])() = 
  {zg_timerCc1_ctrlRead, zg_timerCc1_ctrlWrite, zg_timerCc1_ctrlClr};

int(* timer_cc1_ccv_table[TIMER_READ_WRITE_CLEAR])() = 
  {zg_timerCc1_ccvRead, zg_timerCc1_ccvWrite, zg_timerCc1_ccvClr};

int(* timer_cc1_ccvb_table[TIMER_READ_WRITE_CLEAR])() = 
  {zg_timerCc1_ccvbRead, zg_timerCc1_ccvbWrite, zg_timerCc1_ccvbClr};

int(* timer_cc2_ctrl_table[TIMER_READ_WRITE_CLEAR])() = 
  {zg_timerCc2_ctrlRead, zg_timerCc2_ctrlWrite, zg_timerCc2_ctrlClr};

int(* timer_cc2_ccv_table[TIMER_READ_WRITE_CLEAR])() = 
  {zg_timerCc2_ccvRead, zg_timerCc2_ccvWrite, zg_timerCc2_ccvClr};

int(* timer_cc2_ccvb_table[TIMER_READ_WRITE_CLEAR])() = 
  {zg_timerCc2_ccvbRead, zg_timerCc2_ccvbWrite, zg_timerCc2_ccvbClr};

int(* timer_cc1_ccvp_table[1])() = 
  {zg_timerCc1_ccvpRead};

int(* timer_cc2_ccvp_table[1])() = 
  {zg_timerCc2_ccvpRead};

int(* timer_cc0_ccvp_table[1])() = 
  {zg_timerCc0_ccvpRead};

int(* timer_cmd_table[1])() = 
  {zg_timerCmdWrite};

int(* timer_status_table[1])() = 
  {zg_timerStatusRead};


