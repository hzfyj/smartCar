
#include "sd_storage.h"	//sd��
#include "headfile.h"
#include "Fuzzy_control.h"

/******************************************************
 *									ͼ����Э��
 *	����ͷУ�飺0x01 0x02 0x03 0x04 0x05	��5�ֽڣ�
 *	ͼ��200*70�ֽ� ֱ�Ӵ���	��14000�ֽ�
 *	���в�����50�� ÿλ4�ֽ� ��400�ֽ�
 *	��ͼ��70���У�*7���飩		��490�ֽ�
 ******************************************************/
//#define L_black blackLeft
//#define R_black blackRight
//#define LCenter blackLine
//extern uint8_t blackLine[70];
//extern uint8_t blackLeft[70];
//extern uint8_t blackRight[70];
//���崫��ṹ��
My_Data_Type My_Send_Data;

float my_car_data[50];
extern float tioashi_1,tioashi_2,tioashi_3,tioashi_4,tioashi_5,tioashi_6,tioashi_7,tioashi_8;
extern byte poflag;
extern uint8_t dajiao_ceshi;
extern int16_t Gyro_Y,Gyro_X,Gyro_Z;//Y���жϵ���
extern uint8_t Diaobo_flag;
extern float bianmai,bianmad;
void My_Data_Give(void)
{
	
	my_car_data[0] = aim;
	my_car_data[1] = speed;
	my_car_data[2] = jiance;
  my_car_data[3] = motorpwm;
	my_car_data[4] = pwm;
 	my_car_data[5] = CESHI_bianmai;
	my_car_data[6] =poflag;
	my_car_data[7] = dajiao_ceshi;
	my_car_data[8] = cutline;
	my_car_data[9] =  0;
	my_car_data[10] = Gyro_Y;
	my_car_data[11] = Diaobo_flag;
	my_car_data[12] = 0;
	my_car_data[13] = 0;
//	my_car_data[14] = Dashed_Field;
//	my_car_data[15] = check_DashedField_switch;
//	my_car_data[16] = seecar_flag;
//	my_car_data[17] = error;
//	my_car_data[18] = derror;
//	my_car_data[19] = angleChange;
//	my_car_data[20] = seecar_cnt;
//	my_car_data[21] = anothercar_dashedfield;
//	my_car_data[22] = seecar_process;
//	my_car_data[23] = WirelessReceiveStorage[5];
//	my_car_data[24] = startline;
//	my_car_data[25] = startline_fieldcnt;
//	my_car_data[26] = startline_switch;
//	my_car_data[27] = check_startline_cnt;
//	my_car_data[28] = startline_fieldcnt;
//	my_car_data[29] = scanf_flag;
}

//��float����ĺ���
void My_floattoint32(uint8_t *p_int, uint8_t *p_float)
{
	*p_int = *p_float;
	p_int++;	p_float++;
	*p_int = *p_float;
	p_int++;	p_float++;
	*p_int = *p_float;
	p_int++;	p_float++;
	*p_int = *p_float;
}

void Get_SendData()//��䴫��ṹ��
{
	//����ͷ����
	My_Send_Data.Verific[0] = 0x01;
	My_Send_Data.Verific[1] = 0x02;
	My_Send_Data.Verific[2] = 0x03;
	My_Send_Data.Verific[3] = 0x04;
	My_Send_Data.Verific[4] = 0x05;
	My_Send_Data.Pixels_width = 200;
	My_Send_Data.Pixels_height = 70;
	My_Send_Data.Coefficient_Num = 50;
	My_Send_Data.Parameter_Num = 1;
	//ͼ���ȡ
	
	#if defined gray//�Ҷ�ģʽ ��ѹ��
	uint8_t *p_pixels = My_Send_Data.P_Pixels;
	uint8_t *p_pixels_gray = &P_Pixels[0][0];
	for(uint32_t i = 0;i<Pixels_Len;i++)
	{
		*p_pixels = *p_pixels_gray;
		p_pixels++;	p_pixels_gray++;
	}
	#elif defined bin//��ֵģʽ ��8ѹ����1λ
	uint8_t *p_pixels = My_Send_Data.P_Pixels;//�������
	uint8_t *p_pixels_gray = &P_Pixels[0][0];//��ѹ������
	union//����һ��������
	{	
			uint8_t  Byte;
			struct Byte8_Struct Byte_Bit;
	} BIT;
	for(uint32_t i = 0;i<1750/*Pixels_Len*/;i++)
	{
		//��8λѹ����1λ
		BIT.Byte_Bit.bit8=*p_pixels_gray++;
		BIT.Byte_Bit.bit7=*p_pixels_gray++;
		BIT.Byte_Bit.bit6=*p_pixels_gray++;
		BIT.Byte_Bit.bit5=*p_pixels_gray++;
		BIT.Byte_Bit.bit4=*p_pixels_gray++;
		BIT.Byte_Bit.bit3=*p_pixels_gray++;
		BIT.Byte_Bit.bit2=*p_pixels_gray++;
		BIT.Byte_Bit.bit1=*p_pixels_gray++; 
		//����һλ���䵽����
		*p_pixels++ = BIT.Byte;
	}
	#endif
	//���в���
//	My_Data_Give();
	int32_t *p_data = (int32_t*)My_Send_Data.Data_Con;
	for(uint16_t i = 0;i<50;i++)
	{
		//*(int32_t *)p_data = my_car_data[i];
		My_floattoint32((uint8_t *)p_data, (uint8_t *)&my_car_data[i]);
		*(int32_t *)(p_data + 1) = ~*(int32_t *)p_data;
		p_data += 2;
	}
	//��ͼ
	My_LCR *my_Lcr = (My_LCR *)My_Send_Data.Lcr; //����ͼ���趨��
	for (uint8_t i = 0; i < 70; i++)
	{
			my_Lcr[i].left = L_black[i];
			my_Lcr[i].right = R_black[i];
			my_Lcr[i].center = LCenter[i];
	}
}

#include "dma_old.h"
#define  DMA_UART_CHx                DMA_CH5 //ѡȡDMAͨ��     
#define  UARTx_TRAN_DMAREQ           UART0_TRAN_DMAREQ //ѡȡDMA�ж�Դ     

#define DMA_UART_TX_DB       ((uint8_t*)&(UART0->D))
#define DMA_UART_TX_SB       (uint8_t*)&My_Send_Data //����DMAԭ��ַ
void My_Data_Uart_Init(void)
{
	DMA_InitTypeDef DMA_InitStruct1;
	//��ʼ������
	uart_init(uart0,640000);
	UART0->C2 |= UART_C2_TIE_MASK;
	//uart_txc_irq_en(uart0);//������������ж�
	UART0->C5 |= UART_C5_TDMAS_MASK;
	//UART_DMACmd(UART5,UART_DMAReq_Tx,ENABLE);
	
	
	DMA_InitStruct1.Channelx = DMA_UART_CHx;                    //ʹ��DMA0ͨ��  (0-15)
	DMA_InitStruct1.DMAAutoClose = ENABLE;                      //������Ϻ��Զ��ر�
	DMA_InitStruct1.EnableState = ENABLE;                       //��ʼ����������ʼ����
	DMA_InitStruct1.MinorLoopLength = Send_Data_Len;   					//�������
	DMA_InitStruct1.PeripheralDMAReq  = UARTx_TRAN_DMAREQ;      //UART ������ɴ���
	DMA_InitStruct1.TransferBytes = 1;                          //ÿ�δ���һ���ֽ�
	//����Ŀ�ĵ�ַ�������
	DMA_InitStruct1.DestBaseAddr = (uint32_t)DMA_UART_TX_DB;    //ָ��Ŀ�ĵ�ַ
	DMA_InitStruct1.DestDataSize = DMA_DST_8BIT;                //����Ϊ1Byte
	DMA_InitStruct1.DestMajorInc = 0;                           //ִ��һ�δ�ѭ���� ��ַ������
	DMA_InitStruct1.DestMinorInc = 0;                           //ÿ�δ������ַ������
 
	//����Դ��ַ�������
	DMA_InitStruct1.SourceBaseAddr =  (uint32_t)DMA_UART_TX_SB;
	DMA_InitStruct1.SourceDataSize = DMA_SRC_8BIT;
	DMA_InitStruct1.SourceMajorInc = 0;
	DMA_InitStruct1.SourceMinorInc = 1;
	DMA_Init(&DMA_InitStruct1); 
    //DMA_ITConfig(DMA0,DMA_IT_MAJOR,DMA_CH5,ENABLE);������DMA5�жϷ�����
    //NVIC_EnableIRQ(DMA5_IRQn);
}

void Send_to_Computer()//ͨ��uart���ʹ���ṹ��
{
	//uart_putbuff(uart0,(uint8_t*)&My_Send_Data,Send_Data_Len);
	//�ڳ��Գɹ�֮�� ����uart������ɴ���dma
	while(DMA_IsComplete(DMA_UART_CHx) == FALSE);//�ж�DMA UART�Ƿ������
	DMA0->TCD[DMA_UART_CHx].SADDR = (uint32_t)DMA_UART_TX_SB;//����DMA UART����Դ��ַ
	DMA0->ERQ |= (1<<DMA_UART_CHx);//��ʼ����
}

void My_LiveTransfer()//ʵʱ����
{
	My_Data_Give();//���в������
	Get_SendData();//��䴫��ṹ��
	Send_to_Computer();//ͨ��uart���ʹ���ṹ��
}

void My_Tranfer_Init()//�����ʼ��
{
	uart_init(uart0,640000);//��ʼ��uart
	//���ڿ��Լ���dma����
	My_Data_Uart_Init();
}

/********************************sd�����沿��****************************************/
void My_SdCard_Init(uint8_t sdmode)//��ʼ��sd��������ȡ
{
	sdhc_initcard_40();//����ʼ��
	if(sdmode == sd_save)//����ģʽ
		SD_ManyWT_Init();//���д����
}

uint8_t my_lines[512];
void My_Lines_Pack()//����7���� 7*70=490 һ������
{
	for(uint8_t i = 0; i < 70; i++)
	{
		my_lines[i] = L_black[i];
		my_lines[i + 70] = LCenter[i];
		my_lines[i + 140] = R_black[i];
	}
}

void My_Lines_UnPack()//��ѹ����
{
	for(uint8_t i = 0; i < 70; i++)
	{
		L_black[i] = my_lines[i]; 
		LCenter[i] = my_lines[i + 70];
		R_black[i] = my_lines[i + 140];
	}
}

uint8_t Pixels_zip[1750];
void My_SdCard_Save()//sd������Ҷ�ͼ������
{
	My_Data_Give();//������д������
	My_Lines_Pack();//�����ߺ�һ�����Խ�ʡ����
	
	//ͼ��ѹ��
	uint8_t *p_pixels = Pixels_zip;//�������
	uint8_t *p_pixels_gray = &P_Pixels[0][0];//��ѹ������
	union//����һ��������
	{	
			uint8_t  Byte;
			struct Byte8_Struct Byte_Bit;
	} BIT;
	for(uint32_t i = 0;i<1750/*Pixels_Len*/;i++)
	{
		//��8λѹ����1λ
		BIT.Byte_Bit.bit8=*p_pixels_gray++;
		BIT.Byte_Bit.bit7=*p_pixels_gray++;
		BIT.Byte_Bit.bit6=*p_pixels_gray++;
		BIT.Byte_Bit.bit5=*p_pixels_gray++;
		BIT.Byte_Bit.bit4=*p_pixels_gray++;
		BIT.Byte_Bit.bit3=*p_pixels_gray++;
		BIT.Byte_Bit.bit2=*p_pixels_gray++;
		BIT.Byte_Bit.bit1=*p_pixels_gray++; 
		//����һλ���䵽����
		*p_pixels++ = BIT.Byte;
	}
	
	SD_Many_Write(Pixels_zip,1750, 4);
	
	SD_Many_Write((uint8_t *)my_car_data, Data_Len, 1);
	SD_Many_Write(my_lines,512,1);
}


uint32_t my_blockNum = 0;
void My_SdCard_Read()//��ȡsd��������
{
	sdhc_readblocks(Pixels_zip,my_blockNum,4);
	my_blockNum += 4;
	
	sdhc_readblocks((uint8_t *)my_car_data,my_blockNum,1);
	my_blockNum += 1;
	sdhc_readblocks(my_lines,my_blockNum,1);
	my_blockNum += 1;
	
	//ͼ���ѹ
	uint8_t *p_pixels = Pixels_zip;//�������
	uint8_t *p_pixels_gray = &P_Pixels[0][0];//��ѹ������
	union//����һ��������
	{	
			uint8_t  Byte;
			struct Byte8_Struct Byte_Bit;
	} BIT;
	for(uint32_t i = 0;i<1750/*Pixels_Len*/;i++)
	{
		//��ȡ��ѹͼ��
		BIT.Byte = *p_pixels++;
		//��8λѹ����1λ
		*p_pixels_gray++=BIT.Byte_Bit.bit8;
		*p_pixels_gray++=BIT.Byte_Bit.bit7;
		*p_pixels_gray++=BIT.Byte_Bit.bit6;
		*p_pixels_gray++=BIT.Byte_Bit.bit5;
		*p_pixels_gray++=BIT.Byte_Bit.bit4;
		*p_pixels_gray++=BIT.Byte_Bit.bit3;
		*p_pixels_gray++=BIT.Byte_Bit.bit2;
		*p_pixels_gray++=BIT.Byte_Bit.bit1;
	}
	
	My_Lines_UnPack();//��ѹ����
	//����
	Get_SendData();//��䴫��ṹ��
	Send_to_Computer();//ͨ��uart���ʹ���ṹ��
}
