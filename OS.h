#include "msp.h"

#ifndef OS_H_
#define OS_H_

// fill these depending on your clock
#define TIME_1MS    3000
#define TIME_2MS  	6000	// This is what you should pass as the Timeslice value

void OS_Init(void);
void SetInitialStack(int i);
int OS_AddThreads(void(*Thread0)(void), void(*Thread1)(void));
void OS_Launch(uint32_t theTimeSlice);
int32_t StartCritical(void);
void EndCritical(int32_t primask);
void yield(void);

#endif
