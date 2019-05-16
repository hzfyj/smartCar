#ifndef _ULTRASONIC_H
#define _ULTRASONIC_H

#include "headfile.h"

//���������ͳ�ʼ�����ź궨��
#define PORT_Ultrasonic_Send A15//��ʱʹ��uart0�����������ʹ�� ����C13����
//�������������ź궨��
#define UART_Ultrasonic_Rec uart0//UART2_RX_D2_TX_D3


void Ultrasonic_Init();//������ģ���ʼ��
void Ultrasonic_Receive();//�������жϽ���ģ��

void Ultrasonic_seecar();//�������㳵���

extern uint8_t Uls_receive_flag;
extern uint16_t Uls_Distance;
extern uint8_t startline_cnt,startline_cnt_flag;
extern uint8_t out_cnt,out_cnt_flag;
extern uint8_t startline_give;
extern uint32_t seecar_timer;
extern uint32_t seecar_timer_set;

#endif