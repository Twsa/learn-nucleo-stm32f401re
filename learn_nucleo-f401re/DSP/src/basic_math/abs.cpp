/*************************************************************************************
 *  File Name                                :arm_abs_f32.c
 
 *  Create Date                             :    2017/05/05
 *  Author/Corporation                  :   Twsa
 *  Description                               :   使用RTOS 编程习惯学习M4 DSP库 
                                                          basic math abs() test

 *  Platform                                   :    NUCLEO-STM32F401RE
 *  RTOS                                       :    KEIL RTX
 																			 
 *--------------------------------Revision History--------------------------------------
 *  No         Version         Date        RevisedBy        Item         Description  
 *  1          V1.0           2017/05/05 Twsa                 None           None
 
 **************************************************************************************/
#include "arm_math.h"
#include <cmsis_os.h>
#include "basic_math.h"

float32_t abs_pSrc[3]={-0.432565,	-1.665584,	0.125332};
float32_t abs_pDst[3]={0};
float32_t abs_tmp=0.0;
int abs_i=0;
void abs_thread(void const *argument)
{
	arm_abs_f32(abs_pSrc,abs_pDst,3);
//	arm_abs_q15	(pSrc,pDst,3);
// arm_abs_q31
//arm_abs_q7
	for(;;)
	{
		if(abs_i>3)  abs_i=0;
		  osDelay(1000);
      abs_tmp=abs_pDst[abs_i];
		  abs_i++;
	}
}