作者：Twsa Liu(刘传佳)

RTOS： RTX KEIL
DSP:M4_DSP.lib
平台：NUCLEO-STM32F401RE 
兼容网络平台：mbed 
调试组件：KEIL M4仿真，ITM跟踪调试组件，STLINK /V2
语言：C/C++

2017/05/13
测试GPIO 配置 外部中断响应
2017/05/14
1、测试 USART普通模式，中断通信模式，DMA传输模式
2、ADC1采样 测试内部传感器：
  Note:使用ADC1 16通道测试与18通道测试，误差相差20摄氏度。以笔者直观感受，16通道更贴近真实情况