/**
 * Kernel.c
 *
 * Author(s): Corbin Bremmeyr, Richard Critchlow
 * Date: 11 July 2020
 *
 * System entry point and initialization
 */

// If RUN_TESTS is defined then test will be compiled, else the LED app will be compiled
// Comment out to run LED app
//#define RUN_TESTS

#ifdef RUN_TESTS
#include <LibraryTesting.h>
#endif

// Standard Libraries
//#include <stdio.h>
#include <assert.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "ti/devices/msp432p4xx/inc/msp.h"

// Project Libraries
#include "OS.h"
#include "Threads.h"

// Locks used in Threads.c
extern lock_t RGB_Lock;

void GPIO_Init(void)
{

    //RGB LED
    P2SEL0 &= ~0x07;        // Pin mode: GPIO
    P2SEL1 &= ~0x07;
    P2->DIR |= 0x07;        // Direction: Output
    P2->OUT &= ~0x07;       // State: Off

    // Red LED
    P1SEL0 &= ~0x01;        //Pin mode: GPIO
    P1SEL1 &= ~0x01;
    P1->DIR |= 0x01;        // Direction: Output
    P1->OUT &= ~0x01;       // State: Off
}


// ======= Entry Point =======
int main(void)
{
    // Stop watchdog timer
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;

#ifdef RUN_TESTS

    // Run OS.h tests
    test_run();
#endif

    // Run LED app
    Lock_Init(&RGB_Lock);
    OS_Init();                          // Initialize OS
    GPIO_Init();                        // Initialize GPIO peripheral

    // Add Threads to OS, if any additions fail, abort
    int results = 0;
    //CHANGE PER APPLICATION: Add all threads here
    results += OS_AddThread(Thread0);
    results += OS_AddThread(Thread1);
    results += OS_AddThread(Thread2);
    assert(results == 3);

    OS_Launch(TIME_2MS);                // Launch OS

    // This should never execute
    return 0;
}
