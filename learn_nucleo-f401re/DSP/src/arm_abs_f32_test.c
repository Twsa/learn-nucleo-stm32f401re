#include "arm_math.h"
#include <cmsis_os.h>
#include "led.h"

float32_t pSrc[50]={-0.432565,	-1.665584,	0.125332,	0.287676,	-1.146471,	1.190915,	1.189164,	-0.037633,	
0.327292,	0.174639,	-0.186709,	0.725791,	-0.588317,	2.183186,	-0.136396,	0.113931,	
1.066768,	0.059281,	-5,	-0.832349,	0.294411,	-1.336182,	0.714325,	1.623562,	
-0.691776,	0.857997,	1.254001,	-1.593730,	-1.440964,	0.571148,	-0.399886,	0.689997,	
0.815622,	0.711908,	1.290250,	0.668601,	1.190838,	-1.202457,	-0.019790,	-0.156717,	};
float32_t pDst[50]={0};
void abs_thread(void const *argument);
void led_thread(void const *argument);

osThreadId main_ID,abs_ID,led_ID;
osThreadDef(abs_thread,osPriorityNormal,1,1024);
osThreadDef(led_thread,osPriorityNormal,1,0);

int main(void)
{
	SystemCoreClockConfigure();                              // configure System Clock
  SystemCoreClockUpdate();
	osKernelInitialize();
  Led_Initilize();
	
	led_ID=osThreadCreate(osThread(led_thread),NULL);
	abs_ID=osThreadCreate(osThread(abs_thread),NULL);
	osKernelStart();
	
	while(1);
}

int i=0;
float32_t tmp=0.0;
void abs_thread(void const *argument)
{
	arm_abs_f32(pSrc,pDst,50);
	for(;;)
	{
		if(i>50)  i=0;
		  osDelay(1000);
      tmp=pDst[i];
		  i++;
	}
}

void led_thread(void const *argument)
{
	for(;;)
	{
	  Led_On();
		osDelay(500);
		Led_Off();
		osDelay(500);
	}
}