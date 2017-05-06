#include "lcd1602A.h"
#include <cmsis_os.h>
#include "Serial.h"

/*****lcd 端口配置******/
/*
RS:PB13;
R/W:PB14;
E:PB15;
DB0-DB7:PC0-PC7;
*/

 int32_t lcd_init(void);
int32_t Lcd1602A_Initialize(void)
{
	  RCC->AHB1ENR |=(1ul<<1);         //enable peripheral GPIOB clock
	  RCC->AHB1ENR |=(1ul<<2);         //enable peripheral GPIOC clock 
	   /* Configure LED (PB.13.14.15) pins as General purpose 
	 1.output mode ,
	 2.push-pull outputs, 
	 3.Medium speed, 
	 4.No pull-up,pull-down 
	 */
	 
   /**************set gpio mode**********************/	 
	   GPIOB->MODER  &=(  (~(3ul<<2*13)) | (~(3ul<<2*14)) | (~(3ul<<2*15))  );     
	   GPIOB->MODER  |=((1ul<<2*13) | (1ul<<2*14) | (1ul<<2*15));
	
	   GPIOC->MODER  |=0x5555;           //PC0-PC7为通用输出模式
    /**************end set gpio mode**********************/	 
	 
	  /**************set gpio type**********************/	 
	   GPIOB->OTYPER  &=( (~(1ul<<13)) | ( ~(1ul<<14 )) | (~(1ul<<15)) );
	   GPIOC->OTYPER &=0x0;
	   /**************end set gpio type**********************/	 
	   
	    /**************set gpio speed**********************/	 
	    GPIOB->OSPEEDR &=(  (~(3ul<<2*13)) | (~(3ul<<2*14)) | (~(3ul<<2*15))  );     
	    GPIOB->OSPEEDR |=((1ul<<2*13) | (1ul<<2*14) | (1ul<<2*15));      
			
			GPIOC->OSPEEDR &=~0xffff;
			GPIOC->OSPEEDR |=0x5555;
	   /**************end set gpio speed**********************/	 
		 
		 /**************set gpio  pull-up/pull-down **********************/
		 GPIOB->PUPDR &=(  (~(3ul<<2*13)) | (~(3ul<<2*14)) | (~(3ul<<2*15))  );     
		 GPIOC->PUPDR &=~0xffff;
		 /**************set gpio  pull-up/pull-down **********************/
		 
     lcd_init();
		 return(0);
}

/****Read busy flag and Address *****/
uint8_t Read_Busy_Flag(void)
{
	   uint8_t busy_flag=0x80;                        //初始化为忙状态
		  /***端口初始化操作***/
		GPIOB->ODR &=~0xe000;                    //E,RW,RS=0
	  GPIOC->ODR &=~0xff;    
	   /***端口初始化完成***/
	
	  //RS=0,RW=1;
	  GPIOB->ODR  |=0x4000;
	  GPIOC->MODER  &=~0xffff;                //设置PC0-PC7为输入模式

		osDelay(5);                                             //os系统延时5ms                  
	  //E=1;
	  GPIOB->ODR |=0x8000;
//    //E=1;
//	  GPIOB->ODR |=0x8000;             
//		  //E=0;
//	  GPIOB->ODR &=~0x8000;    
	  //从IDR寄存器中读取数据
	  busy_flag=GPIOC->IDR&0xff;            //等待读操作完成        
    while(busy_flag & 0x80);                        //检测忙信号     
	   
	  return(busy_flag);
}

//busy_flag为0时，检测忙，否则不检测忙
int32_t Wirte_Commend(uint8_t cmd,uint8_t busy_flag) 
{
	  if(busy_flag) Read_Busy_Flag();   //根据需要检测忙状态
		  /***端口初始化操作***/
		GPIOB->ODR &=~0xe000;             //E,RW,RE
	  GPIOC->ODR &=~0xff;                   //DB7-DB0
	  /***端口初始化完成***/
	  GPIOC->MODER  |=0x5555;           //PC0-PC7为通用输出模式
	  
		GPIOC->ODR |=cmd;         
	  osDelay(5);                                         //等待写操作完成
	  //E=0;
	  GPIOB->ODR &=~0x8000;
		  //E=0;
	  GPIOB->ODR &=~0x8000;
		  //E=1;
	  GPIOB->ODR |=0x8000;
	return(0);
}

 int32_t lcd_init(void)
 {
	  GPIOC->MODER  |=0x5555;           //PC0-PC7为通用输出模式
		GPIOC->ODR &=~0xffff;
	 
		Wirte_Commend(0x38,0);
		osDelay(5);
		Wirte_Commend(0x38,0);
		osDelay(5);
		Wirte_Commend(0x38,0);
		osDelay(5); 
	 
	 	Wirte_Commend(0x38,1);                 //显示模式设置，开始要求每次检测忙信号
	 		osDelay(2); 
	  Wirte_Commend(0x08,1);                 //关闭显示
	 		osDelay(2); 
	 	Wirte_Commend(0x01,0);                 //显示清屏
	 		osDelay(2); 
	  Wirte_Commend(0x06,0);                 //显示光标移动设置
	 		osDelay(2); 
	 	Wirte_Commend(0x0C,0);                //显示开及光标的设置
	 		osDelay(2); 
 }

 void Write_Data(uint8_t data)
 {
	  Read_Busy_Flag();                          //检测忙状态
	 	GPIOC->MODER  |=0x5555;   
	 /***端口初始化操作***/
		GPIOB->ODR &=~0xe000;             //E,RW,RE
	  GPIOC->ODR &=~0xff;                   //DB7-DB0
	 	GPIOC->ODR=data;
	 /***端口初始化完成***/
	  GPIOB->ODR |=0x2000;                 //数据输入 写使能
	 	  //E=0;
	  GPIOB->ODR &=~0x8000;
		  //E=0;
	  GPIOB->ODR &=~0x8000;
		  //E=1;
	  GPIOB->ODR |=0x8000;
 }
 /***显示单个字符***/
 int32_t Show_byte(uint8_t x ,uint8_t y, uint8_t str)
 {
	 y&=0x01;
	 x&=0x0f;                //限制x不能大于15，y不能大于1；
	 if(y) x|=0x40;       //当要显示第二行时地址码+0x40;
	 x |=0x80;             //write data 头指令码
	 Wirte_Commend(x,0);           //这里不检测信号，发送地址码
	 Write_Data(str);
	 return(0);
 }
 
 
 void DisplayListChar(uint8_t X, uint8_t Y, uint8_t  *DData) 
	 { 
		 uint8_t  ListLength; 
		 ListLength = 0; 
		 Y &= 0x1;  
		 X &= 0xF;//限制X不能大于15，Y不能大于1  
		 while (DData[ListLength]>0x20)//若到达字串尾则退出
		 { 
			 if (X <= 0xF)//X坐标应小于0xF 
      {  
	      Show_byte(X, Y, DData[ListLength]);//显示单个字符 
				ListLength++; X++; 
	   }
	 } 
}