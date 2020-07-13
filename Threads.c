/**
 * Threads.c
 *
 * Author(s): Corbin Bremmeyr, Richard Critchlow
 * Date: 11 July 2020
 *
 * Source file for the individual thread functions
 */

#include "msp.h"

// ===== Thread 0 =====
//  Responsible for toggling on-board BLUE RGB LED infinitely
//  Control taken away preemptively by the KERNEL
void Thread0(void)
{
    while (1) {
	P2->OUT ^= 0x04;	// Toggle LED
	__delay_cycles(500000);	// Delay
    }
}

// ===== Thread 1 =====
// Responsible for toggling on-board RED LED infinitely
// Control taken away preemptively by the KERNEL
void Thread1(void)
{
    while (1) {
	P1->OUT ^= 0x01;	// Toggle LED
	__delay_cycles(500000);	// Delay
    }
}
