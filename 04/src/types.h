#ifndef BOXO_TYPES_H
#define BOXO_TYPES_H

/*--------------------------------------------------------------------------*/
#include <exec/types.h>
#include <stdio.h>

typedef void(*PVF)(void);
typedef int(*PIF)(void);
#define ARRAY_SIZE(array)  sizeof (array) / sizeof (array[0]) 

enum ReturnCodes
{
	RT_OK = 0,
	RT_FAILED_OPEN_INTUITION,
	RT_FAILED_OPEN_GRAPHICS,
	RT_FAILED_OPEN_DATATYPES,
	RT_FAILED_OPEN_UTILITY,
	RT_FAILED_OPEN_WINDOW,
	RT_FAILED_GET_TILES,
	RT_FAILED_ALLOC_TILES_MEM,
	RT_FAILED_CREATE_TIMER_REQUEST,
	RT_FAILED_TIMER_DEVICE_OPEN,
};
/*--------------------------------------------------------------------------*/
#endif // BOXO_TYPES_H
