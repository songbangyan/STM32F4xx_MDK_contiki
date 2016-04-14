

#ifndef __LED_H__
#define __LED_H__	1
#include "stm32f4xx.h"

#define LED0	0
#define LED0_PIN	GPIO_Pin_0
#define LED0_PORT	GPIOE

#define LED1	1
#define LED1_PIN	GPIO_Pin_1
#define LED1_PORT	GPIOE

#define LED2	2
#define LED2_PIN	GPIO_Pin_2
#define LED2_PORT	GPIOE

#define LED3	3
#define LED3_PIN	GPIO_Pin_3
#define LED3_PORT	GPIOE



void LED_Init(void);
void LED_Tog(unsigned char ledno);
void LED_Off(unsigned char ledno);
void LED_On(unsigned char ledno);



#endif
