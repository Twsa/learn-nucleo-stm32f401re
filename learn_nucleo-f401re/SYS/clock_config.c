#include "stm32f4xx.h"
#include "sys.h"

/********利用STM32F4XX硬件抽象层库对时钟进行配置******/
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef   RCC_OscInitType_Structure;
	RCC_PLLInitTypeDef   RCC_PLLInit_Structure;
  RCC_ClkInitTypeDef     RCC_ClkInitType_Structure;
//	HAL_RCC_DeInit();                 //RCC初始化
	
	  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();
  
  /* The voltage scaling allows optimizing the power consumption when the device is 
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
	
	/***PLL参数初始化***/
  RCC_PLLInit_Structure.PLLState=RCC_PLL_ON;                                  //使能PLL倍频锁相环
	RCC_PLLInit_Structure.PLLSource=RCC_PLLCFGR_PLLSRC_HSI; //HSI内部RC作为PLL锁相环时钟源
	RCC_PLLInit_Structure.PLLM=16;                       //VCO  output 除法除数
	RCC_PLLInit_Structure.PLLN=336;                     //VCO乘法因子
	RCC_PLLInit_Structure.PLLP=RCC_PLLP_DIV4;
	RCC_PLLInit_Structure.PLLQ=7;                       //Division factor for OTG FS, SDIO and RNG clocks.
	
	/****晶振初始化******/
	RCC_OscInitType_Structure.OscillatorType=RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitType_Structure.HSEState=RCC_HSE_OFF;
	RCC_OscInitType_Structure.LSEState=RCC_LSE_OFF;
	RCC_OscInitType_Structure.HSIState=RCC_HSI_ON;           //使用内部时钟  NUCLEO-STM32F401RE
	RCC_OscInitType_Structure.HSICalibrationValue=RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitType_Structure.LSIState=RCC_LSI_OFF;
  RCC_OscInitType_Structure.PLL=RCC_PLLInit_Structure;
	HAL_RCC_OscConfig(&RCC_OscInitType_Structure);
	
	/***配置系统时钟，外设时钟***/
	RCC_ClkInitType_Structure.ClockType=(RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitType_Structure.SYSCLKSource=RCC_SYSCLKSOURCE_PLLCLK;  //PLLCLK作为系统时钟源
	RCC_ClkInitType_Structure.AHBCLKDivider=RCC_SYSCLK_DIV1;
	RCC_ClkInitType_Structure.APB1CLKDivider=RCC_HCLK_DIV2;
	RCC_ClkInitType_Structure.APB2CLKDivider=RCC_HCLK_DIV1;
	
		HAL_RCC_ClockConfig(&RCC_ClkInitType_Structure,FLASH_LATENCY_2);
		
	/***配置系统时钟输出****/
	//PA8 MCO1  外部输出时钟源为内部RC振荡器  
  //	HAL_RCC_MCOConfig(RCC_MCO1,RCC_MCO1SOURCE_HSI,RCC_MCODIV_4);  //4M Hz
	
	/*
		If a failure is detected on the HSE oscillator clock, this
		oscillator is automatically disabled and an interrupt is
		generated to inform the software about the failure (Clock
		Security System Interrupt, CSSI), allowing the MCU to
		perform rescue operations. The CSSI is linked to the Co
		M4 NMI (Non-Maskable Interrupt) exception vector.
	*/
  HAL_RCC_EnableCSS();                                 //使能时钟安全系统
  //	HAL_RCC_DisableCSS();
  __HAL_RCC_GPIOA_CLK_ENABLE();          //AHB1外设时钟
  __HAL_RCC_ADC1_CLK_ENABLE();            //APB2 ADC时钟

}

void HAL_RCC_CSSCallback(void)
{
	printf("HSE Setup failure ,CCS Interrupt occur!\r\n");
}

