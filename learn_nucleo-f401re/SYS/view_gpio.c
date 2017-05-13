#include "sys.h"
#include "Serial.h"
/***
   查看GPIO基本功能
	 查看输入输出情况
***/

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

uint32_t GPIO_ReadPin_PA6=GPIO_PIN_RESET;

void View_GPIO(void)
{
	GPIO_ReadPin_PA6=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6);
	
//	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);

	printf("GPIO_ReadPin_PA6:%d\r\n",GPIO_ReadPin_PA6);
}

