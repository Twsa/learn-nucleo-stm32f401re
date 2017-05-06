/*************************************************************************************
 *  File Name                                :negate.cpp
 
 *  Create Date                             :    2017/05/06
 *  Author/Corporation                  :   Twsa
 *  Description                               :   使用RTOS 编程习惯学习M4 DSP库 
                                                          basic math negate() test

 *  Platform                                   :    NUCLEO-STM32F401RE
 *  RTOS                                       :    KEIL RTX
 																			 
 *--------------------------------Revision History--------------------------------------
 *  No         Version         Date        RevisedBy        Item         Description  
 *  1          V1.0           2017/05/06 Twsa                 None           None
 
 **************************************************************************************/
#include "basic_math.h"
#include "arm_math.h"
#include <cmsis_os.h>


float32_t negate_pSrc[3]={-2.432565,	-1.665584,	3.125332};
float32_t negate_pDst[3]={0};
float32_t negate_tmp=0.0;
float32_t negate_tmp_pDst=0.0;
int negate_i=0;

void negate_thread(void const *agrument)
{
	 	arm_negate_f32(negate_pSrc,negate_pDst,3);

	for(;;)
	{
		if(negate_i>3)  negate_i=0;
		  osDelay(1000);
		  negate_tmp=negate_pSrc[negate_i];
      negate_tmp_pDst=negate_pDst[negate_i];
		  negate_i++;
	}
}