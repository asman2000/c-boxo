#include "window.h"
#include "input.h"
#include "gfx.h"

#include <proto/exec.h>

/*--------------------------------------------------------------------------*/

struct IntuitionBase* IntuitionBase = NULL;
struct GfxBase* GfxBase = NULL;
struct Library* DataTypesBase = NULL;

static int Init(void);
static void Loop(void);
static void Close(void);

/*--------------------------------------------------------------------------*/

int main(void)
{
	if (0 == Init())
	{
		GfxDrawTitle();
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
	
	GfxBase = (struct GfxBase*)OpenLibrary("graphics.library", 34);
	
	if (NULL == GfxBase)
	{
		return -1;
	}
	
	DataTypesBase = OpenLibrary("datatypes.library",0);

	if (NULL == DataTypesBase)
	{
		return -1;
	}
	
	if (0 != WindowInit())
	{
		return -1;
	}
	
	if (0 != GfxInit())
	{
		return -1;
	}

	return 0;
}

/*--------------------------------------------------------------------------*/

static void Close(void)
{
	GfxKill();
	WindowKill();
	CloseLibrary(DataTypesBase);
	CloseLibrary((struct Library*) GfxBase);
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
