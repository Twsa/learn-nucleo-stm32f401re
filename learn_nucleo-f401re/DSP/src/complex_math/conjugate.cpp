/*************************************************************************************
 *  File Name                                :conjugate.cpp
 
 *  Create Date                             :    2017/05/07
 *  Author/Corporation                  :   Twsa
 *  Description                               :   使用RTOS 编程习惯学习M4 DSP库 
                                                          basic math conjugate() test

 *  Platform                                   :    NUCLEO-STM32F401RE
 *  RTOS                                       :    KEIL RTX
 																			 
 *--------------------------------Revision History--------------------------------------
 *  No         Version         Date        RevisedBy        Item         Description  
 *  1          V1.0           2017/05/07 Twsa                 None           None
 
 **************************************************************************************/
#include "complex_math.h"
#include "arm_math.h"
#include <cmsis_os.h>
 

 float32_t conjugate_pSrc[32] =
{
  -1.244916875853235400,  -4.793533929171324800,   0.360705030233248850,   0.827929644170887320,  -3.299532218312426900,   3.427441903227623800,   3.422401784294607700,  -0.108308165334010680,
   0.941943896490312180,   0.502609575000365850,  -0.537345278736373500,   2.088817392965764500,  -1.693168684143455700,   6.283185307179590700,  -0.392545884746175080,   0.327893095115825040,
   3.070147440456292300,   0.170611405884662230,  -0.275275082396073010,  -2.395492805446796300,   0.847311163536506600,  -3.845517018083148800,   2.055818378415868300,   4.672594161978930800,
  -1.990923030266425800,   2.469305197656249500,   3.609002606064021000,  -4.586736582331667500,  -4.147080139136136300,   1.643756718868359500,  -1.150866392366494800,   1.985805026477433800
};
float32_t conjugate_pDst[32]={0};
float32_t conjugate_pSrc_tmp=0.0;
float32_t conjugate_pDst_tmp=0.0;
int conjugate_i=0;

void conjugate_thread(void const *agrument)
{
	arm_cmplx_conj_f32 (conjugate_pSrc, conjugate_pDst,16);
	for(;;)
	{
		if(conjugate_i>32)  conjugate_i=0;
		  osDelay(1000);
      conjugate_pSrc_tmp=conjugate_pSrc[conjugate_i];
		  conjugate_pDst_tmp=conjugate_pDst[conjugate_i];
		  conjugate_i++;
	}
}