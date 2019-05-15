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
#endif

#ifdef DW1000
  #include "config_dw1000.h"
#endif

#ifdef VENUS638
  #include "config_venus638.h"
#endif



/******************************************************************
 *
 *              PUT YOUR INTERRUPT HANLDERS HERE!!!
 *
 *****************************************************************/


#endif


