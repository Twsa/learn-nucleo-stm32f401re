#include "led.h"
#include "lcd1602A.h"
#include "Serial.h"
#include <cmsis_os.h>

void led_thread(void const *argument);
void printf_thread(void const *argument);
/*----------------------------------------------------------------------------
 Define the thread handles and thread parameters
 *---------------------------------------------------------------------------*/
 osThreadId main_ID,led_ID,lcd1602_ID;
 osThreadDef(led_thread,osPriorityNormal,1,0);
int main()
{
	  SystemCoreClockConfigure();                              // configure System Clock
    SystemCoreClockUpdate();
	  
    osKernelInitialize();                          //initialize CMSIS-RTOS	
	  Led_Initilize();
   SER_Initialize();
	  /*Read the Thread-ID of main thread*/
	  main_ID=osThreadGetId();
	  
	  led_ID=osThreadCreate(osThread(led_thread),NULL);
	
	  osKernelStart();
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


void printf_thread(void const *argument)
{
	for(;;)
	{
	  osDelay(500);
     printf("\r\n%s\r\n","Hello World");
		 osDelay(500);
	}
}