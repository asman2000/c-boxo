#ifndef BOXO_TIMER_H
#define BOXO_TIMER_H
/*--------------------------------------------------------------------------*/
#include "types.h"

extern ULONG TimerGetSignal(void);

extern int TimerInit(void);
extern void TimerKill(void);
extern void TimerProcessSignals(void);

/*--------------------------------------------------------------------------*/
#endif // BOXO_TIMER_H
