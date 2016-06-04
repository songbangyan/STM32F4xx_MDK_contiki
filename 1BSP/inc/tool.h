#ifndef __TOOL_H_
#define __TOOL_H_

#include "string.h"


#ifndef FALSE
    #define FALSE 0
#endif

#ifndef TRUE
    #define TRUE !FALSE
#endif

unsigned char Char2Hex(unsigned char b);
unsigned char Hex2Char(unsigned char b);
unsigned char Hex2Bcd(unsigned char b);
unsigned char Bcd2Hex(unsigned char b);
unsigned char iHex2iBcd(unsigned short n, unsigned char *b);
unsigned char Hex64toBcd(double n, unsigned char *b);
unsigned char Mem_Reverse(unsigned char *in, unsigned char len, unsigned char *out);
unsigned short iBcd2iHex(unsigned char *b);

unsigned char mem_comp(unsigned char *pdata_a,unsigned char *pdata_b,unsigned int len);
void mem_copy(unsigned char *pdst,unsigned char *psrc,unsigned int len);
void mem_clear(unsigned char *pdata,unsigned int len);
void mem_set(unsigned char *pdata,unsigned int len);

void one_word_crc32(unsigned int data, unsigned int *result);
void set_crc32_reset(unsigned int *result);
void get_crc32(unsigned char *pdata, unsigned short len, unsigned int *result);

#undef  DEF_CHECKSUM_CALC
#define DEF_CHECKSUM_CALC     0   //计算校验和
#undef  DEF_CHECKSUM_CHECK
#define DEF_CHECKSUM_CHECK      1   //校验校验和
unsigned char Cs_Check(unsigned char bDir, unsigned char *pbCheckbuf, unsigned int uiStartPos, unsigned int uiCheckLen);

////////////////////////////////////////////////////////////////////////////
typedef struct
{
  
  unsigned char pcmd ;
  unsigned char isDbFrame; //是否为电表帧

}SPACK_UPCOM;

//输入参数
//bytDir：校验方向，=0表示加校验，=1表示校验检查
//abytCommOrder：需要加校验或校验检查的命令
//nStartPos：校验开始位置
//nCheckLen：需要校验的字节长度
//返回参数
//若bytDir=0，则返回计算出的校验
//若bytDir=1，则校验正确返回1，否则返回0
unsigned short Crc_Check(unsigned int wInitCrc,unsigned char bytDir, unsigned char *abytCommOrder , unsigned short nStartPos, unsigned short nCheckLen);

//返回参数
//DEF_PACK_UPCOM_RECV_OK    ：收到正确帧
//DEF_PACK_UPCOM_645_RECV_OK      ：收到645帧
//DEF_PACK_UPCOM_PHEAD_ERR  ：未收到帧头
//DEF_PACK_UPCOM_PEND_ERR   ：未收到帧尾
//DEF_PACK_UPCOM_PCS_ERR    ：CS校验错误
signed short PactUpCom_Analysis(unsigned char *bCheckBuf, unsigned char bChecklen, SPACK_UPCOM *pack_UpCom);


//分析一帧上行通道协议是否为转发帧
//输入参数
//bCheckBuf ：需要分析的数据
//bChecklen ：需要分析的数据长度
//DEF_PACK_UPCOM_RECV_OK    ：收到正确帧
//DEF_PACK_UPCOM_645_RECV_OK      ：收到645帧
//DEF_PACK_UPCOM_PHEAD_ERR  ：未收到帧头
//DEF_PACK_UPCOM_PEND_ERR   ：未收到帧尾
//DEF_PACK_UPCOM_PCS_ERR    ：CS校验错误
//DEF_PACK_UPCOM_TRANSPROT    : 电表透明转发
signed short PactUpCom_Analysis_TransPort(unsigned char *bCheckBuf, unsigned char bChecklen,signed short uPackUpComType, SPACK_UPCOM *pack_UpCom);


#define DEF_CMD_645_GET_DATA    0x01    //645协议命令：读数据
#define DEF_CMD_645_SET_DATA    0x04    //645协议命令：写数据
#define DEF_CMD_645_MODIFY_PWD    0x0F    //645协议命令：改电表密码
#define DEF_CMD_645_BROAD_SETTIME 0x08    //645协议命令：广播校时
#define DEF_CMD_645_BROAD_GETADDR 0x0D    //645协议命令：广播读电表地址
#define DEF_CMD_645_BROAD_FREEZE  0x12    //645协议命令：广播冻结电量


/************************07******************************************/
#define DEF_CMD_645_07_GET_DATA     0x11    //645_07协议命令：读数据
#define DEF_CMD_645_07_SET_DATA     0x14    //645_07协议命令：写数据
#define DEF_CMD_645_07_MODIFY_PWD   0x18    //645_07协议命令：改电表密码
#define DEF_CMD_645_07_BROAD_SETTIME  0x08    //645_07协议命令：广播校时
#define DEF_CMD_645_07_BROAD_GETADDR  0x13    //645_07协议命令：广播读电表地址
#define DEF_CMD_645_07_BROAD_SWITCH     0x1c      //645_07协议命令：跳闸，合闸，保电
#define DEF_CMD_645_07_BROAD_CONTROL     0x1d     //645_07协议命令：控制命令
#define DEF_CMD_645_07_SAFEATTH_DATA    0x03  //645_07协议命令：安全认证

//////////////电表规约
#define DEF_DB_GY_645   1   //645协议
#define DEF_DB_GY_07    30 //07规约 
#define DEF_DB_GY_UNKNOW  255 //未知

#define DEF_DB_GY_BROADCAST_SYC_TIME 0XFF //广播同步时间

//得到电表的规约类型
unsigned char GetGyTypeByCtr(unsigned char bCtrCode);


#endif
