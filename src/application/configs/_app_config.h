#ifndef _APP_CONFIG_H
#define _APP_CONFIG_H

/*
 * This is a simple file to configure a project. The configuration 
 * file, pertanent to a device, should be included here with compiler
 * flags.
 *
 */

#ifdef EFM32ZG222F32
  #include "config_efm32zg222f32.h"
  #include "efm32zg222f32_adaptor.h"
  #include "efm32zg_types_HAL.h"
#endif

#ifdef DW1000
  #include "config_dw1000.h"
  #include "dw1000_adaptor.h"
  #include "dw1000_types.h"
#endif

#ifdef VENUS638
  #include "config_venus638.h"
  #include "venus638_adaptor.h"
#endif



/******************************************************************
 *
 *              PUT YOUR INTERRUPT HANLDERS HERE!!!
 *
 *****************************************************************/


#endif


