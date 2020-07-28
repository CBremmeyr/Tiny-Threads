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
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "ti/devices/msp432p4xx/inc/msp.h"

// Project Libraries
#include "OS.h"
#include "test.h"

// ======= Entry Point =======
int main(void)
{
    // Stop watchdog timer
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;

    test_run();
    return 0;
}
