/*************************************************************************************
 *  File Name                                :thread_manage.cpp
 
 *  Create Date                             :    2017/05/06
 *  Author/Corporation                  :   Twsa
 *  Description                               :   RTOS 编程习惯 学习M4 DSP库
                                                           线程管理

 *  Platform                                   :    NUCLEO-STM32F401RE
 *  RTOS                                       :    KEIL RTX
 																			 
 *--------------------------------Revision History--------------------------------------
 *  No         Version         Date        RevisedBy        Item         Description  
 *  1          V1.0           2017/05/06 Twsa                 None           None
 
 **************************************************************************************/
#include "thread_manage.h"
#include "cmsis_os.h"
#include "basic_math.h"
#include "fast_math.h"
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
//	   osThreadDef(add_thread,osPriorityNormal,1,250); //add线程
//	 	 osThreadDef(dot_thread,osPriorityNormal,1,250); //dot线程
//	 	 osThreadDef(mult_thread,osPriorityNormal,1,250); //mult线程
//	 	 osThreadDef(negate_thread,osPriorityNormal,1,250); //negate线程
//	 	 osThreadDef(offset_thread,osPriorityNormal,1,250); //offset线程
//		 osThreadDef(scale_thread,osPriorityNormal,1,250); //scale线程 
//		 osThreadDef(sub_thread,osPriorityNormal,1,250); //sub线程    
		   osThreadDef(cosine_thread,osPriorityNormal,1,250); //sub线程 
	 
	    /******创建线程***********/
	 	led_ID=osThreadCreate(osThread(led_thread),NULL);
//	  abs_ID=osThreadCreate(osThread(abs_thread),NULL);   
//	 	add_ID=osThreadCreate(osThread(add_thread),NULL);   
//	 	add_ID=osThreadCreate(osThread(dot_thread),NULL);   
//	 	add_ID=osThreadCreate(osThread(mult_thread),NULL);   
//		 	add_ID=osThreadCreate(osThread(negate_thread),NULL);   
//		 	add_ID=osThreadCreate(osThread(offset_thread),NULL);   
//			add_ID=osThreadCreate(osThread(scale_thread),NULL);   
//			add_ID=osThreadCreate(osThread(sub_thread),NULL); 
				add_ID=osThreadCreate(osThread(cosine_thread),NULL); 		
				
	 return(0);
 }