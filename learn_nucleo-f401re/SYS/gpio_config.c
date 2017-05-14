/***
Brief:GPIO 配置文件
Author:Twsa Liu
Date:2017/05/13
**/
#include "sys.h"
#include "board_driver.h"
#include "uart2.h"

void GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_Init_Structure_LED;

	GPIO_Init_Structure_LED.Pin=GPIO_PIN_5;
	GPIO_Init_Structure_LED.Mode=GPIO_MODE_OUTPUT_PP;    //推挽输出
	GPIO_Init_Structure_LED.Pull=GPIO_NOPULL;                             
	GPIO_Init_Structure_LED.Speed=GPIO_SPEED_FREQ_MEDIUM;
	//	GPIO_Init_Structure.Alternate=                            //I don't konw what does it mean;
	
	GPIO_InitTypeDef GPIO_Init_Structure_Input;
  GPIO_Init_Structure_Input.Pin=GPIO_PIN_6;
	GPIO_Init_Structure_Input.Mode=GPIO_MODE_INPUT;    //输入模式
	GPIO_Init_Structure_Input.Pull=GPIO_PULLDOWN;                             
//	GPIO_Init_Structure.Speed=GPIO_SPEED_FREQ_MEDIUM;            
	
	HAL_GPIO_Init(GPIOA,&GPIO_Init_Structure_LED);
	HAL_GPIO_Init(GPIOA,&GPIO_Init_Structure_Input);
	USART2_GPIO_Config();                                //USART2 硬件初始化
}



/** @defgroup STM32F4XX_NUCLEO_LOW_LEVEL_Private_Variables STM32F4XX NUCLEO LOW LEVEL Private Variables
  * @{
  */ 

GPIO_TypeDef* BUTTON_PORT[BUTTONn] = {KEY_BUTTON_GPIO_PORT}; 
const uint16_t BUTTON_PIN[BUTTONn] = {KEY_BUTTON_PIN}; 
const uint8_t BUTTON_IRQn[BUTTONn] = {KEY_BUTTON_EXTI_IRQn};
/**
  * @brief  Configures Button GPIO and EXTI Line.
  * @param  Button: Specifies the Button to be configured.
  *   This parameter should be: BUTTON_KEY
  * @param  ButtonMode: Specifies Button mode.
  *   This parameter can be one of following parameters:   
  *     @arg BUTTON_MODE_GPIO: Button will be used as simple IO 
  *     @arg BUTTON_MODE_EXTI: Button will be connected to EXTI line with interrupt
  *                            generation capability  
  */
void BSP_PB_Init(Button_TypeDef Button, ButtonMode_TypeDef ButtonMode)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  
  /* Enable the BUTTON Clock */
  BUTTONx_GPIO_CLK_ENABLE(Button);
  
  if(ButtonMode == BUTTON_MODE_GPIO)
  {
    /* Configure Button pin as input */
    GPIO_InitStruct.Pin = BUTTON_PIN[Button];
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
    HAL_GPIO_Init(BUTTON_PORT[Button], &GPIO_InitStruct);
  }
  
  if(ButtonMode == BUTTON_MODE_EXTI)
  {
    /* Configure Button pin as input with External interrupt */
    GPIO_InitStruct.Pin = BUTTON_PIN[Button];
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING; 
    HAL_GPIO_Init(BUTTON_PORT[Button], &GPIO_InitStruct);
    
    /* Enable and set Button EXTI Interrupt to the lowest priority */
    HAL_NVIC_SetPriority((IRQn_Type)(BUTTON_IRQn[Button]), 0x0F, 0x0F);
    HAL_NVIC_EnableIRQ((IRQn_Type)(BUTTON_IRQn[Button]));
  }
}

/**
  * @brief  Push Button DeInit.
  * @param  Button: Button to be configured
  *   This parameter should be: BUTTON_KEY
  * @note PB DeInit does not disable the GPIO clock
  */
void BSP_PB_DeInit(Button_TypeDef Button)
{
    GPIO_InitTypeDef gpio_init_structure;

    gpio_init_structure.Pin = BUTTON_PIN[Button];
    HAL_NVIC_DisableIRQ((IRQn_Type)(BUTTON_IRQn[Button]));
    HAL_GPIO_DeInit(BUTTON_PORT[Button], gpio_init_structure.Pin);
}

/**
  * @brief  Returns the selected Button state.
  * @param  Button: Specifies the Button to be checked.
  *   This parameter should be: BUTTON_KEY  
  * @retval The Button GPIO pin value.
  */
uint32_t BSP_PB_GetState(Button_TypeDef Button)
{
  return HAL_GPIO_ReadPin(BUTTON_PORT[Button], BUTTON_PIN[Button]);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
		printf("EXTI Interrupt ocurr x\r\n");

}
