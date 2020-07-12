/**
 * OS.h
 *
 * Author(s): Corbin Bremmeyr, Richard Critchlow
 * Date: 11 July 2020
 *
 * Library API functions. Allows user to setup and use two user-space threads
 */

// Header guard start
#ifndef OS_H_
#define OS_H_

#define STACKSIZE   100		// Number of 32-bit words in stack

#define TIME_1MS    3000
#define TIME_2MS    6000

// ====== OS_Init ======
// Disable interrupts until OS_Launch(), setup SysTick timer used by scheduler
void OS_Init(void);

// ====== OS_AddThread ======
// Add three foreground threads to the scheduler in a Round-Robin fashion
// Inputs: three pointers to a void/void foreground tasks
// Outputs: 1 if successful, 0 if this thread can not be added
int OS_AddThreads(void (*Thread0)(void), void(*Thread1)(void));

// ====== OS_Launch =======
// Start the scheduler, Enable interrupts
// Inputs: Time (ms) to give each thread to run before preemtivly changing threads
void OS_Launch(uint32_t theTimeSlice);

// Header guard end
#endif
