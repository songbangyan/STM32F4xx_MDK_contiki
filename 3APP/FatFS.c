
#include "bsp.h"
#include "ff.h"
#include "string.h"

/*保存BMP 和TXT文件的数目*/
unsigned char BMP_NUM=0; 
unsigned char TXT_NUM=0;
char TXT_Files[100][40];	//最多100个文件,
char BMP_Files[100][40];	//最多100个文件,
DIR dirs;
FILINFO finfo;
FATFS fs;
void Find_FileName(void)
{
	const char path[]="";
	unsigned short i;
	FRESULT res;

/*长文件名支持*/	
#if _USE_LFN
	static char lfn[_MAX_LFN * (_DF1S ? 2 : 1) + 1];
	finfo.lfname = lfn;
	finfo.lfsize = sizeof(lfn);
#endif


	/*挂载文件系统*/
	res = f_mount(0, &fs);
	res=f_opendir(&dirs, path);

	if (res == FR_OK) {/*如果打开主目录成功*/
		
		while (f_readdir(&dirs, &finfo) == FR_OK){/*通过dirs，依次阅读文件名，知道末尾*/
			
			   	
			if(finfo.fattrib & AM_DIR){	 /*是目录就结束本次循环*/
				continue;	
			}
			if (finfo.fattrib & AM_ARC) { /*刚打开的文件属性是存档文件,*/
				
				if(!finfo.fname[0])	 break; /*文件尾，跳出while*/		
				if(finfo.lfname[0]){/*长文件名	*/
					i = (unsigned char )strlen(finfo.lfname);/*求文件名的长度，求出之后得到后缀*/

					if((finfo.lfname[i-3]=='t') && (finfo.lfname[i-2]=='x') && (finfo.lfname[i-1]=='t')){
						strcpy(TXT_Files[TXT_NUM],(const char *)finfo.lfname);
						TXT_NUM++;
					}
					else if((finfo.lfname[i-3]=='b') && (finfo.lfname[i-2]=='m') && (finfo.lfname[i-1]=='p')){
						strcpy(BMP_Files[BMP_NUM],(const char *)finfo.lfname);
						BMP_NUM++;
					}
				}
				else{	/*段文件名*/
					i = (unsigned char )strlen(finfo.fname);/*求文件名的长度，求出之后得到后缀*/

					if((finfo.fname[i-3]=='t') && (finfo.fname[i-2]=='x') && (finfo.fname[i-1]=='t')){
						strcpy(TXT_Files[TXT_NUM],(const char *)finfo.fname);
						TXT_NUM++;
					}
					else if((finfo.fname[i-3]=='b') && (finfo.fname[i-2]=='m') && (finfo.fname[i-1]=='p')){
						strcpy(BMP_Files[BMP_NUM],(const char *)finfo.fname);
						BMP_NUM++;
					}	
				}
			}
		}	
	}
}

void dispalyfilename(void)
{
	unsigned char i;
	Find_FileName();
	for(i=0;i<BMP_NUM;i++){
		printf("\r\n%s",BMP_Files[i]);
//		lcd_display_string_line(0,i*16,0xf800,0,(unsigned char *)BMP_Files[i]);	
	}
	//显示.txt文件
	for(i=0;i<TXT_NUM;i++){
		printf("\r\n%s",TXT_Files[i]);
//		lcd_display_string_line(120,i*16,0xf800,0,(unsigned char *)TXT_Files[i]);	
	}

}
