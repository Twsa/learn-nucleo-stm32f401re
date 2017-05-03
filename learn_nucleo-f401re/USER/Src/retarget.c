/*************************************************************************************
 *  File Name                        :   retarget.c
 
 *  Create Date                     :   2017/04/30
 *  Author/Corporation          :   Twsa 
 *  Description                       :  retarget.c的精简版-用于Keil MDK-ARM中的printf

 *  Return Code                     :    None
 
 *  Global Variable                 :    None
 *  File Static Variable            :    None
 *  Function Static Variable    :    None
 																			 
 *--------------------------------Revision History--------------------------------------
 *  No         Version         Date        RevisedBy        Item         Description  
 *  1          V1.0           2017/04/30    Twsa                 None           None
 
***************************************************************************************/
#pragma import(__use_no_semihosting_swi)
#include "stm32f4xx.h"
#include <stdio.h>
struct __FILE{ int handle; /* 在此处添加自己需要的内容 */};
FILE __stdout;
FILE __stdin;

int fputc(int ch , FILE * f)
{
	return (ITM_SendChar(ch));
}

void _sys_exit(int return_code)
{
	label:goto label;             /* 死循环 */
}

/*  retarget.c 中支持用户输入的代码  */
volatile int32_t ITM_RxBuffer=0x5AA55AA5;                  //初始化为EMPTY
int fgetc(FILE * f)
{
	  char tmp;
	  while( ITM_CheckChar()==0);                                        //等待缓冲为空
	  tmp = ITM_ReceiveChar();
	  if(tmp == 13) tmp=10;
	  return (ITM_SendChar(tmp) );
}

/*  retarget.c 用于Keil MDK-ARM 中的UART消息输入/输出  */
