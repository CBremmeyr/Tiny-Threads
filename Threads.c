/**
 * Threads.c
 *
 * Author(s): Corbin Bremmeyr, Richard Critchlow
 * Date: 11 July 2020
 *
 * Source file for the individual thread functions
 */

#include "msp.h"
#include "OS.h"

// ======= Function to acquire the lock to be written in LockAcquire.asm ======
unsigned int Lock_Acquire(unsigned int *lock);
void Lock_Release(unsigned int *lock);
unsigned int RGB_Lock;

// ===== Thread 0 =====
//  Responsible for toggling on-board BLUE RGB LED infinitely
//  Control taken away preemptively by the KERNEL
void Thread0(void)
{
    while (1) {
        P1->OUT ^= BIT0;	// Toggle LED
        __delay_cycles(500000);	// Delay
    }
}

// ===== Thread 1 =====
// Responsible for toggling on-board RED LED infinitely
// Control taken away preemptively by the KERNEL
void Thread1(void)
{
    while (1) {
        if(Lock_Acquire(&RGB_Lock)){        // Try to acquire lock and if successful

            P2->OUT ^= BIT2;	// Toggle LED
            __delay_cycles(500000);	// Delay

            P2->OUT &=~ BIT2;
            Lock_Release(&RGB_Lock);                  // Release lock
        }
        yield();
    }
}

void Thread2(void)
{
    while (1) {
        if(Lock_Acquire(&RGB_Lock)){        // Try to acquire lock and if successful
            P2->OUT ^= BIT1;    // Toggle LED
            __delay_cycles(500000); // Delay

            P2->OUT &=~ BIT1;
            Lock_Release(&RGB_Lock);                  // Release lock
        }
    yield();
    }
}
