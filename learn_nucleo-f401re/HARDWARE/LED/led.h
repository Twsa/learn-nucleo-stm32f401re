#ifndef __LED_H_
#include "sys.h"

 int32_t Led_Initilize(void);
 	/***************led on*************/
	 int32_t Led_On(void);
 	/***************led off*************/
	 int32_t Led_Off(void);
	 void led_thread(void const *argument);
#endif

