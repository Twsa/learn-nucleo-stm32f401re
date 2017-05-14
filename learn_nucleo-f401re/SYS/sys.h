#ifndef __SYS_H_
#define __SYS_H_
//#define HAL_ADC_MODULE_ENABLED

#include "stm32f4xx.h"
#include "thread_manage.h"

uint32_t BSP_GetVersion(void);
void SystemCoreClockConfigure(void);
 void Error_Handler(void);
 
void SystemClock_Config(void);
void View_Clock(void);
extern void HAL_RCC_CSSCallback(void);
extern void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void GPIO_Config(void);
void View_GPIO(void);

//void DMA_Config(void);
#endif

