主程序（RA8803.C）：
/****************************************************
图片横向取模
*********************************************************/
#include <reg52.h>
#include <driver.h>

code uchar s1[]={"320X240液晶驱动"};
code uchar s2[]={"-- RA8803控制器 Crasyboye"};
code uchar s3[]={"RA8803是一款双图层文字/图形LCD控制器,"
                 "支持320X240，扩展模式可支持640X240和320X480。"
                 "RA8803支持屏幕水平卷动及垂直卷动"
                 "支持512Byte sRAM可自行造字等等"};
code uchar s4[]={"本驱动来源于网络，经修参照资料改后显示稳定，"
                 "可以用来测试采用RA8803控制器的液晶屏，"
                 "如转摘请注明出处:"};
code uchar s5[]={"http*//hi*baidu*com*crasyboye"};
/***************************************************
函数：void display_NET()
功能：网点的显示,大小四种网点
****************************************************/
void display_NET(uchar s,uchar n)
{
lcd_cmdwrite(0x00,0xc5); //图形显示模式
lcd_cursorxy(0,0);

for(i=0;i<240;i++) //行画点控制
{
for(j=0;j<40;j++)   //同时进行8列
{
      if(n==1)lcd_datawrite(s);
      if(n==2) lcd_datawrite(s);
      if(n==4)lcd_datawrite(s);
   if(n==8)
     if(j%2)lcd_datawrite(s);
    else lcd_datawrite(~s);
}
   if(n==1) s=~s;
   if(n==2) if((i)%2) s=~s;
   if(n==4) if((i+1)%4==0) s=~s;
   if(n==8) if((i+1)%8==0) s=~s;

}
}
/*************************************************
            主程序
***************************************************/
void main(void)
{
delay(10);
lcd_Initial();
while(1)
   {

    lcd_clear();
    display_NET(0x0f,4);
    DelayKey(1,4);

lcd_clear();
    display_NET(0x00,8);
    DelayKey(1,4);

lcd_clear();
    lcd_clear();
    lcd_cursorxy(5,10);
    display_Bstring(s1);

    lcd_cursorxy(7,50);
    display_string(s2);

    lcd_cursorxy(4,74);
    display_string(s3);
    lcd_cursorxy(4,145);
    display_string(s4);
   lcd_cursorxy(4,200);
    display_string(s5);
DelayKey(1,4);
   }  
}

     头文件（driver.h）：
#ifndef _driver_h
#define _driver_h
#define uchar unsigned char
#define uint unsigned int

#define x 320
#define y 240
#define xy (x/8)*y

sbit lcd_RS=     P3^1; //A0
sbit lcd_WR=     P3^4;
sbit lcd_RD=     P3^3;
sbit lcd_CS=     P3^2 ; //CE27
sbit lcd_RES=    P3^0;
#define lcd_data    P0
sbit key=       P3^4;    //用来定住显示的

uint i,j;
void melay(unsigned int MS)
{
unsigned char us,usn;
while(MS!=0)
{
   usn = 2; //for 12M
   while(usn!=0)
   {
    us=0xf6;
    while (us!=0){us--;};
    usn--;
   }
   MS--;
}
}

void DelayKey(unsigned int Second , unsigned int MS100)
{       //输入精确到0.1S,是用,
unsigned int i;
for(i=0;i<Second*100+MS100;i++)
{
   if(key==0)
   {
    melay(20);
    while(key==0) melay(100);
    break;
   }
   else melay(50);
}    
}
/**********************************************
函数：void delay(uint t)
功能：延时微秒的设定
**************************************************/
void delay(uint t)
{
while(t--);
}
/**************************************************
函数：void lcd_cmdwrite (uchar cmdx , uchar cmdy)
功能：在指定的寄存器写下命令
********************************************************/
void lcd_cmdwrite (uchar cmdx , uchar cmdy)
{
lcd_data=cmdx;
lcd_CS=0;
lcd_RD=1;
lcd_RS=0;   
lcd_WR=0;
lcd_WR=1;   
lcd_RS=1;
lcd_CS=1;
   
lcd_data=cmdy;
lcd_CS=0;
lcd_RD=1;
lcd_RS=0;   
lcd_WR=0;
lcd_WR=1;
lcd_RS=1;
lcd_CS=1;
}
/*************************************************
函数：void lcd_datawrite(unsigned char datax)
功能：写下显示的数据
*****************************************************/
void lcd_datawrite(unsigned char datax)
{
    lcd_data=datax;
lcd_CS=0;
lcd_RD=1;
lcd_RS=1;
lcd_WR=0;
lcd_WR=1;
lcd_RS=0;
lcd_CS=1;
}
/****************************************************
函数：uchar lcd_cmdread(unsigned char cmdx)
功能：读回一个值
*********************************************************/
uchar lcd_cmdread(uchar cmdx)
{
    uchar address_cmd;
lcd_data=cmdx;
lcd_CS=0;
lcd_RD=1;
lcd_RS=0;
lcd_WR=0;
lcd_WR=1;  
lcd_RS=1;
lcd_CS=1;

lcd_data=0xff;
lcd_CS=0;
lcd_WR=1;
lcd_RS=0;  
lcd_RD=0;
address_cmd=lcd_data;
lcd_RD=1;
lcd_RS=1;
lcd_CS=1;
return(address_cmd);
}
/******************************************************
函数：void lcd_Initial(void)
功能：初始化好多寄存器
**********************************************************/
void lcd_Initial(void)
{
lcd_cmdwrite(0x00,0xcd);   //WLCR 正常模式；文字模式；屏幕开启；不闪烁；不反白；
lcd_cmdwrite(0x01,0x03);   //MISC 系统频率选择：8M
lcd_cmdwrite(0x02,0x10);   //APSR  
lcd_cmdwrite(0x03,0x80);   //ADSR 平移方向动控制
lcd_cmdwrite(0x10,0x6b);   //WCCR 正常显示，不加粗

lcd_cmdwrite(0x12,0xb3);   //MAMR   

lcd_cmdwrite(0x20,0x27);   //AWRR  
lcd_cmdwrite(0x30,0xef);   //AWBR  
lcd_cmdwrite(0x40,0x00);   //AWLR  
lcd_cmdwrite(0x50,0x00);   //AWTR  

lcd_cmdwrite(0x21,0x27);   //DWRR  
lcd_cmdwrite(0x31,0xef);   //DWBR  
lcd_cmdwrite(0x41,0x00);   //DWLR
lcd_cmdwrite(0x51,0x00);   //DWTR

lcd_cmdwrite(0x60,0x00);   //CPXR
lcd_cmdwrite(0x61,0x00);   //BGSG
lcd_cmdwrite(0x70,0x00);   //CPYR
lcd_cmdwrite(0x71,0x00);   //BGCM
lcd_cmdwrite(0x72,0xef);   //EDCM       
lcd_cmdwrite(0x90,0x09);   //SCCR  
lcd_cmdwrite(0xc0,0xc8);   //TPCR  
lcd_cmdwrite(0xc1,0x3a);   //TPSR  
lcd_cmdwrite(0xc8,0x80);   //TPXR
lcd_cmdwrite(0xc9,0x80);   //TPYR
lcd_cmdwrite(0xca,0x00);   //TPZR
lcd_cmdwrite(0xd0,0x0f);   //LCCR  
lcd_cmdwrite(0xe0,0x00);   //PNTR
lcd_cmdwrite(0xf0,0xa0);   //FNCR  
lcd_cmdwrite(0xf1,0x0f);   //FVHT      字体不放大
}

/*****************************************************
函数：void lcd_clear()
功能：清除内存
********************************************************/
void lcd_clear()
{
uchar reg;
lcd_cmdwrite(0xe0,0x00);
reg = lcd_cmdread(0xf0);
    reg &=0xf7;
reg |=0x08;
lcd_cmdwrite(0xf0,reg);
    delay(300);
}
/******************************************************
函数：void lcd_cursorxy(unsigned int xn,unsigned int yn)
功能：设定要显示数据的地址
**********************************************************/
void lcd_cursorxy(uint xn,uint yn)
{
lcd_cmdwrite(0x60,xn);
lcd_cmdwrite(0x70,yn);
}
/***********************************************
函数：void lcd_showbig(uchar *text,uint xn)
功能：显示字符，汉字
******************************************************/
void display_string(uchar *text)
{
    lcd_cmdwrite(0x00,0xcd);
lcd_cmdwrite(0xf1,0x0f); //不放大
    while(*text != '\0')         
{
    lcd_datawrite(*text);
    ++text;
    }
}

void display_Bstring(uchar *text)
{
    lcd_cmdwrite(0x00,0xcd);
lcd_cmdwrite(0xf1,0x5f); //放大一倍
    while(*text != '\0')         
{
    lcd_datawrite(*text);
    ++text;
    }
}
/***********************************************
函数：void display_img(uchar code *p)
功能：显示一幅320*240的完美图片,但分正显和反显
      显示，我用的S52，放不下了。
***********************************************
void display_img(uchar code *p,bit c)
{
lcd_cmdwrite(0x00,0xc5);         
lcd_cursorxy(0,0);
for(i=0;i<xy;i++)
     {
      if(c)lcd_datawrite(p[i]);     //320*240
      else lcd_datawrite(~p[i]);
     }
}
*/
#endif