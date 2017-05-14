#include "board_driver.h"
#include "adc.h"

/*************************************************************************************
 *  File Name                                :adc.c
 
 *  Create Date                             :    2017/05/14
 *  Author/Corporation                  :   Twsa  Liu
 *  Description                               :   ADC1配置
 *  setup ADC1  使用dma进行转化
 *  1. ADC driver can be used among three modes: polling, interruption, transfer by DMA

 *  Platform                                   :    NUCLEO-STM32F401RE
 *  RTOS                                       :    KEIL RTX
 																			 
 *--------------------------------Revision History--------------------------------------
 *  No         Version         Date        RevisedBy        Item         Description  
 *  1          V1.0           2017/05/12  Twsa                 None           None
 
 **************************************************************************************/
// Note: The temperature sensor, VREFINT and the VBAT channel are available only on the master
//ADC1 peripheral.
uint32_t  VSENSE[10]={0};

ADC_HandleTypeDef                  ADC_Handle_Structure;
void ADC1_Config(void)
{
	int index=0;
	
	ADC_InitTypeDef                         ADC_Init_Structure;
	ADC_ChannelConfTypeDef        ADC_ChannelConf_Structure;
  DMA_HandleTypeDef                  hdma_adc;    
	__ADC1_CLK_ENABLE();             //ADC时钟使能
	
	ADC_Init_Structure.ClockPrescaler=ADC_CLOCK_SYNC_PCLK_DIV2;
	ADC_Init_Structure.DataAlign=ADC_DATAALIGN_RIGHT;             //数据右对齐
	ADC_Init_Structure.Resolution=ADC_RESOLUTION_12B;           //分辨率为12位
	ADC_Init_Structure.ScanConvMode=ENABLE;
	ADC_Init_Structure.EOCSelection=ADC_EOC_SINGLE_CONV;  //单次转换触发中断
	ADC_Init_Structure.ContinuousConvMode=ENABLE;                      //连续转化模式使能
	ADC_Init_Structure.NbrOfConversion=1;                                           //ADC规转化序列的数字识别码
	ADC_Init_Structure.DiscontinuousConvMode=DISABLE;
	ADC_Init_Structure.NbrOfDiscConversion=1;                      //discared;
	ADC_Init_Structure.ExternalTrigConv=ADC_SOFTWARE_START;  //软件触发ADC转换
	ADC_Init_Structure.DMAContinuousRequests=ENABLE;                   //连续请求DMA传输
//	ADC_Init_Structure.DMAContinuousRequests=DISABLE;     
	
		/***通道配置结构体***/
	ADC_ChannelConf_Structure.Channel=ADC_CHANNEL_16;
	ADC_ChannelConf_Structure.Rank=1;
	ADC_ChannelConf_Structure.SamplingTime=ADC_SAMPLETIME_56CYCLES;
	ADC_ChannelConf_Structure.Offset=0;
	
	/***ADC看门口设置***/
	
	
		/***配置DMA传输***/
		__HAL_RCC_DMA2_CLK_ENABLE();                 

		/* Configure the DMA handler for Transmission process */
		hdma_adc.Instance=DMA2_Stream4;                   //USART2 DMA2发送数据流num是4
		hdma_adc.Init.Channel=DMA_CHANNEL_0;                         //选择DMA 通道0
		hdma_adc.Init.Direction=DMA_MEMORY_TO_PERIPH;     //DMA数据传输方向，从内存到外设
		hdma_adc.Init.PeriphInc=DMA_PINC_DISABLE;                   //外设地址增加的模式禁止
		hdma_adc.Init.MemInc=DMA_MINC_ENABLE;                     //内存地址增加的模式
		hdma_adc.Init.PeriphDataAlignment=DMA_PDATAALIGN_BYTE;  //外设数据宽度 字节
		hdma_adc.Init.MemDataAlignment=DMA_MDATAALIGN_BYTE;    //内存数据宽度 字节
		hdma_adc.Init.Mode=DMA_NORMAL;                                       //DMA模式 循环模式
		hdma_adc.Init.Priority=DMA_PRIORITY_LOW;                           //低优先级
		hdma_adc.Init.FIFOMode=DMA_FIFOMODE_DISABLE;            //禁止FIFO模式
		hdma_adc.Init.FIFOThreshold=DMA_FIFO_THRESHOLD_FULL;   //阈值级别配为 “满”
		hdma_adc.Init.MemBurst=DMA_MBURST_INC4;
		hdma_adc.Init.PeriphBurst=DMA_PBURST_INC4;
						 
		HAL_DMA_Init(&hdma_adc);

		/* Associate the initialized DMA handle to the the ADC1 handle */
		__HAL_LINKDMA(&ADC_Handle_Structure, DMA_Handle, hdma_adc);

		/* NVIC configuration for DMA transfer complete interrupt (USARTx_TX) */
		HAL_NVIC_SetPriority(DMA2_Stream4_IRQn, 0, 12);
		HAL_NVIC_EnableIRQ(DMA2_Stream4_IRQn);
			
	/***ADC操作句柄***/
	ADC_Handle_Structure.Instance=ADC1;                 //ADC  Handle使用的是ADC1
	ADC_Handle_Structure.Init=ADC_Init_Structure;
	ADC_Handle_Structure.DMA_Handle=&hdma_adc;
  


	/***配置ADC中断等级***/
//	HAL_NVIC_SetPriority(ADC_IRQn, 0, 11);   
//	HAL_NVIC_EnableIRQ(ADC_IRQn);   
	HAL_ADC_Init(&ADC_Handle_Structure);
	HAL_ADC_ConfigChannel(&ADC_Handle_Structure,&ADC_ChannelConf_Structure);
	ADC->CCR |=(1UL<<7);                  //使能内部温度传感器
	
	float Temperature=0;
	float V25=760;
	float Avg_Slope=2.5;
	float  Value[10]={0};
	while(index<10)
	{	
		/***单次转换触发中断，DMA中断或者ADC中断***/
		  HAL_ADC_Start_DMA(&ADC_Handle_Structure,VSENSE,10);                     //一次实现该函数即一次实现ADC转化10次
		  VSENSE[index]=HAL_ADC_GetValue (&ADC_Handle_Structure);           //Gets the converted value from data register of regular channel
		  Value[index] =( ((float)VSENSE[index])*3300 )/4096;
	    Temperature = ( ( Value[index] - V25) / Avg_Slope)+ 25;              //温度转换
			 printf("VSENSE  : %d\r\n",VSENSE[index]);
		   printf("Temperature (in C) : %f  C\r\n",Temperature);
		  index++;
	}
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	printf("HAL_ADC_ConvCpltCallback!\r\n");
}
