
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
	unsigned char i;
	RTC_TimeTypeDef rtc;
	unsigned char rtcdatebuf[]={"2016-06-04"};
	unsigned char rtcbuf[]={"00:00:00"};
	RTC_DateTypeDef rtc_date;
	RTC_GetDate(RTC_Format_BIN,&rtc_date);
	sprintf((char *)rtcdatebuf,"20%02d-%02d-%02d",rtc_date.RTC_Year,rtc_date.RTC_Month,rtc_date.RTC_Date);
	printf("\r\n%s",rtcdatebuf);
	
	RTC_GetTime(RTC_Format_BIN,&rtc);
	sprintf((char *)rtcbuf,"%02d:%02d:%02d",rtc.RTC_Hours,rtc.RTC_Minutes,rtc.RTC_Seconds);
	printf("\r\n%s",rtcbuf);
	for(i=0;i<10;i++)
	{
		WriteASCII(0,ASCII_W*i,rtcdatebuf+i);
	}
	for(i=0;i<8;i++)
	{
		WriteASCII(2,ASCII_W*i,rtcbuf+i);
	}
	LCDrefur();
}
