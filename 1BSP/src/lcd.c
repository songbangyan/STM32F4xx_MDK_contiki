
#include "lcd.h"
#include "fonts.h"
//#include "image.h"
#include "systick.h"

#define LCD_RAM    *(__IO uint16_t *) (0x60010000)    	//地址寄存器
#define LCD_REG    *(__IO uint16_t *) (0x60000000)	 		//指令寄存器

#define CS_1()	GPIO_SetBits(GPIOD,GPIO_Pin_7)
#define CS_0()	GPIO_ResetBits(GPIOD,GPIO_Pin_7)

#define RD_1()	GPIO_SetBits(GPIOD,GPIO_Pin_4)
#define RD_0()	GPIO_ResetBits(GPIOD,GPIO_Pin_4)

#define WR_1()	GPIO_SetBits(GPIOD,GPIO_Pin_5)
#define WR_0()	GPIO_ResetBits(GPIOD,GPIO_Pin_5)

#define A0_1()	GPIO_SetBits(GPIOD,GPIO_Pin_11)
#define A0_0()	GPIO_ResetBits(GPIOD,GPIO_Pin_11)	
		/*
	+-------------------+--------------------+------------------+------------------+
	+                       LCD pins assignment                                  +
	+-------------------+--------------------+------------------+------------------+
	| PD14 <-> D0  |  
	| PD15 <-> D1  | 
	| PD0  <-> D2  | 
	| PD1  <-> D3  |  
	| PE7  <-> D4  |
	| PE8  <-> D5  |
	| PE9  <-> D6  | 
	| PE10 <-> D7  | 
	| PD7  <-> CS	 |
	| PD4  <-> RD  |
	| PD5  <-> WR  | 
	| PD11 <-> A0  |
	*/

void lcd_datset( unsigned char dat)
{
	if(dat & 0x01)
	{
		GPIO_SetBits(GPIOD,GPIO_Pin_14);	
	}
	else
	{
		GPIO_ResetBits(GPIOD,GPIO_Pin_14);	
	}
	if(dat & 0x02)
	{
		GPIO_SetBits(GPIOD,GPIO_Pin_15);	
	}
	else
	{
		GPIO_ResetBits(GPIOD,GPIO_Pin_15);	
	}
	if(dat & 0x04)
	{
		GPIO_SetBits(GPIOD,GPIO_Pin_0);	
	}
	else
	{
		GPIO_ResetBits(GPIOD,GPIO_Pin_0);	
	}
	if(dat & 0x08)
	{
		GPIO_SetBits(GPIOD,GPIO_Pin_1);	
	}
	else
	{
		GPIO_ResetBits(GPIOD,GPIO_Pin_1);	
	}
	if(dat & 0x010)
	{
		GPIO_SetBits(GPIOE,GPIO_Pin_7);	
	}
	else
	{
		GPIO_ResetBits(GPIOE,GPIO_Pin_7);	
	}
	if(dat & 0x20)
	{
		GPIO_SetBits(GPIOE,GPIO_Pin_8);	
	}
	else
	{
		GPIO_ResetBits(GPIOE,GPIO_Pin_8);	
	}
	if(dat & 0x40)
	{
		GPIO_SetBits(GPIOE,GPIO_Pin_9);	
	}
	else
	{
		GPIO_ResetBits(GPIOE,GPIO_Pin_9);	
	}
	if(dat & 0x80)
	{
		GPIO_SetBits(GPIOE,GPIO_Pin_10);	
	}
	else
	{
		GPIO_ResetBits(GPIOE,GPIO_Pin_10);	
	}
}


/*
 *	
 */
void write_cmd(unsigned char cmd)
{	
//	LCD_REG = cmd;	
	lcd_datset(cmd);
	A0_0();
	RD_1();
	CS_0();
	WR_0();
//	Delay(10);
	WR_1();
	
	CS_1();
}


void lcd_datawrite(unsigned short data_code )
{	
//	LCD_RAM = data_code;
	lcd_datset(data_code);
	A0_1();
	RD_1();
	CS_0();
	WR_0();
//	Delay(10);
	WR_1();	
	CS_1();
	
}

void lcd_cmdwrite(unsigned char reg_addr,unsigned short reg_val)
{
	write_cmd(reg_addr);
	write_cmd(reg_val);
}

unsigned char lcd_cmdread(unsigned char reg_addr)
{
	unsigned char val=0xFF;
	write_cmd(reg_addr);
//	val = LCD_RAM;
	return (val);
}

/*****************************************************
函数：void lcd_clear()
功能：清除内存
********************************************************/
void lcd_clear(void)
{
	unsigned char reg;
	lcd_cmdwrite(0xe0,0x00);
	reg = lcd_cmdread(0xf0);
	reg &=0xf7;
	reg |=0x08;
	lcd_cmdwrite(0xf0,reg);
	Delay(300);
}
/******************************************************
函数：void lcd_cursorxy(unsigned int xn,unsigned int yn)
功能：设定要显示数据的地址
**********************************************************/
void lcd_cursorxy(unsigned short xn,unsigned short yn)
{
	lcd_cmdwrite(0x60,xn);
	lcd_cmdwrite(0x70,yn);
}
/***********************************************
函数：void lcd_showbig(uchar *text,uint xn)
功能：显示字符，汉字
******************************************************/
void display_string(unsigned char *text)
{
	lcd_cmdwrite(0x00,0xcd);
	lcd_cmdwrite(0xf1,0x0f); //不放大
	while(*text != '\0')         
	{
		lcd_datawrite(*text);
		++text;
	}
}

void display_Bstring(unsigned char *text)
{
	lcd_cmdwrite(0x00,0xcd);
	lcd_cmdwrite(0xf1,0x5f); //放大一倍
	while(*text != '\0')         
	{
    lcd_datawrite(*text);
    ++text;
  }
}

/***************************************************
函数：void display_NET()
功能：网点的显示,大小四种网点
****************************************************/
void display_NET(unsigned char s,unsigned char n)
{
	unsigned short i, j;
	lcd_cmdwrite(0x00,0xc5); //图形显示模式
	lcd_cursorxy(0,0);
	
	for(i=0;i<(240*32/8);i++) //行画点控制
	{
			lcd_datawrite(0x55);
//		for(j=0;j<40;j++)   //同时进行8列
//		{
//			Delay(500);
//      if(n==1)lcd_datawrite(s);
//      if(n==2) lcd_datawrite(s);
//      if(n==4)lcd_datawrite(s);
//			if(n==8)
//			{
//				if(j%2)lcd_datawrite(s);
//				else lcd_datawrite(~s);
//			}				 
//	}
//	 if(n==1) s=~s;
//   if(n==2) if((i)%2) s=~s;
//   if(n==4) if((i+1)%4==0) s=~s;
//   if(n==8) if((i+1)%8==0) s=~s;
//		}
	}
}
void Lcd_regread(void)
{
	unsigned char reg;
	reg = lcd_cmdread(0x00);
	printf("\r\naddr 0x00 data is %2x",reg);
	reg = lcd_cmdread(0x01);
	printf("\r\naddr 0x01 data is %2x",reg);
	reg = lcd_cmdread(0x02);
	printf("\r\naddr 0x02 data is %2x",reg);
	reg = lcd_cmdread(0x03);
	printf("\r\naddr 0x03 data is %2x",reg);
	reg = lcd_cmdread(0x10);
	printf("\r\naddr 0x10 data is %2x",reg);
	reg = lcd_cmdread(0x11);
	printf("\r\naddr 0x11 data is %2x",reg);
//	
//	reg = lcd_cmdread(0x20);
//	printf("\r\naddr 0x20 data is %2x",reg);
//	reg = lcd_cmdread(0x30);
//	printf("\r\naddr 0x30 data is %2x",reg);
//	reg = lcd_cmdread(0x40);
//	printf("\r\naddr 0x40 data is %2x",reg);
//	reg = lcd_cmdread(0x50);
//	printf("\r\naddr 0x50 data is %2x",reg);
//	
//	reg = lcd_cmdread(0x21);
//	printf("\r\naddr 0x21 data is %2x",reg);
//	reg = lcd_cmdread(0x31);
//	printf("\r\naddr 0x31 data is %2x",reg);
//	reg = lcd_cmdread(0x41);
//	printf("\r\naddr 0x41 data is %2x",reg);
//	reg = lcd_cmdread(0x51);
//	printf("\r\naddr 0x51 data is %2x",reg);

//	reg = lcd_cmdread(0x90);
//	printf("\r\naddr 0x90 data is %2x",reg);
//	reg = lcd_cmdread(0xa0);
//	printf("\r\naddr 0xa0 data is %2x",reg);
//	reg = lcd_cmdread(0xa1);
//	printf("\r\naddr 0xa1 data is %2x",reg);
//	reg = lcd_cmdread(0xc0);
//	printf("\r\naddr 0xc0 data is %2x",reg);
//	reg = lcd_cmdread(0xc1);
//	printf("\r\naddr 0xc1 data is %2x",reg);

//	reg = lcd_cmdread(0xe0);
//	printf("\r\naddr 0xe0 data is %2x",reg);
//	reg = lcd_cmdread(0xf0);
//	printf("\r\naddr 0xf0 data is %2x",reg);
//	reg = lcd_cmdread(0xd0);
//	printf("\r\naddr 0xd0 data is %2x",reg);
//	reg = lcd_cmdread(0x00);
//	printf("\r\naddr 0x00 data is %2x",reg);
  
}
void port_fsmc_init(void)
{	
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
	FSMC_NORSRAMTimingInitTypeDef  p;
	GPIO_InitTypeDef GPIO_InitStructure; 

	/* Enable GPIOs clock */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOA, ENABLE);
	/* Enable FSMC clock */
	RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE);	
	/* Configure the RESET pin */
	GPIO_InitStructure.GPIO_Pin = LCD_RST_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LCD_RST_PORT, &GPIO_InitStructure);

	/* Configure the BL pin */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_ResetBits(GPIOA,GPIO_Pin_9);

	/*
	+-------------------+--------------------+------------------+------------------+
	+                       SRAM pins assignment                                  +
	+-------------------+--------------------+------------------+------------------+
	| PD0  <-> FSMC_D2  | PE0  <-> FSMC_NBL0 | PF0  <-> FSMC_A0 | PG0 <-> FSMC_A10 |
	| PD1  <-> FSMC_D3  | PE1  <-> FSMC_NBL1 | PF1  <-> FSMC_A1 | PG1 <-> FSMC_A11 |
	| PD4  <-> FSMC_NOE | PE7  <-> FSMC_D4   | PF2  <-> FSMC_A2 | PG2 <-> FSMC_A12 |
	| PD5  <-> FSMC_NWE | PE8  <-> FSMC_D5   | PF3  <-> FSMC_A3 | PG3 <-> FSMC_A13 |
	| PD8  <-> FSMC_D13 | PE9  <-> FSMC_D6   | PF4  <-> FSMC_A4 | PG4 <-> FSMC_A14 |
	| PD9  <-> FSMC_D14 | PE10 <-> FSMC_D7   | PF5  <-> FSMC_A5 | PG5 <-> FSMC_A15 |
	| PD10 <-> FSMC_D15 | PE11 <-> FSMC_D8   | PF12 <-> FSMC_A6 | PG9 <-> FSMC_NE2 |
	| PD11 <-> FSMC_A16 | PE12 <-> FSMC_D9   | PF13 <-> FSMC_A7 |------------------+
	| PD12 <-> FSMC_A17 | PE13 <-> FSMC_D10  | PF14 <-> FSMC_A8 | 
	| PD14 <-> FSMC_D0  | PE14 <-> FSMC_D11  | PF15 <-> FSMC_A9 | 
	| PD15 <-> FSMC_D1  | PE15 <-> FSMC_D12  |------------------+
	+-------------------+--------------------+
	*/
	/* GPIOD configuration */
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource1, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource4, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource7, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource10, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource11, GPIO_AF_FSMC); 
	//GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_FSMC);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7 |
		GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;

	GPIO_Init(GPIOD, &GPIO_InitStructure);


	/* GPIOE configuration */
	//GPIO_PinAFConfig(GPIOE, GPIO_PinSource0 , GPIO_AF_FSMC);
	//GPIO_PinAFConfig(GPIOE, GPIO_PinSource1 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource7 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource8 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource9 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource10 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource11 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource12 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource13 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource14 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource15 , GPIO_AF_FSMC);

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7 |	GPIO_Pin_8  | GPIO_Pin_9  | GPIO_Pin_10 | GPIO_Pin_11|
		GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;

	GPIO_Init(GPIOE, &GPIO_InitStructure);

	/*-- FSMC Configuration ------------------------------------------------------*/
	p.FSMC_AddressSetupTime = 0;
	p.FSMC_AddressHoldTime = 0;
	p.FSMC_DataSetupTime = 9;
	p.FSMC_BusTurnAroundDuration = 0;
	p.FSMC_CLKDivision = 0;
	p.FSMC_DataLatency = 0;
	p.FSMC_AccessMode = FSMC_AccessMode_B;

	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;
	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
	FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;
	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;  
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
	FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
	FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
	FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;
	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &p;

	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure); 

	/*!< Enable FSMC Bank1_SRAM1 Bank */
	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);	
}

void lcd_lowlevel_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	/* Enable GPIOs clock */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOA, ENABLE);
	/* Configure the RESET pin */
	GPIO_InitStructure.GPIO_Pin = LCD_RST_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LCD_RST_PORT, &GPIO_InitStructure);

		/*
	+-------------------+--------------------+------------------+------------------+
	+                       LCD pins assignment                                  +
	+-------------------+--------------------+------------------+------------------+
	| PD14 <-> D0  |  
	| PD15 <-> D1  | 
	| PD0  <-> D2  | 
	| PD1  <-> D3  |  
	| PE7  <-> D4  |
	| PE8  <-> D5  |
	| PE9  <-> D6  | 
	| PE10 <-> D7  | 
	| PD7  <-> CS	 |
	| PD4  <-> RD  |
	| PD5  <-> WR  | 
	| PD11 <-> RS  |
	*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 |	GPIO_Pin_1  | GPIO_Pin_4  | GPIO_Pin_5 | GPIO_Pin_7|
		GPIO_Pin_11 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7 |	GPIO_Pin_8  | GPIO_Pin_9  | GPIO_Pin_10 ;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
}

void lcd_init(void)
{
	lcd_lowlevel_init();
	GPIO_ResetBits(GPIOD,GPIO_Pin_3);	
	Delay(500);
	GPIO_SetBits(GPIOD,GPIO_Pin_3);	
	Delay(50);
//	GPIO_SetBits(GPIOA,GPIO_Pin_9);
	Delay(50);
	lcd_cmdwrite(0x00,0xc1);   //WLCR 正常模式；文字模式；屏幕开启；不闪烁；不反白；
	lcd_cmdwrite(0x01,0xf2);   //MISC 系统频率选择：8M
	lcd_cmdwrite(0x02,0x10);   //APSR  
	lcd_cmdwrite(0x03,0x80);   //ADSR 平移方向动控制
	lcd_cmdwrite(0x10,0x28);   //WCCR 正常显示，不加粗
	lcd_cmdwrite(0x11,0x00);   //WCCR 正常显示，不加粗

	lcd_cmdwrite(0x20,0x27);   //AWRR  
	lcd_cmdwrite(0x30,0xef);   //AWBR  
	lcd_cmdwrite(0x40,0x00);   //AWLR  
	lcd_cmdwrite(0x50,0x00);   //AWTR  

	lcd_cmdwrite(0x21,0x27);   //DWRR  
	lcd_cmdwrite(0x31,0xef);   //DWBR  
	lcd_cmdwrite(0x41,0x00);   //DWLR
	lcd_cmdwrite(0x51,0x00);   //DWTR

	lcd_cmdwrite(0x90,0x06);  
	lcd_cmdwrite(0xa0,0x00);   
	lcd_cmdwrite(0xa1,0x00);   
	lcd_cmdwrite(0xc0,0x10);  
	lcd_cmdwrite(0xc1,0x3a); 
  
	lcd_cmdwrite(0xe0,0x00);   
	lcd_cmdwrite(0xf0,0xa8); 
  
	lcd_cmdwrite(0xd0,0x07);   
	lcd_cmdwrite(0x00,0xc5);  
}
