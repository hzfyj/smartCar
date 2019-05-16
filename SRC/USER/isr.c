/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2016,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：179029047
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		isr.c
 * @brief      		中断函数库
 * @company	   		成都逐飞科技有限公司
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
//  @brief      PROTA中断执行函数
//  @return     void   
//  @since      v1.0
//  Sample usage:               当A口启用中断功能且发生中断的时候会自动执行该函数
//-------------------------------------------------------------------------------------------------------------------
//void PORTA_IRQHandler(void)
//{
////    //清除中断标志第一种方法直接操作寄存器，每一位对应一个引脚
////	PORTA->ISFR = 0xffffffff;
////	//使用我们编写的宏定义清除发生中断的引脚
//	
//	sonyccd_VSYNC();//场中断处理函数
//	PORTA_FLAG_CLR(sonyccd_VSYNC_Port);	//清楚中断标志位
//}

//void PORTD_IRQHandler(void)
//{
////    //清除中断标志第一种方法直接操作寄存器，每一位对应一个引脚
////	PORTA->ISFR = 0xffffffff;
////	//使用我们编写的宏定义清除发生中断的引脚
//	
//	sonyccd_HREF();//行中断处理函数
//	PORTD_FLAG_CLR(sonyccd_HREF_Port);	//清楚中断标志位
//}


////void PORTC_IRQHandler(void)
////{
////    //清除中断标志第一种方法直接操作寄存器，每一位对应一个引脚
////	PORTC->ISFR = 0xffffffff;
////	//使用我们编写的宏定义清除发生中断的引脚
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
//	PIT_FlAG_CLR(pit0);									//清除中断标志位
////	OLED_Print_Num(0,2,CNT);
////	CNT = 0;
//	count_flag = 1;
//	
//}

#include "oled.h"

extern int camera_cnt;
extern int ind_cnt;
//void PIT2_IRQHandler(void)//电磁执行方案
//{
//	//
//	PIT_FlAG_CLR(pit2);
//	OLED_Write_Num5(8,0,camera_cnt);
//	OLED_Write_Num5(8,2,ind_cnt);
//	camera_cnt = 0;
//	ind_cnt = 0;
//}

//void PIT1_IRQHandler(void)//电磁执行方案
//{
//	
//	PIT_FlAG_CLR(pit1);
//	
//	change_flag = 1;
//	OLED_Write_String(0,4,"in isr");
//}


uint16 Huandao_Cnt=0;

void PIT1_IRQHandler(void)//电磁执行方案
{
	PIT_FlAG_CLR(pit1);
//	SmartCar_Run();//小车运行
}

void PIT2_IRQHandler(void)//电磁执行方案
{
//	PIT_FlAG_CLR(pit2);
//	//电磁执行部分
//		change_flag = 1;
	
}

void UART0_RX_TX_IRQHandler(void)
{
//	uint8_t ch;
//	if(UART0->S1 & UART_S1_RDRF_MASK)                                     //接收数据寄存器满
//	{
//		//用户需要处理接收数据
//		//添加超声波
//		if(transfer_switch == 2)
//		{
//			Ultrasonic_Receive();
//		}
//		else
//		{
//			//其他情况 开启串口停车保护
//			uart_getchar(uart0,&ch);
//			if(ch == 'x')
//			{
//				//停车
//				stop_flag = 1;
//				Motor_stop();
//				OLED_Write_String(0,4,(uint8_t*)"computer");
//			}
//		}
//	}
//	if(UART0->S1 & UART_S1_TDRE_MASK )                                    //发送数据寄存器空
//	{
//			//用户需要处理发送数据

//	}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      UART3中断执行函数
//  @return     void   
//  @since      v1.0
//  Sample usage:               当UART3启用中断功能且发生中断的时候会自动执行该函数
//-------------------------------------------------------------------------------------------------------------------
//void UART3_RX_TX_IRQHandler(void)
//{
//    if(UART3->S1 & UART_S1_RDRF_MASK)                                     //接收数据寄存器满
//    {
//        //用户需要处理接收数据
//        mt9v032_cof_uart_interrupt();
//    }
//    if(UART3->S1 & UART_S1_TDRE_MASK )                                    //发送数据寄存器空
//    {
//        //用户需要处理发送数据

//    }
//}


/*******************总钻风*******************/
//场中断 E12
void PORTE_IRQHandler(void)
{
  //清除中断标志第一种方法直接操作寄存器，每一位对应一个引脚
	PORTE->ISFR = 0xffffffff;
	//使用我们编写的宏定义清除发生中断的引脚
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
    if(UART3->S1 & UART_S1_RDRF_MASK)                                     //接收数据寄存器满
    {
        //用户需要处理接收数据
        mt9v032_cof_uart_interrupt();
    }
    if(UART3->S1 & UART_S1_TDRE_MASK )                                    //发送数据寄存器空
    {
        //用户需要处理发送数据

    }
}

//无线接收中断	PTC9

void PORTC_IRQHandler(void)
{
//	SIM->SCGC5|=SIM_SCGC5_PORTC_MASK;
//	PORTC->ISFR |= (1<<9);
//	//buzzer = 1;
//	NRF2401_RecData(NRF2401RXBuffer); //接收数据
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
中断函数名称，用于设置对应功能的中断函数
Sample usage:当前启用了DMA0中断，然后就到下面去找哪个是DMA0的中断函数名称，找到后写一个该名称的函数即可
void DMA0_IRQHandler(void)
{
    ;
}
记得进入中断后清除标志位


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
                

/*****************死机保护****************/
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


