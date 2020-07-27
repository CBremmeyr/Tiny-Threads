/**
 * Threads.c
 *
 * Author(s): Corbin Bremmeyr, Richard Critchlow
 * Date: 11 July 2020
 *
 * Source file for the individual thread functions
 */

// Header guard start
#ifndef THREADS_H_
#define THREADS_H_

// ===== Thread 0 =====
//  Responsible for toggling on-board blue RGB LED infinitely
//  Control taken away preemptively by the KERNEL
void Thread0(void);

// ===== Thread 1 =====
// Responsible for toggling on-board red ONLY LED infinitely
// Control taken away preemptively by the KERNEL
void Thread1(void);

void Thread2(void);

// Header guard end
#endif
