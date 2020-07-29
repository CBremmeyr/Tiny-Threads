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

/* THIS IS THE ONLY AREA THE USER NEEDS TO MODIFY */

#define STACKSIZE   300     // Number of 32-bit words allocated for each thread's stack
#define NUMTHREADS  3       // Maximum number of threads

/* **************************************************** */

typedef void (*thread_t)(void);
typedef unsigned int lock_t;

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
int OS_AddThread(thread_t thread);

// ====== OS_Launch =======
// Start the scheduler, Enable interrupts
// Inputs: Time (Clock Cycles) to give each thread to run before preemptively  changing threads
void OS_Launch(uint32_t theTimeSlice);

// ====== StartCritical ======
// Make a copy of previous I bit, disable interrupts
// Outputs: previous I bit
int32_t StartCritical(void);

// ====== EndCritical ======
// Using the copy of previous I bit, restore I bit to previous value
// Inputs:  previous I bit
void EndCritical(int32_t primask);

// ====== This function switches to next thread =======
//void yield(void);
#define yield() asm volatile(" SVC #00")

// ===== Function prototypes of functions written in ThreadLocks.asm =====

// ===== Setup lock for future use =====
void Lock_Init(lock_t *lock);

// ===== Lock a resource =====
// Input: Lock to attempt to acquire
// Output: return 1 if lock was successfully acquired, 0 if failed
unsigned int Lock_Acquire(lock_t *lock);

// ===== Release specified lock =====
// Input: Lock to release
void Lock_Release(lock_t *lock);

// Header guard end
#endif
