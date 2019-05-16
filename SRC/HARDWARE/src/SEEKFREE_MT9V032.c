/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2016,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：179029047
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		SEEKFREE_MT9V032.c
 * @brief      		总钻风(灰度摄像头)函数库
 * @company	   		成都逐飞科技有限公司
 * @author     		Go For It(1325536866)
 * @version    		v1.0
 * @Software 		IAR 7.2 or MDK 5.17
 * @Target core		MK60DN512VLL10
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2016-02-25
 * @note	
					MT9V032接线定义：
					------------------------------------ 
						模块管脚            单片机管脚
						SDA(51的RX)         C17
						SCL(51的TX)         C16
						场中断              C6		E12
						像素中断            C18  B9         
						数据口              C8-C15 	D0-07
					------------------------------------ 
	
					默认分辨率是            188*120
					默认FPS                 50帧
 ********************************************************************************************************************/



#include "SEEKFREE_MT9V032.h"


#define MT9V032_COF_UART    uart3


uint8   image[ROW][COL];      //图像数组
extern uint8_t P_Pixels[70][200];
uint8   receive[3];
uint8   receive_num = 0;
uint8   uart_receive_flag = 1;
//分行阈值
uint8_t Threshold_H[70] = 
{
	95,95,95,95,95,95,95,95,95,95,
	95,95,95,95,95,95,95,95,95,95,
	95,95,95,95,95,95,95,95,95,95,
	95,95,95,95,95,95,95,95,95,95,
	95,95,95,95,95,95,95,95,95,95,
	95,95,95,95,95,95,95,95,95,95,
	95,95,95,95,95,95,95,95,95,95,
//	96,97,98,99,100,101,102,103,104,105,
//	106,107,108,109,110,111,112,113,114,115,
//	116,117,118,119,120,121,122,123,124,125,
//	136,137,138,139,130,131,132,133,134,135,
//	90,90,89,89,88,88,87,87,86,86,
//	85,85,84,84,83,83,82,82,81,81,
//	80,80,79,79,78,78,77,77,76,76,
	
	
//	80,80,79,79,78,78,77,77,76,76,
//	75,75,74,74,73,73,72,72,71,71,
//	70,70,69,69,68,68,67,67,66,66,
//	65,65,64,64,63,63,62,62,61,61,
//	60,60,59,59,58,58,57,57,56,56,
//	55,55,54,54,53,53,52,52,51,51,
//	50,50,49,49,48,48,47,47,46,46,
};
uint8_t Threshold = 130;

//需要配置到摄像头的数据
int16 MT9V032_CFG[CONFIG_FINISH][2]=
{
    {AUTO_EXP,          0},   //自动曝光设置      范围1-63 0为关闭 如果自动曝光开启  EXP_TIME命令设置的数据将会变为最大曝光时间，也就是自动曝光时间的上限
                              //一般情况是不需要开启这个功能，因为比赛场地光线一般都比较均匀，如果遇到光线非常不均匀的情况可以尝试设置该值，增加图像稳定性
    {EXP_TIME,          300}, //曝光时间          摄像头收到后会自动计算出最大曝光时间，如果设置过大则设置为计算出来的最大曝光值
    {FPS,               35},//50},  //图像帧率          摄像头收到后会自动计算出最大FPS，如果过大则设置为计算出来的最大FPS
    {SET_COL,           COL}, //图像列数量        范围1-752     K60采集不允许超过188
    {SET_ROW,           ROW}, //图像行数量        范围1-480
    {LR_OFFSET,         0},   //图像左右偏移量    正值 右偏移   负值 左偏移  列为188 376 752时无法设置偏移    摄像头收偏移数据后会自动计算最大偏移，如果超出则设置计算出来的最大偏移
    {UD_OFFSET,         0},   //图像上下偏移量    正值 上偏移   负值 下偏移  行为120 240 480时无法设置偏移    摄像头收偏移数据后会自动计算最大偏移，如果超出则设置计算出来的最大偏移
    {GAIN,              32},  //图像增益          范围16-64     增益可以在曝光时间固定的情况下改变图像亮暗程度

    
    {INIT,              0}    //摄像头开始初始化
};

//从摄像头内部获取到的配置数据
int16 GET_CFG[CONFIG_FINISH-1][2]=
{
    {AUTO_EXP,          0},   //自动曝光设置      
    {EXP_TIME,          0},   //曝光时间          
    {FPS,               0},   //图像帧率          
    {SET_COL,           0},   //图像列数量        
    {SET_ROW,           0},   //图像行数量        
    {LR_OFFSET,         0},   //图像左右偏移量    
    {UD_OFFSET,         0},   //图像上下偏移量    
    {GAIN,              0},   //图像增益          
};


//-------------------------------------------------------------------------------------------------------------------
//  @brief      MT9V032摄像头串口中断函数
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:	
//  @note       该函数在ISR文件 串口3中断程序被调用
//-------------------------------------------------------------------------------------------------------------------
void mt9v032_cof_uart_interrupt(void)
{
    uart_getchar(MT9V032_COF_UART,&receive[receive_num]);;
    receive_num++;
    
    if(1==receive_num && 0XA5!=receive[0])  receive_num = 0;
    if(3 == receive_num)
    {
        receive_num = 0;
        uart_receive_flag = 1;
    }
        
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      获取摄像头内部配置信息
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:				调用该函数前请先初始化uart2
//-------------------------------------------------------------------------------------------------------------------
void get_config(void)
{
	uint16 temp, i;
    uint8  send_buffer[4];
    
    for(i=0; i<CONFIG_FINISH-1; i++)
    {
        send_buffer[0] = 0xA5;
        send_buffer[1] = GET_STATUS;
        temp = GET_CFG[i][0];
        send_buffer[2] = temp>>8;
        send_buffer[3] = (uint8)temp;
        
        uart_putbuff(MT9V032_COF_UART,send_buffer,4);
        
        //等待接受回传数据
        while(!uart_receive_flag);
        uart_receive_flag = 0;
        
        GET_CFG[i][1] = receive[1]<<8 | receive[2];
        
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      获取摄像头固件版本
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:				调用该函数前请先初始化uart2
//-------------------------------------------------------------------------------------------------------------------
uint16 get_version(void)
{
    uint16 temp;
    uint8  send_buffer[4];
    send_buffer[0] = 0xA5;
    send_buffer[1] = GET_STATUS;
    temp = GET_VERSION;
    send_buffer[2] = temp>>8;
    send_buffer[3] = (uint8)temp;
    
    uart_putbuff(MT9V032_COF_UART,send_buffer,4);
        
    //等待接受回传数据
    while(!uart_receive_flag);
    uart_receive_flag = 0;
    
    return ((uint16)(receive[1]<<8) | receive[2]);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      单独设置摄像头曝光时间
//  @param      light   设置曝光时间越大图像越亮，摄像头收到后会根据分辨率及FPS计算最大曝光时间如果设置的数据过大，那么摄像头将会设置这个最大值
//  @return     uint16  当前曝光值，用于确认是否正确写入
//  @since      v1.0
//  Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
uint16 set_exposure_time(uint16 light)
{
	uint16 temp;
    uint8  send_buffer[4];

    send_buffer[0] = 0xA5;
    send_buffer[1] = SET_EXP_TIME;
    temp = light;
    send_buffer[2] = temp>>8;
    send_buffer[3] = (uint8)temp;
    
    uart_putbuff(MT9V032_COF_UART,send_buffer,4);
    
    //等待接受回传数据
    while(!uart_receive_flag);
    uart_receive_flag = 0;
    
    temp = receive[1]<<8 | receive[2];
    return temp;

}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      对摄像头内部寄存器进行写操作
//  @param      addr    摄像头内部寄存器地址
//  @param      data    需要写入的数据
//  @return     uint16  寄存器当前数据，用于确认是否写入成功
//  @since      v1.0
//  Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
uint16 set_mt9v032_reg(uint8 addr, uint16 data)
{
	uint16 temp;
    uint8  send_buffer[4];
    
    send_buffer[0] = 0xA5;
    send_buffer[1] = SET_ADDR;
    temp = addr;
    send_buffer[2] = temp>>8;
    send_buffer[3] = (uint8)temp;
    
    uart_putbuff(MT9V032_COF_UART,send_buffer,4);
    systick_delay_ms(10);
    
    send_buffer[0] = 0xA5;
    send_buffer[1] = SET_DATA;
    temp = data;
    send_buffer[2] = temp>>8;
    send_buffer[3] = (uint8)temp;
    
    uart_putbuff(MT9V032_COF_UART,send_buffer,4);
    
    //等待接受回传数据
    while(!uart_receive_flag);
    uart_receive_flag = 0;
    
    temp = receive[1]<<8 | receive[2];
    return temp;

}

uint16 version;
//-------------------------------------------------------------------------------------------------------------------
//  @brief      MT9V032摄像头初始化
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:		
//-------------------------------------------------------------------------------------------------------------------
void camera_init(void)
{
    //设置参数    具体请参看使用手册
    uint16 temp, i;
    uint8  send_buffer[4];

    
    uart_init (MT9V032_COF_UART, 9600);	//初始换串口 配置摄像头    
    uart_rx_irq_en(MT9V032_COF_UART);
    
    
    //等待摄像头上电初始化成功
    systick_delay_ms(1000);
    uart_receive_flag = 0;
    //开始配置摄像头并重新初始化
    for(i=0; i<CONFIG_FINISH; i++)
    {
        send_buffer[0] = 0xA5;
        send_buffer[1] = MT9V032_CFG[i][0];
        temp = MT9V032_CFG[i][1];
        send_buffer[2] = temp>>8;
        send_buffer[3] = (uint8)temp;
        
        uart_putbuff(MT9V032_COF_UART,send_buffer,4);
        systick_delay_ms(2);
    }
    //等待摄像头初始化成功
    uart_receive_flag = 0;
    while((0xff != receive[1]) || (0xff != receive[2]));
    //以上部分对摄像头配置的数据全部都会保存在摄像头上51单片机的eeprom中
    //利用set_exposure_time函数单独配置的曝光数据不存储在eeprom中
    
    
    //获取配置便于查看配置是否正确
    get_config();

    
    //摄像头采集初始化
    DisableInterrupts;
    //DMA通道0初始化，PTC18触发源(默认上升沿)，源地址为C_IN_DATA(1)(PTC8-PTC15)，目的地址为：image，每次传输1Byte 传输完毕保持目的地址
//    dma_portx2buff_init(DMA_CH0, (void *)&C_IN_DATA(1), (void *)image, C18, DMA_BYTE1, COL*ROW, DADDR_KEEPON);
//		dma_portx2buff_init(DMA_CH0, (void *)&D_IN_DATA(0), (void *)image, B9, DMA_BYTE1, COL*ROW, DADDR_KEEPON);
		dma_portx2buff_init(DMA_CH0, (void *)&D_IN_DATA(0), (void *)image, B9, DMA_BYTE1, COL*80, DADDR_KEEPON);
//    port_init(C18, ALT1 | DMA_RISING | PULLDOWN);  			    //PCLK  触发源设置
		//port_init(B9, ALT1 | DMA_RISING | PULLDOWN);  			    //PCLK  触发源设置
		port_init(B9, ALT1 | DMA_FALLING | PULLDOWN);  			    //PCLK  触发源设置
	DMA_DIS(DMA_CH0);                                     		//禁用DMA通道
    DMA_IRQ_CLEAN(DMA_CH0);                               		//清除通道传输中断标志位
    DMA_IRQ_EN(DMA_CH0);                                  		//允许DMA通道中断
	DMA_EN(DMA_CH0);  											//使能DMA

	
	disable_irq(PORTE_IRQn);                             		//关闭PTE的中断
    //port_init(C7, ALT1 | IRQ_FALLING | PULLDOWN);      			//行中断
    port_init(E12, ALT1 | IRQ_FALLING | PULLDOWN);        		//场中断，下降沿触发中断、下拉
    set_irq_priority(PORTE_IRQn,1);                             // 中断优先级
    enable_irq (PORTE_IRQn);
	EnableInterrupts;
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      MT9V032摄像头场中断
//  @param      NULL
//  @return     void			
//  @since      v1.0
//  Sample usage:				在isr.c里面先创建对应的中断函数，然后调用该函数(之后别忘记清除中断标志位)
//-------------------------------------------------------------------------------------------------------------------
void VSYNC(void)
{
	dma_repeat(DMA_CH0,(void *)&D_IN_DATA(0),(void *)image[0],COL*ROW);
}



uint8   mt9v032_finish_flag = 0;      //一场图像采集完成标志位
//-------------------------------------------------------------------------------------------------------------------
//  @brief      MT9V032摄像头DMA完成中断
//  @param      NULL
//  @return     void			
//  @since      v1.0
//  Sample usage:				在isr.c里面先创建对应的中断函数，然后调用该函数(之后别忘记清除中断标志位)
//-------------------------------------------------------------------------------------------------------------------
void row_finished(void)
{
	Pixels_get();//获取二值化数组
	mt9v032_finish_flag = 1;
	
	//本例程对黑边不做处理，大家在使用数据的时候不使用image数组最左边与最右边即可
	//如果分辨率过大，就没办法转存了，因为K60的RAM会不够
    //一副图像从采集开始到采集结束耗时3.33MS左右(50FPS、188*120分辨率)
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      总钻风摄像头图像发送至上位机查看图像
//  @param      NULL
//  @return     void			
//  @since      v1.0
//  Sample usage:				调用该函数前请先初始化uart2
//-------------------------------------------------------------------------------------------------------------------
void seekfree_sendimg_032(void)
{
	uart_putchar(uart2,0x00);uart_putchar(uart2,0xff);uart_putchar(uart2,0x01);uart_putchar(uart2,0x01);//发送命令
    uart_putbuff(uart2, (uint8_t *)image, ROW*COL);  //发送图像
}


//显示一场CCD画面128*64
uint8_t OlLine=0;
uint8_t OlRow=0;
uint8_t OLED_Pixels[64][128];
uint16_t OledDian[128]=
{
//	0,1,2,4,6,8,10,12,14,16,18,19,20,22,24,26,28,29,30,
//	32,33,34,36,38,40,42,43,44,46,48,50,51,52,54,55,56,58,60,61,62,
//	64,65,66,68,70,71,72,74,76,78,79,80,82,84,86,87,88,90,92,93,94,
//	96,98,100,101,102,103,104,106,108,109,110,112,114,115,116,118,120,122,124,125,126,
//	128,129,130,132,133,134,136,137,138,140,142,144,146,148,150,152,154,156,157,158,
//	160,161,162,163,164,166,168,170,171,172,174,176,177,178,180,181,182,184,186,188,190,
//	192,194,196,198,199,
	0,1,2,4,5,7,8,10,11,13,
	14,16,17,19,20,22,23,24,26,27,
	29,30,32,33,35,36,38,39,41,42,
	44,45,47,48,49,51,52,54,55,57,
	58,60,61,63,64,66,67,69,70,71,
	73,74,76,77,79,80,82,83,85,86,
	88,89,91,92,94,95,96,98,99,101,
	102,104,105,107,108,110,111,113,114,116,
	117,118,120,121,123,124,126,127,129,130,
	132,133,135,136,138,139,141,142,143,145,
	146,148,149,151,152,154,155,157,158,160,
	161,163,164,165,167,168,170,171,173,174,
	176,177,179,180,182,183,185,186,
};
uint8_t OledChooseRow[64]=
{
//	0,1,2,3,4,6,7,8,9,
//	10,11,12,13,15,16,17,18,
//	19,20,21,22,24,25,26,27,
//	28,29,30,31,33,34,35,36,
//  37,38,39,40,42,43,44,45,
//  46,47,48,49,51,52,53,54,	
//	55,56,57,58,59,60,61,62,
//	63,64,65,66,67,68,69,
	0,1,3,5,7,9,11,13,15,16,
	18,20,22,24,26,28,30,31,33,35,
	37,39,41,43,45,46,48,50,52,54,
	56,58,60,61,63,65,67,69,71,73,
	75,76,78,80,82,84,86,88,90,91,
	93,95,97,99,101,103,105,106,108,110,
	112,114,116,118,
};

void ImageGet_image(void)  //OLED图像获取程序
{
	for(OlRow=0;OlRow<64;OlRow++)
	{
		for(OlLine=0;OlLine<127;OlLine++)
		{
			//二值化显示
			if(image[OledChooseRow[OlRow]][OledDian[OlLine]] > 70)
			{
				OLED_Pixels[OlRow][OlLine]=1;
			}
			else
			{
				OLED_Pixels[OlRow][OlLine]=0;
			}
				//OLED_Pixels[OlRow][OlLine]=image[OledChooseRow[OlRow]][OledDian[OlLine]];
		}
//		OLED_Pixels[OlRow][0]=1;  //右边框
//		OLED_Pixels[OlRow][126]=1;  //左边框
	}
//			for(OlLine=0;OlLine<127;OlLine++)
//		{
//				OLED_Pixels[0][OlLine]=1;//下边框
//			  OLED_Pixels[63][OlLine]=1;//上边框
//		}
}

uint16_t OledDian_Pixels[128]=
{
	0,1,2,4,6,8,10,12,14,16,18,19,20,22,24,26,28,29,30,
	32,33,34,36,38,40,42,43,44,46,48,50,51,52,54,55,56,58,60,61,62,
	64,65,66,68,70,71,72,74,76,78,79,80,82,84,86,87,88,90,92,93,94,
	96,98,100,101,102,103,104,106,108,109,110,112,114,115,116,118,120,122,124,125,126,
	128,129,130,132,133,134,136,137,138,140,142,144,146,148,150,152,154,156,157,158,
	160,161,162,163,164,166,168,170,171,172,174,176,177,178,180,181,182,184,186,188,190,
	192,194,196,198,199,
};
uint8_t OledChooseRow_Pixels[64]=
{
	0,1,2,3,4,6,7,8,9,
	10,11,12,13,15,16,17,18,
	19,20,21,22,24,25,26,27,
	28,29,30,31,33,34,35,36,
  37,38,39,40,42,43,44,45,
  46,47,48,49,51,52,53,54,	
	55,56,57,58,59,60,61,62,
	63,64,65,66,67,68,69,
};

void ImageGet_Pixels(void)  //OLED图像获取程序
{
	for(OlRow=0;OlRow<64;OlRow++)
	{
		for(OlLine=0;OlLine<127;OlLine++)
		{
//			//二值化显示
//			if(image[OledChooseRow_Pixels[OlRow]][OledDian_Pixels[OlLine]] > 80)
//			{
//				OLED_Pixels[OlRow][OlLine]=1;
//			}
//			else
//			{
//				OLED_Pixels[OlRow][OlLine]=0;
//			}
				OLED_Pixels[OlRow][OlLine]=P_Pixels[OledChooseRow_Pixels[OlRow]][OledDian_Pixels[OlLine]];
		}
//		OLED_Pixels[OlRow][0]=1;  //右边框
//		OLED_Pixels[OlRow][126]=1;  //左边框
	}
//			for(OlLine=0;OlLine<127;OlLine++)
//		{
//				OLED_Pixels[0][OlLine]=1;//下边框
//			  OLED_Pixels[63][OlLine]=1;//上边框
//		}
}

void DisplayImage_WithOLED(void)
{
	uint8_t i,j,data,k;
	ImageGet_Pixels();//OLED图像获取 200*70 转 127*64
	for(j=0; j<8; j++)
	{
		OLED_Set_XY(0,j);
		for(i=0; i<127; i++)
		{
			data=0;
			for(k=0; k<8; k++)
			{
				data+=(OLED_Pixels[63-(j*8+k)][126-i]<<k);				//将竖直的八个像素合成一个字节x
			}
			OLED_WrDat(data);
		}
	}
}



void Pixels_get()//获取200*70图像 存储在image中
{
	//从80行开始倒序储存 0-186
	uint8_t *p_image = &image[0][1];//直接过滤掉边缘两列 因为不稳定 图像范围0-185
	uint8_t *p_Pixels = &P_Pixels[0][0];
	uint8_t H,W;
	for(H = 0;H<70;H++)
	{
		//p_Pixels = &P_Pixels[H][6];
		for(W = 0;W<186;W++)
		{
			if(*p_image > Threshold_H[H])
			{
				*p_Pixels = 1;
			}
			else
			{
				*p_Pixels = 0;
			}
			//*p_image = *p_Pixels;
			p_image++;
			p_Pixels++;
		}
		p_Pixels+=14;
		p_image+=2;
	}
}

void Threshold_adjust()
{
	int8_t Threshold_change = Threshold-Threshold_H[0];
	for(RowNum = 0;RowNum < 70;RowNum++)
	{
		Threshold_H[RowNum]+=Threshold_change;
	}
	OLED_Clear();
	OLED_Write_Num3(0,0,Threshold_H[10]);
	OLED_Write_Num3(8,0,Threshold);
	DelayMs(100);
}