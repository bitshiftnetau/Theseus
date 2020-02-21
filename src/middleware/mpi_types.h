/*
 * MPI_types.h
 *
 *  Created on: Oct 5, 2018
 *      Author: access
 */

#ifndef MPI_TYPES_H_
#define MPI_TYPES_H_

#include <stdbool.h>
#include <stdint.h>

typedef int (*int_callback)();
typedef int (*int_callback_setter)(int_callback);

typedef void (*void_callback)();
typedef void (*void_callback_setter)(void_callback);

typedef char (*char_callback)();
typedef char (*char_callback_setter)(char_callback);

typedef float (*float_callback)();
typedef float (*float_callback_setter)(float_callback);

#define READ	        0
#define WRITE	        1
#define CLEAR	        2
#define TOGGLE          2
#define READWRITE       3
#define READ_WRITE_RW   4

#ifdef _MPI_TYPES_H_
#endif

#endif /* MPI_TYPES_H_ */
