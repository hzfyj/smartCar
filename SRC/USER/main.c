#include "headfile.h"

int main(void)
{

get_clk();//�ϵ���������һ�������������ȡ����Ƶ����Ϣ�����ں������ģ��Ĳ�������
OLED_Init();//OLED��ʼ��
gpio_init(A4,GPO,1);
buzzer_Init();//������.��04ʼ��
KEY_Init();//������������ʼ��

menu();
	
if(dianbo_switch==1)
{
 IMU_IIC_Init();//II2C��ʼ��
 L3G4200D_Init();//�����ǳ�ʼ��
}
	if(startstart==1)
	{			
		OLED_Write_String(2,0,(uint8_t *)"Ready to Start");
		DelayMs(1000);
		OLED_Clear();
	}	
if(mode_mode==1)
	{
		mode1();
	}
	if(mode_mode==2)//������ͼ
	{
		mode2();
	}
	if(mode_mode==3)//¼ͼ
	{
		mode3();
	}
		if(mode_mode==4)//��ͼ
	{
		mode4();
	}

		if(mode_mode==5)//ʵʱ����
	{

		mode5();
	}
			if(mode_mode==6)//ʵʱ����
	{

		mode6();
	}
}	

