/*************************************************************************************
 *  File Name                                :offset.cpp
 
 *  Create Date                             :    2017/05/06
 *  Author/Corporation                  :   Twsa
 *  Description                               :   使用RTOS 编程习惯学习M4 DSP库 
                                                          basic math offset() test

 *  Platform                                   :    NUCLEO-STM32F401RE
 *  RTOS                                       :    KEIL RTX
 																			 
 *--------------------------------Revision History--------------------------------------
 *  No         Version         Date        RevisedBy        Item         Description  
 *  1          V1.0           2017/05/06 Twsa                 None           None
 
 **************************************************************************************/
#include "basic_math.h"
#include "arm_math.h"
#include <cmsis_os.h>


float32_t offset_pSrc[3]={-0.432565,	-1.665584,	0.125332};
float32_t offset_pDst[3]={0};
float32_t offset=2.1111;
float32_t offset_tmp=0.0;
float32_t offset_tmp_pDst=0.0;
int offset_i=0;

void offset_thread(void const *agrument)
{
	 	arm_offset_f32(offset_pSrc,offset,offset_pDst,3);

	for(;;)
	{
		if(offset_i>3)  offset_i=0;
		  osDelay(1000);
		  offset_tmp=offset_pSrc[offset_i];
      offset_tmp_pDst=offset_pDst[offset_i];
		  offset_i++;
	}
}