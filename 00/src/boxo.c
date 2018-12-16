#include <proto/exec.h>
#include <proto/intuition.h>

#include <dos/dos.h>
#include <intuition/intuition.h>

/*--------------------------------------------------------------------------*/

struct IntuitionBase* IntuitionBase;
struct Window* window = NULL;

static int Init(void);
static void Loop(void);
static void Close(void);
static BOOL WindowDoSingnals();

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

	window = (struct Window*) OpenWindowTags(NULL,
		WA_Left, 0,
		WA_Top, 0,
		WA_Width, 320,
		WA_Height, 256,
		WA_CloseGadget, TRUE,
		WA_Title, (ULONG)"boxo",
		WA_Activate, TRUE,
		WA_DragBar, TRUE,
		WA_GimmeZeroZero, TRUE,
		WA_IDCMP, IDCMP_CLOSEWINDOW | IDCMP_RAWKEY,
		TAG_END);

	if(NULL == window)
	{
		return -1;
	}

	return 0;
}

/*--------------------------------------------------------------------------*/

static void Close(void)
{
	if (window)
	{
		CloseWindow(window);
	}

	CloseLibrary((struct Library*) IntuitionBase);
}

/*--------------------------------------------------------------------------*/

static void Loop(void)
{
	BOOL end = FALSE;

	while (!end)
	{
		const ULONG windowSignal = 1L << window->UserPort->mp_SigBit;
		const ULONG signals = Wait(windowSignal | SIGBREAKF_CTRL_C);

		if(signals & SIGBREAKF_CTRL_C)
		{
			end = TRUE;
		}

		if(signals & windowSignal)
		{
			end = WindowDoSingnals();
		}
	}
}

/*--------------------------------------------------------------------------*/

static BOOL WindowDoSingnals()
{
	BOOL result = FALSE;

	while (TRUE)
	{
		struct IntuiMessage* msg = (struct IntuiMessage*)
			GetMsg(window->UserPort);

		if (NULL == msg)
		{
			break;
		}

		if (IDCMP_CLOSEWINDOW == msg->Class)
		{
			result = TRUE;
		}

		ReplyMsg((struct Message*) msg);
	}

	return result;
}

/*--------------------------------------------------------------------------*/
