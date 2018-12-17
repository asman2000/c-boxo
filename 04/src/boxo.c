#include "window.h"
#include "libs.h"
#include "input.h"
#include "gfx.h"
#include "timer.h"

#include "types.h"

#include <proto/exec.h>
/*--------------------------------------------------------------------------*/

PVF mainLoopFunction;

typedef struct
{
	PIF init;
	PVF kill;
} InitKill;

static InitKill initiations[] =
{
	{&LibsOpen, &LibsClose},
	{&WindowInit, &WindowKill},
	{&GfxInit, &GfxKill},
	{&TimerInit, &TimerKill},
};

static int Init(void);
static void Loop(void);
static void Close(void);

static void exampleLoop(void);
/*--------------------------------------------------------------------------*/

int main(void)
{
	if (RT_OK == Init())
	{
		GfxDrawTitle();
		mainLoopFunction = &exampleLoop;
		
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
	const ULONG timerSignal = TimerGetSignal();
	const ULONG signalSet = windowSignal | timerSignal;
	
	while (TRUE)
	{
		const ULONG signals = Wait(signalSet);

		if (signals & windowSignal)
		{
			WindowProcessSignals();
		}
		
		if (InputIsExitToOsPressed())
		{
			break;
		}
		
		if (signals & timerSignal)
		{
			TimerProcessSignals();
			(*mainLoopFunction)();
		}
	}
}

/*--------------------------------------------------------------------------*/
static int rockPositionX = 96;
static int rockPositionY = 64;

static int rockDirection = 1;

static void exampleLoop(void)
{
	GfxDrawTileEmpty(rockPositionX, rockPositionY);
	
	rockPositionX += rockDirection;
	
	if (rockPositionX > 208)
	{
		rockDirection = -1;
	}
	
	if (rockPositionX < 96)
	{
		rockDirection = 1;
	}
	
	
	GfxDrawTileRock(rockPositionX, rockPositionY);
	
}

/*--------------------------------------------------------------------------*/
