/**
 * Threads.c
 *
 * Author(s): Corbin Bremmeyr, Richard Critchlow
 * Date: 11 July 2020
 *
 * Source file for the individual thread functions
 */

#include "ti/devices/msp432p4xx/inc/msp.h"
#include "Threads.h"
#include "OS.h"

//TODO can we put the below in a .h file to make it just an include
//TODO maybe put in a section for locks?
// ======= Function to acquire the lock to be written in LockAcquire.asm ======
unsigned int Lock_Acquire(unsigned int *lock);
void Lock_Release(unsigned int *lock);


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

void Thread2(){
    while(1){};
}
