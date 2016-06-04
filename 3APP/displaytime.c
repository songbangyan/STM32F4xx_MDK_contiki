
#include "bsp.h"

unsigned char hex2char(unsigned char hex)
{
	unsigned char ret=0;
	unsigned char n;
	if( '0'<=hex && hex<='9' )
			n = hex-'0';
	else if( 'a'<=hex && hex<='f' )
			n = 10 + hex-'a';
	else if( 'A'<=hex && hex<='F' )
			n = 10 + hex-'A';
	ret = n + ret*16;
	return ret;	
}
	
void dispalytime(void)
{
	RTC_TimeTypeDef rtc;
//	unsigned char i;
	unsigned char rtcbuf[]={"00:00:00"};
	RTC_GetTime(RTC_Format_BIN,&rtc);
	sprintf((char *)rtcbuf,"%02d:%02d:%02d",rtc.RTC_Hours,rtc.RTC_Minutes,rtc.RTC_Seconds);
	printf("\r\n%s",rtcbuf);
//	for(i=0;i<8;i++)
//	{
//		WriteASCII(ASCII_W*i,0,rtcbuf+i);
//	}
	WriteASCII(0,0,rtcbuf);
	WriteASCII(0,8,rtcbuf);
	WriteASCII(0,ASCII_W*2,rtcbuf+2);
	WriteASCII(0,ASCII_W*3,rtcbuf+3);
	WriteASCII(0,ASCII_W*4,rtcbuf+4);
	WriteASCII(0,ASCII_W*5,rtcbuf+5);
	WriteASCII(0,ASCII_W*6,rtcbuf+6);
	WriteASCII(0,ASCII_W*7,rtcbuf+7);
	LCDrefur();
}
