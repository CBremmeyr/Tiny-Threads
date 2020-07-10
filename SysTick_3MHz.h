/*******************************************************************************
 * SysTick_3MHz.h
 *
 *  Created on: November 2019
 *    Modified: June 2020
 *      Author: Richard
 *******************************************************************************/

#include "msp.h"

#ifndef SYSTICK_3MHZ_H_
#define SYSTICK_3MHZ_H_

/*******************************************************************************
 * Initializes the SysTick Timer. Can be initialized with or without
 * interrupts.
 *
 * NOTE: if using interrupt ensure you use the handler
 *       Interrupt Routine:  void SysTick_Handler(void)
 *
 * Input:
 *     interruptEnable: Boolean value that determines to set-up the SysTick
 *                      with or without interrupts
 *
 * Output:
 *     None
 *
 * Return:
 *     None
 *******************************************************************************/
void initSysTick(char interruptEnable);

/********************************************************************************
 * Sets up the SysTick Timer to interrupt every "mS" milliseconds. Returns a
 * negative number if there was an error. 0 otherwise.
 *
 * Input:
 *     mS:  The number of milliseconds to be intervaled
 *
 * Output:
 *     None
 *
 * Return:
 *     0    No Error
 *    -1    SysTick timer has not been initialized with interrupts
 *    -2    The number of milliseconds exceeds the max time allowed by SysTick
 ********************************************************************************/
int setSysTickInterrupt_mS(unsigned int mS);

/********************************************************************************
 * Sets up the SysTick Timer to interrupt every "uS" microseconds. Returns a
 * negative number if there was an error. 0 otherwise.
 *
 * Input:
 *     uS:  The number of microseconds for the SysTick timer
 *
 * Output:
 *     None
 *
 * Return:
 *     0    No Error
 *    -1    SysTick timer has not been initialized with interrupts
 *    -2    The number of microseconds exceeds the max time allowed by SysTick
 ********************************************************************************/
int setSysTickInterrupt_uS(unsigned int uS);

/********************************************************************************
 * Uses the SysTick Timer to delay for "mS" milliseconds. This function is set to
 * loop and has no theoretical max value for delay.
 *
 * Input:
 *     mS:  The number of milliseconds to be delayed
 *
 * Output:
 *     None
 *
 * Return:
 *     None
 ********************************************************************************/
void delay_mS(uint16_t msec);

/********************************************************************************
 * Uses the SysTick Timer to delay for "uS" microseconds. This function is set to
 * loop and has no theoretical max value for delay.
 *
 * Input:
 *     uS:  The number of microseconds to be delayed
 *
 * Output:
 *     None
 *
 * Return:
 *     None
 ********************************************************************************/
void delay_uS(uint16_t usec);

#endif /* SYSTICK_48MHZ_H_ */



