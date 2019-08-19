#include "_app_config.h"
#include "mpi_port.h"

int timer_Delay(uint32_t dlyTicks)
{

  timer0_ms_ticks = 0;
  timer0->CMD = TIMER_CMD_START;
  while(timer0_ms_ticks < dlyTicks);
  timer0->CMD = TIMER_CMD_STOP;

  return 0;
}


