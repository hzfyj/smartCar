#ifndef _MY_IMAGETRANSFER_H
#define _MY_IMAGETRANSFER_H

#include "headfile.h"

//#define gray
#define bin

/******************************************************
 *									图像传输协议
 *	传输头校验：0x01 0x02 0x03 0x04 0x05	（5字节）
 *	图像：200*70字节 直接传输	共14000字节
 *	运行参数：50个 每位4字节 一倍校验 共400字节
 *	拟图：70（行）*7（组）		共490字节
 ******************************************************/
 
struct Byte8_Struct
{
 uint8_t bit1:1;
 uint8_t bit2:1;
 uint8_t bit3:1;
 uint8_t bit4:1;
 uint8_t bit5:1;
 uint8_t bit6:1;
 uint8_t bit7:1;
 uint8_t bit8:1;
};
 
typedef struct//传线结构体
{
	uint8_t LEnd;
	uint8_t REnd;
	uint8_t LStart;
	uint8_t RStart;
	uint8_t left;
	uint8_t right;
	uint8_t center;
}My_LCR;
 
typedef struct //传输结构体
{
	uint8_t Verific[5];//校验位
	uint8_t Pixels_width;//图像宽度 186
	uint8_t Pixels_height;//图像高度 70
	uint8_t Coefficient_Num;//datanum 50
	uint8_t Parameter_Num;  //parnum 1
	uint8_t Data_Con[50*4*2];//数据 data_give
	uint8_t Par_Con[1*8];//不用
	My_LCR Lcr[70];//三线
	#if defined gray
	uint8_t P_Pixels[200*70];//灰度图像
	#elif defined bin
	uint8_t P_Pixels[1750];//压缩图像
	#endif
}My_Data_Type;

//传输大小计算
#define Verific_Len	(5+4)
#if defined gray//灰度图像大
#define Pixels_Len	(200*70)
#elif defined bin//二值图像小
#define Pixels_Len	(1750)
#endif
#define Data_Len		(50*4*2)
#define	Lcr_Len			(70*7)
#define Fix_Len			(10)
//传输总长度
#define Send_Data_Len	(Verific_Len+Pixels_Len+Data_Len+Lcr_Len+Fix_Len)//14895

//sd卡存储功能
#define sd_save 1
#define sd_read 2


//接口函数
void My_Tranfer_Init(void);//传输初始化
void My_LiveTransfer(void);//实时传输
void My_SdCard_Init(uint8_t sdmode);//初始化sd卡储存或读取
void My_SdCard_Save(void);//sd卡储存灰度图及参数
void My_SdCard_Read(void);//读取sd卡并传输

#endif

