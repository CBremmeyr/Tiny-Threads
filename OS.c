#include "msp.h"

// ===== Function prototypes of functions written in OSasm.asm =====
void OS_DisableInterrupts();
void OS_EnableInterrupts();
void StartOS();



#define NUMTHREADS  2             // Maximum number of threads
#define STACKSIZE   100           // Number of 32-bit words in stack (You will have to keep increasing intelligently if code does not work)

// ===== Structure to store state of thread ===== Thread Control Block
struct tcb
{
  int32_t *sp;                      // Pointer to stack (valid for threads not running)
  struct tcb *next;                 // Linked-list pointer
};
typedef struct tcb tcbType;

tcbType tcbs[NUMTHREADS];			// Thread table
tcbType *RunPt;						// Pointer to points to the next thread
int32_t Stacks[NUMTHREADS][STACKSIZE];	// 2-dimensional array implemented as STACK




// ===== OS_Init =====
// Initialize operating system, disable interrupts until OS_Launch
// Initialize OS controlled I/O: SysTick, 3 MHz crystal
void OS_Init(void)
{
    OS_DisableInterrupts();
    SysTick->CTRL = 0; //disable SysTick
    SysTick->CTRL = 0x06; //interrupts, main CLK

    SCB -> SHP[1] = (SCB -> SHP[1] & 0x00FFFFFF) | 0xE0000000;          // Set priority 7 so that it allows threads to run
}




// ===== Sets default values in STACK ======
// Inputs: i is the thread number
void SetInitialStack(int i){

  tcbs[i].sp = &Stacks[i][STACKSIZE-16]; // thread stack pointer
  Stacks[i][STACKSIZE-1]  =	0x0F      ;   // XPSR - SysTick Interrupt   	-- Saved by Exception
  // Skipped space for ReturnAddress
  Stacks[i][STACKSIZE-3]  =	0xFFFFFFF9;   // R14 (LR) - Indicates Interrupt return
  Stacks[i][STACKSIZE-4]  =	0x00      ;   // R12 (General Register)
  Stacks[i][STACKSIZE-5]  =	0x00      ;   // R3  (General Register)
  Stacks[i][STACKSIZE-6]  =	0x00      ;   // R2  (General Register)
  Stacks[i][STACKSIZE-7]  =	0x00      ;   // R1  (General Register)
  Stacks[i][STACKSIZE-8]  =	0x00      ;   // R0  (General Register)	    -- Saved by Exception
  Stacks[i][STACKSIZE-9]  =	0x00      ;   // R11 (General Register)
  Stacks[i][STACKSIZE-10] = 0x00      ;   // R10 (General Register)
  Stacks[i][STACKSIZE-11] = 0x00	  ;   // R9  (General Register)
  Stacks[i][STACKSIZE-12] = 0x00	  ;   // R8  (General Register)
  Stacks[i][STACKSIZE-13] = 0x00	  ;   // R7  (General Register)
  Stacks[i][STACKSIZE-14] = 0x05   	  ;   // R6  (General Register)
  Stacks[i][STACKSIZE-15] = 0x00   	  ;   // R5  (General Register)
  Stacks[i][STACKSIZE-16] = 0x08   	  ;   // R4  (General Register)
}


// ====== OS_AddThread ======
// Add three foreground threads to the scheduler in a Round-Robin fashion
// Inputs: three pointers to a void/void foreground tasks
// Outputs: 1 if successful, 0 if this thread can not be added
int OS_AddThreads(void(*Thread0)(void), void(*Thread1)(void)){

    //int32_t status;

									//TODO?// Function call to start the critical section
    tcbs[0].next = &tcbs[1];
    tcbs[1].next = &tcbs[0];

    SetInitialStack(0);
    Stacks[0][STACKSIZE - 2] = (uint32_t) Thread0;								// For Thread 0:
									// 1: Set the default values in stack
									// 2: Make ReturnAddress stored on stack to point to Thread 0
    SetInitialStack(1);
	Stacks[1][STACKSIZE - 2] = (uint32_t) Thread1;								// For Thread 1:
									// 1: Set the default values in stack
									// 2: Make ReturnAddress stored on stack to point to Thread 1



  
    RunPt = &tcbs[0];       // Make RunPt point to Thread 0 so it will run first
							//TODO? Function call to end the critical section

    return 1;               // successful
}


// ===== OS_Launch ======
// Start the scheduler, Enable interrupts
// Inputs: number of 333.33ms clock cycles that corresponds to 2 ms
//         (maximum of 24 bits)
void OS_Launch(uint32_t theTimeSlice) //TODO change to take input as a float mS
{
    SysTick->LOAD = theTimeSlice; //reload Value
    SysTick->CTRL |= 0x01; //SysTick Enable
    StartOS();                     // start on the first task
}


// ====== StartCritical ======
// Make a copy of previous I bit, disable interrupts
// Outputs: previous I bit
extern int32_t StartCritical(void) __attribute__((naked));
int32_t StartCritical(void)
{
								// Save old status
								// Disable interrupt mechanism in assembly
								// Return to the calling function  
    return 1;
}


// ====== EndCritical ======
// Using the copy of previous I bit, restore I bit to previous value
// Inputs:  previous I bit
extern void EndCritical(int32_t primask) __attribute__((naked));
void EndCritical(int32_t primask)
{
								// Enable interrupt mechanism in assembly
								// Return to the calling function  
}


// ====== This function (written in assembly) switches to handler mode. (privileged access) =======
extern void yield(void) __attribute__((naked));
void yield(void)
{
						// Gain privileged access
    //Do this by changing the startup file and changing the SVC Handler vector to point to the Systick_Handler
    //^That should be the whole function
}
