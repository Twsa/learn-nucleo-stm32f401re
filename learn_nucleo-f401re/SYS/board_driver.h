#ifndef __BOARD_DRIVER_H
#define __BOARD_DRIVER_H
 #include "sys.h"
#include "uart2.h"
#include "Serial.h"

typedef enum
{
	BUTTON_USER =0 ,
	/*Alias*/
	BUTTON_KEY = BUTTON_USER
} Button_TypeDef;

typedef enum
{
	 BUTTON_MODE_GPIO =0,
	 BUTTON_MODE_EXTI =1
}ButtonMode_TypeDef;

/**
  * @brief Key push-button
  */
#define BUTTONn                                                              1  
#define USER_BUTTON_PIN                                           GPIO_PIN_13
#define USER_BUTTON_GPIO_PORT                            GPIOC
#define USER_BUTTON_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOC_CLK_ENABLE()   
#define USER_BUTTON_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOC_CLK_DISABLE()  
#define USER_BUTTON_EXTI_LINE                               GPIO_PIN_13
#define USER_BUTTON_EXTI_IRQn                               EXTI15_10_IRQn

#define BUTTONx_GPIO_CLK_ENABLE(__INDEX__)       USER_BUTTON_GPIO_CLK_ENABLE()
#define BUTTONx_GPIO_CLK_DISABLE(__INDEX__)      USER_BUTTON_GPIO_CLK_DISABLE()

/* Aliases */
#define KEY_BUTTON_PIN                                                USER_BUTTON_PIN
#define KEY_BUTTON_GPIO_PORT                                USER_BUTTON_GPIO_PORT
#define KEY_BUTTON_GPIO_CLK_ENABLE()               USER_BUTTON_GPIO_CLK_ENABLE()
#define KEY_BUTTON_GPIO_CLK_DISABLE()              USER_BUTTON_GPIO_CLK_DISABLE()
#define KEY_BUTTON_EXTI_LINE                                   USER_BUTTON_EXTI_LINE
#define KEY_BUTTON_EXTI_IRQn                                   USER_BUTTON_EXTI_IRQn


void             BSP_PB_Init(Button_TypeDef Button, ButtonMode_TypeDef ButtonMode);
void             BSP_PB_DeInit(Button_TypeDef Button);
uint32_t       BSP_PB_GetState(Button_TypeDef Button);void             BSP_PB_Init(Button_TypeDef Button, ButtonMode_TypeDef ButtonMode);
void             BSP_PB_DeInit(Button_TypeDef Button);
uint32_t       BSP_PB_GetState(Button_TypeDef Button);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

#endif