/**
 * Threads.c
 *
 * Author(s): Corbin Bremmeyr, Richard Critchlow
 * Date: 11 July 2020
 *
 * Source file for the individual thread functions
 */

// Header gaurd start
#ifndef THREADS_H_
#define THREADS_H_

// ===== Thread 0 =====
//  Responsible for toggling on-board GREEN RGB LED infinitely
//  Control taken away pre-emtively by the KERNEL
void Thread0(void);

// ===== Thread 1 =====
// Responsible for toggling on-board RED ONLY LED infinitely
// Control taken away pre-emtively by the KERNEL
void Thread1(void);

// Header gaurd end
#endif

