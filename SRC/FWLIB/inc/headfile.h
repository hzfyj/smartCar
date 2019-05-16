/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2017,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：179029047
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		headfile
 * @company	   		成都逐飞科技有限公司
 * @author     		Go For It(1325536866)
 * @version    		v2.0
 * @Software 		IAR 7.7 or MDK 5.17
 * @Target core		MK66FX
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2017-09-19
 ********************************************************************************************************************/



#ifndef _headfile_h
#define _headfile_h


#include "port_cfg.h"
#include "common.h"
#include "misc.h"
#include "stdio.h"

//--------函数库--------
#include "rtc.h"
#include "gpio.h"
#include "systick.h"
#include "port.h"
#include "uart.h"
#include "pit.h"
#include "lptmr.h"
#include "ftm.h"
#include "adc.h"
#include "dac.h"
#include "flash.h"
#include "spi.h"
#include "i2c.h"
#include "wdog.h"
#include "dma.h"
#include "cmt.h"
#include "sdhc.h"
#include "isr.h"
#include "IMU_IIC.h"
#include "L3G4200D.h"

////fatfs文件系统
//#include "ff.h"

//初始化
#include "all_init.h"

//--------逐飞科技产品例程库--------
//#include "SEEKFREE_MT9V032.h"
//#include "SEEKFREE_18TFT.h"
//#include "SEEKFREE_FUN.h"
//#include "SEEKFREE_TSL1401.h"
//#include "SEEKFREE_7725.h"
//#include "SEEKFREE_IIC.h"
//#include "SEEKFREE_NRF24L01.h"
////#include "SEEKFREE_OLED.h"
//#include "SEEKFREE_L3G4200D.h"
//#include "SEEKFREE_MMA8451.h"
//#include "SEEKFREE_MPU6050.h"
//#include "SEEKFREE_28LCD.h"

//智能车模块

#include "sd_storage.h"	//sd卡
#include "dmacnt.h"			//dma脉冲计数
#include "SEEKFREE_MT9V032.h"//总钻风摄像头
#include "data.h"	//数据
#include "menu.h"	//菜单
#include "process.h"	//图像处理
#include "pidcontrol.h"	//pid控制
#include "key.h"	//pid控制
#include "sonyccd.h"

//HDU
#include "oled.h"
#include "sd_yaoxin.h"


//宏定义函数名
#define DelayMs systick_delay_ms

#endif
