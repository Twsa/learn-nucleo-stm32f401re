/*----------------------------------------------------------------------------
 * Name:    Blinky.c
 * Purpose: LED Flasher
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2015 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/


#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX

#include "Board_LED.h"                  // ::Board Support:LED
#include "Board_Buttons.h"              // ::Board Support:Buttons
#include "sys.h"                  // Device header
#include "Serial.h"

/*----------------------------------------------------------------------------
 * blinkLED: blink LED and check button state
 *----------------------------------------------------------------------------*/
unsigned int led_status;
void blinkLED(void const *argument) {
  int32_t max_num = LED_GetCount();
  int32_t num = 0;

  for (;;) {
		led_status=1;
    LED_On(num);                                           // Turn specified LED on
    osSignalWait(0x0001, osWaitForever);
		led_status=0;
    LED_Off(num);                                          // Turn specified LED off
    osSignalWait(0x0001, osWaitForever);

    num++;                                                 // Change LED number
    if (num >= max_num) {
      num = 0;                                             // Restart with first LED
    }
  }

}
int value=0;
void Hello_World(void const *argument) 
{
	
	for(;;)
	{
	  value++;
	   printf("Hello World\r\n");
	   osSignalWait(0x0002, osWaitForever);
	}

}


/*----------------------------------------------------------------------------
 * main: initialize and start the system
 *----------------------------------------------------------------------------*/
int main (void) {
  uint32_t button_msk = (1U << Buttons_GetCount()) - 1;

  // initialize peripherals
  SystemCoreClockConfigure();                              // configure System Clock
  SystemCoreClockUpdate();
	  SER_Initialize();
		SCB->CCR |=SCB_CCR_STKALIGN_Msk;       //使能双字栈对齐
  LED_Initialize();                                        // LED Initialization
  Buttons_Initialize();                                    // Buttons Initialization

  osKernelInitialize ();                                   // initialize CMSIS-RTOS

	osThreadId tid_blinkLED;
	osThreadId tid_Hello_World;
	osThreadDef (blinkLED, osPriorityNormal, 1, 0);
	osThreadDef (Hello_World, osPriorityNormal, 1, 0);

		// create threads
		tid_blinkLED = osThreadCreate (osThread(blinkLED), NULL);
		tid_Hello_World=osThreadCreate (osThread(Hello_World), NULL);
		osKernelStart ();                                        // start thread execution
		
		while(1)
		{
			    osDelay(500);
					osSignalSet(tid_blinkLED, 0x0001);
			    osSignalSet(tid_Hello_World, 0x0002);
		}
//  for (;;) {                                               // main must not be terminated!
//    osDelay(500);
//    while (Buttons_GetState() & (button_msk));             // Wait while holding USER button
//    osSignalSet(tid_blinkLED, 0x0001);
//		osSignalSet(tid_Hello_World, 0x0002);
//  }
}
