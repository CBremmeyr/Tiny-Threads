/**
 * Kernel.c
 *
 * Author(s): Corbin Bremmeyr, Richard Critchlow
 * Date: 11 July 2020
 *
 * System entry point and initialization
 */

// Standard Libraries
#include <stdio.h>
#include "msp.h"

// Project Libraries
#include "OS.h"
#include "Threads.h"

// Initializes peripherals
void GPIO_Init(void)
{
    // RGB LED
    P2SEL0 &= ~0x04;		// Pin mode: GPIO
    P2SEL1 &= ~0x04;
    P2->DIR |= 0x04;		// Direction: Output
    P2->OUT &= ~0x04;		// State: Off

    // Red LED
    P1SEL0 &= ~0x01;		//Pin mode: GPIO
    P1SEL1 &= ~0x01;
    P1->DIR |= 0x01;		// Direction: Output
    P1->OUT &= ~0x01;		// State: Off
}

// ======= Entry Point =======
int main(void)
{
    // Stop watchdog timer
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;

    OS_Init();			// Initialize OS
    GPIO_Init();		// Initialize GPIO peripheral

    OS_AddThreads(Thread0, Thread1);	// Add Threads to OS
    OS_Launch(TIME_2MS);	// Launch OS

    // This never executes
    return 0;
}
