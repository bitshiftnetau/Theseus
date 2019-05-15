#ifndef CONFIG_EXAMPLE_H_
#define CONFIG_EXAMPLE_H_

#include "mpi_port.h"  // This file holds the universal device object prototypes
#include "mpi_types.h"

/*
#include "example_types.h" // This file should hold declarations for device-native data types.
                           // These datatypes will be assigned as members of the device object below

extern example_type_1 example_data_1 // Let's pretend the native datatype is a struct
*/

// If the native data type is a struct then expose the member here and declare in accompanying .c file
// However, if the native data type is an array or some other member that does not allow for instance
// declaration (like a struct, enum, or union), then declare the extern'd token at the device layer 
// and define in the config_example.c file.

#endif 
