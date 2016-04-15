
#include "config.h"

/* Private typedef -----------------------------------------------------------*/
//extern HZ_TypeDef HZ1[];
//extern SZ_TypeDef SZ1[];

unsigned char CtrBytes[39]={
	0xe2, 0xe9, 0x2b, 0x24, 0x81, 0xc6, 0xa4, 0xa6, 0xc4, 0xa3,
	0xd1, 0xd5, 0x84, 0xc8, 0x10, 0xda, 0xf4, 0x25, 0xf6, 0x5a, 
	0xf5, 0x00, 0xf7, 0x9f, 0xf8, 0x89, 0xad, 0x40, 0xf0, 0xc4,
	0x90, 0x00, 0x84, 0xf1, 0x9f, 0xf2, 0x00, 0xf3, 0x9f,
};

//============================================================================= 
//函 数 名:  Delay_ms() 
//功 能：	 软件延时
//入口参数： ch:数据
//出口参数： 无
//返 回 值： 无
//============================================================================= 
void Delay_ms(u16 i)
	{
	u16 m;
	while(i--)
		{
		for(m=0;m<0xFF;m++);
		}
	}

//============================================================================= 
//函 数 名:  WriteCommandUC1698U() 
//功 能：	写命令到UC1698U
//入口参数： CmdData:命令码
//出口参数： 无
//返 回 值： 无
//============================================================================= 
void WriteCommandUC1698U(u8 CmdData)
	{
	*(u8 *) (LCD_BASE ) = CmdData;
	}
//============================================================================= 
//函 数 名:  WriteDataUC1698U() 
//功 能：	写数据到UC1698U
//入口参数： CmdData:写入的数据
//出口参数： 无
//返 回 值： 无
//============================================================================= 
void WriteDataUC1698U(u8 Data)
	{
	*(u8 *) (LCD_BASE + 2) = Data;
	}

//============================================================================= 
//函 数 名: InitUC1698U() 
//功 能：	初始化 UC1698U
//入口参数： 无
//出口参数： 无
//返 回 值： 无
//============================================================================= 
void InitUC1698U(void)
	{
	u16 i;
	GPIO_LCDRST_OFF();
	WriteCommandUC1698U(CtrBytes[0]);
	// Wait LCM ready.
	Delay_ms(100);
	//The beginning of initialization
	for( i=1; i<39; i++ )
		{
		WriteCommandUC1698U(CtrBytes[i]);	
		}

	}

//============================================================================= 
//函 数 名: Write4DotsUC1698U() 
//功 能: 	UC1698U横向写4个点的子函数
//入口参数:  Data:要显示的数据
//出口参数:  无
//返 回 值:  无
//============================================================================= 
void Write4DotsUC1698U(u8 Data)
	{
	u8 TempData = 0;		

	if(Data & 0x08)
		{
		TempData=0xf0;
		}	   
	if(Data & 0x04)
		{
		TempData|=0x0f;
		}	   
	WriteDataUC1698U(TempData);
	
	TempData=0;
	if(Data & 0x02)
		{
		TempData=0xf0;
		}			   	   
	if(Data & 0x01)
		{
		TempData|=0x0f;
		}					   
	WriteDataUC1698U(TempData);
	}

//============================================================================= 
//函 数 名: Write6DotsUC1698U() 
//功 能: 	UC1698U横向写6个点的子函数
//入口参数:  Data:要显示的数据
//出口参数:  无
//返 回 值:  无
//============================================================================= 
void Write6DotsUC1698U(u8 Data)
	{
	u8 TempData = 0;
		
	if(Data & 0x80)
		{
		TempData=0xf0;
		}	  
	if(Data & 0x40)
		{
		TempData|=0x0f;
		}	   
	WriteDataUC1698U(TempData);	

	TempData=0;
	if(Data & 0x20)
		{
		TempData=0xf0;
		}	   
	if(Data & 0x10)
		{
		TempData|=0x0f;
		}				 	   
	WriteDataUC1698U(TempData);
	
	TempData=0;
	if(Data & 0x08)
		{
		TempData=0xf0;
		}	   
	if(Data & 0x04)
		{
		TempData|=0x0f;
		}	   
	WriteDataUC1698U(TempData);
	
	}


//============================================================================= 
//函 数 名: ClearScreenUC1698U() 
//功 能: 	清屏
//入口参数: 无
//出口参数:  无
//返 回 值:  无
//============================================================================= 
void ClearScreenUC1698U(void)
	{
	u16 i;

	WriteCommandUC1698U(0x60);			//row address LSB	
	WriteCommandUC1698U(0x70);			//row address MSB	
	WriteCommandUC1698U(0x05);			//Column address LSB	
	WriteCommandUC1698U(0x12);			//Column address MSB
	
	for(i=0;i<12960;i++)
		{
		WriteDataUC1698U(0x00);			    
		}
	
	}

//============================================================================= 
//函 数 名: DisplayBorder() 
//功 能: 	画边框
//入口参数: 无
//出口参数:  无
//返 回 值:  无
//============================================================================= 
void DisplayBorder(void)
	{
	u16 uc_RowCnt,uc_ColCnt;
	u8 uc_RowAddrH,uc_RowAddrL;
	
	//The First Line
	WriteCommandUC1698U(0x70); //Set Row Address(MSB)
	WriteCommandUC1698U(0x60); //Set Row Address(LSB)

	WriteCommandUC1698U(0x12);//Set Address(MSB) 112->HEX
	WriteCommandUC1698U(0x05);//Set Address(LSB)

	for (uc_ColCnt=0;uc_ColCnt<54;uc_ColCnt++)
		{
		WriteDataUC1698U(0xFF);
		WriteDataUC1698U(0xFF);
		}

	//The Middle Lines
	for (uc_RowCnt=1;uc_RowCnt<159;uc_RowCnt++)
		{
		uc_RowAddrH =uc_RowCnt /16;
		uc_RowAddrL =uc_RowCnt %16;

		WriteCommandUC1698U(0x70 |uc_RowAddrH); //Set Row Address(MSB)
		WriteCommandUC1698U(0x60 |uc_RowAddrL); //Set Row Address(LSB)

		WriteCommandUC1698U(0x12);//Set Address(MSB) 112->HEX
		WriteCommandUC1698U(0x05);//Set Address(LSB)

		WriteDataUC1698U(0xf0);
		WriteDataUC1698U(0x00);
		
		for (uc_ColCnt=0;uc_ColCnt<52;uc_ColCnt++)
		{
			WriteDataUC1698U(0x00);
			WriteDataUC1698U(0x00);
		}

		WriteCommandUC1698U(0x70 |uc_RowAddrH); //Set Row Address(MSB)
		WriteCommandUC1698U(0x60 |uc_RowAddrL); //Set Row Address(LSB)	
		WriteCommandUC1698U(0x15);//Set Address(MSB) 112->HEX
		WriteCommandUC1698U(0x0a);//Set Address(LSB)		
		WriteDataUC1698U(0xff);
		WriteDataUC1698U(0xff);
		}

	//The Last Line
	uc_RowAddrH =159/16;
	uc_RowAddrL =uc_RowCnt %16;

	WriteCommandUC1698U(0x70 |uc_RowAddrH ); //Set Row Address(MSB)
	WriteCommandUC1698U(0x60 |uc_RowAddrL); //Set Row Address(LSB)

	WriteCommandUC1698U(0x12);//Set Address(MSB) 112->HEX
	WriteCommandUC1698U(0x05);//Set Address(LSB)

	for (uc_ColCnt=0;uc_ColCnt<56;uc_ColCnt++)
		{
		WriteDataUC1698U(0xFF);
		WriteDataUC1698U(0xFF);
		}	
	
	}
//============================================================================= 
//函 数 名: WriteWord() 
//功 能: 	写一个点阵为12*12的汉字
//入口参数:  x y位置，index[2]汉字
//出口参数:  无
//返 回 值:  无
//============================================================================= 
void WriteWord(u8 x, u8 y, u8 index[2])
	{
	u8 i;
	u8 RH,RL,CH,CL;
	u8 *p;
	x = x+0x25;
	for(i=0;i<MAXNUMOFHZ;i++)
		{
		if((HZ1[i].Index[1] == index[1])&&(HZ1[i].Index[0] == index[0]))
			{
			p=HZ1[i].Msk;
			break;
			}
		}
	if(i == MAXNUMOFHZ)
		{
		p=HZ1[0].Msk;
		}	
	for(i=0;i<12;i++)
		{
		CH = (x)/16;
		CL = (x)%16;
		RH = (y+i)/16;
		RL = (y+i)%16;
		WriteCommandUC1698U(0x70|RH); //Set Row Address(MSB)
		WriteCommandUC1698U(0x60|RL); //Set Row Address(LSB) 

		WriteCommandUC1698U(0x10|CH);//Set Column Address(MSB) 112->HEX
		WriteCommandUC1698U(0x00|CL);//Set Column Address(LSB)

		Write4DotsUC1698U(*(p+(i*2))>>4);
		Write4DotsUC1698U(*(p+(i*2)));
		Write4DotsUC1698U(*(p+i*2+1)>>4);		
		}
	}


//============================================================================= 
//函 数 名: WriteASCII() 
//功 能: 	写一个点阵为12*6的数字
//入口参数:  x y位置，index[1]为数字
//出口参数:  无
//返 回 值:  无
//============================================================================= 
void WriteASCII(u8 x, u8 y, u8 index[1])
	{
	u8 i;
	u8 RH,RL,CH,CL;
	u8 *p;
	x = x+0x25;
	for(i=0;i<MAXNUMOFSZ;i++)
		{
		if((SZ1[i].Index[0] == index[0]))
			{
			p=SZ1[i].Msk;
			break;
			}
		}
	if(i == MAXNUMOFSZ)
		{
		p=SZ1[0].Msk;
		}

	for(i=0;i<12;i++)
		{
		CH = (x)/16;
		CL = (x)%16;
		RH = (y+i)/16;
		RL = (y+i)%16;
		WriteCommandUC1698U(0x70|RH); //Set Row Address(MSB)
		WriteCommandUC1698U(0x60|RL); //Set Row Address(LSB)

		WriteCommandUC1698U(0x10|CH);//Set Column Address(MSB) 
		WriteCommandUC1698U(0x00|CL);//Set Column Address(LSB)

		Write6DotsUC1698U(*(p+i));
		}
	}
//============================================================================= 
//函 数 名: WriteBCD() 
//功 能: 	写一个点阵为12*6的数字
//入口参数:  x y位置，index为BCD码
//出口参数:  无
//返 回 值:  无
//============================================================================= 
void WriteBCD(u8 x, u8 y, u8 index)
	{
	u8 i;
	u8 RH,RL,CH,CL;
	u8 *p;
	x = x+0x25;
	p=SZ1[index].Msk;

	for(i=0;i<12;i++)
		{
		CH = (x)/16;
		CL = (x)%16;
		RH = (y+i)/16;
		RL = (y+i)%16;
		WriteCommandUC1698U(0x70|RH); //Set Row Address(MSB)
		WriteCommandUC1698U(0x60|RL); //Set Row Address(LSB)

		WriteCommandUC1698U(0x10|CH);//Set Column Address(MSB) 
		WriteCommandUC1698U(0x00|CL);//Set Column Address(LSB)

		Write6DotsUC1698U(*(p+i));
		}	
	}
//============================================================================= 
//函 数 名: WriteLine(u8 y) 
//功 能: 	画横线
//入口参数:  y：位置
//出口参数:  无
//返 回 值:  无
//============================================================================= 
void WriteLine(u8 y)
	{
	u8 i;

	WriteCommandUC1698U(0x70|(y/16)); //Set Row Address(MSB)
	WriteCommandUC1698U(0x60|(y%16)); //Set Row Address(LSB)

	WriteCommandUC1698U(0x12);//Set Address(MSB) 112->HEX
	WriteCommandUC1698U(0x05);//Set Address(LSB)
	for (i=0;i<54;i++)
		{
		WriteDataUC1698U(0xFF);
		WriteDataUC1698U(0xFF);
		}
	y++	;	  	
	WriteCommandUC1698U(0x70|(y/16)); //Set Row Address(MSB)
	WriteCommandUC1698U(0x60|(y%16)); //Set Row Address(LSB)

	WriteCommandUC1698U(0x12);//Set Address(MSB) 112->HEX
	WriteCommandUC1698U(0x05);//Set Address(LSB)
	for (i=0;i<54;i++)
		{
		WriteDataUC1698U(0x00);
		WriteDataUC1698U(0x00);
		}	
	}

//============================================================================= 
//函 数 名: SetBL(void)
//功 能: 	开启LCD背光
//入口参数:  无
//出口参数:  无
//返 回 值:  无
//============================================================================= 
void SetBL(void)
	{
	GPIO_ResetBits(GPIOF, GPIO_Pin_11);
	}
  
//============================================================================= 
//函 数 名: ClearBL(void)
//功 能: 	关闭LCD背光
//入口参数:  无
//出口参数:  无
//返 回 值:  无
//============================================================================= 
void ClearBL(void)
	{
	GPIO_SetBits(GPIOF, GPIO_Pin_11);
	}

//============================================================================= 
//函 数 名: ResetLCD(void)
//功 能: 	复位LCD
//入口参数:  无
//出口参数:  无
//返 回 值:  无
//============================================================================= 
void ResetLCD(void)
	{
	GPIO_ResetBits(GPIOC, GPIO_Pin_5);
	}

//============================================================================= 
//函 数 名: SetLCD(void)
//功 能: 	复位LCD
//入口参数:  无
//出口参数:  无
//返 回 值:  无
//============================================================================= 
void SetLCD(void)
	{
	GPIO_SetBits(GPIOC, GPIO_Pin_5);
	}

