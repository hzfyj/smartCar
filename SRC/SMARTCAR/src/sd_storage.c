
#include "sd_storage.h"	//sd卡
#include "headfile.h"
#include "Fuzzy_control.h"

/******************************************************
 *									图像传输协议
 *	传输头校验：0x01 0x02 0x03 0x04 0x05	（5字节）
 *	图像：200*70字节 直接传输	共14000字节
 *	运行参数：50个 每位4字节 共400字节
 *	拟图：70（行）*7（组）		共490字节
 ******************************************************/
//#define L_black blackLeft
//#define R_black blackRight
//#define LCenter blackLine
//extern uint8_t blackLine[70];
//extern uint8_t blackLeft[70];
//extern uint8_t blackRight[70];
//定义传输结构体
My_Data_Type My_Send_Data;

float my_car_data[50];
extern float tioashi_1,tioashi_2,tioashi_3,tioashi_4,tioashi_5,tioashi_6,tioashi_7,tioashi_8;
extern byte poflag;
extern uint8_t dajiao_ceshi;
extern int16_t Gyro_Y,Gyro_X,Gyro_Z;//Y轴判断颠簸
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

//将float传输的函数
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

void Get_SendData()//填充传输结构体
{
	//传输头检验
	My_Send_Data.Verific[0] = 0x01;
	My_Send_Data.Verific[1] = 0x02;
	My_Send_Data.Verific[2] = 0x03;
	My_Send_Data.Verific[3] = 0x04;
	My_Send_Data.Verific[4] = 0x05;
	My_Send_Data.Pixels_width = 200;
	My_Send_Data.Pixels_height = 70;
	My_Send_Data.Coefficient_Num = 50;
	My_Send_Data.Parameter_Num = 1;
	//图像获取
	
	#if defined gray//灰度模式 不压缩
	uint8_t *p_pixels = My_Send_Data.P_Pixels;
	uint8_t *p_pixels_gray = &P_Pixels[0][0];
	for(uint32_t i = 0;i<Pixels_Len;i++)
	{
		*p_pixels = *p_pixels_gray;
		p_pixels++;	p_pixels_gray++;
	}
	#elif defined bin//二值模式 将8压缩成1位
	uint8_t *p_pixels = My_Send_Data.P_Pixels;//传输变量
	uint8_t *p_pixels_gray = &P_Pixels[0][0];//待压缩变量
	union//定义一个公用体
	{	
			uint8_t  Byte;
			struct Byte8_Struct Byte_Bit;
	} BIT;
	for(uint32_t i = 0;i<1750/*Pixels_Len*/;i++)
	{
		//将8位压缩成1位
		BIT.Byte_Bit.bit8=*p_pixels_gray++;
		BIT.Byte_Bit.bit7=*p_pixels_gray++;
		BIT.Byte_Bit.bit6=*p_pixels_gray++;
		BIT.Byte_Bit.bit5=*p_pixels_gray++;
		BIT.Byte_Bit.bit4=*p_pixels_gray++;
		BIT.Byte_Bit.bit3=*p_pixels_gray++;
		BIT.Byte_Bit.bit2=*p_pixels_gray++;
		BIT.Byte_Bit.bit1=*p_pixels_gray++; 
		//将这一位传输到里面
		*p_pixels++ = BIT.Byte;
	}
	#endif
	//运行参数
//	My_Data_Give();
	int32_t *p_data = (int32_t*)My_Send_Data.Data_Con;
	for(uint16_t i = 0;i<50;i++)
	{
		//*(int32_t *)p_data = my_car_data[i];
		My_floattoint32((uint8_t *)p_data, (uint8_t *)&my_car_data[i]);
		*(int32_t *)(p_data + 1) = ~*(int32_t *)p_data;
		p_data += 2;
	}
	//拟图
	My_LCR *my_Lcr = (My_LCR *)My_Send_Data.Lcr; //传拟图所需定义
	for (uint8_t i = 0; i < 70; i++)
	{
			my_Lcr[i].left = L_black[i];
			my_Lcr[i].right = R_black[i];
			my_Lcr[i].center = LCenter[i];
	}
}

#include "dma_old.h"
#define  DMA_UART_CHx                DMA_CH5 //选取DMA通道     
#define  UARTx_TRAN_DMAREQ           UART0_TRAN_DMAREQ //选取DMA中断源     

#define DMA_UART_TX_DB       ((uint8_t*)&(UART0->D))
#define DMA_UART_TX_SB       (uint8_t*)&My_Send_Data //设置DMA原地址
void My_Data_Uart_Init(void)
{
	DMA_InitTypeDef DMA_InitStruct1;
	//初始化串口
	uart_init(uart0,640000);
	UART0->C2 |= UART_C2_TIE_MASK;
	//uart_txc_irq_en(uart0);//开启发送完成中断
	UART0->C5 |= UART_C5_TDMAS_MASK;
	//UART_DMACmd(UART5,UART_DMAReq_Tx,ENABLE);
	
	
	DMA_InitStruct1.Channelx = DMA_UART_CHx;                    //使用DMA0通道  (0-15)
	DMA_InitStruct1.DMAAutoClose = ENABLE;                      //传输完毕后自动关闭
	DMA_InitStruct1.EnableState = ENABLE;                       //初始化后不立即开始传输
	DMA_InitStruct1.MinorLoopLength = Send_Data_Len;   					//传输次数
	DMA_InitStruct1.PeripheralDMAReq  = UARTx_TRAN_DMAREQ;      //UART 传输完成触发
	DMA_InitStruct1.TransferBytes = 1;                          //每次传输一个字节
	//配置目的地址传输参数
	DMA_InitStruct1.DestBaseAddr = (uint32_t)DMA_UART_TX_DB;    //指向目的地址
	DMA_InitStruct1.DestDataSize = DMA_DST_8BIT;                //数组为1Byte
	DMA_InitStruct1.DestMajorInc = 0;                           //执行一次大循环后 地址不增加
	DMA_InitStruct1.DestMinorInc = 0;                           //每次传输完地址不增加
 
	//配置源地址传输参数
	DMA_InitStruct1.SourceBaseAddr =  (uint32_t)DMA_UART_TX_SB;
	DMA_InitStruct1.SourceDataSize = DMA_SRC_8BIT;
	DMA_InitStruct1.SourceMajorInc = 0;
	DMA_InitStruct1.SourceMinorInc = 1;
	DMA_Init(&DMA_InitStruct1); 
    //DMA_ITConfig(DMA0,DMA_IT_MAJOR,DMA_CH5,ENABLE);不启动DMA5中断服务函数
    //NVIC_EnableIRQ(DMA5_IRQn);
}

void Send_to_Computer()//通过uart发送传输结构体
{
	//uart_putbuff(uart0,(uint8_t*)&My_Send_Data,Send_Data_Len);
	//在尝试成功之后 加入uart传输完成触发dma
	while(DMA_IsComplete(DMA_UART_CHx) == FALSE);//判断DMA UART是否发送完毕
	DMA0->TCD[DMA_UART_CHx].SADDR = (uint32_t)DMA_UART_TX_SB;//设置DMA UART发送源地址
	DMA0->ERQ |= (1<<DMA_UART_CHx);//开始发送
}

void My_LiveTransfer()//实时传输
{
	My_Data_Give();//运行参数填充
	Get_SendData();//填充传输结构体
	Send_to_Computer();//通过uart发送传输结构体
}

void My_Tranfer_Init()//传输初始化
{
	uart_init(uart0,640000);//初始化uart
	//后期可以加入dma传输
	My_Data_Uart_Init();
}

/********************************sd卡储存部分****************************************/
void My_SdCard_Init(uint8_t sdmode)//初始化sd卡储存或读取
{
	sdhc_initcard_40();//仅初始化
	if(sdmode == sd_save)//储存模式
		SD_ManyWT_Init();//多块写命令
}

uint8_t my_lines[512];
void My_Lines_Pack()//给出7条线 7*70=490 一个扇区
{
	for(uint8_t i = 0; i < 70; i++)
	{
		my_lines[i] = L_black[i];
		my_lines[i + 70] = LCenter[i];
		my_lines[i + 140] = R_black[i];
	}
}

void My_Lines_UnPack()//解压三线
{
	for(uint8_t i = 0; i < 70; i++)
	{
		L_black[i] = my_lines[i]; 
		LCenter[i] = my_lines[i + 70];
		R_black[i] = my_lines[i + 140];
	}
}

uint8_t Pixels_zip[1750];
void My_SdCard_Save()//sd卡储存灰度图及参数
{
	My_Data_Give();//将参数写入数组
	My_Lines_Pack();//将三线合一储存以节省扇区
	
	//图像压缩
	uint8_t *p_pixels = Pixels_zip;//传输变量
	uint8_t *p_pixels_gray = &P_Pixels[0][0];//待压缩变量
	union//定义一个公用体
	{	
			uint8_t  Byte;
			struct Byte8_Struct Byte_Bit;
	} BIT;
	for(uint32_t i = 0;i<1750/*Pixels_Len*/;i++)
	{
		//将8位压缩成1位
		BIT.Byte_Bit.bit8=*p_pixels_gray++;
		BIT.Byte_Bit.bit7=*p_pixels_gray++;
		BIT.Byte_Bit.bit6=*p_pixels_gray++;
		BIT.Byte_Bit.bit5=*p_pixels_gray++;
		BIT.Byte_Bit.bit4=*p_pixels_gray++;
		BIT.Byte_Bit.bit3=*p_pixels_gray++;
		BIT.Byte_Bit.bit2=*p_pixels_gray++;
		BIT.Byte_Bit.bit1=*p_pixels_gray++; 
		//将这一位传输到里面
		*p_pixels++ = BIT.Byte;
	}
	
	SD_Many_Write(Pixels_zip,1750, 4);
	
	SD_Many_Write((uint8_t *)my_car_data, Data_Len, 1);
	SD_Many_Write(my_lines,512,1);
}


uint32_t my_blockNum = 0;
void My_SdCard_Read()//读取sd卡并传输
{
	sdhc_readblocks(Pixels_zip,my_blockNum,4);
	my_blockNum += 4;
	
	sdhc_readblocks((uint8_t *)my_car_data,my_blockNum,1);
	my_blockNum += 1;
	sdhc_readblocks(my_lines,my_blockNum,1);
	my_blockNum += 1;
	
	//图像解压
	uint8_t *p_pixels = Pixels_zip;//传输变量
	uint8_t *p_pixels_gray = &P_Pixels[0][0];//待压缩变量
	union//定义一个公用体
	{	
			uint8_t  Byte;
			struct Byte8_Struct Byte_Bit;
	} BIT;
	for(uint32_t i = 0;i<1750/*Pixels_Len*/;i++)
	{
		//读取解压图像
		BIT.Byte = *p_pixels++;
		//将8位压缩成1位
		*p_pixels_gray++=BIT.Byte_Bit.bit8;
		*p_pixels_gray++=BIT.Byte_Bit.bit7;
		*p_pixels_gray++=BIT.Byte_Bit.bit6;
		*p_pixels_gray++=BIT.Byte_Bit.bit5;
		*p_pixels_gray++=BIT.Byte_Bit.bit4;
		*p_pixels_gray++=BIT.Byte_Bit.bit3;
		*p_pixels_gray++=BIT.Byte_Bit.bit2;
		*p_pixels_gray++=BIT.Byte_Bit.bit1;
	}
	
	My_Lines_UnPack();//解压三线
	//传输
	Get_SendData();//填充传输结构体
	Send_to_Computer();//通过uart发送传输结构体
}
