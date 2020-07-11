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
  Stacks[i][STACKSIZE-1]  =	0x21000000      ;   // XPSR - SysTick Interrupt   	-- Saved by Exception
  //specific initialization for each thread      (ReturnAddress)
  Stacks[i][STACKSIZE-3]  =	0x10      ;   // R14 (LR) - Indicates Interrupt return
  Stacks[i][STACKSIZE-4]  =	0x20      ;   // R12 (General Register)
  Stacks[i][STACKSIZE-5]  =	0x30      ;   // R3  (General Register)
  Stacks[i][STACKSIZE-6]  =	0x40      ;   // R2  (General Register)
  Stacks[i][STACKSIZE-7]  =	0x50      ;   // R1  (General Register)
  Stacks[i][STACKSIZE-8]  =	0x60      ;   // R0  (General Register)	    -- Saved by Exception
  Stacks[i][STACKSIZE-9]  =	0x70      ;   // R11 (General Register)
  Stacks[i][STACKSIZE-10] = 0x80      ;   // R10 (General Register)
  Stacks[i][STACKSIZE-11] = 0x90	  ;   // R9  (General Register)
  Stacks[i][STACKSIZE-12] = 0x11	  ;   // R8  (General Register)
  Stacks[i][STACKSIZE-13] = 0x22	  ;   // R7  (General Register)
  Stacks[i][STACKSIZE-14] = 0x33   	  ;   // R6  (General Register)
  Stacks[i][STACKSIZE-15] = 0x44   	  ;   // R5  (General Register)
  Stacks[i][STACKSIZE-16] = 0x55   	  ;   // R4  (General Register)
}


// ====== OS_AddThread ======
// Add three foreground threads to the scheduler in a Round-Robin fashion
// Inputs: three pointers to a void/void foreground tasks
// Outputs: 1 if successful, 0 if this thread can not be added
int OS_AddThreads(void(*Thread0)(void), void(*Thread1)(void)){


    tcbs[0].next = &tcbs[1];
    tcbs[1].next = &tcbs[0];

    SetInitialStack(0);
    //Stacks[0][STACKSIZE - 3] = (uint32_t) Thread0;
    Stacks[0][STACKSIZE - 2] = (uint32_t) Thread0;
    SetInitialStack(1);
	Stacks[1][STACKSIZE - 3] = (uint32_t) Thread1;
	Stacks[1][STACKSIZE - 2] = (uint32_t) Thread1;

    RunPt = &tcbs[0];       // Make RunPt point to Thread 0 so it will run first

    return 1;
}


// ===== OS_Launch ======
// Start the scheduler, Enable interrupts
// Inputs: number of 333.33ms clock cycles that corresponds to 2 ms
//         (maximum of 24 bits)
void OS_Launch(uint32_t theTimeSlice) //TODO change to take input as a float mS
{
    SysTick->LOAD = theTimeSlice;   //reload Value
    SysTick->CTRL |= 0x01;          //SysTick Enable
    StartOS();                      // start on the first task
}


// ====== This function (written in assembly) switches to handler mode. (privileged access) =======
extern void yield(void) __attribute__((naked));
void yield(void)
{
						// Gain privileged access
    //Do this by changing the startup file and changing the SVC Handler vector to point to the Systick_Handler
    //^That should be the whole function
}
