#include "bsp.h"

void Bsp_Init(void)
{
	LED_Init();
	uart_init();
	InitLCD();
	BSP_RTC_init();
}
