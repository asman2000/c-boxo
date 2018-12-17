#include "timer.h"

#include <proto/exec.h>
#include <devices/timer.h>
/*--------------------------------------------------------------------------*/
static ULONG signal;

static BOOL timerRequestWasSend = FALSE;
static struct MsgPort* port = NULL;
static struct timerequest* request = NULL;
static struct timeval m_tv;

static void TimerSendRequest(void);

/*--------------------------------------------------------------------------*/

int TimerInit(void)
{
	port = CreateMsgPort();
	request = (struct timerequest*) 
		CreateIORequest(port, sizeof(struct timerequest));

	if (0 == request)
	{
		return RT_FAILED_CREATE_TIMER_REQUEST;
	}

	LONG error = OpenDevice(TIMERNAME, UNIT_VBLANK,
		(struct IORequest*)request, 0);

	if (0 != error)
	{
		return RT_FAILED_TIMER_DEVICE_OPEN;
	}

	signal = 1L << port->mp_SigBit;

	request->tr_node.io_Command = TR_ADDREQUEST;
	TimerSendRequest();
	timerRequestWasSend = TRUE;

	return RT_OK;
}
/*--------------------------------------------------------------------------*/

void TimerKill(void)
{
	if (TRUE == timerRequestWasSend)
	{
		AbortIO((struct IORequest*)request);
		WaitIO((struct IORequest*)request);

		CloseDevice((struct IORequest*)request);
	}

	DeleteIORequest(request);
	DeleteMsgPort(port);
}

/*--------------------------------------------------------------------------*/

void TimerProcessSignals(void)
{
	while (TRUE)
	{
		if (0 == GetMsg(port))
		{
			break;
		}
	}

	TimerSendRequest();
}

/*--------------------------------------------------------------------------*/

static void TimerSendRequest(void)
{
	request->tr_time.tv_secs = 0;
	request->tr_time.tv_micro = 20000;

	SendIO((struct IORequest*)request);
}

/*--------------------------------------------------------------------------*/

ULONG TimerGetSignal(void)
{
	return signal;
}

/*--------------------------------------------------------------------------*/