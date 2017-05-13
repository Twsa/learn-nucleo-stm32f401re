/*************************************************************************************
 *  File Name                                :dsp_test.cpp
 
 *  Create Date                             :    2017/05/06
 *  Author/Corporation                  :   Twsa
 *  Description                               :   使用RTOS 编程习惯学习M4 DSP库

 *  Platform                                   :    NUCLEO-STM32F401RE
 *  RTOS                                       :    KEIL RTX
 																			 
 *--------------------------------Revision History--------------------------------------
 *  No         Version         Date        RevisedBy        Item         Description  
 *  1          V1.0           2017/05/06 Twsa                 None           None
 
 **************************************************************************************/
#include "arm_math.h"
#include <cmsis_os.h>
#include "sys.h"
#include "led.h"

int main(void)
{
//	SystemCoreClockConfigure();                              // configure System Clock
//  SystemCoreClockUpdate();
	osKernelInitialize();
  Led_Initilize();

  Twsa_Thread();
	osKernelStart();
	
	while(1);
}
