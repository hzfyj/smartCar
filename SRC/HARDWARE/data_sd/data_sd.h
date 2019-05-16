#ifndef __DATA_SD_h_
#define __DATA_SD_h_

#include "sys.h"

#define SD_DATA_LENGTH 1750  //��sdͼ�����ݳ���
#define SD_8G_BlocksNum 15000000//16777216//8G�ڴ��������//ԭ�ȴ�С̫�������
#define SD_4G_BlocksNum 7500000

#define SD_DATA_NUM 22 //��sd�������� �������Ϊ16λ ÿ�����ݷֳ�2��8λ


void MySD_Init(void);
void Unpack_Data(void);
void SD_datachange16to8(void);
void SD_datachange8to16(void);
void SD_Many_Write(const uint8_t *pbuffer,uint16_t Count,uint8_t BlockNum);
void SD_Write(void);
void SD_ReadData(void);
void data_give(void);
void SD_ManyWT_Init(void);
void SD_ManyWT_ONE(const uint8_t *pbuffer,uint16_t Count);
void MySD_Init1(void);
void Live_Transmission(void);
#endif
