#include "Ultrasonic.h"

uint16_t Uls_Distance=0;
uint8_t Uls_dat[3];
uint8_t Uls_Num;
uint8_t Uls_receive_flag = 0;
//汇车计时
uint32_t seecar_timer = 0;//初值为0直接开始汇车检测
uint32_t seecar_timer_set = 10;//存储秒数时间

void Ultrasonic_Init()//超声波模块初始化
{
	#ifdef yellow_car//摄像头车 用于接收
	
	//初始化uart0并使能中断
	uart_init(UART_Ultrasonic_Rec,115200);//串口初始化
	NVIC_DisableIRQ(UART0_RX_TX_IRQn);
	set_irq_priority(UART0_RX_TX_IRQn,0);//uart0中断
	uart_rx_irq_en(UART_Ultrasonic_Rec);//使能中断	
	
	#elif red_car//电磁车 用于发送
	gpio_init(PORT_Ultrasonic_Send,GPO,1);
	
	#endif
}

void Ultrasonic_Receive()//超声波中断接受模块
{
	//超声波接受数据
	uart_getchar(UART_Ultrasonic_Rec,&Uls_dat[Uls_Num]);
	//检查头帧是否正确，不正确就重新接收
	if(Uls_dat[0] != 0xa5)
	{Uls_Num = 0;}	
	else 
	{Uls_Num++;}
	//接受完成，开始处理数据
	if(Uls_Num==3)					
	{
		Uls_Num = 0;
		Uls_Distance = Uls_dat[1]<<8 | Uls_dat[2];
		Uls_receive_flag = 1;
		//OLED_Write_Num5(0,4,Uls_Distance);
	}
}


uint8_t in_cnt = 0,out_cnt = 0,out_cnt_flag = 0;
uint16_t Uls_Distance_last = 0;
uint8_t startline_cnt = 0,startline_cnt_flag = 0;
uint8_t startline_give = 0;
uint8_t seecar_cnt = 0;

void Ultrasonic_seecar()//超声波汇车检测
{
	if(Uls_receive_flag == 1)
	{
		OLED_Write_Num4(8,6,Uls_Distance);
		if(Uls_Distance <= 2000 && Uls_Distance - Uls_Distance_last <= 100)//100cm汇车准备
		{
			
			in_cnt++;
			out_cnt_flag = 0;//如果还在清空汇车标志的时候再次检测到汇车距离 清空
			if(in_cnt >= 5)
			{
				seecar_flag = 1;
			}
		}
		else
		{
			in_cnt = 0;//清空标志位
		}
		if(Uls_Distance >= 2000 && seecar_flag == 1 && out_cnt_flag == 0)//汇车结束 距离变大 处于汇车状态 不是正在清空
		{
			//延时计数清空汇车标志位
			out_cnt_flag = 1;
			out_cnt = 2;//延时2场
		}
		if(out_cnt_flag == 1)
		{
			out_cnt--;
			if(out_cnt == 0)
			{
				out_cnt_flag = 0;
				seecar_flag = 0;
				seecar_cnt++;//汇车计数
				//如果另一辆车起跑线 停车
				//延后25场才给另一辆车
				if(startline == 1 && startline_cnt_flag == 0)
				{
					startline_cnt = 25;
					startline_cnt_flag = 1;
				}
				//如果这是第一次汇车 进行计时汇车判断
				if(seecar_cnt == 1)
				{
					seecar_timer = seecar_timer_set * 200;
				}
				
//				startline = anothercar_startline;
			}
		}
		
		if(startline_cnt_flag == 1)
		{
			startline_cnt--;
			if(startline_cnt == 0)
			{
				startline_cnt_flag = 0;
				startline_give = 1;
			}
		}
		
		Uls_Distance_last = Uls_Distance;
		Uls_receive_flag = 0;//清空标志位
	}
	
}
