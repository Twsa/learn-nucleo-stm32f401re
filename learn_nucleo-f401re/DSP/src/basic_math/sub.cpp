/*************************************************************************************
 *  File Name                                :sub.cpp
 
 *  Create Date                             :    2017/05/06
 *  Author/Corporation                  :   Twsa
 *  Description                               :   使用RTOS 编程习惯学习M4 DSP库 
                                                          basic math sub() test

 *  Platform                                   :    NUCLEO-STM32F401RE
 *  RTOS                                       :    KEIL RTX
 																			 
 *--------------------------------Revision History--------------------------------------
 *  No         Version         Date        RevisedBy        Item         Description  
 *  1          V1.0           2017/05/06 Twsa                 None           None
 
 **************************************************************************************/
#include "basic_math.h"
#include "arm_math.h"
#include <cmsis_os.h>


float32_t sub_pSrcA[3]={-0.432565,	-1.665584,	0.125332};
float32_t sub_pSrcB[3]={-1.146471,	1.190915,	1.189164};
float32_t sub_pDst[3]={0};
float32_t sub_tmp_pDst=0.0;
int sub_i=0;

void sub_thread(void const *agrument)
{
	 	arm_sub_f32(sub_pSrcA,sub_pSrcB,sub_pDst,3);

	for(;;)
	{
		if(sub_i>3)  sub_i=0;
		  osDelay(1000);
      sub_tmp_pDst=sub_pDst[sub_i];
		  sub_i++;
	}
}