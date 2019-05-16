#include "DATA_SD.h"
#include "sd.h"
#include "data_sent.h"
#include "ov7620.h"
#include "shangweiji.h"

#define  ImageWidth  200
#define	 ImageLength 70
#define  SD_Data_Num 2

extern Data_Type DATA_ALL;
extern Data_Type *Sent_Data;
extern int SW_speed,SW_duoji,SW_Dajiaohang,PIDRealZhi,DjiaoType;
extern uint8_t RDProject_Cnt,ZhiDaoJianV_Flag,ZHiJieZhiH,ChangZi_DaoJianV_Cnt,Speedtype,SW_Ldiu,SW_Rdiu;
extern uint8_t Piancha,RDprojectFlag,Wandao_Weizhi1,ZhiDao_Cnt,ZhiDaoJianV_Cnt,ChangZhiDao_Cnt,Wandao_Weizhi2,WanjieZhi_H,Wandao_IN_Flag;

int16_t car_data[SD_DATA_NUM/2];
int16_t CarData[512];
uint8_t lines[512];
uint32_t sdnum=0;//SD��������ѡ����

/**********************************************************
*                    SD����ʼ��
***********************************************************/
void MySD_Init1(void)
{
  SD_InitTypeDef SD_InitStruct1;
	
  	SD_InitStruct1.SD_BaudRate = 10000000;
		//�ȴ�SD����ʼ���ɹ�
  	while(SD_Init(&SD_InitStruct1) != ESDHC_OK);
}
/***********************************************************
*                  ���д�����
************************************************************/
void SD_ManyWT_Init(void)
{
	SD_CommandTypeDef SD_CommandStruct1;

	SD_CommandStruct1.COMMAND = ESDHC_CMD25;
	SD_CommandStruct1.BLOCKS = SD_8G_BlocksNum;
	SD_CommandStruct1.BLOCKSIZE = 512;
	SD_CommandStruct1.ARGUMENT = 0;//sd����ʼ��ַ
	SD_SendCommand(&SD_CommandStruct1);
}

/*******************************************************
*              ��Ҫ�������ݴ浽car_data����
*******************************************************/
//void data_give(void)
//{

//car_data[0] =	maichong;
////car_data[1] = Encoder_Left;
////car_data[2] =	Encoder_Right;
////car_data[3] =	g_CarSpeed; 
////car_data[4] =	Angle_Line;
////car_data[5] =	Error_turn;
////car_data[6] = 0;
////car_data[7] =	0;
////car_data[8] = 0;
////car_data[9] =	0;
////car_data[10] =0;
//////	car_data[0] = Mode;
//////	car_data[1] = Threshold;
//////	car_data[2] = Servo;
//////	car_data[3] =	Speed; 
//////	car_data[4] =	Servo_Mid;
//////	car_data[5] =	Error_turn;
//////	car_data[6] = 1 ;
//////	car_data[7] =1;
//////	car_data[8] = 1;
//////	car_data[9] = Line_Count;
//////	car_data[10] = Mid;
//}

void data_give(void)
{
	car_data[0] =  aim;
	car_data[1] =  speed;
	car_data[2] =  jiance;
	car_data[3]=LCenter[15];
	
}
/**********************************************************
*                    SD����ʼ��
***********************************************************/
void MySD_Init(void)
{
  SD_InitTypeDef SD_InitStruct1;
  SD_InitStruct1.SD_BaudRate = 40000000;
	//�ȴ�SD����ʼ���ɹ�
  while(SD_Init(&SD_InitStruct1) != ESDHC_OK);
}
	
/***********************************************************
*                 ��ѹ����
************************************************************/
void Unpack_Data(void) //���ݽ�ѹ
{
	  uint8_t *P;
    uint8_t H,W; 
    uint8_t *Data_Pixels=Sent_Data->Pixels;  
	 // uint16_t count=0;
    union//����һ��������
    {
        uint8_t  Byte;
        struct Byte8_Struct Byte_Bit;
    } BIT;
    P=*Pixels;//��ָ��ָ��ǰ��Ҫ�������
		Data_Pixels+=0;
    for(H=0;H<Image_Height;H++)
    {
        for(W=0;W<(Image_Width>>3);W++)
        {
            BIT.Byte=*Data_Pixels++;

            *P++=BIT.Byte_Bit.bit8;
            *P++=BIT.Byte_Bit.bit7;
            *P++=BIT.Byte_Bit.bit6;
            *P++=BIT.Byte_Bit.bit5;
            *P++=BIT.Byte_Bit.bit4;
            *P++=BIT.Byte_Bit.bit3;
            *P++=BIT.Byte_Bit.bit2;
            *P++=BIT.Byte_Bit.bit1; 

        }

    }

}

/********************************************************
*                  ���д�뺯��
*             *pbuffer:д������ԭ��ַ
*              Count  :д�����ݳ���
*              BlockNum:д���������
*********************************************************/
void SD_Many_Write(const uint8_t *pbuffer,uint16_t Count,uint8_t BlockNum)
{
  uint32_t j;
	uint8_t* ptr=(uint8_t *) pbuffer;	
	
	for (j=0 ;j<(BlockNum*((512+3)>>2));j++)
	{
		while (0 == (SDHC->PRSSTAT & SDHC_PRSSTAT_BWEN_MASK)); //�ȴ�����׼����

		if((j<<2)<Count)
		{
			SDHC->DATPORT =  *(uint32_t *)ptr;
			ptr+=4;
		}
		else
		{
			SDHC->DATPORT = 0xFFFFFFFF;
		}
	}
}


/********************************************************************
*                     SD��д�뺯��
*********************************************************************/
void SD_Write(void)
{
  uint8_t *Data_Pixels=Sent_Data->Pixels; 
	uint8_t i;
	Set_DataToCon();
	Compressed_Data();

	data_give();
	
	for(i=0;i<70;i++)
	{
		lines[i] = L_black[i];
		lines[i+70] = LCenter[i];
		lines[i+140] = R_black[i];
	}
	
	SD_Many_Write(Data_Pixels,SD_DATA_LENGTH,4);	
//	SD_Many_Write((uint8_t*)L_black,512,1);	
//	SD_Many_Write((uint8_t*)LCenter,512,1);
//	SD_Many_Write((uint8_t*)R_black,512,1);
	SD_Many_Write((uint8_t*)car_data,SD_DATA_NUM,1);
	SD_Many_Write((uint8_t*)lines,512,1);
	
}


//���ߺ���
void Live_Transmission()
{
	LCR  *Lcr=(LCR *)Sent_Data->Lcr;//����ͼ���趨��
	uint8_t i=0;
	for(i=0;i<70;i++)
	{
	  Lcr[i].left = L_black[i];
		Lcr[i].right = R_black[i];
		Lcr[i].center = LCenter[i];
	}
	UART_Send_Con();
}

/******************************************************************
*                     ��SD������
******************************************************************/
void SD_ReadData(void)
{
	LCR  *Lcr=(LCR *)Sent_Data->Lcr;//����ͼ���趨��
	uint8_t i;
	uint8_t *Data_Pixels=Sent_Data->Pixels; 
	
	
	//OLED_Clear();
	
//������512
	while(SD_ReadSingleBlock(sdnum,Data_Pixels) != ESDHC_OK);
	sdnum++;
	Data_Pixels += 512;
	while(SD_ReadSingleBlock(sdnum,Data_Pixels) != ESDHC_OK);
	sdnum++;
	Data_Pixels += 512;
	while(SD_ReadSingleBlock(sdnum,Data_Pixels) != ESDHC_OK);
	sdnum++;
	Data_Pixels += 512;
	while(SD_ReadSingleBlock(sdnum,Data_Pixels) != ESDHC_OK);
	sdnum++;
//	while(SD_ReadSingleBlock(sdnum,L_black) != ESDHC_OK);
//	sdnum++;
//	while(SD_ReadSingleBlock(sdnum,LCenter) != ESDHC_OK);                     
//	sdnum++;
//	while(SD_ReadSingleBlock(sdnum,R_black) != ESDHC_OK);
//	sdnum++;	
	while(SD_ReadSingleBlock(sdnum,(uint8_t*)car_data) != ESDHC_OK);
	sdnum++;
	
	while(SD_ReadSingleBlock(sdnum,lines) != ESDHC_OK);
	sdnum++;

	for(i=0;i<70;i++)
	{
		L_black[i] = lines[i];
		LCenter[i] = lines[i+70];
		R_black[i] = lines[i+140];
	}

	for(i = 0;i < 70;i ++)
	{
	  Lcr[i].left = L_black[i];	
		Lcr[i].center = LCenter[i];
		Lcr[i].right = R_black[i];
	}
	Unpack_Data();
	UART_Send_Con();
}
