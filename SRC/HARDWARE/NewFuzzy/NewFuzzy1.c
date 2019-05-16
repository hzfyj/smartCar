#include "NewFuzzy1.h"

/*模糊PID*/
float Temp_Kp, Temp_Ki;
//////////////FUZZY_speed????/////////////////////
//int pff[5]={0,200,300,400,500};
//int pff[5]={0,100,150,250,300};
//int pff[5]={0,150,200,350,500};//11.35
float Speed_Fuzzy(float P,float D)                      //电机模糊
{
/*输入量P语言值特征点*/
float PFF[7]={-250,-150,-50,0,50,150,250};
/*输入量D语言值特征点*/
float DFF[5]={-50,-30,0,30,50};
/*输出量U语言值特征点(根据赛道类型选择不同的输出值)*/
float UFF[7]={0,4,8,12,17,22,30};

int rule[7][5]={

//  -2  -1  0   1   2 ec    e
  { 0,  0,  0,  0,  0}, //  -3
  { 0,  0,  0,  0,  0}, //  -2
  { 0,  0,  0,  0,  0}, //  -1
  { 1,  2,  6,  5,  3}, //   0
  { 1,  2,  5,  4,  2}, //   1
  { 1,  2,  4 , 2,  1}, //  2
  { 1,  3,  2,  1,  0}  //   3

 };

float U=0;  /*偏差,偏差微分以及输出值的精确量*/
float PF[2]={0},DF[2]={0},UF[4]={0};
 /*偏差,偏差微分以及输出值的隶属度*/
int Pn=0,Dn=0,Un[4]={0};
float t1=0,t2=0,t3=0,t4=0,temp1=0,temp2=0;
/*隶属度的确定*/
/*根据PD的指定语言值获得有效隶属度*/
 if(P>PFF[0] && P<PFF[6])
{
 if(P<=PFF[1])
 {
  Pn=-2;
  PF[0]=(PFF[1]-P)/(PFF[1]-PFF[0]);
 }
 else if(P<=PFF[2])
 {
  Pn=-1;
  PF[0]=(PFF[2]-P)/(PFF[2]-PFF[1]);
 }
 else if(P<=PFF[3])
 {
  Pn=0;
  PF[0]=(PFF[3]-P)/(PFF[3]-PFF[2]);
 }
 else if(P<=PFF[4])
 {
  Pn=1;
  PF[0]=(PFF[4]-P)/(PFF[4]-PFF[3]);
 }
 else if(P<=PFF[5])
 {
  Pn=2;
  PF[0]=(PFF[5]-P)/(PFF[5]-PFF[4]);
 }
 else if(P<=PFF[6])
 {
  Pn=3;
  PF[0]=(PFF[6]-P)/(PFF[6]-PFF[5]);
 }
}

 else if(P<=PFF[0])
 {
  Pn=-2;
  PF[0]=1;
 }
 else if(P>=PFF[6])
 {
  Pn=3;
  PF[0]=0;
 }

PF[1]=1-PF[0];


//判断D的隶属度
 if(D>DFF[0]&&D<DFF[4])
 {
  if(D<=DFF[1])
  {
   Dn=-2;
   DF[0]=(DFF[1]-D)/(DFF[1]-DFF[0]);
  }
 else if(D<=DFF[2])
 {
  Dn=-1;
  DF[0]=(DFF[2]-D)/(DFF[2]-DFF[1]);
  }
 else if(D<=DFF[3])
 {
  Dn=0;
  DF[0]=(DFF[3]-D)/(DFF[3]-DFF[2]);
  }
 else if(D<=DFF[4])
 {
  Dn=1;
  DF[0]=(DFF[4]-D)/(DFF[4]-DFF[3]);
 }
 }
 //不在给定的区间内
 else if (D<=DFF[0])
 {
  Dn=-2;
  DF[0]=1;
 }
 else if(D>=DFF[4])
 {
  Dn=1;
  DF[0]=0;
 }

DF[1]=1-DF[0];

 /*使用误差范围优化后的规则表rule[7][7]*/
 /*输出值使用13个隶属函数,中心值由UFF[7]指定*/
 /*一般都是四个规则有效*/

//由于规则都是紧紧挨着的
Un[0]=rule[Pn-1+3][Dn-1+3];
Un[1]=rule[Pn+3][Dn-1+3];
Un[2]=rule[Pn-1+3][Dn+3];
Un[3]=rule[Pn+3][Dn+3];


//获得应用单值模糊化获得对应规则的隶属函数
 if(PF[0]<=DF[0])    //求小 （求U的隶属度）
  UF[0]=PF[0];
 else
  UF[0]=DF[0];
 if(PF[1]<=DF[0])
  UF[1]=PF[1];
 else
  UF[1]=DF[0];
 if(PF[0]<=DF[1])
  UF[2]=PF[0];
 else
  UF[2]=DF[1];
 if(PF[1]<=DF[1])
  UF[3]=PF[1];
 else
  UF[3]=DF[1];
/*同隶属函数输出语言值求大*/
 if(Un[0]==Un[1])      //对相等的隶属值的隶属度进行处理
 {
  if(UF[0]>UF[1])
  UF[1]=0;
  else
  UF[0]=0;
 }
 if(Un[0]==Un[2])
 {
  if(UF[0]>UF[2])
  UF[2]=0;
  else
  UF[0]=0;
 }
 if(Un[0]==Un[3])
 {
  if(UF[0]>UF[3])
  UF[3]=0;
  else
  UF[0]=0;
 }
 if(Un[1]==Un[2])
 {
  if(UF[1]>UF[2])
  UF[2]=0;
  else
  UF[1]=0;
 }
 if(Un[1]==Un[3])
 {
  if(UF[1]>UF[3])
  UF[3]=0;
  else
  UF[1]=0;
 }
 if(Un[2]==Un[3])	
 {
  if(UF[2]>UF[3])
  UF[3]=0;
  else
  UF[2]=0;
 }

 t1=UF[0]*UFF[Un[0]];
 t2=UF[1]*UFF[Un[1]];
 t3=UF[2]*UFF[Un[2]];
 t4=UF[3]*UFF[Un[3]];
 temp1=t1+t2+t3+t4;
 temp2=UF[0]+UF[1]+UF[2]+UF[3];//模糊量输出
 U=temp1/temp2;
 return U;
}






/**************PID*****************/
int Moto_Err = 0, Moto_Last_Err = 0;
float Moto_kP = 0.0, Moto_kI = 0.0;
int Serov_Err = 0, Serov_Last_Err = 0;
float Serov_kP = 0.0,Serov_kD = 0.0;
/*************电机*****************/
int Moto_Duty = 0;
//uint16_t Moto_Aim = 0;
//uint16_t Moto_First = 0;
//byte First_Dr_Flag = 0;

//uint16_t Moto_Kp = 0, Moto_Ki = 0;
//uint16_t kong;
//uint16_t SDrFtm = 0, CurveFtm = 0,LDrFtm = 0,SSFtm = 0,BSFtm = 0,CirqueFtm = 0;
/*************舵机*****************/

//uint16_t SS_Kp = 0,SS_Kd = 0;
//uint16_t BS_Kp = 0,BS_Kd = 0;
//uint16_t Cirque_Kp = 0, Cirque_Kd = 0;
//uint16_t SDr_Kp = 0, SDr_Kd = 0, LDr_Kp = 0,LDr_Kd = 0;
//uint16_t LCurve_Kp = 0, RCurve_Kp = 0;
//uint16_t LCurve_Kd = 0, RCurve_Kd = 0;
//byte Turn_Line = 0;
//byte SDr_Line = 0,LDr_Line = 0, Curve_Line = 0, SS_Line = 0,BS_Line = 0,Cirque_Line = 0;

/*
 * 函数部分
 */
/*RIT*/

/*PID 电机/舵机*/
/*模糊PID 电机*/

//uint16_t Position_PD (uint16_t Serov_Pwm, float kP, float kD, int Encoder, int Target)
//{
//	Serov_Last_Err = Serov_Err;
//	Serov_Err = Target - Encoder;
//	Serov_Pwm = SEROV_MID + kP * Serov_Err + kD * (Serov_Err - Serov_Last_Err);
//	return Serov_Pwm;
//}
uint8_t longCnt=0;
//extern uint16_t vLong;
//extern uint8_t runState;
//int Incrmental_PI(int Moto_Pwm, float kP, float kI, int Encoder, int Target)
//{
//	Moto_Last_Err = Moto_Err;
//	Moto_Err = Target - Encoder;
//	if(Target==vLong*4)
//	{
//		longCnt++;
//	}
//	else if(longCnt<5)
//	{
//		Moto_Last_Err = 0;
//		Moto_Err = Target - Encoder;
//		longCnt=0;
//	}
//	else 
//	{
//		longCnt=0;
//	}
//	Temp_Kp=kP;
//	Temp_Ki= kI;
//	Moto_Pwm += (int)((Temp_Kp)*(Moto_Err-Moto_Last_Err)*Speed_Fuzzy(Moto_Err,Moto_Last_Err)+(Temp_Ki) * Moto_Err);
//	return Moto_Pwm;
//}	

//void Get_Turn_Line(void)
//{
//	if(BMQ_L_value < 160) Turn_Line = Turn_Min_Line + 3;
//	else if(BMQ_L_value < 180) Turn_Line = Turn_Min_Line + 4;
//	else if(BMQ_L_value < 200) Turn_Line = Turn_Min_Line + 5;
//	else if(BMQ_L_value < 220) Turn_Line = Turn_Min_Line + 6;
//	else if(BMQ_L_value < 240) Turn_Line = Turn_Min_Line + 6;
//	else if(BMQ_L_value < 260) Turn_Line = Turn_Min_Line + 7; //10
//	else if(BMQ_L_value < 280) Turn_Line = Turn_Min_Line + 8;
//	else if(BMQ_L_value < 300) Turn_Line = Turn_Min_Line + 9; //14
//	else if(BMQ_L_value < 320) Turn_Line = Turn_Min_Line + 9; //14
//	else if(BMQ_L_value < 340) Turn_Line = Turn_Min_Line + 9;
//	else if(BMQ_L_value < 360) Turn_Line = Turn_Min_Line + 10;
//	else if(BMQ_L_value < 380) Turn_Line = Turn_Min_Line + 10;
//	else if(BMQ_L_value < 400) Turn_Line = Turn_Min_Line + 11;
//	else if(BMQ_L_value < 420) Turn_Line = Turn_Min_Line + 12;
//	else if(BMQ_L_value < 440) Turn_Line = Turn_Min_Line + 13;
//	else if(BMQ_L_value < 460) Turn_Line = Turn_Min_Line + 14;
//	else if(BMQ_L_value < 480) Turn_Line = Turn_Min_Line + 15;
//	else if(BMQ_L_value < 500) Turn_Line = Turn_Min_Line + 16;
//	else if(BMQ_L_value < 520) Turn_Line = Turn_Min_Line + 17;
//	else if(BMQ_L_value < 540) Turn_Line = Turn_Min_Line + 18;
//	else if(BMQ_L_value < 560) Turn_Line = Turn_Min_Line + 19;
//	else if(BMQ_L_value < 580) Turn_Line = Turn_Min_Line + 20;
//	else if(BMQ_L_value < 600) Turn_Line = Turn_Min_Line + 21;
//	else if(BMQ_L_value < 620) Turn_Line = Turn_Min_Line + 22;
//	else if(BMQ_L_value < 640) Turn_Line = Turn_Min_Line + 23;
//	else if(BMQ_L_value < 660) Turn_Line = Turn_Min_Line + 24;
//	else if(BMQ_L_value < 680) Turn_Line = Turn_Min_Line + 25;
//	else if(BMQ_L_value < 700) Turn_Line = Turn_Min_Line + 26;
//	else if(BMQ_L_value < 720) Turn_Line = Turn_Min_Line + 27;
//	else if(BMQ_L_value < 740) Turn_Line = Turn_Min_Line + 28;
//	else if(BMQ_L_value < 760) Turn_Line = Turn_Min_Line + 29;
//	else if(BMQ_L_value < 780) Turn_Line = Turn_Min_Line + 30;
//	else Turn_Line = Turn_Min_Line   + 31;
//	
//	if(Turn_Line >= Last_Line) Turn_Line = Last_Line;
//}

//void Contral_Paramenter(void)
//{
//		if (Element == SDr)
//		{
//				if(First_Dr_Flag == 1) First_Dr_Flag = 2;
//				Mid_Line = LCenter[SDr_Line];
//				Serov_kP = SDr_Kp/10.0;
//				Serov_kD = SDr_Kd/10.0;
//			
//				Moto_Aim = SDrFtm;
//		}
//		else if (Element == LDr)
//		{		
//				if(First_Dr_Flag == 1) First_Dr_Flag = 2;
//				Mid_Line = LCenter[LDr_Line];
//				Serov_kP = LDr_Kp/10.0;
//				Serov_kD = LDr_Kd/10.0;
//			
//				Moto_Aim = LDrFtm;
//		}
//		else if(Element == Small_S)
//		{		
//				if(First_Dr_Flag == 1) First_Dr_Flag = 2;
//				Mid_Line = LCenter[SS_Line];
//				Moto_Aim = SSFtm;
//				Serov_kP = SS_Kp/10.0;
//				Serov_kD = SS_Kd/10.0;
//			
//				Moto_Aim = SSFtm;
//		}
//		else if(Element == Big_S)
//		{
//				if(First_Dr_Flag == 1) First_Dr_Flag = 2;
//				Mid_Line = LCenter[BS_Line];
//				Serov_kP = BS_Kp/10.0;
//				Serov_kD = BS_Kd/10.0;
//			
//				Moto_Aim = BSFtm;
//		}
//		else if (Element == Curve_P)
//		{
//				if(First_Dr_Flag == 0) First_Dr_Flag = 1;
//				Mid_Line = LCenter[Curve_Line];

//				if (LCenter[Curve_In_Line] - LCenter[0] > 0) //L
//				{
//						Serov_kP = LCurve_Kp/10.0;
//						Serov_kD = LCurve_Kd/10.0;
//				}
//				else                                         //R
//				{
//						Serov_kP = RCurve_Kp/10.0;
//						Serov_kD = RCurve_Kd/10.0;
//				}
//					
//				Moto_Aim = CurveFtm;
//		}
//		else if(Element == Series_Curve_Gental)
//		{		
//				if(First_Dr_Flag == 0) First_Dr_Flag = 1;
//				Mid_Line = LCenter[Curve_Line];

//				if (LCenter[Curve_In_Line] - LCenter[0] > 0) //L
//				{
//						Serov_kP = (LCurve_Kp/10.0) - 4;
//						Serov_kD = LCurve_Kd/10.0;
//				}
//				else                                         //R
//				{
//						Serov_kP = (RCurve_Kp/10.0) - 4;
//						Serov_kD = RCurve_Kd/10.0;
//				}
//					
//				Moto_Aim = CurveFtm;
//		}			
//		else if(Element == Series_Curve_Sharp)
//		{
//				if(First_Dr_Flag == 0) First_Dr_Flag = 1;
//				Mid_Line = LCenter[Curve_Line];

//				if (LCenter[Curve_In_Line] - LCenter[0] > 0) //L
//				{
//						Serov_kP = (LCurve_Kp/10.0) + 8;
//						Serov_kD = LCurve_Kd/10.0;
//				}
//				else                                         //R
//				{
//						Serov_kP = (RCurve_Kp/10.0) + 8;
//						Serov_kD = RCurve_Kd/10.0;
//				}
//					
//				Moto_Aim = CurveFtm;
//		}
//		else if(Element == Cirque)
//		{
//				Mid_Line = LCenter[Cirque_Line];

//				if (LCenter[Curve_In_Line] - LCenter[0] > 0) //L
//				{
//						Serov_kP = Cirque_Kp/10.0;
//						Serov_kD = Cirque_Kp/10.0;
//				}
//				else                                         //R
//				{
//						Serov_kP = Cirque_Kp/10.0;
//						Serov_kD = Cirque_Kp/10.0;
//				}
//					
//				Moto_Aim = CirqueFtm;
//		}
//}

///* 电机模糊PID */
//void RIT_IRQHandler(void)
//{
//	/* Clearn interrupt */
//	Chip_RIT_ClearInt(LPC_RITIMER);//清除定时中断标志位
//		
//	PWM_Cap();//获得编码器值
//	
//	Get_Turn_Line();
//	Mid_Line = LCenter[Turn_Line];
//	
//	Moto_kP = Moto_Kp/10.0f;
//	Moto_kI = Moto_Ki/10.0f;
//	
//	
//	if(Start_Car_Flag == 3) Moto_Duty = 0;
//	if(First_Dr_Flag != 2 || Field_Cnt < 100) 
//	{
//		Moto_Duty = Moto_First * 10;
//	}
//	
//	if(Moto_Duty <= -6000) Moto_Duty = -6000;
//	if(Moto_Duty >= 6000) Moto_Duty = 6000;
//	
//	Motor_Power_switch(Moto_Duty,0);
//}
