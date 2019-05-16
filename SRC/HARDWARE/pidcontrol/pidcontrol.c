#include "data.h"
#include "pidcontrol.h"
#include "process.h"
#include "Fuzzy_control.h"
#include "NewFuzzy1.h"
 float motorp;
 float bianmap;
 float bianmai;
 float bianmad;
float motord=0; 
int pwm;
 int ZhanKongBi;
 int FTM_BiHuan;
 int Fuzzy_piancha,Fuzzy_lastpiancha;

 float CESHI_bianmai;
 float CESHI_bianmad;


struct PID
{
	int iError;
	int LastError;
	int PrevError;
	double Proportion;
	double Integral;
	double Derivative;
	int LastOutput;
};

struct PID MotorPID;


int Motor_PID(int SetPoint,int NextPoint)  //±àÂëÆ÷PID¹«Ê½
{

// int  BACK; 
//MotorPID.iError = SetPoint- NextPoint; //????
//	
// 	CESHI_bianmai = MyFuzzy1((int)(-MotorPID.iError), (int)(-(MotorPID.iError-MotorPID.LastError)),0);
////CESHI_bianmad=MyFuzzy1((int)(-MotorPID.iError), (int)(-(MotorPID.iError-MotorPID.LastError)),1);
//BACK =bianmap/20* (MotorPID.iError-MotorPID.LastError) 

//+ bianmai/20 * MotorPID.iError *CESHI_bianmai

//+ bianmad/20* (MotorPID.PrevError-2*MotorPID.LastError+MotorPID.iError); 

//MotorPID.PrevError = MotorPID.LastError;

//MotorPID.LastError = MotorPID.iError;
//return(BACK);	


	int  BACK; 
MotorPID.iError = SetPoint- NextPoint; //????
	
 	CESHI_bianmai = Speed_Fuzzy((int)(-MotorPID.iError), (int)(-(MotorPID.iError-MotorPID.LastError)))/10.0;//CESHI_bianmad=MyFuzzy1((int)(-MotorPID.iError), (int)(-(MotorPID.iError-MotorPID.LastError)),1);
BACK =bianmap/20* (MotorPID.iError-MotorPID.LastError)*CESHI_bianmai

+ bianmai/20 * MotorPID.iError 

+ bianmad/20* (MotorPID.PrevError-2*MotorPID.LastError+MotorPID.iError); 

MotorPID.PrevError = MotorPID.LastError;

MotorPID.LastError = MotorPID.iError;
return(BACK);	

}	





void protect()
{
  if(pwm<zuo)
	{
		pwm=zuo;
	}
	if(pwm>you)
	{
		pwm=you;
	}
}
 int erornow = 0,erorpast;
 int turnpidzuo()    
{
 erorpast=erornow;
	erornow=midleline-100;
	pwm=zhong-(double)((double)leftp/10)*erornow-(double)((double)leftd/10)*(erornow-erorpast);
	protect();
	return pwm;
}
int turnpidyou()  
{
	erorpast=erornow;
	erornow=midleline-100;
	pwm=zhong-(double)((double)rightp/10)*erornow-(double)((double)rightd/10)*(erornow-erorpast);
  protect();
	return pwm;
}
	
int longstraightpid()       
{
	erorpast=erornow;
	erornow=midleline-100;
	pwm=zhong-(double)((double)longstraightp/10)*erornow-(double)((double)longstraightd/10)*(erornow-erorpast);
  protect();
	return pwm;
}
int straightpid()       
{

	erorpast=erornow;
	erornow=midleline-100;
	pwm=zhong-(double)((double)straightp/10)*erornow-(double)((double)straightd/10)*(erornow-erorpast);
  protect();
	return pwm;
}
int huandaopid()  
{
	erorpast=erornow;
	erornow=midleline-100;
	pwm=zhong-(double)((double)huandaop/10)*erornow-(double)((double)huandaod/10)*(erornow-erorpast);
  protect();
	return pwm;
}
int smallspid()    
{
	erorpast=erornow;
	erornow=midleline-100;
	pwm=zhong-(double)(smallsp/10)*erornow-(double)((double)smallsd/10)*(erornow-erorpast);
  protect();
	return pwm;
}
int blockpid()    
{
	erorpast=erornow;
	erornow=midleline-100;
	pwm=zhong-(double)(70/10)*erornow-(double)(100/10)*(erornow-erorpast);
  protect();
	return pwm;
}

int lianwanyou()  
{
	
	erorpast=erornow;
	erornow=midleline-100;
	
	pwm=zhong-(double)((double)rightp/10*doub_temp)*erornow-(double)((double)rightd/10*doub_temp)*(erornow-erorpast);
  protect();
	return pwm;
}
 int lianwanzuo()    
{

  erorpast=erornow;
	erornow=midleline-100;
	
	pwm=zhong-(double)((double)leftp/10*doub_temp)*erornow-(double)((double)leftd/10*doub_temp)*(erornow-erorpast);
	protect();
	return pwm;
}

int bigspid()    
{
	erorpast=erornow;
	erornow=midleline-100;
	pwm=zhong-(double)((double)Bigsp/10)*erornow-(double)((double)Bigsd/10)*(erornow-erorpast);
  protect();
	return pwm;
}
