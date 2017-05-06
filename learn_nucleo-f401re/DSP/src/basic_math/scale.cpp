/*************************************************************************************
 *  File Name                                :scale.cpp
 
 *  Create Date                             :    2017/05/06
 *  Author/Corporation                  :   Twsa
 *  Description                               :   使用RTOS 编程习惯学习M4 DSP库 
                                                          basic math scale() test

 *  Platform                                   :    NUCLEO-STM32F401RE
 *  RTOS                                       :    KEIL RTX
 																			 
 *--------------------------------Revision History--------------------------------------
 *  No         Version         Date        RevisedBy        Item         Description  
 *  1          V1.0           2017/05/06 Twsa                 None           None
 
 **************************************************************************************/
#include "basic_math.h"
#include "arm_math.h"
#include <cmsis_os.h>


float32_t scale_pSrc[3]={0.432565,	1.665584,	0.125332};
float32_t scale_pDst[3]={0};
float32_t scale=2.1111;
float32_t scale_tmp=0.0;
float32_t scale_tmp_pDst=0.0;
int scale_i=0;

void scale_thread(void const *agrument)
{
	 	arm_scale_f32(scale_pSrc,scale,scale_pDst,3);

	for(;;)
	{
		if(scale_i>3)  scale_i=0;
		  osDelay(1000);
		  scale_tmp=scale_pSrc[scale_i];
      scale_tmp_pDst=scale_pDst[scale_i];
		  scale_i++;
	}
}