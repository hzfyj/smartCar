#include "sd_yaoxin.h"

#define SD_8G_BlocksNum 15000000//16777216//8G�ڴ��������//ԭ�ȴ�С̫�������

/***********************************************************
*                  ���д�����
************************************************************/
void SD_ManyWT_Init(void)
{
	ESDHC_COMMAND_STRUCT command;
	command.COMMAND = ESDHC_CMD25;
	command.ARGUMENT = 0;
	command.BLOCKS = SD_8G_BlocksNum;
	command.BLOCKSIZE = IO_SDCARD_BLOCK_SIZE;
	sdhc_sendcommand(&command);
}

/********************************************************
*                  ���д�뺯��
*             *pbuffer:д������ԭ��ַ
*              Count  :д�����ݳ���
*              BlockNum:д���������
*********************************************************/
void SD_Many_Write(const uint8_t *pbuffer, uint16_t Count, uint8_t BlockNum)
{
    uint32_t j;
    uint8_t *ptr = (uint8_t *)pbuffer;

    for (j = 0; j < (BlockNum * ((512 + 3) >> 2)); j++)
    {
        while (0 == (SDHC->PRSSTAT & SDHC_PRSSTAT_BWEN_MASK)); //�ȴ�����׼����

        if ((j << 2) < Count)
        {
            SDHC->DATPORT = *(uint32_t *)ptr;
            ptr += 4;
        }
        else
        {
            SDHC->DATPORT = 0xFFFFFFFF;
        }
    }
}

