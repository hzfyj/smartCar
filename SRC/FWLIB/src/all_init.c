#include "all_init.h"
#include "headfile.h"

void all_Init()//��ʼ������ģ��
{
	get_clk();//�ϵ���������һ�������������ȡ����Ƶ����Ϣ�����ں������ģ��Ĳ�������
	OLED_Init();//OLED��ʼ��
//	uart_init(uart0,115200);//���ڳ�ʼ��
//	uart_rx_irq_en(uart0);//ʹ���ж�
	buzzer_Init();//��������ʼ��
	//A4���ø�
	gpio_init(A4,GPO,1);
	
	
	//Encoder_Init();//������
	//sonyccd_Init();//����ͷ��ʼ��
	
	
//	camera_init();//��ʼ������ͷ
	
}

void Car_Set()//����С���ı�� ����С�������Ų�ͬ
{
	if(Car_Flag == 1)//�Ƴ�
	{
		//AD��ж˿�
		AD_chanel[0] = ADC1_SE12;
		AD_chanel[1] = ADC1_SE10;
		AD_chanel[2] = ADC0_SE12;
		AD_chanel[3] = ADC1_SE8;
		AD_chanel[4] = ADC1_SE11;
		AD_chanel[5] = ADC0_SE13;
		AD_chanel[6] = ADC0_SE9;
		//��������� ��ֵ
		servo_Min = 630;
		servo_Max = 800;
		//�������ת
		motor_LU.Port = ftm1;
		motor_LU.Ch = ftm_ch1;
		motor_LD.Port = ftm1;
		motor_LD.Ch = ftm_ch0;
		motor_RU.Port = ftm0;
		motor_RU.Ch = ftm_ch3;
		motor_RD.Port = ftm0;
		motor_RD.Ch = ftm_ch4;
	}
	else if(Car_Flag == 2)//�쳵
	{
		//AD��ж˿�
		AD_chanel[0] = ADC1_SE12;
		AD_chanel[1] = ADC1_SE10;
		AD_chanel[2] = ADC0_SE12;
		AD_chanel[3] = ADC1_SE8;
		AD_chanel[4] = ADC1_SE11;
		AD_chanel[5] = ADC0_SE13;
		AD_chanel[6] = ADC0_SE9;
		//��������� ��ֵ
		servo_Min = 595;
		servo_Max = 750;
		//�������ת
		motor_LU.Port = ftm1;
		motor_LU.Ch = ftm_ch0;
		motor_LD.Port = ftm1;
		motor_LD.Ch = ftm_ch1;
		motor_RU.Port = ftm0;
		motor_RU.Ch = ftm_ch4;
		motor_RD.Port = ftm0;
		motor_RD.Ch = ftm_ch3;
	}
}

void Car_Init_AfterSet()//Ŀ¼֮���ʼ�� ��� ad���
{
	Motor_Init();//�����ʼ��
}

void Car_Init_WhenMenu()//�˵���ʼ��֮��ص�
{
	//��ʼ����� ���ݶ����ֵ
	if(menuValue[20] > 650 && menuValue[20] < 750)
	{
		servo_Mid = menuValue[20];
		Servo_Init();//�����ʼ��
	}
}