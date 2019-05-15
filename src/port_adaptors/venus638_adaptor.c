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

#include <stdio.h>
#include <stdint.h>

#include "venus638.h"
#include "mpi_port.h"

/**********************************************************
 *
 * TODO: Change all struct pointer parameters to uin32_t* 
 * array where you are calling the function from another layer
 *
 *********************************************************/

/*
int venus638_Init(void* host_object, int read_write, int(*host_usart)(), void* ext_dev_object){

  MPI_ext_dev* venus_object = (MPI_ext_dev*)ext_dev_object;
  VENUS_message_io* venus_message = (VENUS_message_io*)venus_object->MPI_data[VENUS_MESSAGE_INDEX];

  for(int i = 0; i < 11; i++){
      venus_message->message_id = venus_query_lookup_table[i]; 
      venus638_Tx(host_object, host_usart, ext_dev_object); 
  }

  return EXIT_SUCCESS;
}

int venus638_RegDump(void* host_object, int read_write, int(*host_usart)(), void* ext_dev_object){

  MPI_ext_dev* venus_object = (MPI_ext_dev*)ext_dev_object;
  VENUS_message_io* venus_message = (VENUS_message_io*)venus_object->MPI_data[VENUS_MESSAGE_INDEX];

  for(int i = 0; i < 11; i++){
      venus_message->message_id = venus_query_lookup_table[i]; 
      venus638_Rx(host_object, host_usart, ext_dev_object); 
  }

  return EXIT_SUCCESS;
}

int venus638_ConfigReg(void* host_object, int reg_index, int(*host_usart)(), void* ext_dev_object){
  
  MPI_ext_dev* venus_object = (MPI_ext_dev*)ext_dev_object;
  VENUS_message_io* venus_message = (VENUS_message_io*)venus_object->MPI_data[VENUS_MESSAGE_INDEX];

  venus_message->message_id = venus_query_lookup_table[reg_index];
  return venus638_Tx(host_object, host_usart, ext_dev_object);
}

int venus638_QueryReg(void* host_object, int reg_index, int (*host_usart)(), void* ext_dev_object){
  
  MPI_ext_dev* venus_object = (MPI_ext_dev*)ext_dev_object;
  VENUS_message_io* venus_message = (VENUS_message_io*)venus_object->MPI_data[VENUS_MESSAGE_INDEX];

  venus_message->message_id = venus_query_lookup_table[reg_index];
  return venus638_Rx(host_object, host_usart, ext_dev_object);
}

int venus638_Data(void* host_object, int reg_index, int(*host_usart)(), void* ext_dev_object){

  MPI_ext_dev* venus_object = (MPI_ext_dev*)ext_dev_object;
  VENUS_message_io* venus_message = (VENUS_message_io*)venus_object->MPI_data[VENUS_MESSAGE_INDEX];

  return venus638_Rx(host_object, host_usart, ext_dev_object);
}


int venus638_Reset(void* host_object, int read_write, int(*host_usart)(), void* ext_dev_object){

  MPI_ext_dev* venus_object = (MPI_ext_dev*)ext_dev_object;
  VENUS_message_io* venus_message = (VENUS_message_io*)venus_object->MPI_data[VENUS_MESSAGE_INDEX];

  //call to comm jump table and 
  //use tx function to send reset

  return EXIT_SUCCESS;
}

int venus638_Off(void* host_object, int read_write, int(*host_usart)(), void* ext_dev_object){

  MPI_ext_dev* venus_object = (MPI_ext_dev*)ext_dev_object;
  VENUS_message_io* venus_message = (VENUS_message_io*)venus_object->MPI_data[VENUS_MESSAGE_INDEX];

  //call to comm jump table and
  //use tx function to send off
  //also cut power to device

  return EXIT_SUCCESS;
}

int venus638_Sleep(void* host_object, int read_write, int(*host_usart)(), void* ext_dev_object){

  MPI_ext_dev* venus_object = (MPI_ext_dev*)ext_dev_object;
  VENUS_message_io* venus_message = (VENUS_message_io*)venus_object->MPI_data[VENUS_MESSAGE_INDEX];

  //call to comm jump table and 
  //use tx function to send sleep 

  return EXIT_SUCCESS;
}

int venus638_Wakeup(void* host_object, int read_write, int(*host_usart)(), void* ext_dev_object){

  MPI_ext_dev* venus_object = (MPI_ext_dev*)ext_dev_object;
  VENUS_message_io* venus_message = (VENUS_message_io*)venus_object->MPI_data[VENUS_MESSAGE_INDEX];

  //call to comm jump table and 
  //use tx function to send wakeup

  return EXIT_SUCCESS;
}

int venus638_ModeLevel(void* host_object, int read_write, int(*host_usart)(), void* ext_dev_object){

  MPI_ext_dev* venus_object = (MPI_ext_dev*)ext_dev_object;
  VENUS_message_io* venus_message = (VENUS_message_io*)venus_object->MPI_data[VENUS_MESSAGE_INDEX];

  //call to comm jump table and 
  //use tx function to send mode level

  return EXIT_SUCCESS;
}
*/

