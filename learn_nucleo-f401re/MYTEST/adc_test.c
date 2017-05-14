/*************************************************************************************
 *  File Name                                :adc_test.c
 
 *  Create Date                             :    2017/05/12
 *  Author/Corporation                  :   Twsa
 *  Description                               :   ADC2 and ADC3 are not available in STM32F401xB/C and STM32F401xD/E
                                                           ADC1 Test;							

 *  Platform                                   :    NUCLEO-STM32F401RE
 *  RTOS                                       :    KEIL RTX
 																			 
 *--------------------------------Revision History--------------------------------------
 *  No         Version         Date        RevisedBy        Item         Description  
 *  1          V1.0           2017/05/12  Twsa                 None           None
 
 **************************************************************************************/
#include "arm_math.h"
#include <cmsis_os.h>
#include "Serial.h"
#include "sys.h"
#include "board_driver.h"
#include "adc.h"



int main(void)
{
//		SCB->CCR |=SCB_CCR_STKALIGN_Msk;       //使能双字栈对齐
  /* STM32F4xx HAL library initialization:
       - Configure the Flash prefetch, Flash preread and Buffer caches
       - Systick timer is configured by default as source of time base, but user 
             can eventually implement his proper time base source (a general purpose 
             timer for example or other time source), keeping in mind that Time base 
             duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and 
             handled in milliseconds basis.
       - Low Level Initialization
     */
//  HAL_Init();
	
	SystemClock_Config();
	SER_Initialize();
	BSP_PB_Init(BUTTON_KEY,BUTTON_MODE_EXTI);
	GPIO_Config();
//	Uart2_Init();
//  Uart2_Test();

  /* -3- Toggle PA05 IO in an infinite loop */  

//  while (1)
//  {
//			HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);
//	 /* Insert delay 100 ms */
//   osDelay(100);
//  }
   ADC1_Config();
   while(1);
}
