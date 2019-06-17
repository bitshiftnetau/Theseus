#ifndef CONFIG_VENUS638_H_
#define CONFIG_VENUS638_H_

#include "venus638.h"

extern VENUS_message_io venus_message; 
extern VENUS_response_store venus_response;
extern VENUS_nmea_store venus_nmea;
extern VENUS_config venus_config;
extern MPI_ext_dev venus638;

#define VENUS_MSG_INDEX   0
#define VENUS_RESP_INDEX  1
#define VENUS_NMEA_INDEX  2


#endif
