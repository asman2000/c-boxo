#include "window.h"
#include "input.h"
#include <assert.h>

#include <proto/exec.h>
#include <proto/intuition.h>
#include <intuition/intuition.h>

/*--------------------------------------------------------------------------*/
ULONG windowSignal;

static struct Window* window = NULL;

/*--------------------------------------------------------------------------*/

int WindowInit(void)
{
	window = (struct Window*)OpenWindowTags(NULL,
		WA_Left, 0, WA_Top, 0,
		WA_Width, 320, WA_Height, 256,
		WA_Title, (ULONG)"boxo", 
		WA_Activate, TRUE, 
		WA_DragBar, TRUE, 
		WA_GimmeZeroZero, TRUE, 
		WA_IDCMP, IDCMP_RAWKEY,
		TAG_END);

	if (NULL == window)
	{
		return RT_FAILED_OPEN_WINDOW;
	}

	windowSignal = 1L << window->UserPort->mp_SigBit;

	return RT_OK;
}

/*--------------------------------------------------------------------------*/

void WindowKill(void)
{
	if (window)
	{
		CloseWindow(window);
	}
}

/*--------------------------------------------------------------------------*/

void WindowProcessSignals(void)
{
	while (TRUE)
	{
		struct IntuiMessage* msg = (struct IntuiMessage*)
					   GetMsg(window->UserPort);

		if (NULL == msg)
		{
			break;
		}

		InputSetKeys(msg->Code);

		ReplyMsg((struct Message*)msg);
	}
}

/*--------------------------------------------------------------------------*/

struct RastPort* WindowGetRastPort(void)
{
	assert(window != NULL);
	
	return window->RPort;
}

/*--------------------------------------------------------------------------*/