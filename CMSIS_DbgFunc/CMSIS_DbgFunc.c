/**************************************************************************//**
 * @file     main.c
 * @brief    CMSIS Cortex-M3 ITM example
 *           Demonstrate CMSIS Debug features
 * @version  V1.00
 * @date     12. May 2010
 *
 * @note
 * Copyright (C) 2010 ARM Limited. All rights reserved.
 *
 * @par
 * ARM Limited (ARM) is supplying this software for use with Cortex-M 
 * processor based microcontrollers.  This file can be freely distributed 
 * within development tools that are supporting such ARM based processors. 
 *
 * @par
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 ******************************************************************************/

#include <stdio.h>
#include "stm32f10x.h"

volatile int ITM_RxBuffer = ITM_RXBUFFER_EMPTY;       /* used for Debug Input */


volatile uint32_t msTicks;                            /* counts 1ms timeTicks */
/*----------------------------------------------------------------------------
  SysTick_Handler
 *----------------------------------------------------------------------------*/
void SysTick_Handler(void) {
  msTicks++;                        /* increment counter necessary in Delay() */
}

/*------------------------------------------------------------------------------
  delays number of tick Systicks (happens every 1 ms)
 *------------------------------------------------------------------------------*/
__INLINE static void Delay (uint32_t dlyTicks) {
  uint32_t curTicks;

  curTicks = msTicks;
  while ((msTicks - curTicks) < dlyTicks);
}


/*----------------------------------------------------------------------------
  print a character over ITM                      (used from Retarget.c)
 *----------------------------------------------------------------------------*/
int sendchar(int ch) {
  return (ITM_SendChar(ch));
}


/*----------------------------------------------------------------------------
  Receive a character via Debugger (blocking)     (used from Retarget.c)
 *----------------------------------------------------------------------------*/
int getkey(void){
  while (ITM_CheckChar() != 1);
  return (ITM_ReceiveChar());
}


/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
int main (void) {
  FILE *dbgIn;
  unsigned char c;


  if (SysTick_Config(SystemCoreClock / 1000)) { /* Setup SysTick Timer for 1 msec interrupts  */
    while (1);                                  /* Capture error */
  }
  
  printf ("Example demonstrating CMSIS Debug Functions\r\n\r\n");
 
  while(1) {
    printf ("Press a key. ");
    c = fgetc(dbgIn);
    printf ("\r\n");
    printf ("You pressed '%c'.\r\n\r\n", c);

    Delay (10);
  }
  
}

