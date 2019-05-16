/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2016,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��179029047
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		isr.c
 * @brief      		�жϺ�����
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		Go For It(1325536866)
 * @version    		v1.0
 * @Software 		IAR 7.7 or MDK 5.17
 * @Target core		MK60DN512VLL10
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2016-02-25
 ********************************************************************************************************************/



#include "isr.h"

extern int CNT;
extern uint8_t controlFlag;
//extern uint8_t wireless_received_flag;
//-------------------------------------------------------------------------------------------------------------------
//  @brief      PROTA�ж�ִ�к���
//  @return     void   
//  @since      v1.0
//  Sample usage:               ��A�������жϹ����ҷ����жϵ�ʱ����Զ�ִ�иú���
//-------------------------------------------------------------------------------------------------------------------
//void PORTA_IRQHandler(void)
//{
////    //����жϱ�־��һ�ַ���ֱ�Ӳ����Ĵ�����ÿһλ��Ӧһ������
////	PORTA->ISFR = 0xffffffff;
////	//ʹ�����Ǳ�д�ĺ궨����������жϵ�����
//	
//	sonyccd_VSYNC();//���жϴ�����
//	PORTA_FLAG_CLR(sonyccd_VSYNC_Port);	//����жϱ�־λ
//}

//void PORTD_IRQHandler(void)
//{
////    //����жϱ�־��һ�ַ���ֱ�Ӳ����Ĵ�����ÿһλ��Ӧһ������
////	PORTA->ISFR = 0xffffffff;
////	//ʹ�����Ǳ�д�ĺ궨����������жϵ�����
//	
//	sonyccd_HREF();//���жϴ�����
//	PORTD_FLAG_CLR(sonyccd_HREF_Port);	//����жϱ�־λ
//}


////void PORTC_IRQHandler(void)
////{
////    //����жϱ�־��һ�ַ���ֱ�Ӳ����Ĵ�����ÿһλ��Ӧһ������
////	PORTC->ISFR = 0xffffffff;
////	//ʹ�����Ǳ�д�ĺ궨����������жϵ�����
////	//PORTC_FLAG_CLR(C1);
////    VSYNC();
////}


//void DMA0_IRQHandler(void)
//{
//	sonyccd_DMA_IRQ();
//	DMA_IRQ_CLEAN(DMA_CH0);
//    //row_finished();
//	
//}

extern uint8 change_flag,count_flag;

//void PIT0_IRQHandler(void)
//{
//	PIT_FlAG_CLR(pit0);									//����жϱ�־λ
////	OLED_Print_Num(0,2,CNT);
////	CNT = 0;
//	count_flag = 1;
//	
//}

#include "oled.h"

extern int camera_cnt;
extern int ind_cnt;
//void PIT2_IRQHandler(void)//���ִ�з���
//{
//	//
//	PIT_FlAG_CLR(pit2);
//	OLED_Write_Num5(8,0,camera_cnt);
//	OLED_Write_Num5(8,2,ind_cnt);
//	camera_cnt = 0;
//	ind_cnt = 0;
//}

//void PIT1_IRQHandler(void)//���ִ�з���
//{
//	
//	PIT_FlAG_CLR(pit1);
//	
//	change_flag = 1;
//	OLED_Write_String(0,4,"in isr");
//}


uint16 Huandao_Cnt=0;

void PIT1_IRQHandler(void)//���ִ�з���
{
	PIT_FlAG_CLR(pit1);
//	SmartCar_Run();//С������
}

void PIT2_IRQHandler(void)//���ִ�з���
{
//	PIT_FlAG_CLR(pit2);
//	//���ִ�в���
//		change_flag = 1;
	
}

void UART0_RX_TX_IRQHandler(void)
{
//	uint8_t ch;
//	if(UART0->S1 & UART_S1_RDRF_MASK)                                     //�������ݼĴ�����
//	{
//		//�û���Ҫ�����������
//		//��ӳ�����
//		if(transfer_switch == 2)
//		{
//			Ultrasonic_Receive();
//		}
//		else
//		{
//			//������� ��������ͣ������
//			uart_getchar(uart0,&ch);
//			if(ch == 'x')
//			{
//				//ͣ��
//				stop_flag = 1;
//				Motor_stop();
//				OLED_Write_String(0,4,(uint8_t*)"computer");
//			}
//		}
//	}
//	if(UART0->S1 & UART_S1_TDRE_MASK )                                    //�������ݼĴ�����
//	{
//			//�û���Ҫ����������

//	}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      UART3�ж�ִ�к���
//  @return     void   
//  @since      v1.0
//  Sample usage:               ��UART3�����жϹ����ҷ����жϵ�ʱ����Զ�ִ�иú���
//-------------------------------------------------------------------------------------------------------------------
//void UART3_RX_TX_IRQHandler(void)
//{
//    if(UART3->S1 & UART_S1_RDRF_MASK)                                     //�������ݼĴ�����
//    {
//        //�û���Ҫ�����������
//        mt9v032_cof_uart_interrupt();
//    }
//    if(UART3->S1 & UART_S1_TDRE_MASK )                                    //�������ݼĴ�����
//    {
//        //�û���Ҫ����������

//    }
//}


/*******************�����*******************/
//���ж� E12
void PORTE_IRQHandler(void)
{
  //����жϱ�־��һ�ַ���ֱ�Ӳ����Ĵ�����ÿһλ��Ӧһ������
	PORTE->ISFR = 0xffffffff;
	//ʹ�����Ǳ�д�ĺ궨����������жϵ�����
	//PORTC_FLAG_CLR(C1);
    VSYNC();
	//printf("chang in");
}

//void DMA0_IRQHandler(void)
//{
//	DMA_IRQ_CLEAN(DMA_CH0);
//    row_finished();
//	//printf("dma in ");
//}

void UART3_RX_TX_IRQHandler(void)
{
	//printf("uart in");
    if(UART3->S1 & UART_S1_RDRF_MASK)                                     //�������ݼĴ�����
    {
        //�û���Ҫ�����������
        mt9v032_cof_uart_interrupt();
    }
    if(UART3->S1 & UART_S1_TDRE_MASK )                                    //�������ݼĴ�����
    {
        //�û���Ҫ����������

    }
}

//���߽����ж�	PTC9

void PORTC_IRQHandler(void)
{
//	SIM->SCGC5|=SIM_SCGC5_PORTC_MASK;
//	PORTC->ISFR |= (1<<9);
//	//buzzer = 1;
//	NRF2401_RecData(NRF2401RXBuffer); //��������
//	//OLED_Write_Num2(8,2,NRF2401RXBuffer[1]);
//	if(NRF2401RXBuffer[0]==36) 
//	{
//		WirelessReceiveStorage[0] = NRF2401RXBuffer[1];
//		WirelessReceiveStorage[1] = NRF2401RXBuffer[2];
//		WirelessReceiveStorage[2] = NRF2401RXBuffer[3];
//		WirelessReceiveStorage[3] = NRF2401RXBuffer[4];
//		WirelessReceiveStorage[4] = NRF2401RXBuffer[5];
//		WirelessReceiveStorage[5] = NRF2401RXBuffer[6];
//		WirelessReceiveStorage[6] = NRF2401RXBuffer[7];
//		WirelessReceiveStorage[7] = NRF2401RXBuffer[8];
//		WirelessReceiveStorage[8] = NRF2401RXBuffer[9];
//		WirelessReceiveStorage[9] = NRF2401RXBuffer[10];
//		
//		wireless_received_flag = 1;
//	}
}


/*
�жϺ������ƣ��������ö�Ӧ���ܵ��жϺ���
Sample usage:��ǰ������DMA0�жϣ�Ȼ��͵�����ȥ���ĸ���DMA0���жϺ������ƣ��ҵ���дһ�������Ƶĺ�������
void DMA0_IRQHandler(void)
{
    ;
}
�ǵý����жϺ������־λ


DMA0_IRQHandler  
DMA1_IRQHandler  
DMA2_IRQHandler  
DMA3_IRQHandler  
DMA4_IRQHandler  
DMA5_IRQHandler  
DMA6_IRQHandler  
DMA7_IRQHandler  
DMA8_IRQHandler  
DMA9_IRQHandler  
DMA10_IRQHandler 
DMA11_IRQHandler 
DMA12_IRQHandler 
DMA13_IRQHandler 
DMA14_IRQHandler 
DMA15_IRQHandler 
DMA_Error_IRQHandler      
MCM_IRQHandler            
FTFL_IRQHandler           
Read_Collision_IRQHandler 
LVD_LVW_IRQHandler        
LLW_IRQHandler            
Watchdog_IRQHandler       
RNG_IRQHandler            
I2C0_IRQHandler           
I2C1_IRQHandler           
SPI0_IRQHandler           
SPI1_IRQHandler           
SPI2_IRQHandler           
CAN0_ORed_Message_buffer_IRQHandler    
CAN0_Bus_Off_IRQHandler                
CAN0_Error_IRQHandler                  
CAN0_Tx_Warning_IRQHandler             
CAN0_Rx_Warning_IRQHandler             
CAN0_Wake_Up_IRQHandler                
I2S0_Tx_IRQHandler                     
I2S0_Rx_IRQHandler                     
CAN1_ORed_Message_buffer_IRQHandler    
CAN1_Bus_Off_IRQHandler                
CAN1_Error_IRQHandler                  
CAN1_Tx_Warning_IRQHandler             
CAN1_Rx_Warning_IRQHandler             
CAN1_Wake_Up_IRQHandler                
Reserved59_IRQHandler                  
UART0_LON_IRQHandler                   
UART0_RX_TX_IRQHandler                 
UART0_ERR_IRQHandler                   
UART1_RX_TX_IRQHandler                 
UART1_ERR_IRQHandler  
UART2_RX_TX_IRQHandler
UART2_ERR_IRQHandler  
UART3_RX_TX_IRQHandler
UART3_ERR_IRQHandler  
UART4_RX_TX_IRQHandler
UART4_ERR_IRQHandler  
UART5_RX_TX_IRQHandler
UART5_ERR_IRQHandler  
ADC0_IRQHandler
ADC1_IRQHandler
CMP0_IRQHandler
CMP1_IRQHandler
CMP2_IRQHandler
FTM0_IRQHandler
FTM1_IRQHandler
FTM2_IRQHandler
CMT_IRQHandler 
RTC_IRQHandler 
RTC_Seconds_IRQHandler  
PIT0_IRQHandler  
PIT1_IRQHandler  
PIT2_IRQHandler  
PIT3_IRQHandler  
PDB0_IRQHandler  
USB0_IRQHandler  
USBDCD_IRQHandler
ENET_1588_Timer_IRQHandler
ENET_Transmit_IRQHandler  
ENET_Receive_IRQHandler
ENET_Error_IRQHandler  
Reserved95_IRQHandler  
SDHC_IRQHandler
DAC0_IRQHandler
DAC1_IRQHandler
TSI0_IRQHandler
MCG_IRQHandler 
LPTimer_IRQHandler 
Reserved102_IRQHandler 
PORTA_IRQHandler 
PORTB_IRQHandler 
PORTC_IRQHandler 
PORTD_IRQHandler 
PORTE_IRQHandler 
Reserved108_IRQHandler
Reserved109_IRQHandler
SWI_IRQHandler 
*/
                

/*****************��������****************/
#define  CHIP_DEBUG         ON		//??????????????a???????????
#if(CHIP_DEBUG==ON)
__asm void wait()
{
  BX lr	//?????????
}
#endif

void HardFault_Handler(void)//?????????
{

	
	#if(CHIP_DEBUG==ON)
	wait();
	#endif
	while(1);
}

void NMI_Handler(void)//??????
{

	#if(CHIP_DEBUG==ON)	
	wait();
	#endif
	while(1);
}

void MemManage_Handler(void)//??????
{

	#if(CHIP_DEBUG==ON)	
	wait();
	#endif
}

void BusFault_Handler(void)//??????
{


	#if(CHIP_DEBUG==ON)	
	wait();
	#endif
}

void UsageFault_Handler(void)//??????
{



	#if(CHIP_DEBUG==ON)	
	wait();
	#endif
}


