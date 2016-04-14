

#ifndef __LCD_H__
#define __LCD_H__	1
#include "stm32f4xx.h"
#include "uart.h"



/*lcd reset pin def*/
#define LCD_RST_PORT_RCC	RCC_AHB1Periph_GPIOD
#define LCD_RST_PIN			GPIO_Pin_3
#define LCD_RST_PORT		GPIOD





#define LCD_WIDTH   240
#define LCD_HEIGHT  320



void lcd_init(void);
void lcd_clear(void);
unsigned char lcd_cmdread(unsigned char reg_addr);
void lcd_cursorxy(unsigned short xn,unsigned short yn);
void display_string(unsigned char *text);
void display_Bstring(unsigned char *text);
void Lcd_regread(void);
void display_NET(unsigned char s,unsigned char n);


#endif
