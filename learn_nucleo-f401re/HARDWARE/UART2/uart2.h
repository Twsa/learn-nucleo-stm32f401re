#ifndef __UART2_H_
#define __UART2_H_
#include "sys.h"
extern void USART2_GPIO_Config(void);
extern void Uart2_Init(void);
extern UART_HandleTypeDef  uart2_handle;

extern void USART2_Tx_Normal(uint8_t * tx_pData,uint16_t Size,uint32_t Timeout);
extern void USART2_Rx_Normal(uint8_t * rx_pData,uint16_t Size,uint32_t Timeout);
extern void USART2_Tx_nonBlocking(uint8_t * rx_pData,uint16_t Size);
extern void USART2_Rx_nonBlocking(uint8_t * rx_pData,uint16_t Size);
extern void Uart2_Test(void);
#endif