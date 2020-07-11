/*******************************************************************************
 * SysTick_3MHz.c
 *
 * A wrapper for the SysTick Timer. Can create delays or interrupts
 *
 *       Author: Richard Critchlow
 * Date Created: November 19, 2020
 *     Modified: June 24, 2020
 *******************************************************************************/

#include <SysTick_3MHz.h>

//------------------------------------------------------------------------------
void initSysTick(char interruptEnable){

    if(interruptEnable) {
        SysTick->CTRL = 0;          // Disable SysTick
        SysTick->LOAD = 0xFFFFFF;   // Reload Value
        SysTick->VAL  = 0;
        SysTick->CTRL = 0x07;       // Enable SysTick, interrupts, main CLK
    }
    else {
        SysTick->CTRL = 0;      // Disable SysTick
        SysTick->VAL  = 0;      // Initialize count value
        SysTick->CTRL = 0x05;   // Enable SysTick, no interrupts, main CLK
    }
}

//------------------------------------------------------------------------------
int setSysTickInterrupt_mS(unsigned int mS){

    // Check to see if SysTick is already enabled
    // (reads interrupt enable bit)
    if(SysTick->CTRL & 0x02){
        return -1;
    }

    // If input is over max time SysTick can time
    if(mS > 5592){
        return -2;
    }

    // Convert from ms to ticks and load into SysTick timer
    float percentCycle = (mS) / 5592.40533; // %of full iteration
    SysTick->LOAD = (int) (percentCycle * 0x00FFFFFF + .001);
    SysTick->VAL = 0;

    return 0;
}

//------------------------------------------------------------------------------
int setSysTickInterrupt_uS(unsigned int uS){

    // Check to see if SysTick is already enabled
    // (reads interrupt enable bit)
    if(SysTick->CTRL & 0x02){
        return -1;
    }

    // If input is over max time SysTick can time
    if(uS > 5592405){
        return -1;
    }

    // Convert from ms to ticks and load into SysTick timer
    float percentCycle = uS / 5592405.33; // %of full iteration
    SysTick->LOAD = (int) (percentCycle * 0x00FFFFFF);
    SysTick->VAL = 0;

    return 0;
}


//------------------------------------------------------------------------------
void delay_mS(uint16_t msec){

    // Max range of SysTick for 3MHz is 5.59240533 sec

    // Do the number of full iterations
    int iterations = (int) (msec / 5592.40533);
    for(; iterations > 0; iterations--){
        SysTick->LOAD = 0x00FFFFFF;
        SysTick->VAL = 0;
        while((SysTick->CTRL & 0x00010000) == 0);
    }

    // Finish the remainder
    // Start by finding the percent remaining
    float percentCycle = (msec - (5592.40533 * iterations)) / 5592.40533;
    SysTick->LOAD = (int) (percentCycle * 0x00FFFFFF);
    SysTick->VAL = 0;
    while((SysTick->CTRL & 0x00010000) == 0);
}

//------------------------------------------------------------------------------
void delay_uS(uint16_t usec){
    // Max range of SysTick for 3MHz is 5.5924 sec

    // Do the number of full iterations
    int iterations = (int) (usec / 5592405.33);
    for(; iterations > 0; iterations--){
        SysTick->LOAD = 0x00FFFFFF;
        SysTick->VAL = 0;
        while((SysTick->CTRL & 0x00010000) == 0);
    }

    // Finish the remainder
    // Start by finding the percent remaining
    float percentCycle = (usec - (5592405.33 * iterations)) / 5592405.33;
    SysTick->LOAD = (int) (percentCycle * 0x00FFFFFF);
    SysTick->VAL = 0;
    while((SysTick->CTRL & 0x00010000) == 0);
}

