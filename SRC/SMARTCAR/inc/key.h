#ifndef _KEY_H_
#define _KEY_H_
#include "common.h"
#include "gpio.h"
//按键 
#define Key_up_Port		    D15
#define Key_Up			 PDin(15)

#define Key_down_Port		  D13
#define Key_Down		PDin(13)


#define Key_left_Port	  D14
#define Key_Minus				PDin(14) 

#define Key_right_Port			D12
#define Key_Add 					 	PDin(12)

#define Key_1_Port				D10
#define Key_1						   PDin(10) 

#define Key_2_Port			D11
#define Key_In						PDin(11)


#define   Motordown_port    ftm0
#define   Motordown_ch	  	ftm_ch5

#define   Motorup_port      ftm0
#define   Motorup_ch	    	ftm_ch4

#define Steer_port    ftm2
#define Steer_ch	   	ftm_ch0

#define Motor_Frequency  10000
#define Steer_Frequency  300

//左编码器脉冲口
#define Bianma_Fangxiang   D3
#define Bianma_Maichong   D2
//蜂鸣器
#define buzzer_Port C12
#define buzzer PCout(12)

#define TuoLuoYi 1 //有没有陀螺仪 1是有

void KEY_Init(void);					//按键初始化
void buzzer_Init(void);//蜂鸣器初始化

#endif
