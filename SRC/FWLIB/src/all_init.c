#include "all_init.h"
#include "headfile.h"

void all_Init()//初始化所有模块
{
	get_clk();//上电后必须运行一次这个函数，获取各个频率信息，便于后面各个模块的参数设置
	OLED_Init();//OLED初始化
//	uart_init(uart0,115200);//串口初始化
//	uart_rx_irq_en(uart0);//使能中断
	buzzer_Init();//蜂鸣器初始化
	//A4脚置高
	gpio_init(A4,GPO,1);
	
	
	//Encoder_Init();//编码器
	//sonyccd_Init();//摄像头初始化
	
	
//	camera_init();//初始化摄像头
	
}

void Car_Set()//根据小车的编号 决定小车的引脚不同
{
	if(Car_Flag == 1)//黄车
	{
		//AD电感端口
		AD_chanel[0] = ADC1_SE12;
		AD_chanel[1] = ADC1_SE10;
		AD_chanel[2] = ADC0_SE12;
		AD_chanel[3] = ADC1_SE8;
		AD_chanel[4] = ADC1_SE11;
		AD_chanel[5] = ADC0_SE13;
		AD_chanel[6] = ADC0_SE9;
		//舵机上下限 中值
		servo_Min = 630;
		servo_Max = 800;
		//电机正反转
		motor_LU.Port = ftm1;
		motor_LU.Ch = ftm_ch1;
		motor_LD.Port = ftm1;
		motor_LD.Ch = ftm_ch0;
		motor_RU.Port = ftm0;
		motor_RU.Ch = ftm_ch3;
		motor_RD.Port = ftm0;
		motor_RD.Ch = ftm_ch4;
	}
	else if(Car_Flag == 2)//红车
	{
		//AD电感端口
		AD_chanel[0] = ADC1_SE12;
		AD_chanel[1] = ADC1_SE10;
		AD_chanel[2] = ADC0_SE12;
		AD_chanel[3] = ADC1_SE8;
		AD_chanel[4] = ADC1_SE11;
		AD_chanel[5] = ADC0_SE13;
		AD_chanel[6] = ADC0_SE9;
		//舵机上下限 中值
		servo_Min = 595;
		servo_Max = 750;
		//电机正反转
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

void Car_Init_AfterSet()//目录之后初始化 电机 ad电感
{
	Motor_Init();//电机初始化
}

void Car_Init_WhenMenu()//菜单初始化之后回调
{
	//初始化舵机 根据舵机的值
	if(menuValue[20] > 650 && menuValue[20] < 750)
	{
		servo_Mid = menuValue[20];
		Servo_Init();//舵机初始化
	}
}