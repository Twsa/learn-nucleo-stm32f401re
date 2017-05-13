/*************************************************************************************
 *  File Name                                :thread_manage.cpp
 
 *  Create Date                             :    2017/05/06
 *  Author/Corporation                  :   Twsa
 *  Description                               :   RTOS 编程习惯 
                                                           线程管理

 *  Platform                                   :    NUCLEO-STM32F401RE
 *  RTOS                                       :    KEIL RTX
 																			 
 *--------------------------------Revision History--------------------------------------
 *  No         Version         Date        RevisedBy        Item         Description  
 *  1          V1.0           2017/05/06 Twsa                 None           None
 
 **************************************************************************************/
#include "thread_manage.h"
#include "cmsis_os.h"
#include "led.h"


//线程ID号定义
osThreadId main_ID,abs_ID,led_ID,add_ID;

/*************************************************************************************
 *  Function Name                        :  Twsa_Thread
 
 *  Create Date                             :    2017/05/06
 *  Author/Corporation                  :   Twsa
 *  Description                               :   创建线程

 *  Return Code                            :    int32_t
 
 *  Global Variable                       :    None
 *  File Static Variable                  :    None
 *  Function Static Variable          :    None
 																			 
 *--------------------------------Revision History--------------------------------------
 *  No         Version         Date        RevisedBy        Item         Description  
 *  1          V1.0           2017/05/06 Twsa                 None           None
 
 **************************************************************************************/
 
 int32_t  Twsa_Thread(void)  
 {
	    /******线程配置定义******/       
	 	 osThreadDef(led_thread,osPriorityNormal,1,0);    //led 线程
//	   osThreadDef(abs_thread,osPriorityNormal,1,250); //abs线程
	 
	    /******创建线程***********/
	 	led_ID=osThreadCreate(osThread(led_thread),NULL);
//	  abs_ID=osThreadCreate(osThread(abs_thread),NULL);   

			 
	 return(0);
 }