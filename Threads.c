#include "msp.h"

// These are the user-space threads. Note that they are completely oblivious
// to the technical concerns of the scheduler. The only interface to the
// scheduler is the single function yield() 

// ===== Thread 0 =====
// ===== Responsible for toggling on-board GREEN RGB LED infinitely ====
// ===== Use BIT-BANDING approach to reference the LED =====
// ===== Control taken away pre-emtively by the KERNEL =====
void Thread0(void)
{
  while(1)
  {
      P2->OUT ^= 0x04;
      __delay_cycles(500000); //TODO does this break the code?
  }
  
}


// ===== Thread 1 =====
// ===== Responsible for toggling on-board RED ONLY LED infinitely ====
// ===== Use BIT-BANDING approach to reference the LED =====
// ===== Control taken away pre-emtively by the KERNEL =====
void Thread1(void)
{

    while(1)
    {
        P1->OUT ^= 0x01;
        __delay_cycles(500000); //TODO does this break the code?
    }



    /*
     *  RC3
     * the code below was left as a reference but should be changed for LED purposes
     *

    int* threadlock;
    int count;
    //^^^^^THIS IS BULLSHIt^^^^^^ (NEEDED TO COMPILE)
  
  while(1)
  {
   if(Lock_Acquire(&threadlock))		// Try to acquire lock and if successful
   {
    
    printf("\n\rEntered");
    yield();					// Give up control voluntarily (context switch "interrupt")

    printf(" Thread 1 -- pass %d", count);
	Lock_Release(&threadlock);					// Release lock
   }
   yield();                		// Give up control voluntarily (context switch "interrupt")
  }
  */
}



