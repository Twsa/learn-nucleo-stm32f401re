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

				HAL_NVIC_SetPriority(USART2_IRQn, 0, 15);  //Configure the USARTx interrupt priority
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
			  DMA_HandleTypeDef  hdma_tx,hdma_rx;     
	
        uart2_handle.Instance = USART2;
        uart2_handle.Init.BaudRate = 115200;
        uart2_handle.Init.WordLength = UART_WORDLENGTH_8B;
        uart2_handle.Init.StopBits = UART_STOPBITS_1;
        uart2_handle.Init.Parity = UART_PARITY_NONE;
        uart2_handle.Init.Mode = UART_MODE_TX_RX;
        uart2_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
        uart2_handle.Init.OverSampling = UART_OVERSAMPLING_16;

      /***配置DMA传输***/
			__HAL_RCC_DMA1_CLK_ENABLE();  

			/* Configure the DMA handler for Transmission process */
			hdma_tx.Instance=DMA1_Stream6;                   //USART2 DMA1发送数据流num是6
			hdma_tx.Init.Channel=DMA_CHANNEL_4;                         //选择DMA 通道4
			hdma_tx.Init.Direction=DMA_MEMORY_TO_PERIPH;     //DMA数据传输方向，从内存到外设
			hdma_tx.Init.PeriphInc=DMA_PINC_DISABLE;                   //外设地址增加的模式禁止
			hdma_tx.Init.MemInc=DMA_MINC_ENABLE;                     //内存地址增加的模式
			hdma_tx.Init.PeriphDataAlignment=DMA_PDATAALIGN_BYTE;  //外设数据宽度 字节
			hdma_tx.Init.MemDataAlignment=DMA_MDATAALIGN_BYTE;    //内存数据宽度 字节
			hdma_tx.Init.Mode=DMA_NORMAL;                                       //DMA模式 正常模式
			hdma_tx.Init.Priority=DMA_PRIORITY_LOW;                           //低优先级
			hdma_tx.Init.FIFOMode=DMA_FIFOMODE_DISABLE;            //使能FIFO模式
			hdma_tx.Init.FIFOThreshold=DMA_FIFO_THRESHOLD_FULL;   //阈值级别配为 “满”
			hdma_tx.Init.MemBurst=DMA_MBURST_INC4;
			hdma_tx.Init.PeriphBurst=DMA_PBURST_INC4;
								 
			HAL_DMA_Init(&hdma_tx);

			/* Associate the initialized DMA handle to the the UART handle */
			__HAL_LINKDMA(&uart2_handle, hdmatx, hdma_tx);

			/* Configure the DMA handler for Transmission process */
			hdma_rx.Instance=DMA1_Stream5;                   //USART2 DMA1接受数据流num是5
			hdma_rx.Init.Channel=DMA_CHANNEL_4;                         //选择DMA 通道4
			hdma_rx.Init.Direction=DMA_PERIPH_TO_MEMORY;     //DMA数据传输方向，从外设到内存
			hdma_rx.Init.PeriphInc=DMA_PINC_DISABLE;                   //外设地址增加的模式禁止
			hdma_rx.Init.MemInc=DMA_MINC_ENABLE;                     //内存地址增加的模式
			hdma_rx.Init.PeriphDataAlignment=DMA_PDATAALIGN_BYTE;  //外设数据宽度 字节
			hdma_rx.Init.MemDataAlignment=DMA_MDATAALIGN_BYTE;    //内存数据宽度 字节
			hdma_rx.Init.Mode=DMA_NORMAL;                                       //DMA模式 正常模式
			hdma_rx.Init.Priority=DMA_PRIORITY_HIGH;                           //高优先级
			hdma_rx.Init.FIFOMode=DMA_FIFOMODE_DISABLE;            //使能FIFO模式
			hdma_rx.Init.FIFOThreshold=DMA_FIFO_THRESHOLD_FULL;   //阈值级别配为 “满”
			hdma_rx.Init.MemBurst=DMA_MBURST_INC4;
			hdma_rx.Init.PeriphBurst=DMA_PBURST_INC4;

			HAL_DMA_Init(&hdma_rx);
			/* Associate the initialized DMA handle to the the UART handle */
			__HAL_LINKDMA(&uart2_handle, hdmarx, hdma_rx);

			/* NVIC configuration for DMA transfer complete interrupt (USARTx_TX) */
			HAL_NVIC_SetPriority(DMA1_Stream6_IRQn, 0, 13);
			HAL_NVIC_EnableIRQ(DMA1_Stream6_IRQn);

			/* NVIC configuration for DMA transfer complete interrupt (USARTx_RX) */
			HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 0, 14);   
			HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);   
			
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