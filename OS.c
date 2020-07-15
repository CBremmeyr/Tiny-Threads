/**
 * OS.c
 *
 * Author(s): Corbin Bremmeyr, Richard Critchlow
 * Date: 11 July 2020
 *
 * Library that enables user to use user-space threads
 */

// Standard Libraries
#include "msp.h"

// Project Libraries
#include "OS.h"
#include "Threads.h"

// Maximum number of threads, used for memory allocation of stacks and thread table
#define NUMTHREADS  3

// ===== Function prototypes of functions in OSasm.asm =====
void OS_DisableInterrupts();
void OS_EnableInterrupts();
void StartOS();

// ===== Local functions ======
void SetInitialStack(int i);

// ===== Structure to store state of thread =====
// Thread Control Block
typedef struct tcb {
    int32_t *sp;		// Pointer to stack (valid only for threads not running)
    struct tcb *next;		// Linked-list pointer
} tcbType;

static tcbType tcbs[NUMTHREADS];	// Thread table
tcbType *RunPt;			// Pointer to the next thread
static int32_t Stacks[NUMTHREADS][STACKSIZE];	// 2-dimensional array implemented as STACK

// ===== OS_Init =====
// Disable interrupts until OS_Launch(), setup SysTick timer used by scheduler
void OS_Init(void)
{
    OS_DisableInterrupts();	// Disable interrupts until OS_Launch

    // Initialize OS controlled I/O: SysTick Timer, 3 MHz crystal input clock
    SysTick->CTRL = 0;		//disable SysTick
    SysTick->CTRL = 0x06;	//interrupts, main CLK

    // Set priority to 7 so that it allows threads to run
    SCB->SHP[1] = (SCB->SHP[1] & 0x00FFFFFF) | 0xE0000000;
}

// ===== Sets default values in STACK ======
// Inputs: i is the thread number
void SetInitialStack(int i)
{
    tcbs[i].sp = &Stacks[i][STACKSIZE - 16];// Thread stack pointer

    Stacks[i][STACKSIZE - 1] = 0x21000000;	// XPSR - SysTick Interrupt   -- Saved by Exception
    //Stacks[i][STACKSIZE - 2] = Skipped    // ReturnAddress (Fill in OS_AddThreads())
    Stacks[i][STACKSIZE - 3] = 0x0;	        // R14 (LR)
    Stacks[i][STACKSIZE - 4] = 0x0;	        // R12 (General Register)
    Stacks[i][STACKSIZE - 5] = 0x0;	        // R3  (General Register)
    Stacks[i][STACKSIZE - 6] = 0x0;	        // R2  (General Register)
    Stacks[i][STACKSIZE - 7] = 0x0;	        // R1  (General Register)
    Stacks[i][STACKSIZE - 8] = 0x0;	        // R0  (General Register)     -- Saved by Exception
    Stacks[i][STACKSIZE - 9] = 0x0;	        // R11 (General Register)     -- Manually saved
    Stacks[i][STACKSIZE - 10] = 0x0;	    // R10 (General Register)
    Stacks[i][STACKSIZE - 11] = 0x0;	    // R9  (General Register)
    Stacks[i][STACKSIZE - 12] = 0x0;	    // R8  (General Register)
    Stacks[i][STACKSIZE - 13] = 0x0;	    // R7  (General Register)
    Stacks[i][STACKSIZE - 14] = 0x0;	    // R6  (General Register)
    Stacks[i][STACKSIZE - 15] = 0x0;	    // R5  (General Register)
    Stacks[i][STACKSIZE - 16] = 0x0;	    // R4  (General Register)     -- Manually saved
}

// ====== OS_AddThread ======
// Add foreground threads to the scheduler in a Round-Robin fashion
// Inputs: pointers to a void/void foreground tasks
// Outputs: 1 if successful, 0 if this thread can not be added
int OS_AddThreads(void (*Thread0)(void), void(*Thread1)(void))
{
    tcbs[0].next = &tcbs[1];
    tcbs[1].next = &tcbs[2];
    tcbs[2].next = &tcbs[0];

    int i; //TODO why cant i put this in da loop
    for( i = 0; i < NUMTHREADS; ++i){
        SetInitialStack(i);
    }

    Stacks[0][STACKSIZE - 2] = (uint32_t) Thread0;

    Stacks[1][STACKSIZE - 2] = (uint32_t) Thread1;

    Stacks[2][STACKSIZE - 2] = (uint32_t) Thread2;

    // Make RunPt point to Thread 0 so it will run first
    RunPt = &tcbs[0];

    return 1;
}

// ===== OS_Launch ======
// Start the scheduler, Enable interrupts
// Inputs: Time (Clock Cycles) to give each thread to run before preemptively  changing threads
void OS_Launch(uint32_t theTimeSlice)	//TODO change to take input as a float mS
{
    SysTick->LOAD = theTimeSlice;	// Reload Value
    SysTick->CTRL |= 0x01;	// SysTick Enable
    StartOS();			// Start on the first task
}

// ====== This function (written in assembly) switches to handler mode. (privileged access) =======
extern void yield(void) __attribute__((naked));
void yield(void){

    asm volatile(" SVC #00");  //Jumps to SysTick_Handler (changed interrupt Vector)
}
