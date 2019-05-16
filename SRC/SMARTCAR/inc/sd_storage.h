#ifndef _MY_IMAGETRANSFER_H
#define _MY_IMAGETRANSFER_H

#include "headfile.h"

//#define gray
#define bin

/******************************************************
 *									ͼ����Э��
 *	����ͷУ�飺0x01 0x02 0x03 0x04 0x05	��5�ֽڣ�
 *	ͼ��200*70�ֽ� ֱ�Ӵ���	��14000�ֽ�
 *	���в�����50�� ÿλ4�ֽ� һ��У�� ��400�ֽ�
 *	��ͼ��70���У�*7���飩		��490�ֽ�
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
 
typedef struct//���߽ṹ��
{
	uint8_t LEnd;
	uint8_t REnd;
	uint8_t LStart;
	uint8_t RStart;
	uint8_t left;
	uint8_t right;
	uint8_t center;
}My_LCR;
 
typedef struct //����ṹ��
{
	uint8_t Verific[5];//У��λ
	uint8_t Pixels_width;//ͼ���� 186
	uint8_t Pixels_height;//ͼ��߶� 70
	uint8_t Coefficient_Num;//datanum 50
	uint8_t Parameter_Num;  //parnum 1
	uint8_t Data_Con[50*4*2];//���� data_give
	uint8_t Par_Con[1*8];//����
	My_LCR Lcr[70];//����
	#if defined gray
	uint8_t P_Pixels[200*70];//�Ҷ�ͼ��
	#elif defined bin
	uint8_t P_Pixels[1750];//ѹ��ͼ��
	#endif
}My_Data_Type;

//�����С����
#define Verific_Len	(5+4)
#if defined gray//�Ҷ�ͼ���
#define Pixels_Len	(200*70)
#elif defined bin//��ֵͼ��С
#define Pixels_Len	(1750)
#endif
#define Data_Len		(50*4*2)
#define	Lcr_Len			(70*7)
#define Fix_Len			(10)
//�����ܳ���
#define Send_Data_Len	(Verific_Len+Pixels_Len+Data_Len+Lcr_Len+Fix_Len)//14895

//sd���洢����
#define sd_save 1
#define sd_read 2


//�ӿں���
void My_Tranfer_Init(void);//�����ʼ��
void My_LiveTransfer(void);//ʵʱ����
void My_SdCard_Init(uint8_t sdmode);//��ʼ��sd��������ȡ
void My_SdCard_Save(void);//sd������Ҷ�ͼ������
void My_SdCard_Read(void);//��ȡsd��������

#endif

