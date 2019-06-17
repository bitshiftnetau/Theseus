/**************************************************
 *
 *   \_____            \_____
 *       \_____            \_____
 *          \_____            \_____
 *             \_____            \_____
 *                /_____            /_____
 *             /_____            /_____
 *          /_____            /_____
 *       /_____            /_____
 *   /_____            /_____
 *      
 *   bitshift.net.au 
 *  
 *
 *  This file serves as a skeleton header library for the 
 *  SkyTrak Venus638 GPS Reciever. The programmer will have 
 *  to fill in the gaps where no values are actually defined. 
 *  
 *  This file covers all available functionality as stated in
 *  the datasheet, however no ROM or flash programming logic
 *  has been considered here nor provided by the vendor. 
 *
 *  The chip is capable of a sleep mode through external components, 
 *  I refer you to the datasheet to view the specific regulators.
 *  
 *  As for control and initialization of the unit, SkyTraq have 
 *  provided a binary message interface which this library
 *  encapsulates.
 *
 *  KEY NOTES:
 *
 *   - This device reads and writes as BigEndian, please ensure
 *     your UART/USART port is set accordingly
 *   - Default baud rate is 115200
 *   - Basic hookup and usage is simple serial and power
 *   - If you want to store logs, best option is external flash
 *     as internal is only accessible via proprietary tools
 *     or rolling your own accoring to the binary message protocol
 *     found in this file.
 *   - 
 *   
 *
 *  For further details, please see the datasheets and application 
 *  notes within this repo.
 *  
 *  Copyright (C) 2019 Aidan Millar-Powell aka medicineman25
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 * 
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <https://www.gnu.org/licenses/>.
 *
 *
 *
 **************************************************/

#ifndef VENUS638_ADAPTOR_H_
#define VENUS638_ADAPTOR_H_

#include <stdint.h>

#include "venus638.h"

int venus638_Init(void* host_object, int(*host_usart)(), void* ext_dev_object);
int venus638_RegDump(void* host_object, int(*host_usart)(), void* ext_dev_object);
int venus638_Reset(void* host_object, int(*host_usart)(), void* ext_dev_object);
int venus638_Off(void* host_object, int(*host_usart)(), void* ext_dev_object);
int venus638_Data(void* host_object, int(*host_usart)(), void* ext_dev_object, uint32_t read_write);
int venus638_Wakeup(void* host_object, int(*host_usart)(), void* ext_dev_object);
int venus638_Sleep(void* host_object, int(*host_usart)(), void* ext_dev_object);
int venus638_ModeLevel(void* host_object, int(*host_usart)(), void* ext_dev_object);
int venus638_QueryReg(void* host_object, int(*host_usart)(), void* ext_dev_object, void* config_register);
int venus638_ConfigReg(void* host_object, int(*host_usart)(), void* ext_dev_object, void* config_register);

#endif
