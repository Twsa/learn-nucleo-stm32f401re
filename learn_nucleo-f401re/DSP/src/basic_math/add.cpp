/*************************************************************************************
 *  File Name                                :add.cpp
 
 *  Create Date                             :    2017/05/06
 *  Author/Corporation                  :   Twsa
 *  Description                               :   使用RTOS 编程习惯学习M4 DSP库 
                                                          basic math add() test

 *  Platform                                   :    NUCLEO-STM32F401RE
 *  RTOS                                       :    KEIL RTX
 																			 
 *--------------------------------Revision History--------------------------------------
 *  No         Version         Date        RevisedBy        Item         Description  
 *  1          V1.0           2017/05/06 Twsa                 None           None
 
 **************************************************************************************/
#include "basic_math.h"
#include "arm_math.h"
#include <cmsis_os.h>


float32_t add_pSrcA[3]={-0.432565,	-1.665584,	0.125332};
float32_t add_pSrcB[3]={-1.146471,	1.190915,	1.189164};
float32_t add_pDst[3]={0};
float32_t add_tmp_A=0.0;
float32_t add_tmp_B=0.0;
float32_t add_tmp_pDst=0.0;
int add_i=0;

void add_thread(void const *agrument)
{
	 	arm_add_f32(add_pSrcA,add_pSrcB,add_pDst,3);

	for(;;)
	{
		if(add_i>3)  add_i=0;
		  osDelay(1000);
		  add_tmp_A=add_pSrcA[add_i];
		  add_tmp_B=add_pSrcB[add_i];
      add_tmp_pDst=add_pDst[add_i];
		  add_i++;
	}
}