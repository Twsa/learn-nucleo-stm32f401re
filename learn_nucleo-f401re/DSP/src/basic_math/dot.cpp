/*************************************************************************************
 *  File Name                                :dot.cpp
 
 *  Create Date                             :    2017/05/06
 *  Author/Corporation                  :   Twsa
 *  Description                               :   使用RTOS 编程习惯学习M4 DSP库 
                                                          basic math multiplied element-by-element and  then summed

 *  Platform                                   :    NUCLEO-STM32F401RE
 *  RTOS                                       :    KEIL RTX
 																			 
 *--------------------------------Revision History--------------------------------------
 *  No         Version         Date        RevisedBy        Item         Description  
 *  1          V1.0           2017/05/06 Twsa                 None           None
 
 **************************************************************************************/
#include "basic_math.h"
#include "arm_math.h"
#include <cmsis_os.h>

float32_t dot_pSrcA[3]={-0.432565,	-1.665584,	0.125332};
float32_t dot_pSrcB[3]={-1.146471,	1.190915,	1.189164};
float32_t dot_pDst[3]={0};

float32_t dot_tmp_A=0.0;
float32_t dot_tmp_B=0.0;
int dot_i=0;

void dot_thread(void const *agrument)
{
		 	arm_dot_prod_f32(dot_pSrcA,dot_pSrcB,3,dot_pDst);

	for(;;)
	{
		if(dot_i>3)  dot_i=0;
		  osDelay(1000);
		  dot_tmp_A=dot_pSrcA[dot_i];
		  dot_tmp_B=dot_pSrcB[dot_i];
		  dot_i++;
	}
}