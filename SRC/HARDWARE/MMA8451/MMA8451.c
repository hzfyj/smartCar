#include "mma8451.h"
#include "IMU_IIC.h"
#include "sys.h"
#include "oled.h"
//�˴��������ص�ͷ�ļ�


void mma_delay(uint16_t k)		 //��ʱ����
{
    uint8_t i;	 //�ں����У�����������������Ȼ����ܵ���
    while(--k)
    {
       for(i=0;i<100;i++); //��ʱʱ�䳤�̣�0--255��ѡ
    }
}


//��ȡMMA8451��1���ֽ�
uint8_t MMA8451_readbyte(uint8_t address)
{
	uint8_t ret;
	IIC_start();		//����
	send_byte(MMA845x_IIC_ADDRESS);	//д���豸ID��д�ź�
	send_byte(address);	//X��ַ
	IIC_start();		//���·��Ϳ�ʼ
	send_byte(MMA845x_IIC_ADDRESS+1);	//д���豸ID������
	ret = read_byte();	//��ȡһ�ֽ�
	IIC_stop();
	return ret;
}



//д��MMA8451��1���ֽ�
void MMA8451_writebyte(uint8_t address, uint8_t thedata)
{
	IIC_start();		//����
	send_byte(MMA845x_IIC_ADDRESS);	//д���豸ID��д�ź�
	send_byte(address);	//X��ַ
	send_byte(thedata);	//д���豸ID������
	IIC_stop();
}


/*
 * �������ܣ���MAA8451���ٶ����
 * �����w
 *       Status - ���ݼĴ���״̬
 *       Regs_Addr - ���ݼĴ�����ַ
 * ��������ֵ�����ٶ�ֵ��int16��
 */   
int16_t MMA8451_GetResult(uint8_t Status, uint8_t Regs_Addr) 
{
  uint8_t ret=0;
  uint16_t cnt=0;
  int16_t result,temp;
  if(Regs_Addr>MMA8451_REG_OUTZ_LSB)
    return 0;
  
  // �ȴ�ת����ɲ�ȡ��ֵ 
  while(!(ret&Status)) 
  {
    ret = MMA8451_readbyte( MMA8451_REG_STATUS);
    if(++cnt>500)
      break;
  }
  
  result= MMA8451_readbyte( Regs_Addr);
  temp  = MMA8451_readbyte( Regs_Addr+1);
  result=result<<8;
  result=result|temp;
  
  return result>>2;
}


//��ȡ3����ٶ�
int16_t ACC_X, ACC_Y,ACC_Z,ACC_Z1; 
void MMA8451_XYZ()
{
    ACC_X = MMA8451_GetResult(MMA8451_STATUS_X_READY, MMA8451_REG_OUTX_MSB);
    ACC_Y = MMA8451_GetResult(MMA8451_STATUS_Y_READY, MMA8451_REG_OUTY_MSB);  
    ACC_Z = MMA8451_GetResult(MMA8451_STATUS_X_READY, MMA8451_REG_OUTZ_MSB); 
}




//MMA8451��ʼ��
void MMA8451_Init()
{	

  while(MMA8451_readbyte(MMA8451_REG_WHOAMI)!=0x1a);
	mma_delay(10);
	MMA8451_writebyte(MMA8451_REG_SYSMOD,0x00);	   //Ĭ��ģʽStandby Mode
	mma_delay(10);
	MMA8451_writebyte(MMA8451_REG_CTRL_REG2,0x02); //High Resolution
  mma_delay(10);
	MMA8451_writebyte(MMA8451_REG_CTRL_REG1,0x01); //����ģʽ,800H
	mma_delay(10);
	MMA8451_writebyte(MMA8451_XYZ_DATA_CFG,0x00); //12λAD X/4096=��
	mma_delay(10);
	MMA8451_writebyte(MMA8451_HP_FILTER_CUTOFF,0x10); //��ͨ�˲�
}



  		
  
