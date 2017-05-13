#ifndef __THREAD_MANAGE_H_
#define  __THREAD_MANAGE_H_
#include <cmsis_os.h>

#define  LED_MSG  0X01
#define ADD_MSG  0X02
#define DOT_MAG  0X03
#define  MULT_MSG 0X04
#define NEGATE_MSG 0X05
#define OFFSET_MSG 0X06
#define SCALE_MSG 0X07
#define SUB_MSG 0X08
#define COSINE 0X09
#define CONJUGATE_MSG 0X0A

extern osMessageQId Q_DSP;
 int32_t  Twsa_Thread(void);

#endif