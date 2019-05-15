#ifndef CONFIG_VENUS638_H_
#define CONFIG_VENUS638_H_

#include "venus638.h"

extern VENUS_message_io venus_message; 
extern VENUS_response_store venus_response;
extern VENUS_nmea_store venus_nmea;
extern VENUS_config venus_config;
extern MPI_ext_dev venus638;

#ifdef VENUS_CONFIG_VA_INDEX
  VENUS_CONFIG_INDEX(0)
#endif

#endif
