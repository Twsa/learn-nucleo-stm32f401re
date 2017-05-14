/*
Brief:UART2配置文件
Aurhor:Twsa Liu
Date:2017/05/14
*/
#include "uart2.h"
#include "board_driver.h"
UART_HandleTypeDef  uart2_handle;

/***USART2 IO口配置****/
void USART2_GPIO_Config(void)
{
				GPIO_InitTypeDef GPIO_InitStruct;
				/* Peripheral clock enable */
				__USART2_CLK_ENABLE();
				__GPIOA_CLK_ENABLE();
        __HAL_UART_ENABLE_IT(&uart2_handle,UART_IT_TC);
	      __HAL_UART_ENABLE_IT(&uart2_handle,UART_IT_RXNE);
	
				/**USART2 GPIO Configuration    
				PA3     ------> USART2_RX
				PA2     ------> USART2_TX 
				*/
				GPIO_InitStruct.Pin = GPIO_PIN_3 | GPIO_PIN_2;
				GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
				GPIO_InitStruct.Pull = GPIO_NOPULL;
				GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
				GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
				HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

				HAL_NVIC_SetPriority(USART2_IRQn, 0, 0X0F);  //Configure the USARTx interrupt priority
				HAL_NVIC_EnableIRQ(USART2_IRQn);                 //Enable the NVIC USART IRQ handle
}

/*********************************************************************
* @fn      Uart2_Init()
*
* @brief   uart2 initiate
*
* @param   none
* @return  none
*/
void Uart2_Init(void)
{
        uart2_handle.Instance = USART2;
        uart2_handle.Init.BaudRate = 115200;
        uart2_handle.Init.WordLength = UART_WORDLENGTH_8B;
        uart2_handle.Init.StopBits = UART_STOPBITS_1;
        uart2_handle.Init.Parity = UART_PARITY_NONE;
        uart2_handle.Init.Mode = UART_MODE_TX_RX;
        uart2_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
        uart2_handle.Init.OverSampling = UART_OVERSAMPLING_16;

        if (HAL_UART_Init(&uart2_handle) != HAL_OK) {
                Error_Handler();
        }
}

/***UART2 正常发送数据****/
void USART2_Tx_Normal(uint8_t * tx_pData,uint16_t Size,uint32_t Timeout)
{
    HAL_StatusTypeDef uart_state=HAL_BUSY;
	  while(uart_state!=HAL_OK)
		{
				uart_state=HAL_UART_Transmit(&uart2_handle,tx_pData,Size,Timeout);
		}
}

/***UART2 正常接收数据****/
void USART2_Rx_Normal(uint8_t * rx_pData,uint16_t Size,uint32_t Timeout)
{
    HAL_StatusTypeDef uart_state=HAL_BUSY;
	 /*可以设置结束数据长度达到预定的长度时结束接受*/
	  while(uart_state!=HAL_OK)  
		{
				uart_state=HAL_UART_Receive(&uart2_handle,rx_pData,Size,Timeout);
			 /***设置停止位***/		
		}
}


/***UART2 测试函数***/
void Uart2_Test(void)
{
  uint8_t rx_buf[4]="123";
	
//	USART2_Rx_Normal(rx_buf,sizeof(rx_buf),30);
//  USART2_Tx_Normal(rx_buf,sizeof(rx_buf),30);
	
	HAL_UART_Transmit_DMA(&uart2_handle,rx_buf,sizeof(rx_buf));

	//  HAL_UART_Receive_IT(&uart2_handle,rx_buf,sizeof(rx_buf));   //中断接受  USART 中断接受还不懂
//  HAL_UART_Transmit_IT(&uart2_handle,rx_buf,sizeof(rx_buf));   //中断发送

}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	printf("UART TX Complete!\r\n");
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
		printf("UART RX Complete!\r\n");
}