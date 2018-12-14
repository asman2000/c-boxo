#ifndef BOXO_WINDOW_H
#define BOXO_WINDOW_H
/*--------------------------------------------------------------------------*/
#include <exec/types.h>

extern ULONG windowSignal;

extern void WindowProcessSignals(void);
extern int WindowInit(void);
extern void WindowKill(void);

/*--------------------------------------------------------------------------*/
#endif // BOXO_WINDOW_H
