#include "led.h"
#include "cmsis_os.h"

/*************************************************************************************
 *  File Name                                 :led.c
 
 *  Create Date                             :    2017/05/04
 *  Author/Corporation                  :   Twsa
 *  Description                               :   led_test ,get know how to config general IO

 *  Return Code                            :    None
 
 *  Global Variable                       :    None
 *  File Static Variable                  :    None
 *  Function Static Variable          :    None
 																			 
 *--------------------------------Revision History--------------------------------------
 *  No         Version         Date        RevisedBy        Item         Description  
 *  1          V1.0           2017/05/04 Twsa                 None           None
 
 **************************************************************************************/
 
 /***************led端口配置*************/
 int32_t Led_Initilize(void)
 {
	    RCC->AHB1ENR |=(1ul<<0);         //enable peripheral GPIOA clock
	   
	   /* Configure LED (PA.5) pins as General purpose 
	 1.output mode ,
	 2.push-pull outputs, 
	 3.Medium speed, 
	 4.No pull-up,pull-down 
	 */
	 
   /**************set gpio mode**********************/	 
	   GPIOA->MODER  &=~((3ul<<2*5));     
	   GPIOA->MODER  |=((1ul<<2*5));      
    /**************end set gpio mode**********************/	 
	 
	  /**************set gpio type**********************/	 
	   GPIOA->OTYPER  &=~(1ul<<5);
	   /**************end set gpio type**********************/	 
	   
	    /**************set gpio speed**********************/	 
	    GPIOA->OSPEEDR &=~((3ul<<2*5));
	    GPIOA->OSPEEDR |=((1ul<<2*5));
	   /**************end set gpio speed**********************/	 
		 
		 /**************set gpio  pull-up/pull-down **********************/
		 GPIOA->PUPDR &=~((3ul<<2*5));
		 /**************set gpio  pull-up/pull-down **********************/
		 return(0);
	 }
 
	/***************led on*************/
	 int32_t Led_On(void)
	 {
       GPIOA->ODR=0x20;
		 
		   return(0);
	 }
 
 	/***************led off*************/
	 int32_t Led_Off(void)
	 {
       GPIOA->ODR=0x0;
		   return(0);
	 }
	 
/*******led thread******/
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