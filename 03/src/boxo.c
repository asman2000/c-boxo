#include "window.h"
#include "libs.h"
#include "input.h"
#include "gfx.h"

#include "types.h"

#include <proto/exec.h>
/*--------------------------------------------------------------------------*/

typedef struct
{
	PIF init;
	PVF kill;
} InitKill;



static int Init(void);
static void Loop(void);
static void Close(void);

static InitKill initiations[] =
{
	{&LibsOpen, &LibsClose},
	{&WindowInit, &WindowKill},
	{&GfxInit, &GfxKill},
};

/*--------------------------------------------------------------------------*/

int main(void)
{
	if (RT_OK == Init())
	{
		GfxDrawTitle();
		Loop();
	}

	Close();

	return RT_OK;
}

/*--------------------------------------------------------------------------*/

static int Init(void)
{
	int i = 0;

	while (i < ARRAY_SIZE(initiations))
	{
		const int result = (*initiations[i].init)();
		i++;

		if (RT_OK != result)
		{
			return result;
		}
	}

	return RT_OK;
}

/*--------------------------------------------------------------------------*/

static void Close(void)
{
	int i = ARRAY_SIZE(initiations) - 1;

	while (i > -1)
	{
		(*initiations[i].kill)();
		i--;
	}
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
