
#include "RTC.h"


//Time_Def rtc_real;




volatile  u32  g_sec;

  
//u8 RTC_GetWeek(u16 year,u8 month,u8 day);
//判断是否是闰年函数
//月份 1 2 3 4 5 6 7 8 9 10 11 12
//闰年 31 29 31 30 31 30 31 31 30 31 30 31
//非闰年 31 28 31 30 31 30 31 31 30 31 30 31
//输入:年份
//输出:该年份是不是闰年.1，是.0，不是
u8 Is_LeapYear(u16 year)
{
  if(((year%4==0)&&(year%100!=0))||(year%400==0))
    return 1;
  else
    return 0;
}
//设置时钟
//把输入的时钟转换为秒钟
//以1970 年1 月1 日为基准
//1970~2099 年为合法年份
//返回值:1，成功;其他:错误代码.
//月份数据表
const u8 week_table[12]={0,3,3,6,1,4,6,2,5,0,3,5};
//平年的月份日期表
const u8 month_table[12]={31,28,31,30,31,30,31,31,30,31,30,31};
u8 RTC_Set(Time_Def *rtc)
{
  u16 i;
  u8 tpmon;
  u32 seccount = 0;
  if(rtc->year<1970||rtc->year>2099)//超限
  return 0;
  for(i=1970;i<rtc->year;i++)//计算年份的秒数
  {
    if(Is_LeapYear(i))
      seccount+=31622400;//闰年的秒钟数
    else
      seccount+=31536000; //平年的秒钟数 
  }
  tpmon = rtc->mon - 1;
  for(i=0;i<tpmon;i++)
  {
    seccount+=(u32)month_table[i]*86400;//月份秒钟数相加
    if(Is_LeapYear(rtc->year)&&(i==1))
      seccount+=86400;//闰年2 月份增加一天的秒钟数
  }
  seccount += (u32)(rtc->day-1)*86400;//把前面日期的秒钟数相加
  seccount += (u32)rtc->hour*3600;//小时秒钟数
  seccount += (u32)rtc->min*60; //分钟秒钟数
  seccount += rtc->sec;//最后的秒钟加上去
  //设置时钟
  g_sec = seccount;
  return 1;
}
//得到当前的时间
//返回值:1，成功;其他:错误代码.
u8 RTC_Get(Time_Def *rtc_real)
{
  u32 temp=0;
  u16 temp1=0;
  u32 seccount=0;

  seccount = g_sec;//获取秒计数器的值
  temp=seccount/86400; //得到天数(秒钟数对应的)
  if(temp>0)//超过一天
  {
    temp1=1970;
    while(temp>=365)
    {
      if(Is_LeapYear(temp1))//闰年
      {
        if(temp>=366)
         temp-=366;
        else //当前年份即为此闰年
         break;
     }
     else
        temp-=365;
    temp1++;
    }
  }
  rtc_real->year=temp1;//得到年份
  temp1=0;
  while(temp>=28)//超过了一个月
  {
    if(Is_LeapYear(rtc_real->year)&&(temp1==1))//当年是不是闰年/2 月份
    {
      if(temp>=29)
        temp-=29;//闰年的2月天数
      else
        break;
    }else
    {
      if(temp>=month_table[temp1])
        temp-=month_table[temp1];//平年
      else
        break;
    }
    temp1++;
  }
  rtc_real->mon=temp1+1;//得到月份
  rtc_real->day=temp+1; //得到日期
  temp=seccount%86400; //得到秒钟数
  rtc_real->hour=temp/3600; //小时
  rtc_real->min=(temp%3600)/60; //分钟
  rtc_real->sec=(temp%60); //秒钟
  rtc_real->week=RTC_GetWeek(rtc_real->year,rtc_real->mon,rtc_real->day); 
  return 1;
}
//获得现在是星期几
//功能描述:输入公历日期得到星期(只允许1901-2099年)
//输入参数：公历年月日
//返回值：星期号                      
u8 RTC_GetWeek(u16 year,u8 month,u8 day)
{ 
  u16 temp;
  u8 yearH,yearL; 
  yearH=year/100; yearL=year%100;
  // 如果为21世纪,年份数加100 
  if (yearH>19)
  yearL+=100;
  // 所过闰年数只算1900年之后的 
  temp=yearL+yearL/4;
  temp=temp%7;
  temp=temp+day+week_table[month-1];
  if (yearL%4==0&&month<3)
    temp--;
  return(temp%7);
}
//计算传入的时间和现在时间对比已经过了多少时间
//返回为秒数
u32 Time_Pasted(Time_Def *Oldtime)
{
  u16 i;
  u8 tpmon;
  u32 seccount = 0;
  if(Oldtime->year<1970||Oldtime->year>2099)//超限
  return 0;
  for(i=1970;i<Oldtime->year;i++)//计算年份的秒数
  {
    if(Is_LeapYear(i))
      seccount+=31622400;//闰年的秒钟数
    else
      seccount+=31536000; //平年的秒钟数 
  }
  tpmon = Oldtime->mon - 1;
  for(i=0;i<tpmon;i++)
  {
    seccount+=(u32)month_table[i]*86400;//月份秒钟数相加
    if(Is_LeapYear(Oldtime->year)&&(i==1))
      seccount+=86400;//闰年2 月份增加一天的秒钟数
  }
  seccount += (u32)(Oldtime->day-1)*86400;//把前面日期的秒钟数相加
  seccount += (u32)Oldtime->hour*3600;//小时秒钟数
  seccount += (u32)Oldtime->min*60; //分钟秒钟数
  seccount += Oldtime->sec;//最后的秒钟加上去
  return g_sec - seccount;
}
u32 Time_comp(Time_Def *Oldtime, Time_Def *Newtime)
{
  u16 i;
  u8 tpmon;
  u32 seccount = 0;
  u32 seccount1 = 0;
  
  if(Oldtime->year<1970||Oldtime->year>2099)//超限
  return 0;
  for(i=1970;i<Oldtime->year;i++)//计算年份的秒数
  {
    if(Is_LeapYear(i))
      seccount+=31622400;//闰年的秒钟数
    else
      seccount+=31536000; //平年的秒钟数 
  }
  tpmon = Oldtime->mon - 1;
  for(i=0;i<tpmon;i++)
  {
    seccount+=(u32)month_table[i]*86400;//月份秒钟数相加
    if(Is_LeapYear(Oldtime->year)&&(i==1))
      seccount+=86400;//闰年2 月份增加一天的秒钟数
  }
  seccount += (u32)(Oldtime->day-1)*86400;//把前面日期的秒钟数相加
  seccount += (u32)Oldtime->hour*3600;//小时秒钟数
  seccount += (u32)Oldtime->min*60; //分钟秒钟数
  seccount += Oldtime->sec;//最后的秒钟加上去

  if(Newtime->year<1970||Newtime->year>2099)//超限
  return 0;
  for(i=1970;i<Newtime->year;i++)//计算年份的秒数
  {
    if(Is_LeapYear(i))
      seccount1+=31622400;//闰年的秒钟数
    else
      seccount1+=31536000; //平年的秒钟数 
  }
  tpmon = Newtime->mon - 1;
  for(i=0;i<tpmon;i++)
  {
    seccount1+=(u32)month_table[i]*86400;//月份秒钟数相加
    if(Is_LeapYear(Newtime->year)&&(i==1))
      seccount1+=86400;//闰年2 月份增加一天的秒钟数
  }
  seccount1 += (u32)(Newtime->day-1)*86400;//把前面日期的秒钟数相加
  seccount1 += (u32)Newtime->hour*3600;//小时秒钟数
  seccount1 += (u32)Newtime->min*60; //分钟秒钟数
  seccount1 += Newtime->sec;//最后的秒钟加上去
  
  return seccount1 - seccount;
}/*******************************************************************************
* Function Name  : RTC_Configuration
* Description    : Configures the RTC.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void BSP_RTC_init(void)
{
  Time_Def rtc_real;
  NVIC_InitTypeDef NVIC_InitStructure;
  /* Enable PWR and BKP clocks */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);  
  /* Allow access to BKP Domain */
  PWR_BackupAccessCmd(ENABLE);  
  /* Reset Backup Domain */
  BKP_DeInit(); 
  /* Select the RTC Clock Source */
  RCC_RTCCLKConfig(RCC_RTCCLKSource_HSE_Div128);  
  /* Enable RTC Clock */
  RCC_RTCCLKCmd(ENABLE);  
  /* Wait for RTC registers synchronization */
  RTC_WaitForSynchro(); 
  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();  
  /* Enable the RTC Second */
  RTC_ITConfig(RTC_IT_SEC, ENABLE); 
  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();  
  /* Set RTC prescaler: set RTC period to 1sec */
  RTC_SetPrescaler(62499);  
  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();  
  /* To output second signal on Tamper pin, the tamper functionality
     must be disabled (by default this functionality is disabled) */
  BKP_TamperPinCmd(DISABLE);  
  
  /* Configure the NVIC Preemption Priority Bits */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0); 
  /* Enable the RTC Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 8;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  GetBuildTime(&rtc_real);
  rtc_real.year += 2000;
  RTC_Set(&rtc_real);
}
/*******************************************************************************
* Function Name  : RTC_IRQHandler
* Description    : This function handles RTC global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RTC_IRQHandler(void)
{
  if (RTC_GetITStatus(RTC_IT_SEC) != RESET)
  {
    /* Clear the RTC Second interrupt */
    RTC_ClearITPendingBit(RTC_IT_SEC);    
    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();
    g_sec++;
  }
}


