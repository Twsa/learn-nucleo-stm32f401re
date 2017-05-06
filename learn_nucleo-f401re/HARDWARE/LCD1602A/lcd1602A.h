#ifndef __LCD1602_H_
#define __LCD1602_H_
#include "sys.h"
int32_t Lcd1602A_Initialize(void);
uint8_t Read_Busy_Flag(void);
 int32_t Show_byte(uint8_t x ,uint8_t y, uint8_t str);
 void DisplayListChar(uint8_t X, uint8_t Y, uint8_t  *DData) ;
#endif
