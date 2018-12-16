#include "input.h"

#include <exec/types.h>

/*--------------------------------------------------------------------------*/

#define KEY_ESC 0x45 

static UBYTE keys[128];

/*--------------------------------------------------------------------------*/

void InputSetKeys(UWORD msgCode)
{
	keys[msgCode & 0x7f] = msgCode & 0x80;
}

/*--------------------------------------------------------------------------*/

BOOL InputIsExitToOsPressed(void)
{
	if (keys[KEY_ESC])
	{
		return TRUE;
	}

	return FALSE;
}

/*--------------------------------------------------------------------------*/
