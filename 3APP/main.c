
#include "bsp.h"
#include <clock.h>  
#include <sys/process.h>  
#include <sys/procinit.h>  
#include <etimer.h>  
#include <sys/autostart.h>  
#include "contiki.h"


int main(void)
{
	unsigned char i;
	LED_Init();
	uart_init();
	Systick_Init();
	//lcd 初始
	lcd_init();
	printf("\r\nlcd init suc");
	//lcd设置成红色
	Lcd_regread();	
//	lcd_clear();
	printf("\r\nLcd is clear");
	
	display_NET(0x55,4);
	
//	//查找.bmp 和 .txt文件
//	Find_FileName();
//	
//	//显示.bmp文件
//	for(i=0;i<BMP_NUM;i++){
//		lcd_display_string_line(0,i*16,0xf800,0,(unsigned char *)BMP_Files[i]);	
//	}
//	//显示.txt文件
//	for(i=0;i<TXT_NUM;i++){
//		lcd_display_string_line(120,i*16,0xf800,0,(unsigned char *)TXT_Files[i]);	
//	}
	while(1)
	{
		LED_Tog(LED0);
		Delay(500);
		LED_Tog(LED1);
		Delay(500);
		LED_Tog(LED2);
		Delay(500);
		LED_Tog(LED3);
		Delay(500);
	}
}
