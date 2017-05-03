/*  hello world 改进版，支持重定向的双向通信  */
#include <stdio.h>
#include "Serial.h"
#include "sys.h"

int main(void)
{
		 char textbuffer[40];                                                  //消息缓冲
	  /* STM32F4xx HAL library initialization:
       - Configure the Flash prefetch, Flash preread and Buffer caches
       - Systick timer is configured by default as source of time base, but user 
             can eventually implement his proper time base source (a general purpose 
             timer for example or other time source), keeping in mind that Time base 
             duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and 
             handled in milliseconds basis.
       - Low Level Initialization
     */
  HAL_Init();
  
  /* Configure the System clock to 48 MHz */
   SystemCoreClockConfigure();
	  SystemCoreClockUpdate();
  SER_Initialize();
		SCB->CCR |=SCB_CCR_STKALIGN_Msk;       //使能双字栈对齐
	 //(Cortex-M3 r1p1 推荐使用 ，Cortex-M3 r2p2和Cortext-M4默认启动)
	 printf("\r\nHello World!\n");
//	 while(1)
//	 {
//		 printf("Please enter text:");
//		 fgets(textbuffer,(sizeof(textbuffer)-1),stdin);
//		 //		 scanf("%s",&textbuffer[0]);                                  
//		 //一般应用程序开发中不推荐使用scanf的，因为该函数不会检查缓冲，可以利用自己的输入函数代替
//		 printf("\nYou entered : %s\n",textbuffer);
//	 }
}

