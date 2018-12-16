#include "window.h"
#include "input.h"

#include <proto/exec.h>

/*--------------------------------------------------------------------------*/

struct IntuitionBase* IntuitionBase;

static int Init(void);
static void Loop(void);
static void Close(void);

/*--------------------------------------------------------------------------*/

int main(void)
{
	if (0 == Init())
	{
		Loop();
	}

	Close();

	return 0;
}

/*--------------------------------------------------------------------------*/

static int Init(void)
{
	IntuitionBase = (struct IntuitionBase*)
			OpenLibrary("intuition.library", 36L);
	
	if (NULL == IntuitionBase)
	{
		return -1;
	}
	
	if (0 != WindowInit())
	{
		return -1;
	}

	return 0;
}

/*--------------------------------------------------------------------------*/

static void Close(void)
{
	WindowKill();
	CloseLibrary((struct Library*) IntuitionBase);
}

/*--------------------------------------------------------------------------*/

static void Loop(void)
{
	while (TRUE)
	{
		const ULONG signals = Wait(windowSignal);

		if (signals & windowSignal)
		{
			WindowProcessSignals();
		}
		
		if (InputIsExitToOsPressed())
		{
			break;
		}
	}
}

/*--------------------------------------------------------------------------*/
