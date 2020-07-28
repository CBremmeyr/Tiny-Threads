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

#include "ti/devices/msp432p4xx/inc/msp.h"

/* THIS IS THE ONLY AREA THE PROGRAMMER NEEDS TO MODIFY */

//Include files that need to be threaded
#include "Threads.h"

#define STACKSIZE   300     // Number of 32-bit words allocated for each stack
#define NUMTHREADS  3       // Maximum number of threads

//Array of the thread function pointers
static void (*threads[NUMTHREADS])(void) = {
      Thread0,              //Place the function pointers to each thread here
      Thread1,
      Thread2
};

//Create Thread Locks Here
unsigned int default_Threadlock;
unsigned int RGB_Lock;

/* END OF AREA THAT NEEDS TO BE MODIFIED        */

#define TIME_1MS    3000
#define TIME_2MS    6000

// ====== OS_Init ======
// Disable interrupts until OS_Launch(), setup SysTick timer used by scheduler
void OS_Init(void);

// ====== OS_AddThread ======
// Add foreground threads to the scheduler in a Round-Robin fashion
// Inputs: pointers to a void/void foreground tasks
// Outputs: 1 if successful, 0 if this thread can not be added
int OS_AddThreads(void);

// ====== OS_Launch =======
// Start the scheduler, Enable interrupts
// Inputs: Time (Clock Cycles) to give each thread to run before preemptively  changing threads
void OS_Launch(uint32_t theTimeSlice);

int32_t StartCritical(void);
void EndCritical(int32_t primask);
void yield(void);

// Header guard end
#endif
