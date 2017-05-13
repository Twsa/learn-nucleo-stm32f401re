#include "sys.h"
#include "adc.h"
/*************************************************************************************
 *  File Name                                :adc.c
 
 *  Create Date                             :    2017/05/12
 *  Author/Corporation                  :   Twsa
 *  Description                               :   ADC1配置

 *  Platform                                   :    NUCLEO-STM32F401RE
 *  RTOS                                       :    KEIL RTX
 																			 
 *--------------------------------Revision History--------------------------------------
 *  No         Version         Date        RevisedBy        Item         Description  
 *  1          V1.0           2017/05/12  Twsa                 None           None
 
 **************************************************************************************/
// Note: The temperature sensor, VREFINT and the VBAT channel are available only on the master
//ADC1 peripheral.

/***setup ADC1****/
void ADC1_Initilize(void)
{
	RCC->AHB1ENR |=(1ul<<0);          //enable GPIOA clock
//	RCC->APB2ENR &=~0xffff;              //clear APB2ENR reg bits
	
	  /* Setup and initialize ADC converter                                       */
	ADC->CCR |=(1UL<<23);               /*1: Temperature sensor and VREFINT channel enabled*/
//	RCC->CFGR |= ( 6ul << 13);           	/* ADC clk = PCLK2 / 8              */
	ADC->CCR |=(3UL<<16);                  /* 11: PCLK2 divided by 8 */
	RCC->APB2ENR |=0x100;                //enable ADC1 clock;
	
	
	ADC1->CR1 &=~0XFFFF;
	ADC1->CR1 |=(2UL<<24);                               //RES  11: 6-bit (9 ADCCLK cycles)
	ADC1->CR1 |=(1UL<<8);                                 //1: Scan mode enabled
  ADC1->CR1 |=(1UL<<5);                                 //1: EOC interrupt enabled. An interrupt is generated when the EOC bit is set.
	
	ADC1->CR2 &=~0XFFFF;  
	ADC1->CR2 |=(1UL<<30);                               //SWSTART   1: Starts conversion of regular channels
//	ADC1->CR2 |=(1UL<<11);                               //1: Left alignment
	ADC1->CR2 |=(3UL<<0);                                 //Continuous conversion mode Enable ADC
	
	ADC1->SMPR1&=~0XFFFF;
	ADC1->SMPR1 |=(3UL<<24);
	
	ADC1->SQR1 &=0XFFFF;
	ADC1->SQR1 = 0;                     	/* Regular chn. Sequence length = 1 */
	ADC1->SQR2 = 0;                     	/* Clear register                   */
	ADC1->SQR3 = (16UL << 0);           		/* 1. conversion = channe 16        */
}



