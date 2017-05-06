/*************************************************************************************
 *  File Name                                :mult.cpp
 
 *  Create Date                             :    2017/05/06
 *  Author/Corporation                  :   Twsa
 *  Description                               :   使用RTOS 编程习惯学习M4 DSP库 
                                                          basic math mult() test

 *  Platform                                   :    NUCLEO-STM32F401RE
 *  RTOS                                       :    KEIL RTX
 																			 
 *--------------------------------Revision History--------------------------------------
 *  No         Version         Date        RevisedBy        Item         Description  
 *  1          V1.0           2017/05/06 Twsa                 None           None
 
 **************************************************************************************/
#include "basic_math.h"
#include "arm_math.h"
#include <cmsis_os.h>


float32_t mult_pSrcA[3]={4.432565,	2.665584,	1.125332};
float32_t mult_pSrcB[3]={1.146471,	3.190915,	3.189164};
float32_t mult_pDst[3]={0};
float32_t mult_tmp_A=0.0;
float32_t mult_tmp_B=0.0;
float32_t mult_tmp_pDst=0.0;
int mult_i=0;

void mult_thread(void const *agrument)
{
	 	arm_mult_f32(mult_pSrcA,mult_pSrcB,mult_pDst,3);

	for(;;)
	{
		if(mult_i>3)  mult_i=0;
		  osDelay(1000);
		  mult_tmp_A=mult_pSrcA[mult_i];
		  mult_tmp_B=mult_pSrcB[mult_i];
      mult_tmp_pDst=mult_pDst[mult_i];
		  mult_i++;
	}
}