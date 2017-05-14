/*
Brief: 基础DMA传输配置
Author:Twsa Liu
Date:2017/05/13
*/
#include "sys.h"
#include "stm32f4xx.h"
#include "uart2.h"


void DMA_Config(void)
{

	DMA_HandleTypeDef  hdma_tx,hdma_rx;     
	
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
	
//	HAL_DMA_Start(&hdma_tx,(uint32_t)&testbuffer,(uint32_t)&(USART2->DR)/*USART2 数字寄存器*/,sizeof(testbuffer));  
//	HAL_DMA_IRQHandler(huart.hdmatx);
}


