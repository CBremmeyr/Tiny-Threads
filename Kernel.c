
//Standard Libraries
#include <stdio.h>
#include "msp.h"

//Project Libraries
#include "OS.h"

// ===== This is the kernel that will setup everything and run the scheduler ======


//Defines
//TODO is this right? What is this define we also have TIME_2MS
#define TIMESLICE   6000      //2ms @ 3MHz used for Thread context switch time in clockcycles



//Static Variable
unsigned threadlock;            // Variable Lock

// Code below is the interface to the C standard I/O library
// All the I/O are directed to the console which is UART0
struct __FILE { int handle; };
FILE __stdin = {0};
FILE __stdout = {1};
FILE __stderr = {2};


//Initializes any peripherals
//Here it initializes the Onboard LEDs
void GPIO_Init(void)
{
    //RGB LED
    P2SEL0  &= ~0x07;   //GPIO
    P2SEL1  &= ~0x07;
    P2->DIR |=  0x07;   //Output
    P2->OUT &= ~0x07;   //Off

    //RED LED
    P1SEL0  &= ~0x01;   //GPIO
    P1SEL1  &= ~0x01;
    P1->DIR |=  0x01;   //Output
    P1->OUT &= ~0x01;   //Off
}


// ======== Function to initialize LOCK (you need to modify) =============
void Lock_Init(unsigned *lock)
{
    ;
}

// ======= Function to acquire the lock to be written in LockAcquire.asm ======
unsigned Lock_Acquire(unsigned *lock)
{
  return 1; // always succeeds
}

// ======== Function to release LOCK (you need to modify) ===========
void Lock_Release(unsigned *lock)
{
	;
}


// ======= MAIN =========
int main(void)
{

    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
                                                    // Initialize the global thread lock
    OS_Init();                                      // Initialize OS
    GPIO_Init();                                    // Initialize GPIO peripheral

	//TODO OS_AddThreads(Thread0, Thread1);		    // Add Threads to the list
	//TODO OS_Launch(TIMESLICE);					// Launch OS



  return 0;            // This never executes

}





