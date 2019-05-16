#include "headfile.h"

int main(void)
{

get_clk();//上电后必须运行一次这个函数，获取各个频率信息，便于后面各个模块的参数设置
OLED_Init();//OLED初始化
gpio_init(A4,GPO,1);
buzzer_Init();//蜂鸣器.初04始化
KEY_Init();//电机舵机按键初始化

menu();
	
if(dianbo_switch==1)
{
 IMU_IIC_Init();//II2C初始化
 L3G4200D_Init();//陀螺仪初始化
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
	if(mode_mode==2)//仅仅有图
	{
		mode2();
	}
	if(mode_mode==3)//录图
	{
		mode3();
	}
		if(mode_mode==4)//传图
	{
		mode4();
	}

		if(mode_mode==5)//实时传输
	{

		mode5();
	}
			if(mode_mode==6)//实时传输
	{

		mode6();
	}
}	

