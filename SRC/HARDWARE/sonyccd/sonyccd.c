#include "sonyccd.h"
#include "headfile.h"

//摄像头采集行数


uint8_t DMABuffer[700]; 
uint8_t P_Pixels[CCD_IMAGE_H][CCD_IMAGE_W];
uint16_t Sony_HREFCnt,RealCnt;
uint8_t CCD_flag;
uint8_t YuZhi,Sony_Rownum; 
 uint8_t YuzhiAdd1=0;
int CountChang=0;
extern uint8_t YUzhiAdd,ZHiJieZhiH;
uint16_t P_Spot_H [70] = 
{
	
    90 ,92 ,95 ,97 ,100,102,105,107,110,112,
    115,117,120,122,125,128,131,133,136,138,
    141,143,146,148,151,153,156,158,161,163,
    165,167,170,172,174,176,178,181,183,185,
    187,189,192,194,196,198,200,203,205,207,
    209,211,214,216,218,220,222,225,227,229,
    231,233,236,238,240,242,244,247,249,251

};

uint8_t YuzhiFinal[200];  
//偏右  -
uint16_t P_Spot_W [200] = {


//82,85,88,91,94,96,99,102,104,107,110,
//112,115,118,120,122,125,128,131,134,137,
//140,143,146,149,152,155,158,161,164,167,
//170,173,176,179,182,185,188,191,194,197,
//200,203,206,209,212,215,218,221,224,227,
//230,233,236,239,242,245,248,251,254,257,
//260,263,266,269,272,275,278,281,284,287,
//290,293,296,299,302,305,308,311,314,317,
//320,323,326,329,332,335,338,341,344,347,
//350,353,356,359,362,365,368,371,374,377,
//380,383,386,389,392,395,398,401,404,407,
//410,413,416,419,422,425,428,431,434,437,
//440,443,446,449,452,455,458,461,464,467,
//470,473,476,479,482,485,488,491,494,497,
//500,503,506,509,512,515,518,521,524,527,
//530,533,536,539,542,545,548,551,554,557,
//560,563,566,569,572,575,578,581,584,587,
//590,593,596,599,602,605,608,610,613,616,
//618,621,624,626,629,632,634,637,640,642,
//645,648,650,653,656,659,662,665,668,


85,88,91,94,97,99,102,105,107,110,113,
115,118,121,123,125,128,131,134,137,140,
143,146,149,152,155,158,161,164,167,170,
173,176,179,182,185,188,191,194,197,200,
203,206,209,212,215,218,221,224,227,230,
233,236,239,242,245,248,251,254,257,260,
263,266,269,272,275,278,281,284,287,290,
293,296,299,302,305,308,311,314,317,320,
323,326,329,332,335,338,341,344,347,350,
353,356,359,362,365,368,371,374,377,380,
383,386,389,392,395,398,401,404,407,410,
413,416,419,422,425,428,431,434,437,440,
443,446,449,452,455,458,461,464,467,470,
473,476,479,482,485,488,491,494,497,500,
503,506,509,512,515,518,521,524,527,530,
533,536,539,542,545,548,551,554,557,560,
563,566,569,572,575,578,581,584,587,590,
593,596,599,602,605,608,611,613,616,619,
621,624,627,629,632,635,637,640,643,645,
648,651,653,656,659,662,665,668,671,

};

uint16_t *p_H=P_Spot_H;
uint8_t *p_DMA=DMABuffer;
uint8_t *PSonyCCD_Image=&P_Pixels[0][0];
void SonyCCD_Init(void)
{
	
	uint32_t i = 0;
	//有效行
	gpio_init(B0,GPI,0);	//数据0
	gpio_init(B1,GPI,0);	//数据1
	gpio_init(B2,GPI,0);
	gpio_init(B3,GPI,0);
	gpio_init(B4,GPI,0);
	gpio_init(B5,GPI,0);
	gpio_init(B6,GPI,0);
	gpio_init(B7,GPI,0);

	//行中断，场中断都被打开，场中断一直不关闭，行中断在一场结束后关闭
	//行中断 HREF
	port_init (sonyccd_HREF_Port, IRQ_RISING | PF | ALT1 | PULLDOWN );//行中断
	//gpio_init(sonyccd_VSYNC_Port,GPI,0);	//场中断
	port_init (sonyccd_VSYNC_Port, IRQ_EITHER | PF | ALT1 | PULLDOWN );//场中断
	
	NVIC_EnableIRQ(PORTA_IRQn);//场中断打开
	NVIC_EnableIRQ(PORTD_IRQn);//行中断
	
	
dma_portx2buff_init_new(sonyccd_DMA_CH, (void *)&sonyccd_DATA_PORT, (void *)sonyccd_DATA_BIN, DMA_BYTE1, sonyccd_DATA_NUM, DADDR_RECOVER);

NVIC_EnableIRQ(DMA0_IRQn); //打开DMA中断?

}


void PORTA_IRQHandler(void)//场中断
{	
	CCD_flag=0;

		NVIC_EnableIRQ(PORTD_IRQn);//开行中断
		  //计数清0
		p_H=P_Spot_H;//选行
	 PSonyCCD_Image=&P_Pixels[0][0];//每场开始从头开始存图像数组

Sony_Rownum=0;
	Sony_HREFCnt = 0;	
		PORTA_FLAG_CLR(sonyccd_VSYNC_Port);	//清楚中断标志位
}

void PORTD_IRQHandler(void)///行中断
{
uint8_t i;
	if(Sony_HREFCnt==*p_H)
	{
		DMA0->TCD[DMA_CH0].DADDR = (uint32_t)(DMABuffer);
	 	DMA_IRQ_EN(sonyccd_DMA_CH);
		DMA_EN(sonyccd_DMA_CH);
	  p_H++;
  	Sony_Rownum++;
		if(Sony_Rownum==70)
		{Sony_Rownum=0;}

if(Sony_Rownum<=cutline) //在上一场截断行以下，进行阈值变化
{
	if(crossflag==1)
	{
		for(i=0;i<60;i++)
{YuzhiFinal[i]=My_yuzhi[Sony_Rownum]+yuzhi-13;}	
for(i=60;i<140;i++)
{YuzhiFinal[i]=My_yuzhi[Sony_Rownum]+yuzhi-5;}   
for(i=140;i<200;i++)
{YuzhiFinal[i]=My_yuzhi[Sony_Rownum]+yuzhi-10;} 
	}
	else if((huandaochu1==1||huandaochu==1)&&huandaoyouflag3==1)
	{
for(i=0;i<60;i++)
{YuzhiFinal[i]=My_yuzhi[Sony_Rownum]+yuzhi-10;}	
for(i=60;i<140;i++)
{YuzhiFinal[i]=My_yuzhi[Sony_Rownum]+yuzhi;}   
for(i=140;i<200;i++)
{YuzhiFinal[i]=My_yuzhi[Sony_Rownum]+yuzhi-10;} 
	}
		else if((huandaochu1==1||huandaochu==1)&&huandaozuoflag3==1)
	{
for(i=0;i<60;i++)
{YuzhiFinal[i]=My_yuzhi[Sony_Rownum]+yuzhi-10;}	
for(i=60;i<140;i++)
{YuzhiFinal[i]=My_yuzhi[Sony_Rownum]+yuzhi;}   
for(i=140;i<200;i++)
{YuzhiFinal[i]=My_yuzhi[Sony_Rownum]+yuzhi-10;} 
	}
  else if(huandaowanflag==0&&huandaoyouflag3==1)
	{
		for(i=0;i<40;i++)
{YuzhiFinal[i]=My_yuzhi[Sony_Rownum]+yuzhi-12;}	
for(i=40;i<160;i++)
{YuzhiFinal[i]=My_yuzhi[Sony_Rownum]+yuzhi;}   
for(i=160;i<200;i++)
{YuzhiFinal[i]=My_yuzhi[Sony_Rownum]+yuzhi-4;} 
}
	  else if(huandaowanflag==0&&huandaozuoflag3==1)
	{
		for(i=0;i<40;i++)
{YuzhiFinal[i]=My_yuzhi[Sony_Rownum]+yuzhi-4;}	
for(i=40;i<160;i++)
{YuzhiFinal[i]=My_yuzhi[Sony_Rownum]+yuzhi;}   
for(i=160;i<200;i++)
{YuzhiFinal[i]=My_yuzhi[Sony_Rownum]+yuzhi-12;} 
	}


	else
	{
for(i=0;i<40;i++)
{YuzhiFinal[i]=My_yuzhi[Sony_Rownum]+yuzhi-4 ;}	
for(i=40;i<160;i++)
{YuzhiFinal[i]=My_yuzhi[Sony_Rownum]+yuzhi;}   
for(i=160;i<200;i++)
{YuzhiFinal[i]=My_yuzhi[Sony_Rownum]+yuzhi-4;} 
}
}

else
{
for(i=0;i<40;i++)
{YuzhiFinal[i]=My_yuzhi[Sony_Rownum]+yuzhi;}	
for(i=40;i<160;i++)
{YuzhiFinal[i]=My_yuzhi[Sony_Rownum]+yuzhi;}   
for(i=160;i<200;i++)
{YuzhiFinal[i]=My_yuzhi[Sony_Rownum]+yuzhi;} 	
}
		


          
	}
			if(Sony_HREFCnt>=P_Spot_H[69])
	{
		NVIC_DisableIRQ(PORTD_IRQn);
		CCD_flag=1;//关闭行中断
	}
	Sony_HREFCnt++;//行中断计数	
		PORTD_FLAG_CLR(sonyccd_HREF_Port);	//清楚中断标志位
}

void DMA0_IRQHandler(void)//DMA中断（DMA中断后）自动触发
{
	uint8_t i;
	
uint16_t *p_W=P_Spot_W;//???
uint8_t *PDMABuffer=DMABuffer;//700的一行数组
uint8_t   *PMyuzhi=YuzhiFinal;
if(crossflag==1)
{
	YuzhiAdd1=13;
}
else if(huandaoflag==1&&huandaowanflag==0)
{
	YuzhiAdd1=8;
}
else if(huandaoflag==1&&huandaowanflag!=0&&huandaochu1==1)
{
	YuzhiAdd1=0;
}
else
{
	YuzhiAdd1=0;
}
	for(i=0;i<200;i++)
		{

			if(*(PDMABuffer+*p_W)>(*PMyuzhi-YuzhiAdd1))
			
	    *PSonyCCD_Image=1;
			else 
	  	*PSonyCCD_Image=0;

	
      p_W++;
			PMyuzhi++;
    PSonyCCD_Image++;	//70*200的整场数组，顺序往下存储
		}
	DMA_IRQ_CLEAN(DMA_CH0);
}
	


void New_OLED_DISAPLAY()
{
uint16_t OLED_Spot_H[64]= {
	0,1,2,3,4,6,7,8,9,
	10,11,12,13,15,16,17,18,
	19,20,21,22,24,25,26,27,
	28,29,30,31,33,34,35,36,
  37,38,39,40,42,43,44,45,
  46,47,48,49,51,52,53,54,	
	55,56,57,58,59,60,61,62,
	63,64,65,66,67,68,69,
},OLED_Spot_W[128] = {
	0,1,2,4,6,8,10,12,14,16,18,19,20,22,24,26,28,29,30,
	32,33,34,36,38,40,42,43,44,46,48,50,51,52,54,55,56,58,60,61,62,
	64,65,66,68,70,71,72,74,76,78,79,80,82,84,86,87,88,90,92,93,94,
	96,98,100,101,102,103,104,106,108,109,110,112,114,115,116,118,120,122,124,125,126,
	128,129,130,132,133,134,136,137,138,140,142,144,146,148,150,152,154,156,157,158,
	160,161,162,163,164,166,168,170,171,172,174,176,177,178,180,181,182,184,186,188,190,
	192,194,196,198,199,
};
uint16_t *pOLED_Spot_H,*pOLED_Spot_W;
		uint16_t high,wide;
uint8_t Xiangsu,Xiangsu_8;
uint8_t (*pCCD_Image)[CCD_IMAGE_W];
	pCCD_Image=P_Pixels;
pOLED_Spot_H=OLED_Spot_H;
pOLED_Spot_W=OLED_Spot_W;

//MidPoint_OLED();
for(high=0;high<8;high++)	//??
	{
		OLED_Set_XY(0,high);
	for(wide=0;wide<128;wide++)//????128*8
			{
				Xiangsu=0;
for(Xiangsu_8=0;Xiangsu_8<8;Xiangsu_8++)//???8???
		{
				 Xiangsu>>=1;
			
						if(*(*(pCCD_Image+CCD_IMAGE_H-*(pOLED_Spot_H+Xiangsu_8+high*8))+CCD_IMAGE_W-*(pOLED_Spot_W+wide))==0) //????
					 {
							Xiangsu=Xiangsu|0x00;
					
					 }
					 else
					 {
		 			 	 	Xiangsu=Xiangsu|0x80;
					 }
		}
		OLED_WrDat(Xiangsu);
	
	}
}
	
}
void oled_Display(void)
{
	uint8_t i,j,k;
	uint8_t temp;				//temp存储从上到下8个像素点的图像
	//指针赋初值
//	p_dis_H = &OLED_Spot_H[63];
//	p_dis_W = &OLED_Spot_W[127];
	
	//从上往下，从左往右显示
	for(i=0;i<8;i++)
	{
		OLED_Set_XY(0,i);				//设置坐标位置
		for(j=0;j<100;j++)
		{
			for(k=0;k<8;k++)
			{
				temp >>= 1;		//数据左移1位		末位清空
				if(P_Pixels[63-(i*8+k)][199-j*2] == 1)		//判断该点的数据是否为1
				{
					temp |= 0x80;		//最高位1
				}
			}
			//显示图像
			OLED_WrDat(temp);
		}
	}
}