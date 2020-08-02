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

lock_t RGB_Lock;

// ===== Thread 0 =====
//  Responsible for toggling on-board BLUE RGB LED infinitely
//  Control taken away preemptively by the KERNEL
void Thread0(void)
{
    while (1) {
        if(Lock_Acquire(&RGB_Lock)) {

            yield();
            __delay_cycles(500000); // Delay
            P2->OUT ^= 0x04;    // Toggle LED
            Lock_Release(&RGB_Lock);

        }
    yield();
    }
}

// ===== Thread 1 =====
// Responsible for toggling on-board RED LED infinitely
// Control taken away preemptively by the KERNEL
void Thread1(void)
{
    while (1) {
        P1->OUT ^= 0x01;    // Toggle LED
        __delay_cycles(500000); // Delay
    }
}

void Thread2(void){
    uint32_t count = 0;

    while (1) {
        if(Lock_Acquire(&RGB_Lock)) {
            count++;
            yield();
            __delay_cycles(500000); // Delay
            P2->OUT ^= 0x02;    // Toggle LED

            // Close thread after some number of LED toggles
            if(count >= 10) {
                OS_CloseThread();
            }

            Lock_Release(&RGB_Lock);

        }
    yield();

    }




}
