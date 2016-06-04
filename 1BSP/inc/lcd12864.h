

#ifndef __LCD12864_H__
#define __LCD12864_H__	1
#include "stm32f4xx.h"


/* Define the LCD register command code */
#define Disp_On  0xaf	// Display Enable
#define Disp_Off 0xae	// Display Disable
#define Page_Add 0xb0	// Page Address Start
#define Row_AddL 0x04	// Scroll Line LSB
#define Row_AddH 0x10	// Scroll Line MSB
#define Row_Add  0x40   // Scroll Line Start


#define		ASCII_W	8

/*lcd reset pin def*/
#define LCD_RST_PORT_RCC	RCC_AHB1Periph_GPIOD
#define LCD_RST_PIN			GPIO_Pin_3
#define LCD_RST_PORT		GPIOD
/*
2-PD12 	CS
3-PE6	RES
4-PD13	A0
5-PE5	SCK
6-PE4	SDA
*/
#define GPIO_LCDRST_ON()	GPIO_ResetBits(GPIOE, GPIO_Pin_6)
#define GPIO_LCDRST_OFF()	GPIO_SetBits(GPIOE, GPIO_Pin_6)

#define GPIO_LCDCS_1()	GPIO_SetBits(GPIOD, GPIO_Pin_12)
#define GPIO_LCDCS_0()	GPIO_ResetBits(GPIOD, GPIO_Pin_12)
#define GPIO_LCDSCL_1()	GPIO_SetBits(GPIOE, GPIO_Pin_5)
#define GPIO_LCDSCL_0()	GPIO_ResetBits(GPIOE, GPIO_Pin_5)
#define GPIO_LCDSDA_1()	GPIO_SetBits(GPIOE, GPIO_Pin_4)
#define GPIO_LCDSDA_0()	GPIO_ResetBits(GPIOE, GPIO_Pin_4)
#define GPIO_LCDA0_1()	GPIO_SetBits(GPIOD, GPIO_Pin_13)
#define GPIO_LCDA0_0()	GPIO_ResetBits(GPIOD, GPIO_Pin_13)


void InitLCD(void);
void ClearScreen(void);
void WriteASCII(u8 x, u8 y, u8 index[1]);
void LCDrefur(void);
void WriteLine(u8 index);
void LCD_shutup(void);
void LCD_shutdown(void);


#endif
