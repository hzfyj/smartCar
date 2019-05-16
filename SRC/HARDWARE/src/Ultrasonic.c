#include "Ultrasonic.h"

uint16_t Uls_Distance=0;
uint8_t Uls_dat[3];
uint8_t Uls_Num;
uint8_t Uls_receive_flag = 0;
//�㳵��ʱ
uint32_t seecar_timer = 0;//��ֵΪ0ֱ�ӿ�ʼ�㳵���
uint32_t seecar_timer_set = 10;//�洢����ʱ��

void Ultrasonic_Init()//������ģ���ʼ��
{
	#ifdef yellow_car//����ͷ�� ���ڽ���
	
	//��ʼ��uart0��ʹ���ж�
	uart_init(UART_Ultrasonic_Rec,115200);//���ڳ�ʼ��
	NVIC_DisableIRQ(UART0_RX_TX_IRQn);
	set_irq_priority(UART0_RX_TX_IRQn,0);//uart0�ж�
	uart_rx_irq_en(UART_Ultrasonic_Rec);//ʹ���ж�	
	
	#elif red_car//��ų� ���ڷ���
	gpio_init(PORT_Ultrasonic_Send,GPO,1);
	
	#endif
}

void Ultrasonic_Receive()//�������жϽ���ģ��
{
	//��������������
	uart_getchar(UART_Ultrasonic_Rec,&Uls_dat[Uls_Num]);
	//���ͷ֡�Ƿ���ȷ������ȷ�����½���
	if(Uls_dat[0] != 0xa5)
	{Uls_Num = 0;}	
	else 
	{Uls_Num++;}
	//������ɣ���ʼ��������
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

void Ultrasonic_seecar()//�������㳵���
{
	if(Uls_receive_flag == 1)
	{
		OLED_Write_Num4(8,6,Uls_Distance);
		if(Uls_Distance <= 2000 && Uls_Distance - Uls_Distance_last <= 100)//100cm�㳵׼��
		{
			
			in_cnt++;
			out_cnt_flag = 0;//���������ջ㳵��־��ʱ���ٴμ�⵽�㳵���� ���
			if(in_cnt >= 5)
			{
				seecar_flag = 1;
			}
		}
		else
		{
			in_cnt = 0;//��ձ�־λ
		}
		if(Uls_Distance >= 2000 && seecar_flag == 1 && out_cnt_flag == 0)//�㳵���� ������ ���ڻ㳵״̬ �����������
		{
			//��ʱ������ջ㳵��־λ
			out_cnt_flag = 1;
			out_cnt = 2;//��ʱ2��
		}
		if(out_cnt_flag == 1)
		{
			out_cnt--;
			if(out_cnt == 0)
			{
				out_cnt_flag = 0;
				seecar_flag = 0;
				seecar_cnt++;//�㳵����
				//�����һ���������� ͣ��
				//�Ӻ�25���Ÿ���һ����
				if(startline == 1 && startline_cnt_flag == 0)
				{
					startline_cnt = 25;
					startline_cnt_flag = 1;
				}
				//������ǵ�һ�λ㳵 ���м�ʱ�㳵�ж�
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
		Uls_receive_flag = 0;//��ձ�־λ
	}
	
}
