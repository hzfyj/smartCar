#include "key.h"
#include "data.h"
#include "ftm.h"
#include "dmacnt.h"
//�������� ����Ϊ0

void KEY_Init(void)					//������ʼ��
{
	gpio_init(Key_left_Port,GPI,2);
	gpio_init(Key_right_Port,GPI,2);
	gpio_init(Key_up_Port,GPI,2);
	gpio_init(Key_down_Port,GPI,2);
	gpio_init(Key_1_Port,GPI,2);
	gpio_init(Key_2_Port,GPI,2);
	ftm_pwm_init(Motorup_port,Motorup_ch,Motor_Frequency,0);   //���
  ftm_pwm_init(Motordown_port,Motordown_ch,Motor_Frequency,0);	
	DMACNT_Init(DMA_CH1,Bianma_Maichong);
	gpio_init(Bianma_Fangxiang,GPI,2);
	ftm_pwm_init(Steer_port,Steer_ch,Steer_Frequency,zhong);   //���


	
}

void buzzer_Init()//��������ʼ��
{ 

}


