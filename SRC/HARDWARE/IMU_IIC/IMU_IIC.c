#include "IMU_IIC.h"
#include "gpio.h"
#include "headfile.h"

//�˴��������ص�ͷ�ļ�




//SA0����ӵ�

//�ڲ����ݶ���
uint8_t IIC_ad_main; //�����ӵ�ַ	    
uint8_t IIC_ad_sub;  //�����ӵ�ַ	   
uint8_t *IIC_buf;    //����|�������ݻ�����	    
uint8_t IIC_num;     //����|�������ݸ���	     

#define ack 1      //��Ӧ��
#define no_ack 0   //��Ӧ��	 


void nops()		 
{
    uint8_t k=13;	 
    while(--k);
}

void IMU_IIC_Init()
{
	
	gpio_init(C10,GPO,1);//k60��ֲ��k66�����ų�ʼ��
	
//  GPIO_InitTypeDef GPIO_InitStruct1;//
//	GPIO_InitStruct1.GPIO_Pin = IIC_SCL_PIN;                 
//	GPIO_InitStruct1.GPIO_InitState = Bit_SET;//
//	GPIO_InitStruct1.GPIO_IRQMode = GPIO_IT_DISABLE;//��
//	GPIO_InitStruct1.GPIO_Mode = GPIO_Mode_OPP;//��
//	GPIO_InitStruct1.GPIOx = IIC_SCL_PORT;
//	GPIO_Init(&GPIO_InitStruct1);
		gpio_init(C11,GPO,1);

//	GPIO_InitStruct1.GPIO_Pin = IIC_SDA_PIN;                 
//	GPIO_InitStruct1.GPIO_InitState = Bit_SET;
//	GPIO_InitStruct1.GPIO_IRQMode = GPIO_IT_DISABLE;
//	GPIO_InitStruct1.GPIO_Mode = GPIO_Mode_OPP;
//	GPIO_InitStruct1.GPIOx = IIC_SDA_PORT;
//	GPIO_Init(&GPIO_InitStruct1);
}
void IIC_start(void)
{
	SCL=0;	//ʱ���ߵ�
	SDA_OUT = 1;//�����ߵ�
	nops();
	SCL = 1;//ʱ���߸�
	nops();	
	SDA_OUT = 0;//�����ߴӸ����䵽��
	nops();	
	SCL = 0;//ʱ���ߵ�
}
//************************************************
//��ֹͣλ SDA=0->1
void IIC_stop(void)
{
	SCL = 0;//ʱ���ߵ�
	SDA_OUT = 0;//�����ߵ�
	nops();
	SCL = 1;//ʱ���߸�
	nops();	
	SDA_OUT = 1;//������������
	nops();
	SCL = 0;//ʱ���ߵ�
}
//************************************************
//��Ӧ��(����ack:SDA=0��no_ack:SDA=0)
void IIC_ack_main(uint8_t ack_main)
{
	SCL = 0;	
	if(ack_main)
	{
	  SDA_OUT = 0; //ack��Ӧ��
	}
	else 
	{
	  SDA_OUT = 1; //no_ack����Ӧ��
	}
	nops();	
	SCL = 1;
	nops();	
	SCL = 0;
}
//*************************************************
//�ֽڷ��ͳ���
//����c(����������Ҳ���ǵ�ַ)���������մ�Ӧ��
//�����Ǵ�Ӧ��λ
void send_byte(uint8_t c)
{
	uint8_t i;
	for(i=0;i<8;i++)
	{
		SCL = 0;
		nops();
		if((c<<i) & 0x80)
		{
		  SDA_OUT = 1; //�жϷ���λ
		}
		else 
		{
		  SDA_OUT = 0;
		}
		nops();
		SCL = 1;
		nops();	
		SCL = 0;
	}
	nops();//�ھŸ�����
	SDA_OUT = 1; //������8bit���ͷ�����׼������Ӧ��λ
	nops();
	SCL = 1;	
	nops();//sda�����ݼ��Ǵ�Ӧ��λ              
	SCL = 0; //�����Ǵ�Ӧ��λ|��Ҫ���ƺ�ʱ��
}
//**************************************************
//�ֽڽ��ճ���
//�����������������ݣ��˳���Ӧ���|��Ӧ����|IIC_ack_main()ʹ��
//return: uchar��1�ֽ�
uint8_t read_byte(void)
{
	uint8_t i;
	uint8_t c;
	c=0;
	SCL = 0;
	nops();
	SDA_OUT = 1; //��������Ϊ���뷽ʽ
	nops();
	//	//����Ϊ����
	IIC_SDA_PORT ->PDDR &= ~(1<<IIC_SDA_PIN);	//����
	//������������
	IIC_SDA_PORTx->PCR[IIC_SDA_PIN]|= PORT_PCR_PE_MASK; 	//����������ʹ��
	IIC_SDA_PORTx->PCR[IIC_SDA_PIN]|= PORT_PCR_PS_MASK;
	for(i=0;i<8;i++)
	{
		nops();
		SCL = 0; //��ʱ����Ϊ�ͣ�׼����������λ
		nops();
		SCL = 1; //��ʱ����Ϊ�ߣ�ʹ��������������Ч
		nops();
		c<<=1;
		if(SDA_IN == 1)
		  c+=1; //������λ�������յ����ݴ�c
	}
	SCL = 0;	
	nops();
	//��������Ϊ���
	IIC_SDA_PORT ->PDDR |= (1<<IIC_SDA_PIN);//���
	IIC_SDA_PORTx->PCR[IIC_SDA_PIN]&=~(PORT_PCR_PE_MASK); 
	IIC_SDA_PORT ->PDOR |= (1<<IIC_SDA_PIN);
	IIC_SDA_PORTx->PCR[IIC_SDA_PIN]&= ~PORT_PCR_ODE_MASK;
	return c;
}

/*******************************


							����û�õ�

**************************************/

void write_reg(uint8_t slaveaddress, uint8_t address, uint8_t thedata)
{
	IIC_start();		//����
	send_byte( (slaveaddress<<1) | 0x00);	//д���豸ID��д�ź�
	send_byte(address);	//X��ַ
	send_byte(thedata);	//д���豸ID������
	IIC_stop();
}

uint8_t read_reg(uint8_t slaveaddress, uint8_t address)
{
	uint8_t ret;
	IIC_start();		//����
	send_byte((slaveaddress<<1) | 0x00);	//д���豸ID��д�ź�
	send_byte(address);	//X��ַ
	IIC_start();		//���·��Ϳ�ʼ
	send_byte((slaveaddress<<1) | 0x01);	//д���豸ID������
	ret = read_byte();	//��ȡһ�ֽ�
	IIC_stop();
	return ret;
}


//***************************************************
//�����ӵ�ַ�������͵��ֽ�����
void send_to_byte(uint8_t ad_main,uint8_t c)
{
	IIC_start();
	send_byte(ad_main); //����������ַ
	send_byte(c); //��������c
	IIC_stop();
}
//***************************************************
//�����ӵ�ַ�������Ͷ��ֽ�����
void send_to_nbyte(uint8_t ad_main,uint8_t ad_sub,uint8_t *buf,uint8_t num)
{
	uint8_t i;
	IIC_start();
	send_byte(ad_main); //����������ַ
	send_byte(ad_sub); //���������ӵ�ַ
	for(i=0;i<num;i++)
	{
		send_byte(*buf); //��������*buf
		buf++;
	}
	IIC_stop();
}
//***************************************************
//�����ӵ�ַ���������ֽ�����
//function:������ַ���������ݴ��ڽ��ջ�������ǰ�ֽ�
void read_from_byte(uint8_t ad_main,uint8_t *buf)
{
	IIC_start();
	send_byte(ad_main); //����������ַ
	*buf=read_byte();
	IIC_ack_main(no_ack); //����Ӧ��<no_ack=0>
	IIC_stop();
}
//***************************************************
//�����ӵ�ַ����������ֽ�����
//function:
void read_from_nbyte(uint8_t ad_main,uint8_t ad_sub,uint8_t *buf,uint8_t num)
{
	uint8_t i;
	IIC_start();
	send_byte(ad_main);
	send_byte(ad_sub);
	for(i=0;i<num-1;i++)
	{
		*buf=read_byte();
		IIC_ack_main(ack); //��Ӧ��<ack=1>
		buf++;
	}
	*buf=read_byte();
	buf++; //����ָ����������壬Ŀ���ǲ�����bufָ����һ��ַ
	IIC_ack_main(no_ack); //����Ӧ��<no_ack=0>
	IIC_stop();
}
