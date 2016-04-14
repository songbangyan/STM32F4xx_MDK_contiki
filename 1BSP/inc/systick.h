

#ifndef __SYSTICK_H__
#define __SYSTICK_H__	1
#include "stm32f4xx.h"

void Systick_Init(void);
void Delay(__IO uint32_t nTime);
void TimingDelay_Decrement(void);



#endif
