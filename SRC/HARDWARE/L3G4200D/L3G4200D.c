#include "IMU_IIC.h"
#include "L3G4200D.h"
#include "gpio.h"
#include "math.h"
#include "oled.h"
#include "headfile.h"


//��ʱ����
void tly_delay(uint16_t k)		 
{
    uint8_t i;	 

    while(--k)
    {
        for(i=0;i<100;i++); //��ʱʱ�䳤�̣�0--255��ѡ
    }
}

//��ȡL3G4200D��1���ֽ�
uint8_t L3G4200D_readbyte(uint8_t address)
{
	uint8_t ret;
	IIC_start();		//����
	send_byte(SlaveAddress);	//д���豸ID��д�ź�
	send_byte(address);	//X��ַ
	IIC_start();		//���·��Ϳ�ʼ
	send_byte(SlaveAddress+1);	//д���豸ID������
	ret = read_byte();	//��ȡһ�ֽ�
	IIC_stop();
	return ret;
}



//д��L3G4200D��1���ֽ�
void L3G4200D_writebyte(uint8_t address, uint8_t thedata)
{
	IIC_start();		//����
	send_byte(SlaveAddress);	//д���豸ID��д�ź�
	send_byte(address);	//X��ַ
	send_byte(thedata);	//д���豸ID������
	IIC_stop();
}

/*
 * �������ܣ���L3G4200D���ٶ����
 * �����w
 *       Status - ���ݼĴ���״̬
 *       Regs_Addr - ���ݼĴ�����ַ
 * ��������ֵ�����ٶ�ֵ��int16��
 */   
int16_t L3G4200D_GetResult(uint8_t Status, uint8_t Regs_Addr) 
{
  uint8_t ret=0;
  uint16_t cnt=0;
  int16_t result,temp;
  
  if(Regs_Addr>L3G4200D_OUT_Z_H)//Regs_Addr>L3G4200D_OUT_Z_H
    return 0;
  
  // �ȴ�ת����ɲ�ȡ��ֵ 
  while(!(ret&Status)) 
  {
    ret = L3G4200D_readbyte( L3G4200D_STATUS_REG);
    if(++cnt>500)
      break;
  }
  
  result= L3G4200D_readbyte( Regs_Addr);
  temp  = L3G4200D_readbyte( Regs_Addr-1);
  result=result<<8;
  result=result|temp;
  
  return result>>2;
}

//��ȡ3����ٶ�
int16_t Gyro_X, Gyro_Y, Gyro_Z;
void L3G4200D_XYZ()
{
  //  Gyro_X = L3G4200D_GetResult(L3G4200D_STATUS_REG, L3G4200D_OUT_X_H);
    Gyro_Y = L3G4200D_GetResult(L3G4200D_STATUS_REG, L3G4200D_OUT_Y_H);
  //  Gyro_Z = L3G4200D_GetResult(L3G4200D_STATUS_REG, L3G4200D_OUT_Z_H);
}




//*****************************************************************

//��ʼ��L3G4200D��������Ҫ��ο�pdf�����޸�************************
void L3G4200D_Init()//2
{
   while(L3G4200D_readbyte(L3G4200D_WHO_AM_I)!=0xD3);
   tly_delay(10);
   L3G4200D_writebyte(L3G4200D_CTRL_REG1, 0xFF);   
   tly_delay(10);
   L3G4200D_writebyte(L3G4200D_CTRL_REG2, 0x00);   // 
   tly_delay(10);
   L3G4200D_writebyte(L3G4200D_CTRL_REG3, 0x08);   //
   tly_delay(10);
   L3G4200D_writebyte(L3G4200D_CTRL_REG4, 0x30);  //+-2000dps ����2000��/�� ������70mdps/digit->X*70/1000=Y��ÿ��
   tly_delay(10);
   L3G4200D_writebyte(L3G4200D_CTRL_REG5, 0x00);
   tly_delay(10);
}
